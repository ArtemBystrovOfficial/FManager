#pragma once

#include <iostream>
#include <cstring>
#include <string>

struct MainPocket
{

    int n;
   

    ///////////////////////
    // Before your data
    ///////////////////////
    
//DON'T EDIT BELOW

    // define operator << for logs how you need it;
    friend std::string & operator+=(std::string& left, const MainPocket& pocket);
};

std::string & operator+=(std::string& left,const MainPocket& pocket);
