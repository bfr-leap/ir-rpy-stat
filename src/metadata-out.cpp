#include "metadata-out.h"
#include <iostream>

void outputMetadata(const std::vector<std::pair<std::filesystem::path, RpyMetadata>> &metadataList, const cxxopts::ParseResult &args)
{
    std::ostringstream oss;

    std::string formatStr;

    if (args.count("format"))
    {
        formatStr = args["format"].as<std::string>();
    }
    else if (args.count("compact"))
    {
        formatStr = "%n %u %t";
    }
    else
    {
        for (const auto &[filePath, metadata] : metadataList)
        {
            oss << "File: " << filePath.filename().string() << "\n";
            oss << "userId: " << metadata.userId << "\n";
            oss << "carId: " << metadata.car_Id << "\n";
            oss << "sessionId: " << metadata.sessId << "\n";
            oss << "subsessionId: " << metadata.sbseId << "\n";
            oss << "host: " << metadata.hostZn << "\n";
            oss << "track: " << metadata.track << "\n";
            oss << "layout: " << metadata.layout << "\n";
            oss << "userName: " << metadata.userNm << "\n";
            oss << "timestamp: " << metadata.tmstmp << "\n";
            oss << "\n";
        }

        std::cout << oss.str();
        return;
    }

    // TODO: User these tags
    // {"$c", "car_id"},
    // {"%h", "host/server"},
    // {"%n", "file_name"},
    // {"%u", "user_id"},
    // {"%S", "session_id"},
    // {"%s", "subsession_id"},
    // {"%t", "track"},
    // {"%l", "layout"},
    // {"%U", "user_name"},
    // {"%T", "timestamp"},
    // {"%%", "%"}

    std::cout << oss.str();
}
