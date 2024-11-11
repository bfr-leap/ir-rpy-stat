#include <gtest/gtest.h>
#include "options-parser.h"
#include <sstream>

TEST(findFilesToProcess, EmptyFile)
{
    std::ostringstream stdout_;
    std::ostringstream stderr_;

    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "./tests/input-files/empty.rpy"};

    auto parseResult = loadOptions(2, argv, stdout_, stderr_);

    auto files = findFilesToProcess(parseResult, stdoutstrm, stderrstrm);

    EXPECT_EQ(files.size(), 1);

    EXPECT_EQ(files[0].generic_string(), "./tests/input-files/empty.rpy");

    const char *expectedOut = "";
    const char *expectedErr = "";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
    EXPECT_EQ(stderrstrm.str(), expectedErr);
}

TEST(findFilesToProcess, MissingFile)
{
    std::ostringstream stdout_;
    std::ostringstream stderr_;

    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "./tests/input-files/missing.rpy"};

    auto parseResult = loadOptions(2, argv, stdout_, stderr_);

    auto files = findFilesToProcess(parseResult, stdoutstrm, stderrstrm);

    EXPECT_EQ(files.size(), 0);

    const char *expectedOut = "";
    const char *expectedErr = "Warning: File does not exist: \"./tests/input-files/missing.rpy\"\n";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
    EXPECT_EQ(stderrstrm.str(), expectedErr);
}

TEST(findFilesToProcess, MissingAndExistingFile)
{
    std::ostringstream stdout_;
    std::ostringstream stderr_;

    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "./tests/input-files/empty.rpy", "./tests/input-files/missing.rpy"};

    auto parseResult = loadOptions(3, argv, stdout_, stderr_);

    auto files = findFilesToProcess(parseResult, stdoutstrm, stderrstrm);

    EXPECT_EQ(files.size(), 1);
    EXPECT_EQ(files[0].generic_string(), "./tests/input-files/empty.rpy");

    const char *expectedOut = "";
    const char *expectedErr = "Warning: File does not exist: \"./tests/input-files/missing.rpy\"\n";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
    EXPECT_EQ(stderrstrm.str(), expectedErr);
}

TEST(findFilesToProcess, Directory)
{
    std::ostringstream stdout_;
    std::ostringstream stderr_;

    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "./tests/input-files"};

    auto parseResult = loadOptions(2, argv, stdout_, stderr_);

    auto files = findFilesToProcess(parseResult, stdoutstrm, stderrstrm);

    EXPECT_EQ(files.size(), 0);

    const char *expectedOut = "";
    const char *expectedErr = "Warning: Directories are not supported: \"./tests/input-files\"\n";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
    EXPECT_EQ(stderrstrm.str(), expectedErr);
}

TEST(findFilesToProcess, DevNull)
{
    std::ostringstream stdout_;
    std::ostringstream stderr_;

    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "/dev/null"};

    auto parseResult = loadOptions(2, argv, stdout_, stderr_);

    auto files = findFilesToProcess(parseResult, stdoutstrm, stderrstrm);

    EXPECT_EQ(files.size(), 0);

    const char *expectedOut = "";
    const char *expectedErr = "Warning: Unsupported file type: \"/dev/null\"\n";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
    EXPECT_EQ(stderrstrm.str(), expectedErr);
}

TEST(findFilesToProcess, NoFiles)
{
    std::ostringstream stdout_;
    std::ostringstream stderr_;

    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk"};

    auto parseResult = loadOptions(1, argv, stdout_, stderr_);

    auto files = findFilesToProcess(parseResult, stdoutstrm, stderrstrm);

    EXPECT_EQ(files.size(), 0);

    const char *expectedOut = "";
    const char *expectedErr = "";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
    EXPECT_EQ(stderrstrm.str(), expectedErr);
}