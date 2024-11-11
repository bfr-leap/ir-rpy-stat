#include <ostream>
#include <string>
#include "options-parser.h"

cxxopts::ParseResult loadOptions(int argc, const char *argv[], std::ostream &stdoutstrm, std::ostream &stderrstrm)
{
    cxxopts::Options options("ir-rpy-stat", "Display metadata information for iRacing .rpy replay files.");

    options.add_options()(
        "h,help", "Show help")(
        "V,version", "Show version")(
        "f,format", "Use the specified format instead of the default; output a newline after each use of FORMAT",
        cxxopts::value<std::string>())(
        "c,compact", "Display a compact view of essential fields")(
        "L", "Follow symbolic links")(
        "files", "Input files", cxxopts::value<std::vector<std::string>>());

    options.parse_positional({"files"});
    options.positional_help("file.rpy [file2.rpy ...]");
    options.show_positional_help();

    auto args = options.parse(argc, argv);

    if (args.count("help"))
    {
        stdoutstrm << options.help() << std::endl;
        return args;
    }

    if (args.count("version"))
    {
        stdoutstrm << "ir-rpy-stat version 0.0.1" << std::endl;
        return args;
    }

    if (!args.count("files"))
    {
        stderrstrm << "Error: No input files provided." << std::endl;
        stdoutstrm << options.help() << std::endl;
        return args;
    }

    return args;
}

std::vector<std::filesystem::path> findFilesToProcess(const cxxopts::ParseResult &args, std::ostream &stdoutstrm, std::ostream &stderrstrm)
{
    auto files = args["files"];
    std::vector<std::filesystem::path> filesToProcess;
    if (files.count() < 1)
    {
        return filesToProcess;
    }

    auto inputFiles = files.as<std::vector<std::string>>();

    for (const auto &input : inputFiles)
    {
        std::filesystem::path path(input);
        if (std::filesystem::exists(path))
        {
            if (std::filesystem::is_regular_file(path))
            {
                filesToProcess.push_back(path);
            }
            else if (std::filesystem::is_directory(path))
            {
                stderrstrm << "Warning: Directories are not supported: " << path << std::endl;
            }
            else
            {
                stderrstrm << "Warning: Unsupported file type: " << path << std::endl;
            }
        }
        else
        {
            stderrstrm << "Warning: File does not exist: " << path << std::endl;
        }
    }

    return filesToProcess;
}
