#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"

std::string transformChar( const char in_char );

bool processCommandLine(const std::vector<std::string>& args,
                        bool& helpRequested,
                        bool& versionRequested,
                        std::string& inputFile,
                        std::string& outputFile,
                        size_t& key,
                        bool& encrypt);

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt);

int main(int argc, char* argv[])
{
    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    size_t key{0};
    bool encrypt{true};

    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    if (!processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, key, encrypt))
    {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n"
            << "  -k               Key value\n"
            << "                   Zero is used if not supplied\n"
            << "  --encrypt        Set encrypt variable to true\n"
            << "  --decrypt        Set encrypt variable to false\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.1" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText{""}, outputText{""};

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::ifstream inputStream{inputFile};

        if (!inputStream.good())
        {
            std::cerr << "Unable to open file" << std::endl;
            return 1;
        }

        while (inputStream >> inputChar)
        {
            inputText += transformChar(inputChar);
        }

        // std::cerr << "[warning] input from file ('" << inputFile
        //           << "') not implemented yet, using stdin\n";
    }
    else
    {
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    outputText = runCaesarCipher(inputText, key, encrypt);

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::ofstream outputStream{outputFile};

        if (!outputStream.good())
        {
            std::cerr << "Unable to open file for writing" << std::endl;
            return 1;
        }
        outputStream << outputText << std::endl;
    }
    else
    {
        // Print out the transliterated text
        std::cout << inputText << std::endl;
    }
    
    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
