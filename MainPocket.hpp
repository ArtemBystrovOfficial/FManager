#pragma once

#include <iostream>
#include <string>

struct MainPocket
{

	enum class Command
	{
		Register,
		Login,
		Msg,
		Send_All,
		Ok,
		Error
	};

	MainPocket() {};

	MainPocket(Command&& com, const std::string& msg_s,
		const std::string& login_s, const std::string& password_s) : command(com)
	{
		strcpy(msg, msg_s.c_str());
		strcpy(login, login_s.c_str());
		strcpy(password, password_s.c_str());
	};


	Command command;
	char msg[256];
	char login[32];
	char password[32];
   

    ///////////////////////
    // Before your data
    ///////////////////////
    
//DON'T EDIT BELOW

    // define operator << for logs how you need it;
    friend std::string & operator+=(std::string& left, const MainPocket& pocket);
};

std::string & operator+=(std::string& left,const MainPocket& pocket);