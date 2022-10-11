#include "Tasks.hpp"

using namespace std::chrono_literals;

///////////////
// TASK
///////////////

Task::Task()
{
	_state.store(new Free(this));
}

bool Task::start()
{
	return _state.load()->start();
}

bool Task::stop()
{
	return _state.load()->stop();
}

bool Task::setRange(int range)
{
	return _state.load()->setRange(range);
}

StatusTask Task::getStatus()
{
	return _state.load()->getStatus();
}

std::optional<float> Task::getResult()
{
	return _state.load()->getResult();
}

void Task::_process()
{
	// 10s - 20s
	int rand_time_working = rand() % 10000 + 10000;

	int out = 0; // some work

	//error event 10% chance
	int error_chance = rand() % 10;

	if (!error_chance)
	{
		_state.store(new Error(this));
			return;
	}

	_is_working.store(true);

	while (_is_working.load() && rand_time_working--)
	{
		out += rand() % 2;
		std::this_thread::sleep_for(1ms);
	}

	if (!_is_working.load())
		return;

	out /= 10;

	result.store(out);

	_is_working.store(false);

	_state.store(new GetResult(this));

}

void Task::SetState(State* state)
{
	if (_state.load())
		delete _state.load();

	_state.store(state);
}


///////////////
// FREE
///////////////

bool Free::start()
{
	task->run = std::thread([&]
		{
			task->_process();
		});

	task->SetState(new Working(task));

	return true;
}

bool Free::stop()
{
	return false;
}

std::optional<float> Free::getResult()
{
	return std::nullopt;
}

///////////////
// WORKING
///////////////

bool Working::start()
{
	return false;
}

bool Working::stop()
{
	task->_is_working.store(false);

	task->run.join();

	task->SetState(new Free(task));

	return true;
}

std::optional<float> Working::getResult()
{
	return std::nullopt;
}


///////////////
// ERROR
///////////////

bool Error::start()
{
	return false;
}

bool Error::stop()
{
	return false;
}

std::optional<float> Error::getResult()
{
	return std::nullopt;
}

///////////////
// GETRESULT
///////////////

bool GetResult::start()
{
	return false;
}

bool GetResult::stop()
{
	return false;
}

std::optional<float> GetResult::getResult()
{

	task->SetState(new Free(task));

	return std::optional<float>(task->result.load());
}