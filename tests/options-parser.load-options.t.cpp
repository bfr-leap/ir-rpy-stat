#include <gtest/gtest.h>
#include "options-parser.h"
#include <sstream>

TEST(loadOptions, NoArgs)
{
    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk"};

    auto parseResult = loadOptions(1, argv, stdoutstrm, stderrstrm);

    const char *expectedOut = "\
Display metadata information for iRacing .rpy replay files.\n\
Usage:\n\
  ir-rpy-stat [OPTION...] file.rpy [file2.rpy ...]\n\
\n\
  -h, --help        Show help\n\
  -V, --version     Show version\n\
  -f, --format arg  Use the specified format instead of the default; output \n\
                    a newline after each use of FORMAT\n\
  -c, --compact     Display a compact view of essential fields\n\
  -L                Follow symbolic links\n\
      --files arg   Input files\n\n\
";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
}

TEST(loadOptions, Help)
{
    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "-h"};

    auto parseResult = loadOptions(2, argv, stdoutstrm, stderrstrm);

    const char *expectedOut = "\
Display metadata information for iRacing .rpy replay files.\n\
Usage:\n\
  ir-rpy-stat [OPTION...] file.rpy [file2.rpy ...]\n\
\n\
  -h, --help        Show help\n\
  -V, --version     Show version\n\
  -f, --format arg  Use the specified format instead of the default; output \n\
                    a newline after each use of FORMAT\n\
  -c, --compact     Display a compact view of essential fields\n\
  -L                Follow symbolic links\n\
      --files arg   Input files\n\n\
";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
}

TEST(loadOptions, Help2)
{
    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "--help"};

    auto parseResult = loadOptions(2, argv, stdoutstrm, stderrstrm);

    const char *expectedOut = "\
Display metadata information for iRacing .rpy replay files.\n\
Usage:\n\
  ir-rpy-stat [OPTION...] file.rpy [file2.rpy ...]\n\
\n\
  -h, --help        Show help\n\
  -V, --version     Show version\n\
  -f, --format arg  Use the specified format instead of the default; output \n\
                    a newline after each use of FORMAT\n\
  -c, --compact     Display a compact view of essential fields\n\
  -L                Follow symbolic links\n\
      --files arg   Input files\n\n\
";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
}

#define EXPECTED_VERSION "ir-rpy-stat version 0.0.1\n"

TEST(loadOptions, Version)
{
    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "-V"};

    auto parseResult = loadOptions(2, argv, stdoutstrm, stderrstrm);

    const char *expectedOut = EXPECTED_VERSION;

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
}

TEST(loadOptions, Version2)
{
    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "--version"};

    auto parseResult = loadOptions(2, argv, stdoutstrm, stderrstrm);

    const char *expectedOut = EXPECTED_VERSION;

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
}

TEST(loadOptions, Files)
{
    std::ostringstream stdoutstrm;
    std::ostringstream stderrstrm;

    const char *argv[] = {"/home/amayorga/dev/leap/ir-rpy-stat/build/ir-rpy-stat.tsk", "./tests/input-files/empty.rpy"};

    auto parseResult = loadOptions(2, argv, stdoutstrm, stderrstrm);

    const char *expectedOut = "";
    const char *expectedErr = "";

    EXPECT_EQ(stdoutstrm.str(), expectedOut);
    EXPECT_EQ(stderrstrm.str(), expectedErr);
}