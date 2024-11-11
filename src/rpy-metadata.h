#ifndef _rpy_metadata_h_
#define _rpy_metadata_h_

#include <string>
#include <filesystem>

struct RpyMetadata
{
    uint32_t userId;
    uint32_t sessId;
    uint32_t sbseId;
    uint32_t leagId;
    uint32_t car_Id;
    char hostZn[28];
    char track[64];
    char layout[64];
    char userNm[64];
    char tmstmp[32];
};

RpyMetadata extractMetadata(const std::filesystem::path &file_path);

#endif