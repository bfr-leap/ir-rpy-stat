#include "metadata-out.h"
#include <ostream>

enum FormatterState
{
    FMST_PASSTHROUGH,
    FMST_SLASH,
    FMST_PERCENT
};

void outputFormatMetadata(RpyMetadata &metadata, const char *fileName, const char *format, std::ostream &stdoutstrm)
{
    int i = 0;
    char c = format[i++];
    auto state = FMST_PASSTHROUGH;

    while (c)
    {
        switch (state)
        {
        case FMST_PASSTHROUGH:
            if ('\\' == c)
            {
                state = FMST_SLASH;
            }
            else if ('%' == c)
            {
                state = FMST_PERCENT;
            }
            else
            {
                stdoutstrm << c;
            }
            break;
        case FMST_SLASH:
            switch (c)
            {
            case 'n':
                stdoutstrm << std::endl;
                break;
            case 't':
                stdoutstrm << '\t';
            }
            state = FMST_PASSTHROUGH;
            break;

        case FMST_PERCENT:
            switch (c)
            {
            case 'c':
                stdoutstrm << metadata.car_Id;
                break;
            case 'H':
                stdoutstrm << metadata.hostZn;
                break;
            case 'L':
                stdoutstrm << metadata.layout;
                break;
            case 'l':
                stdoutstrm << metadata.leagId;
                break;
            case 'n':
                stdoutstrm << fileName;
                break;
            case 'S':
                stdoutstrm << metadata.sessId;
                break;
            case 's':
                stdoutstrm << metadata.sbseId;
                break;
            case 'T':
                stdoutstrm << metadata.track;
                break;
            case 't':
                stdoutstrm << metadata.tmstmp;
                break;
            case 'U':
                stdoutstrm << metadata.userNm;
                break;
            case 'u':
                stdoutstrm << metadata.userId;
                break;
            case '%':
                stdoutstrm << '%';
                break;
            }
            state = FMST_PASSTHROUGH;
            break;
        }

        c = format[i++];
    }
}

void outputMetadata(const std::vector<std::pair<std::filesystem::path, RpyMetadata>> &metadataList, const cxxopts::ParseResult &args, std::ostream &stdoutstrm)
{
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
        formatStr = "File: %n\\nuserId: %u\\ncarId: %c\\nsessionId: %S\\nsubsessionId: %s\\nhost: %H\\ntrack: %T\\nlayout: %L\\nuserName: %U\\ntimestamp: %t\\n";
    }

    for (const auto &[filePath, constMetadata] : metadataList)
    {
        auto &metadata = const_cast<RpyMetadata &>(constMetadata);
        outputFormatMetadata(metadata, filePath.filename().string().c_str(), formatStr.c_str(), stdoutstrm);
        stdoutstrm << std::endl;
    }
}
