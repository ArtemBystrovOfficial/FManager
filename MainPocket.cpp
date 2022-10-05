#include "MainPocket.hpp"


std::string& operator+=(std::string& left, const MainPocket& pocket)
{

    left += "msg : "; 
    left += pocket.msg;

    /////////////////////////////////////////
    // Before your logs operator for struct
    ////////////////////////////////////////

    return left;
}