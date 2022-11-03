#include "ProcessCommandLine.hpp"


bool processCommandLine(const std::vector<std::string>& args,
                        bool& helpRequested,
                        bool& versionRequested,
                        std::string& inputFile,
                        std::string& outputFile,
                        size_t& key,
                        bool& encrypt)
{
    const std::size_t nCmdLineArgs{args.size()};

    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                inputFile = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                outputFile = args[i + 1];
                ++i;
            }
        } 
        else if (args[i] == "-k") 
        {
            // Handle key option
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -k requires a key value"
                          << std::endl;
                return 1;
            }
            else
            {
                key = stoi(args[i + 1]);
                ++i;
            }
        }
        else if (args[i] == "--encrypt")
        {
            encrypt = true;
        }
        else if (args[i] == "--decrypt")
        {
            encrypt = false;
        }

        else 
        {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i] << "'\n";
            return false;
        }
    }
    return true;
}