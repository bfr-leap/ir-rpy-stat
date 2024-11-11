#ifndef _metadata_out_h_
#define _metadata_out_h_

#include <vector>
#include <filesystem>
#include "rpy-metadata.h"
#include "cxxopts.hpp"

void outputMetadata(const std::vector<std::pair<std::filesystem::path, RpyMetadata>> &metadataList, const cxxopts::ParseResult &args, std::ostream &stdout);

void outputFormatMetadata(RpyMetadata &metadata, const char *fileName, const char *format, std::ostream &stdout);

#endif