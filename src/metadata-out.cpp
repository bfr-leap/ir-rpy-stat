#include "metadata-out.h"
#include <ostream>

enum FormatterState
{
    FMST_PASSTHROUGH,
    FMST_SLASH,
    FMST_PERCENT
};

void outputFormatMetadata(RpyMetadata &metadata, const char *fileName, const char *format, std::ostream &stdout)
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
                stdout << c;
            }
            break;
        case FMST_SLASH:
            switch (c)
            {
            case 'n':
                stdout << std::endl;
                break;
            case 't':
                stdout << '\t';
            }
            state = FMST_PASSTHROUGH;
            break;

        case FMST_PERCENT:
            switch (c)
            {
            case 'c':
                stdout << metadata.car_Id;
                break;
            case 'H':
                stdout << metadata.hostZn;
                break;
            case 'L':
                stdout << metadata.layout;
                break;
            case 'l':
                stdout << metadata.leagId;
                break;
            case 'n':
                stdout << fileName;
                break;
            case 'S':
                stdout << metadata.sessId;
                break;
            case 's':
                stdout << metadata.sbseId;
                break;
            case 'T':
                stdout << metadata.track;
                break;
            case 't':
                stdout << metadata.tmstmp;
                break;
            case 'U':
                stdout << metadata.userNm;
                break;
            case 'u':
                stdout << metadata.userId;
                break;
            case '%':
                stdout << '%';
                break;
            }
            state = FMST_PASSTHROUGH;
            break;
        }

        c = format[i++];
    }
}

void outputMetadata(const std::vector<std::pair<std::filesystem::path, RpyMetadata>> &metadataList, const cxxopts::ParseResult &args, std::ostream &stdout)
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
        outputFormatMetadata(metadata, filePath.filename().string().c_str(), formatStr.c_str(), stdout);
        stdout << std::endl;
    }
}
