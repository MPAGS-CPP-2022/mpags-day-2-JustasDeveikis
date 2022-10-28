#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include <vector>
#include <string>
#include <iostream>


//! Transliterate char to string
bool processCommandLine(const std::vector<std::string>& args,
                        bool& helpRequested,
                        bool& versionRequested,
                        std::string& inputFile,
                        std::string& outputFile,
                        size_t& key,
                        bool& encrypt);

#endif // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP