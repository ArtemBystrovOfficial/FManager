#include "FManager.hpp"

bool log_active = false;

void printN(const unsigned char& ch, int count)
{
	for (int i = 0; i < count; i++)
		std::cout << ch;
}

void drawMenuFrame(const std::string& str, bool is_active)
{

	if (is_active)
	{
		std::cout << sim1; printN(sim5, 16); std::cout << sim2 << "\n";
		std::cout << "|";
		int space = (16 - str.size()) / 2;
		for (int i = 0; i < space; i++)std::cout << " ";
		std::cout << str;
		for (int i = 0; i < space; i++)std::cout << " ";
		if (space * 2 + str.size() != 16)std::cout << " ";
		std::cout << "|\n";
		std::cout << sim4; printN(sim5, 16); std::cout << sim3 << "\n";
	}
	else
	{
		std::cout << " "; printN(sim6, 16); std::cout << " \n";
		std::cout << " ";
		int space = (16 - str.size()) / 2;
		for (int i = 0; i < space; i++)std::cout << " ";
		std::cout << str;
		for (int i = 0; i < space; i++)std::cout << " ";
		if (space * 2 + str.size() != 16)std::cout << " ";
		std::cout << " \n ";
		printN(sim6, 16); std::cout << " \n";
	}
}

void LeafMenu::draw()
{
	switch (func)
	{
	case Function::Logs:
	{
		if (!log_active)
		{
			log_active = true;
			server->switchLog();
		}
	}
	break;
	case Function::Pause:
	{
		if (server->isWorking())
		{
			server->stop();
			setName("Start");
		}
		else
		{
			server->start();
			setName("Pause");
		}

	}
	break;
	case Function::OnlineList:
	{
		// Logo
		printN(' ', 3);
		std::cout << "Online List";
		std::cout << std::endl;
		printN(' ', 1);
		printN(sim6, 16);
		printN(' ', 1);
		std::cout << std::endl << std::endl;

		// Logo end
		auto list = server->getOnlineIpList();

		for (auto& user : list)
		{
			auto& [fid, ip] = user;
			std::cout << fid << " " << ip << std::endl;
		}
		std::cout << std::endl;

	}
	break;
	case Function::FidIp:
	{
		int fid = 0;

		std::cout << "Write fid: ";

		std::cin >> fid;

		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::string str;


		str = server->getIpByFid(fid);
		if (str != "")
		{
			std::cout << "IP: " << str << std::endl;
			std::cout << "Retry [ENTER] or Exit [ESC]" << std::endl;
		}
		else
			std::cout << "Bad fid, try again [ENTER] or [ESC]\n";
	}
	break;
	case Function::BanIp:
	{
		std::string str = "";

		std::cout << "Ban IP: ";

		std::cin >> str;

		if (str.size() >= 7 && str.size() <= 14 && std::count(str.begin(), str.end(), '.') == 3)
		{
			std::cout << "OK\n";
			server->banIp(str);
		}
		else
			std::cout << "Bad fid, try again [ENTER] or [ESC]\n";
	}
	break;
	case Function::UnbanIp:
	{
		std::string str = "";

		std::cout << "Unban IP: ";

		std::cin >> str;

		if (str.size() >= 7 && str.size() <= 14 && std::count(str.begin(), str.end(), '.') == 3)
		{
			if (server->unbanIp(str))
				std::cout << "OK [ENTER] or [ESC]\n";
			else
				std::cout << "Ip not banned, try again [ENTER] or [ESC]\n";

		}
		else
			std::cout << "Bad fid, try again [ENTER] or [ESC]\n";
	}
	break;
	case Function::BanList:
	{
		// Logo
		printN(' ', 5);
		std::cout << "Ban List";
		std::cout << std::endl;
		printN(' ', 1);
		printN(sim6, 16);
		printN(' ', 1);
		std::cout << std::endl << std::endl;

		// Logo end
		auto list = server->getBanListIp();
		for (auto& it : list)
		{
			std::cout << it << std::endl;
		}
	}
	break;
	case Function::AddtoGroup:
	{

		int fid, gid;

		std::cout << "Which fid add: ";

		std::cin >> fid;

		std::cout << "At group: ";

		std::cin >> gid;

		if (server->addToGroup(gid, fid))
			std::cout << "Ok [ENTER] or [ESC]\n";
		else
			std::cout << "Bad fid or gid, try again [ENTER] or [ESC]\n";

	}
	break;
	case Function::NewGroup:
	{
		std::cout << "Group created, she gid is " << server->newGroup() << std::endl;
		std::cout << "Create new [ENTER] exit [ESC]\n";
	}
	break;
	case Function::ListGroup:
	{

		// Logo
		printN(' ', 5);
		std::cout << "Groups List";
		std::cout << std::endl;
		printN(' ', 1);
		printN(sim6, 16);
		printN(' ', 1);
		std::cout << std::endl << std::endl;

		auto list = server->getGroups();

		for (auto& it : list)
		{
			std::cout << "gid: " << it << "\tfids: ";
			auto list_fids = server->getGroupList(it);

			for (auto& fids : list_fids)
			{
				std::cout << fids << " ";
			}
			std::cout << std::endl;
		}
	}
	break;
	case Function::Refresh:
	{
		server->refreshOnline();
		std::cout << "Refreshed. Exit [ESC]\n";
	}
	break;
	case Function::Off:
	{
		is_exit->store(true);
	}
	break;
	default:

		break;
	}
}

void FManager::menuSetting()
{

	/////////////////////////////////////////////
	// AUTOMATIC garbage collector of childerns
	/////////////////////////////////////////////

	auto* lf0 = new LeafMenu("Logs", LeafMenu::Function::Logs, srv);

	auto* lf1 = new LeafMenu("Pause", LeafMenu::Function::Pause, srv);

	auto* comp1 = new CompositorMenu("Online");

	auto* lf11 = new LeafMenu("Online list", LeafMenu::Function::OnlineList, srv);
	auto* lf12 = new LeafMenu("Fid IP", LeafMenu::Function::FidIp, srv);

	auto* comp2 = new CompositorMenu("Bans");

	auto* lf21 = new LeafMenu("Ban IP", LeafMenu::Function::BanIp, srv);
	auto* lf22 = new LeafMenu("Unban IP", LeafMenu::Function::UnbanIp, srv);
	auto* lf23 = new LeafMenu("Ban List", LeafMenu::Function::BanList, srv);

	auto* comp3 = new CompositorMenu("Groups");
	auto* lf31 = new LeafMenu("Add to group", LeafMenu::Function::AddtoGroup, srv);
	auto* lf32 = new LeafMenu("New group", LeafMenu::Function::NewGroup, srv);
	auto* lf33 = new LeafMenu("List groups", LeafMenu::Function::ListGroup, srv);

	auto* lf2 = new LeafMenu("Refresh", LeafMenu::Function::Refresh, srv);
	auto* lf3 = new LeafMenu("Off", LeafMenu::Function::Off, srv);
	lf3->setExitCondition(&_exit_app);


	comp1->addChild(lf11);
	comp1->addChild(lf12);

	comp2->addChild(lf21);
	comp2->addChild(lf22);
	comp2->addChild(lf23);

	comp3->addChild(lf31);
	comp3->addChild(lf32);
	comp3->addChild(lf33);

	main_menu->addChild(lf0);
	main_menu->addChild(lf1);
	main_menu->addChild(comp1);
	main_menu->addChild(comp2);
	main_menu->addChild(comp3);
	main_menu->addChild(lf2);
	main_menu->addChild(lf3);

	////////////////////////////////////////////////
	// you must delete or automatic clean only root
	////////////////////////////////////////////////

}

FManager::FManager(const std::string& ip, int port) :
	srv(new FServer <MainPocket>(ip, port)),
	main_menu(std::make_unique<CompositorMenu>("Main"))
{
	srv->start();
	current_item = main_menu.get();
}

FManager::~FManager()
{
	delete srv;

	if (run.joinable())
		run.join();
}

int FManager::exec()
{
	menuSetting();

	run = std::move(std::thread([&] {
		realisationOfCLogic();
		}
	));

	_key_viewer();

	return 0;
}

void FManager::_key_viewer()
{
	// realistation of your platform
	// keys of menu

	//Pattern brige on compile

	while (!_exit_app.load())
	{

		system("cls");

		current_item->draw();

		if (_exit_app.load())
			return;

		if (current_item->isPause())
		{
			_keyEscape();
			continue;
		}

		switch (getch())
		{
			//UP
		case 72: {  _keyUp(); }break;

			//DOWN
		case 80: {	_keyDown(); }break;

			//ENTER
		case 13: {  _keyEnter(); }break;

			//ESCAPE
		case 27: {  _keyEscape(); }break;
		}

	std::cout << std::endl << "ENTER - Refresh/Entry | ESC - Return\n";

}


void FManager::_keyUp()
{
	current_item->Up();
}


void FManager::_keyDown()
{
	current_item->Down();
}


void FManager::_keyEnter()
{
	if (!current_item->isLeaf())
	{
		current_item = current_item->In();
	}
}


void FManager::_keyEscape()
{

	if (current_item->isLog())
		if (log_active)
		{
			log_active = false;
			srv->switchLog();
		}


	if (main_menu.get() != current_item)
		current_item = current_item->Out();
}