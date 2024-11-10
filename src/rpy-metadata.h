#ifndef _rpy_metadata_h_
#define _rpy_metadata_h_

#include <string>
#include <filesystem>

struct RpyMetadata
{
    std::string userId;
    std::string sessionId;
    std::string track;
    std::string layout;
    std::string userName;
    std::string timestamp;
};

RpyMetadata extractMetadata(const std::filesystem::path &file_path);

#endif