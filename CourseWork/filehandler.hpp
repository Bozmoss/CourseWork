/*****************************************************************//**
 * \file   filehandler.hpp
 * \brief  File handling class
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

#include <string>

class FileHandler
{
public:
    
    /**
     * Initialises the file handler class
     * 
     * \param char* fileName
     */
    FileHandler(const char* fileName);

    ~FileHandler();

    /**
     * Reads a file
     * 
     * \return string
     */
    std::string readFile() const;

    /**
     * Writes to a file
     * 
     * \param string content
     */
    void writeFile(const std::string& content) const;

    /**
     * Returns the file name of the open file
     * 
     * \return char*
     */
    const char* fileName() const;

    /**
     * Determines whether an error has occured
     * 
     * \return bool
     */
    bool error() const;

private:
    bool m_error;

    char* m_fileName;
};
