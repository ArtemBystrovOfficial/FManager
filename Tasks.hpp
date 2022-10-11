#pragma once

#include <thread>
#include <optional>
#include <atomic>


// use Pattern State
enum class StatusTask
{
	Free,
	Working,
	Error,
	GetResult
};

class Task
{
	friend class State;
	friend class Free;
	friend class Working;
	friend class Error;
	friend class GetResult;

public:

	// implemintation of State * ( safe threading)

	Task();

	bool start();

	bool stop();

	bool setRange(int range);

	StatusTask getStatus();

	std::optional <float> getResult();
	
	~Task()
	{
		//safety work with row pointers
		if (_state.load())
			delete _state.load();

		_is_working.store(false);

		run.join();

	}

public:

	void _process();

	void SetState(State* state);

	std::atomic < State * > _state;

	float range;
	std::atomic <float> result;

	//thread procces

	std::thread run;
	std::atomic <bool> _is_working;

};

class State
{
public:

	State(Task * task) : task(task) {};

	virtual bool start() {};

	virtual bool stop() {};

	bool setRange(int range){
	
		float kof;

		switch (range)
		{
		case 0: kof = 0.000'001; break;
		case 1: kof = 0.001; break;
		case 2: kof = 1; break;
		case 3: kof = 1000; break;
		default: return false; break;
		}

		task->range = kof;

		return true;

	};

	virtual std::optional <float> getResult() {};

	StatusTask getStatus()
	{
		return status;
	}

protected:

	Task* task;
	StatusTask status;

};

class Free : public State
{
public:

	Free(Task* task) : State(task){
		status = StatusTask::Free;
	};

	bool start() override;

	bool stop() override;

	std::optional <float> getResult() override;

private:
};

class Working : public State
{
public:

	Working(Task* task) : State(task){
		status = StatusTask::Working;
	};

	bool start() override;

	bool stop() override;

	std::optional <float> getResult() override;


private:

};

class Error : public State
{
public:

	Error(Task* task) : State(task) {
		status = StatusTask::Error;
	};

	bool start() override;

	bool stop() override;

	std::optional <float> getResult() override;


private:

};

class GetResult : public State
{
public:

	GetResult(Task* task) : State(task) {
		status = StatusTask::GetResult;
	};

	bool start() override;

	bool stop() override;

	std::optional <float> getResult() override;


private:

};