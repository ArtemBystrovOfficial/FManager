#pragma once
#include "MainPocket.hpp"
#include "FServer.hpp"
#include <memory>
#include <algorithm>
#include <iostream>

#ifdef  WIN32
#include <conio.h>
#endif

void drawMenuFrame(const std::string& str,bool is_active)
{

	if (is_active)
	{
		std::cout << "╔════════════════╗\n";
		std::cout << "║";
		int space = (16 - str.size()) / 2;
		for (int i = 0; i < space; i++)std::cout << " ";
		std::cout << str;
		for (int i = 0; i < space; i++)std::cout << " ";
		if (space * 2 + str.size() != 16)std::cout << " ";
		std::cout << "║\n";
		std::cout << "╚════════════════╝\n";
	}
	else
	{
		std::cout << "------------------\n";
		std::cout << "|";
		int space = (16 - str.size()) / 2;
		for (int i = 0; i < space; i++)std::cout << " ";
		std::cout << str;
		for (int i = 0; i < space; i++)std::cout << " ";
		if (space * 2 + str.size() != 16)std::cout << " ";
		std::cout << "|\n";
		std::cout << "------------------\n";
	}
}

class CompositionMenu
{

public:
	CompositionMenu(const std::string & name) : name(name)
	{}

	virtual void addChild(std::shared_ptr < CompositionMenu > ptr){}

	void setParrent(std::shared_ptr < CompositionMenu > ptr) {
		parrent = ptr;
	}

	virtual bool isLeaf() = 0;
	virtual void draw() = 0;

	virtual void Up(){}
	virtual void Down(){}

	virtual std::shared_ptr < CompositionMenu >  In() = 0;

	std::shared_ptr < CompositionMenu > Out()
	{
		if (parrent.get() != nullptr)
			return parrent;
		else
			return std::make_shared< CompositionMenu >(this);
	}

	std::string getName()
	{
		return name;
	}
protected:

	std::string name;

	std::shared_ptr <CompositionMenu> parrent;
};

class CompositorMenu : public CompositionMenu
{
public:

	CompositorMenu(const std::string& name) : CompositionMenu(name)
	{
		
	}

	void addChild(std::shared_ptr <CompositionMenu> ptr) override
	{
		ptr->setParrent(parrent);
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
	std::shared_ptr < CompositionMenu > In() override
	{
		return items.at(active_item);
	}

private:

	// service
	std::vector < std::shared_ptr < CompositionMenu > > items;

	int active_item = 0;
};

class LeafMenu : public CompositionMenu
{
public:
	enum class Function
	{
		none,
		Ban
	};

	LeafMenu(const std::string& name, Function&& func) : CompositionMenu(name),  func(func)
	{
	
	}

	bool isLeaf() override
	{
		return true;
	}
	void draw() override
	{
		// draw functions
	}
	std::shared_ptr < CompositionMenu > In() override
	{
		return std::make_shared< CompositionMenu >(this);
	}

private:
	Function func = Function::none;
};

template <class Pocket>
struct FManager
{
public:
	FManager(const std::string& ip, int port);

	int exec();

private:

	void menuSetting();

	bool realisationOfCLogic();

	void _key_viewer();

	void _keyUp();
	void _keyDown();
	void _keyEnter();
	void _keyEscape();

	std::shared_ptr <CompositionMenu> current_item;
	std::shared_ptr <CompositorMenu> main_menu;

	FServer <Pocket>  srv;
	int current_position;

};

template <class Pocket>
void FManager<Pocket>::menuSetting()
{
	auto lf1 = std::make_shared<LeafMenu>("Pause", LeafMenu::Function::none);

	auto comp1 = std::make_shared<CompositorMenu>("Online");
	auto lf11 = std::make_shared<LeafMenu>("Online list", LeafMenu::Function::none);
	auto lf12 = std::make_shared<LeafMenu>("Fid IP", LeafMenu::Function::none);

	auto comp2 = std::make_shared<CompositorMenu>("Bans");
	auto lf21 = std::make_shared<LeafMenu>("Ban IP", LeafMenu::Function::none);
	auto lf22 = std::make_shared<LeafMenu>("Unban IP", LeafMenu::Function::none);
	auto lf23 = std::make_shared<LeafMenu>("Ban List", LeafMenu::Function::none);

	auto comp3 = std::make_shared<CompositorMenu>("Groups");
	auto lf31 = std::make_shared<LeafMenu>("Add to group", LeafMenu::Function::none);
	auto lf32 = std::make_shared<LeafMenu>("New group", LeafMenu::Function::none);
	auto lf33 = std::make_shared<LeafMenu>("List groups", LeafMenu::Function::none);

	auto lf2 = std::make_shared<LeafMenu>("Refresh", LeafMenu::Function::none);

	auto lf3 = std::make_shared<LeafMenu>("Off", LeafMenu::Function::none);

	comp1->addChild(lf11);
	comp1->addChild(lf12);

	comp2->addChild(lf21);
	comp2->addChild(lf22);
	comp2->addChild(lf23);

	comp3->addChild(lf31);
	comp3->addChild(lf32);
	comp3->addChild(lf33);

	current_item->addChild(lf1);
	current_item->addChild(comp1);
	current_item->addChild(comp2);
	current_item->addChild(comp3);
	current_item->addChild(lf2);
	current_item->addChild(lf3);
}

template<class Pocket>
inline FManager<Pocket>::FManager(const std::string& ip, int port):
srv(ip, port),
main_menu(std::make_shared<CompositorMenu>("Main"))
{
	current_item = main_menu;
}

template<class Pocket>
inline int FManager<Pocket>::exec()
{
	_key_viewer();
	return 0;
}


/////////////////////
// You're code there
/////////////////////

//return if your server have some problems
template<class Pocket>
inline bool FManager<Pocket>::realisationOfCLogic()
{
	return false;
}

template<class Pocket>
inline void FManager<Pocket>::_key_viewer()
{
	// realistation of your platform
	// keys of menu

//Pattern brige on compile
#ifdef  WIN32

	current_item->draw();

	switch (getch())
	{
		//UP
		case 72:{  _keyUp(); }break;

		//RIGHT
		case 77:{  _keyDown(); }break;

		//ENTER
		case 13:{  _keyEnter(); }break;

		//ESCAPE
		case 8: {  _keyEscape(); }break;
	}

#else



#endif

}

template<class Pocket>
inline void FManager<Pocket>::_keyUp()
{
	current_item->Up();
}

template<class Pocket>
inline void FManager<Pocket>::_keyDown()
{
	current_item->Down();
}

template<class Pocket>
inline void FManager<Pocket>::_keyEnter()
{
	current_item = current_item->In();
}

template<class Pocket>
inline void FManager<Pocket>::_keyEscape()
{
	current_item = current_item->Out();
}
