#pragma once
#include "MainPocket.hpp"
#include "FServer.hpp"
#include <memory>
#include <algorithm>
#include <iostream>
#include <thread>

#ifdef  WIN32
#include <conio.h>
#endif

// console frame symbols
const uint8_t sim1 = 213,sim2 = 184,sim3 = 190,sim4 = 212,sim5 = 205,sim6 = 196;

void printN(const unsigned char& ch, int count);


void drawMenuFrame(const std::string& str, bool is_active);

/////////////////////////////////////////////
// AUTOMATIC garbage collector of childerns
/////////////////////////////////////////////

class CompositionMenu
{

public:
	CompositionMenu(const std::string & name) : name(name)
	{}

	void setParrent(CompositionMenu* ptr) {
		parrent = ptr;
	}

	virtual bool isLeaf() = 0;
	virtual void draw() = 0;

	virtual void Up(){}
	virtual void Down(){}

	virtual CompositionMenu * In() = 0;
    virtual CompositionMenu * Out() = 0;

	//custom options
	virtual bool isPause() { return false; };
	virtual bool isLog() { return false; };

	void setName(const std::string& name)
	{
		this->name = name;
	}

	std::string & getName()
	{
		return name;
	}
	virtual ~CompositionMenu(){}
protected:

	std::string name;

	CompositionMenu * parrent;

};

class CompositorMenu : public CompositionMenu
{
public:

	CompositorMenu(const std::string& name) : CompositionMenu(name)
	{
		
	}

	void addChild(CompositionMenu * ptr) 
	{
		ptr->setParrent(this);
		items.push_back(ptr);
	}

	bool isLeaf() override
	{
		return false;
	}
	void draw() override
	{
		int id = 0;
		for (auto it = items.begin(); it < items.end(); ++it)
		{
			drawMenuFrame((*it)->getName(), active_item == id);
			id++;
		}
	}
	void Up() override
	{
		if (active_item)
			active_item--;
	}
	void Down() override
	{
		if(active_item != items.size()-1)
			active_item++;
	}

	 CompositionMenu * In() override
	{
		return items.at(active_item);
	}

	CompositionMenu * Out() override
	{
		if (parrent != nullptr)
			return parrent;
		else
			return this;
	}

	virtual ~CompositorMenu() 
	{
		for (int i = 0; i < items.size(); i++)
		{
			delete items[i];
		}
	}
private:

	// service
	std::vector <  CompositionMenu * > items;

	int active_item = 0;
};

class LeafMenu : public CompositionMenu
{
public:
	enum class Function
	{
		none,
		Logs,
		Pause,
		OnlineList,
		FidIp,
		BanIp,
		UnbanIp,
		BanList,
		AddtoGroup,
		NewGroup,
		ListGroup,
		Refresh,
		Off
	};

	LeafMenu(const std::string& name, Function&& func, FServer<MainPocket>* server)
		: CompositionMenu(name), func(func), server(server) {}

	bool isLeaf() override
	{
		return true;
	}

	bool isPause() override
	{
		return func == Function::Pause;
	}

	virtual bool isLog()
	{
		return func == Function::Logs;
	}

	void draw() override;

	CompositionMenu * In() override
	{
		return nullptr;
	}

	CompositionMenu * Out() override
	{
		if (parrent != nullptr)
			return parrent;
		else
			return this;
	}

	void setExitCondition(std::atomic<bool> * is_exit)
	{
		this->is_exit = is_exit;
	}

	virtual ~LeafMenu() = default;
private:

	std::atomic<bool> * is_exit;

	FServer <MainPocket> * server;

	Function func = Function::none;
};

struct FManager
{
public:
	FManager(const FManager &) = delete;
	FManager(FManager &&) = default;

	FManager(const std::string& ip, int port);

	int exec();

	~FManager();

private:

	void menuSetting();

	void realisationOfCLogic();

	void _key_viewer();

	void _keyUp();
	void _keyDown();
	void _keyEnter();
	void _keyEscape();

private:
	CompositionMenu * current_item;
	std::unique_ptr <CompositorMenu> main_menu;

	FServer <MainPocket> * srv;
	std::thread run;

	std::atomic <bool> _exit_app = false;
	
};

