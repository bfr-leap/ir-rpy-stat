#ifndef _options_parser_h_
#define _options_parser_h_

#include <vector>
#include <filesystem>
#include "cxxopts.hpp"

cxxopts::ParseResult loadOptions(int argc, const char *argv[], std::ostream &stdout, std::ostream &stderr);

std::vector<std::filesystem::path> findFilesToProcess(const cxxopts::ParseResult &args, std::ostream &stdout, std::ostream &stderr);

#endif