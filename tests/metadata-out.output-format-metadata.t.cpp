#include <gtest/gtest.h>
#include "metadata-out.h"
#include <sstream>

void rpyMetadata(RpyMetadata &ret, uint32_t userId, uint32_t sessionId, uint32_t subsessionId, uint32_t leagueId, uint32_t carId, const char *hostZone, const char *track, const char *layout, const char *userName, const char *timestamp)
{
    ret.userId = userId;
    ret.sessId = sessionId;
    ret.sbseId = subsessionId;
    ret.leagId = leagueId;
    ret.car_Id = carId;
    snprintf(ret.hostZn, sizeof(ret.hostZn), "%s", hostZone);
    snprintf(ret.track, sizeof(ret.track), "%s", track);
    snprintf(ret.layout, sizeof(ret.layout), "%s", layout);
    snprintf(ret.userNm, sizeof(ret.userNm), "%s", userName);
    snprintf(ret.tmstmp, sizeof(ret.tmstmp), "%s", timestamp);
};

TEST(outpuFormatMetadata, BaseCaseNoInserts)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "abc def ghij, klmn: opq\trst\nuv xyz. !@#$ *()_ {}^&*", stdout);

    const char *expectedOut = "abc def ghij, klmn: opq\trst\nuv xyz. !@#$ *()_ {}^&*";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseSlash)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "abc def ghij, klmn: opq\\trst\\nuv xyz. !@#$ *()_ {}^&*", stdout);

    const char *expectedOut = "abc def ghij, klmn: opq\trst\nuv xyz. !@#$ *()_ {}^&*";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseUserName)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%U", stdout);

    const char *expectedOut = "Full Name";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseUserId)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%u", stdout);

    const char *expectedOut = "1234";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseSessionId)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%S", stdout);

    const char *expectedOut = "2345";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseSubsessionId)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%s", stdout);

    const char *expectedOut = "3456";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseLeagueId)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%l", stdout);

    const char *expectedOut = "7890";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseCarId)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%c", stdout);

    const char *expectedOut = "5678";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseHostZone)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%H", stdout);

    const char *expectedOut = "host_zone";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseTrack)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%T", stdout);

    const char *expectedOut = "track";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseLayout)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%L", stdout);

    const char *expectedOut = "layout";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseTimestamp)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%t", stdout);

    const char *expectedOut = "2024-01-01 00:11:22";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCasePercent)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%%", stdout);

    const char *expectedOut = "%";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseCompact)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(meta, "file_name.rpy", "%n %u %t", stdout);

    const char *expectedOut = "file_name.rpy 1234 2024-01-01 00:11:22";

    EXPECT_EQ(stdout.str(), expectedOut);
}

TEST(outpuFormatMetadata, BaseCaseDefault)
{
    std::ostringstream stdout;

    RpyMetadata meta;
    rpyMetadata(meta, 1234, 2345, 3456, 7890, 5678, "host_zone", "track", "layout", "Full Name", "2024-01-01 00:11:22");

    outputFormatMetadata(
        meta,
        "file_name.rpy",
        "File: %n\\nuserId: %u\\ncarId: %c\\nsessionId: %S\\nsubsessionId: %s\\nhost: %H\\ntrack: %T\\nlayout: %L\\nuserName: %U\\ntimestamp: %t\\n\\n",
        stdout);

    const char *expectedOut = "File: file_name.rpy\nuserId: 1234\ncarId: 5678\nsessionId: 2345\nsubsessionId: 3456\nhost: host_zone\ntrack: track\nlayout: layout\nuserName: Full Name\ntimestamp: 2024-01-01 00:11:22\n\n";

    EXPECT_EQ(stdout.str(), expectedOut);
}