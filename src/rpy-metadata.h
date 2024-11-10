#ifndef _rpy_metadata_h_
#define _rpy_metadata_h_

#include <string>
#include <filesystem>

struct RpyMetadata
{
    uint32_t userId;
    uint32_t sessionId;
    uint32_t subsessionId;
    uint32_t carId;
    char host[28];
    char track[64];
    char layout[64];
    char userName[64];
    char timestamp[32];
};

RpyMetadata extractMetadata(const std::filesystem::path &file_path);

#endif