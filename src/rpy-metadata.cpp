#include "rpy-metadata.h"

RpyMetadata extractMetadata(const std::filesystem::path &file_path)
{
    RpyMetadata ret;
    ret.userId = "12345";
    ret.sessionId = "67890";
    ret.track = "Laguna Seca";
    ret.layout = "Full Course";
    ret.userName = "JohnDoe";
    ret.timestamp = "2023-10-01T12:34:56Z";

    return ret;
};
