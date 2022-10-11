#include "MainPocket.hpp"

std::string& operator+=(std::string& log, const MainPocket& pocket)
{

    log += "code: ";
    log += std::to_string(pocket.channel);
    log += " range: ";
    log += std::to_string(pocket.range);
    log += " isOk: ";
    log += std::to_string(pocket.isOk);
    log += " result: ";
    log += std::to_string(pocket.result);


    // Before your logs operator for struct

    return log;
}