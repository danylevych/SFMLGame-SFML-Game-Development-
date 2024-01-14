#include "ParalelTask.h"

ParalelTask::ParalelTask()
	: thread(&ParalelTask::RunTask, this)
	, isFinished(false)
{	}

void ParalelTask::Execute()
{
	isFinished = false;
	elipsedTime.restart();
	thread.launch();
}

float ParalelTask::GetCompletion()
{
	sf::Lock _(mutex);
	
	return elipsedTime.getElapsedTime().asMicroseconds() / 10.f;
}

bool ParalelTask::IsFinished()
{
	sf::Lock _(mutex);

	return isFinished;
}

void ParalelTask::RunTask()
{
	// Dummy task - stall 10 seconds.
	bool ended = false;
	while (!ended)
	{
		sf::Lock _(mutex);
		if (elipsedTime.getElapsedTime().asSeconds() >= 10.f)
		{
			ended = true;
		}
	}

	{
		sf::Lock _(mutex);
		isFinished = true;
	}
}