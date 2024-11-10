#include "rpy-metadata.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <stdexcept>

RpyMetadata extractMetadata_(const std::filesystem::path &file_path)
{
    RpyMetadata ret;
    ret.userId = 12345;
    ret.sessionId = 67890;

    snprintf(ret.host, sizeof(ret.host), "Spa");
    snprintf(ret.layout, sizeof(ret.layout), "GP");
    snprintf(ret.userName, sizeof(ret.userName), "JohnDoe");
    snprintf(ret.timestamp, sizeof(ret.timestamp), "2023-10-01T12:34:56Z");

    return ret;
};

// Helper function to skip bytes in a file
void skipBytes(std::ifstream &file, std::streamsize length)
{
    file.seekg(length, std::ios::cur);
    if (!file)
    {
        throw std::runtime_error("Failed to skip bytes in file");
    }
}

// Helper function to read a null-terminated string from a fixed-length buffer
void readString(std::ifstream &file, char *buffer, std::size_t length)
{
    file.read(buffer, length);
    if (!file)
    {
        throw std::runtime_error("Failed to read string from file");
    }
    buffer[length - 1] = '\0';
}

RpyMetadata extractMetadata(const std::filesystem::path &file_path)
{
    std::ifstream file(file_path, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file");
    }

    RpyMetadata metadata = {};

    char magic[4];
    file.read(magic, sizeof(magic));
    if (std::strncmp(magic, "YLPR", 4) != 0)
    {
        throw std::runtime_error("Invalid file format: magic number mismatch");
    }

    skipBytes(file, 40);
    file.read(reinterpret_cast<char *>(&metadata.userId), sizeof(metadata.userId));

    file.read(reinterpret_cast<char *>(&metadata.carId), sizeof(metadata.carId));

    skipBytes(file, 4);
    readString(file, metadata.userName, sizeof(metadata.userName));

    skipBytes(file, 8);
    uint32_t entriesCount;
    file.read(reinterpret_cast<char *>(&entriesCount), sizeof(entriesCount));
    readString(file, metadata.timestamp, sizeof(metadata.timestamp));
    skipBytes(file, 120);
    skipBytes(file, entriesCount * 12);

    uint32_t assetListLength;
    file.read(reinterpret_cast<char *>(&assetListLength), sizeof(assetListLength));
    skipBytes(file, assetListLength);
    std::cout << "asset list len: " << assetListLength << std::endl;

    skipBytes(file, 6);
    file.read(reinterpret_cast<char *>(&metadata.sessionId), sizeof(metadata.sessionId)); // TODO: this is not quite right

    skipBytes(file, 24);
    file.read(reinterpret_cast<char *>(&metadata.subsessionId), sizeof(metadata.subsessionId));

    skipBytes(file, 88);
    readString(file, metadata.host, sizeof(metadata.host));

    char trackLayout[64];
    readString(file, trackLayout, sizeof(trackLayout));
    const char *separator = std::strchr(trackLayout, '\\');
    if (separator)
    {
        std::size_t trackLength = separator - trackLayout;
        std::strncpy(metadata.track, trackLayout, trackLength);
        metadata.track[trackLength] = '\0';
        std::strncpy(metadata.layout, separator + 1, sizeof(metadata.layout) - 1);
    }
    else
    {
        std::strncpy(metadata.track, trackLayout, sizeof(metadata.track) - 1);
        metadata.layout[0] = '\0'; // No layout provided
    }

    file.close();
    return metadata;
}
