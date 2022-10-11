#include "FManager.hpp"

#include "Tasks.hpp"

// 1 start with srv->start();
// 2 use while (!_exit_app.load()) {} for loop recv
// 3 using Out for <<

using Out = _Out<MainPocket>;

void FManager::realisationOfCLogic() { 
	
	srv->start();

	std::pair <MainPocket, int > pocket_recv;

	while (!_exit_app.load()) {

		*srv >> pocket_recv;

		auto& [pocket, fid] = pocket_recv;

		pocket.n *= 2;

		*srv << Out{ pocket , FType::FID, fid };

	}

}
