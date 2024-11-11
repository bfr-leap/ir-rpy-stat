#ifndef _rpy_metadata_h_
#define _rpy_metadata_h_

#include <string>
#include <filesystem>

struct RpyMetadata
{
    RpyMetadata() : userId(0),
                    sessId(0),
                    sbseId(0),
                    leagId(0),
                    car_Id(0)
    {
        hostZn[0] = '\0';
        track[0] = '\0';
        layout[0] = '\0';
        userNm[0] = '\0';
        tmstmp[0] = '\0';
    }
    
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