#include "FClient.hpp"
#include "MainPocket.hpp"
#include <ctime>

using fec = ReciverSingle<MainPocket>::f_error;

int main()
{

    int start = clock();

    FClient<MainPocket> cl("188.168.25.28",21112);

    cl.connect();

    int sum = 0;

    std::pair <MainPocket, fec> pocket_recv;


    for (int i = 0; i < 1; i++)
    {
        cl << MainPocket{i};
       

        if (!cl.isConnected())
            break;

        cl >> pocket_recv;

        auto& [pocket, err] = pocket_recv;

        if(err == fec::none)
            sum += pocket.n;
    }
    std::cout << sum<<std::endl;

    int stop = clock();

    std::cout <<"time: "<< (stop - start) / 1000.0 << std::endl;

    system("pause");

}