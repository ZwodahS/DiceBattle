#include "debugging.hpp"
#include <vector>
#include <iostream>
namespace z_db
{
    void point(std::string filename, int linenumber, std::string description)
    {
        std::cout << filename << " :" << linenumber << " [" << description <<"]" << std::endl;
    }
}
