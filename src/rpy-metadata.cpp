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
    ret.sessId = 67890;

    snprintf(ret.hostZn, sizeof(ret.hostZn), "Spa");
    snprintf(ret.layout, sizeof(ret.layout), "GP");
    snprintf(ret.userNm, sizeof(ret.userNm), "JohnDoe");
    snprintf(ret.tmstmp, sizeof(ret.tmstmp), "2023-10-01T12:34:56Z");

    return ret;
};

void skipBytes(std::ifstream &file, std::streamsize length)
{
    file.seekg(length, std::ios::cur);
    if (!file)
    {
        throw std::runtime_error("Failed to skip bytes in file");
    }
}

void readString(std::ifstream &file, char *buffer, std::size_t length, std::streamsize offset)
{
    if (offset)
    {
        skipBytes(file, offset);
    }

    file.read(buffer, length);
    if (!file)
    {
        throw std::runtime_error("Failed to read string from file");
    }
    buffer[length - 1] = '\0';
}

void readUint32(std::ifstream &file, uint32_t &buffer, std::streamsize offset)
{
    if (offset)
    {
        skipBytes(file, offset);
    }
    file.read(reinterpret_cast<char *>(&buffer), sizeof(uint32_t));
}

void seekToNext(std::ifstream &file, char marker, std::streamsize offset)
{
    skipBytes(file, offset);
    char c = marker + 1;
    while (c != marker)
    {
        file.read(&c, 1);
        if (!file)
        {
            throw std::runtime_error("Failed to read string from file");
        }
    }
}

void saveTrackInfoToMetadata(RpyMetadata &metadata, const char *trackLayoutComb)
{
    const char *separator = std::strchr(trackLayoutComb, '\\');
    if (separator)
    {
        std::size_t trackLength = separator - trackLayoutComb;
        std::strncpy(metadata.track, trackLayoutComb, trackLength);
        metadata.track[trackLength] = '\0';
        std::strncpy(metadata.layout, separator + 1, sizeof(metadata.layout) - 1);
    }
    else
    {
        std::strncpy(metadata.track, trackLayoutComb, sizeof(metadata.track) - 1);
        metadata.layout[0] = '\0'; // No layout provided
    }
}

RpyMetadata extractMetadata(const std::filesystem::path &file_path)
{
    std::ifstream f(file_path, std::ios::binary);
    if (!f)
    {
        throw std::runtime_error("Failed to open file");
    }

    RpyMetadata metadata;
    uint32_t hdrEntriesCount;
    uint32_t assetListLength;
    char trackLayoutComb[64];
    char endOfStringMark = '\0';

    char magic[4];
    f.read(magic, sizeof(magic));
    if (std::strncmp(magic, "YLPR", 4) != 0)
    {
        throw std::runtime_error("Invalid file format: magic number mismatch");
    }

    readUint32(f, metadata.userId, /**********************/ 40);
    readUint32(f, metadata.car_Id, /**********************/ 0);
    readString(f, metadata.userNm, sizeof(metadata.userNm), 4);
    readUint32(f, hdrEntriesCount, /**********************/ 8);
    readString(f, metadata.tmstmp, sizeof(metadata.tmstmp), 0);
    readUint32(f, assetListLength, /**********************/ (12 * hdrEntriesCount) + 120);
    seekToNext(f, endOfStringMark, /**********************/ assetListLength + 6);
    readUint32(f, metadata.sessId, /**********************/ 18);
    readUint32(f, metadata.sbseId, /**********************/ 0);
    readString(f, metadata.hostZn, sizeof(metadata.hostZn), 88);
    readString(f, trackLayoutComb, sizeof(trackLayoutComb), 0);

    saveTrackInfoToMetadata(metadata, trackLayoutComb);

    f.close();
    return metadata;
}
