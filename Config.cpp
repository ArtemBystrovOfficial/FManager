#include "FManager.hpp"
/////////////////////
// You're code there
/////////////////////

using Out = _Out<MainPocket>;

void FManager::realisationOfCLogic() { 
	
	srv->start();

	std::pair <MainPocket, int> data;

	std::map  < std::string, std::string > data_u;

	std::map  <int, bool> is_login_u;

	auto online_group = srv->newGroup();

	while (!_exit_app.load()) {

		*srv >> data;

		auto& pocket = data.first;
		auto fid = data.second;

		switch (pocket.command)
		{
		case(MainPocket::Command::Register):
		{
			auto is_be = data_u.find(pocket.login);
			if (is_be == data_u.end())
			{
				data_u[pocket.login] = pocket.password;
				*srv << Out{ MainPocket(MainPocket::Command::Ok,"","",""),FType::FID, fid };
				break;
			}

			*srv << Out{ MainPocket(MainPocket::Command::Error,"Login exsist","",""),FType::FID, fid };

		} break;
		case(MainPocket::Command::Login):
		{
			auto password = data_u.find(pocket.login);
			if (password != data_u.end())
			{
				if (password->second == pocket.password)
				{
					is_login_u[fid] = true;
					srv->addToGroup(online_group, fid);
					*srv << Out{ MainPocket(MainPocket::Command::Ok,"","",""),FType::FID, fid };
					break;
				}
			}

			*srv << Out{ MainPocket{MainPocket::Command::Error,"uncorrect login or password","",""},FType::FID, fid };

		} break;
		case(MainPocket::Command::Send_All):
		{
			auto connect = is_login_u.find(fid);
			if (connect != is_login_u.end())
			{
				if (connect->second)
				{
					*srv << Out{ MainPocket(MainPocket::Command::Msg,pocket.msg,"",""),FType::ALL, fid };

					break;
				}
			}

			*srv << Out{ MainPocket{MainPocket::Command::Error,"You don't auntification","",""},FType::FID, fid };

		} break;
		
		}
	}

}
