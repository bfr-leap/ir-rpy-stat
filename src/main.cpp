#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <regex>

#include "cxxopts.hpp"

#include "options-parser.h"
#include "rpy-metadata.h"
#include "metadata-out.h"

int main(int argc, char *argv[])
{
    try
    {
        auto parseResult = loadOptions(argc, (const char **)argv, std::cout, std::cerr);
        std::vector<std::filesystem::path> filesToProcess = findFilesToProcess(parseResult, std::cout, std::cerr);

        std::vector<std::pair<std::filesystem::path, RpyMetadata>> metadataList;
        for (const auto &filePath : filesToProcess)
        {
            try
            {
                auto metadata = extractMetadata(filePath);
                metadataList.emplace_back(filePath, metadata);
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error loading metadata: " << e.what() << " :: [" << filePath << ']' << std::endl;
            }
        }

        outputMetadata(metadataList, parseResult, std::cout);
    }
    catch (const cxxopts::exceptions::exception &e)
    {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
