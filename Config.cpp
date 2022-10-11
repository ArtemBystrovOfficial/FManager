#include "FManager.hpp"

#include "Tasks.hpp"

// 1 start with srv->start();
// 2 use while (!_exit_app.load()) {} for loop recv
// 3 using Out for <<

using Out = _Out<MainPocket>;

// max 8 channels
const int N = 8;

bool checkTasksSize(int n)
{
	return ( n >= 0 ) && ( n < N );
}

void FManager::realisationOfCLogic() { 
	
	srv->start();

	std::pair <MainPocket, int > pocket_recv;

	std::vector <Task> tasks;

	using cs = MainPocket::codeState;

	while (!_exit_app.load()) {

		*srv >> pocket_recv;

		auto& [pocket, fid] = pocket_recv;
		
		if (checkTasksSize(pocket.channel))
		{

			switch (pocket.func)
			{
				case MainPocket::function::getResult:
				{

					auto out = tasks[pocket.channel].getResult();

					if (out.has_value())
					{
						pocket.result = out.value();
						pocket.isOk = true;
					}
					else
						pocket.isOk = false;


				}
				break;
				case MainPocket::function::getStatus:
				{
					switch (tasks[pocket.channel].getStatus())
					{
						case StatusTask::Free:  pocket.code = cs::idle_state; break;
						case StatusTask::Error:  pocket.code = cs::error_state; break;
						case StatusTask::GetResult:  pocket.code = cs::busy_state; break;
						case StatusTask::Working:  pocket.code = cs::measure_state; break;
					}
					pocket.isOk = true;
				}
				break;
				case MainPocket::function::setRange:
				{
					pocket.isOk = tasks[pocket.channel].setRange(pocket.range);
				}
				break;
				case MainPocket::function::startMeasure:
				{
					pocket.isOk = tasks[pocket.channel].start();
				}
				break;
				case MainPocket::function::stopMeasure:
				{
					pocket.isOk = tasks[pocket.channel].stop();
				}
				break;
			}
		}
		else
			pocket.isOk = false;

		*srv << Out{ pocket , FType::FID, fid };

	}

}
