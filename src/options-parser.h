#ifndef _options_parser_h_
#define _options_parser_h_

#include <vector>
#include <filesystem>
#include <ostream>
#include "cxxopts.hpp"

cxxopts::ParseResult loadOptions(int argc, const char *argv[], std::ostream &stdoutstrm, std::ostream &stderrstrm);

std::vector<std::filesystem::path> findFilesToProcess(const cxxopts::ParseResult &args, std::ostream &stdoutstrm, std::ostream &stderrstrm);

#endif