#pragma once

#include <iostream>
#include <string>

// N - count of channels
// M - count of ranges

struct MainPocket
{

    enum class function
    {
        stopMeasure,
        startMeasure,
        setRange,
        getStatus,
        getResult
    };
    
    enum class codeState
    {
        error_state,
        idle_state,
        measure_state,
        busy_state
    };

    codeState code;

    function func;

    int32_t channel, range;

    bool isOk;

    float result;

    
//DON'T EDIT BELOW

    // define operator << for logs how you need it;
    friend std::string & operator+=(std::string& left, const MainPocket& pocket);
};

std::string & operator+=(std::string& left,const MainPocket& pocket);
