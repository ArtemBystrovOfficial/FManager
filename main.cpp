#include "FManager.hpp"

void printHelp()
{
	std::cerr << "FMan -i [ip] -p [port]\n";
}

int main(int argc, char ** argv)
{

	std::string ip;
	int port = -1;

	for ( int i = 1; i!=argc; ++i )
	{
		
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "-help"))
		{
			printHelp();
			exit(0);
		}
		else
		if (!strcmp(argv[i],"-i") || !strcmp(argv[i],"-ip"))
		{
			if (i != argc - 1)
			{
				if (!strcmp(argv[i+1], "-i") || !strcmp(argv[i+1], "-ip"))
				{
					std::cerr << "FManager: -ip [argument]\n";
					exit(0);
				}
				else
					ip = argv[i + 1];
			}
			else
			{
					std::cerr << "FManager: -ip [unknown argument]\n";
					exit(0);
			}			
		}
		else
		if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "-port"))
		{
			if (i != argc - 1)
			{
				if (!strcmp(argv[i+1], "-p") || !strcmp(argv[i+1], "-port"))
				{
					std::cerr << "FManager: -ip [argument]\n";
					exit(0);
				}
				else
					port = std::atoi(argv[i + 1]);
			}
			else
			{
				std::cerr << "FManager: -port [argument]\n";
				exit(0);
			}
		}

	}

	// extra safe
	if (ip.size() < 7 || ip.size() > 15 || port == -1 || std::count(ip.begin(), ip.end(), '.')!=3 )
	{
		printHelp();
		exit(0);
	}

	FManager manage(ip, port);
	return manage.exec();
}
