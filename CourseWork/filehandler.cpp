#include <string>       // Include necessary headers
#include <memory>
#include <fstream>
#include <sstream>
#include <string.h>     // Include C-style string header for strlen and strcpy_s functions

#include "filehandler.hpp"  // Include the header file for the FileHandler class

FileHandler::FileHandler(const char* fileName)
    : m_error{ false }   // Initialize m_error to false by default
{
    // Allocate memory for m_fileName and copy fileName into it
    size_t length = strlen(fileName) + 1;  // Calculate length of fileName including null terminator
    m_fileName = static_cast<char*>(std::malloc(length));  // Allocate memory

    if (m_fileName) {
        // Use strcpy_s for safer string copy
        if (strcpy_s(m_fileName, length, fileName) != 0) {
            m_error = true;  // Set m_error to true if copy fails
            std::free(m_fileName);  // Free allocated memory
            m_fileName = nullptr;  // Set pointer to nullptr
        }
    }
    else {
        m_error = true;  // Set m_error to true if memory allocation fails
    }
}

FileHandler::~FileHandler()
{
    std::free(m_fileName);  // Free allocated memory for m_fileName in destructor
}

std::string FileHandler::readFile() const
{
    std::ifstream iStream(m_fileName);  // Open file for reading

    if (!iStream) {
        return "";  // Return empty string if file opening fails
    }

    std::stringstream sStream;  // Create string stream to store file content
    sStream << iStream.rdbuf();  // Read file content into stringstream
    std::string content(sStream.str());  // Convert stringstream to string
    iStream.close();  // Close input stream
    return content;  // Return file content as string
}

void FileHandler::writeFile(const std::string& content) const
{
    std::ofstream oStream(m_fileName);  // Open file for writing

    if (!oStream) {
        return;  // Return if file opening fails
    }

    for (int i = 0; i < content.length(); ++i) {
        oStream << content.at(i);  // Write content character by character to file
    }

    oStream.close();  // Close output stream
}

const char* FileHandler::fileName() const
{
    return m_fileName;  // Return m_fileName (C-style string)
}

bool FileHandler::error() const
{
    return m_error;  // Return error status
}
