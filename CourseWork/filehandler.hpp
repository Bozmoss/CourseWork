#pragma once  // Include guard to ensure header is included only once

#include <string>  // Include necessary header for std::string

class FileHandler
{
public:
    // Constructor: initializes FileHandler with a given fileName
    FileHandler(const char* fileName);

    // Destructor: cleans up resources when FileHandler is destroyed
    ~FileHandler();

    // readFile: reads content from the file and returns it as a string
    std::string readFile() const;

    // writeFile: writes the given content to the file
    void writeFile(const std::string& content) const;

    // fileName: returns the name of the file as a C-style string
    const char* fileName() const;

    // error: returns true if an error occurred during file operations
    bool error() const;

private:
    bool m_error;  // Flag indicating if an error occurred

    char* m_fileName;  // Pointer to store the filename (C-style string)
};
