#ifndef _ZF_ZFCOMMON_DEBUGGING_H_
#define _ZF_ZFCOMMON_DEBUGGING_H_
#include <string>
namespace z_db
{
    void point(std::string filename, int linenumber, std::string description = "");
}

#endif
