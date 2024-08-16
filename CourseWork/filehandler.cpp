#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <string.h>

#include "filehandler.hpp"

FileHandler::FileHandler(const char* fileName)
    : m_error{ false }
{
    size_t length = strlen(fileName) + 1;
    m_fileName = static_cast<char*>(std::malloc(length));

    if (m_fileName) {
        if (strcpy_s(m_fileName, length, fileName) != 0) {
            m_error = true;
            std::free(m_fileName);
            m_fileName = nullptr;
        }
    }
    else {
        m_error = true;
    }
}

FileHandler::~FileHandler()
{
    std::free(m_fileName);
}

std::string FileHandler::readFile() const
{
    std::ifstream iStream(m_fileName);

    if (!iStream) {
        return "";
    }

    std::stringstream sStream;
    sStream << iStream.rdbuf();
    std::string content(sStream.str());
    iStream.close();
    return content;
}

void FileHandler::writeFile(const std::string& content) const
{
    std::ofstream oStream(m_fileName);

    if (!oStream) {
        return;
    }

    for (int i = 0; i < content.length(); ++i) {
        oStream << content.at(i);
    }

    oStream.close();
}

const char* FileHandler::fileName() const
{
    return m_fileName;
}

bool FileHandler::error() const
{
    return m_error;
}
