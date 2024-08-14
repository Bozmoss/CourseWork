#pragma once

#include <string>  // String data type library

class FileHandler
{
public:
    
    FileHandler(const char* fileName);                // Initializes FileHandler with a given fileName

    ~FileHandler();                                   // Cleans up resources when FileHandler is destroyed

    std::string readFile() const;                     // Reads content from the file and returns it as a string

    void writeFile(const std::string& content) const; // Writes the given content to the file

    const char* fileName() const;                     // Returns the name of the file as a C-style string

    bool error() const;                               // Returns true if an error occurred during file operations

private:
    bool m_error;     // Flag indicating if an error occurred

    char* m_fileName; // Pointer to store the filename
};
