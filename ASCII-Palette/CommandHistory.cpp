#include "StdAfx.h"
#include "CommandHistory.h"
#include "CanvasCommand.h"


CommandHistory::CommandHistory(DrawingWindow& drawingWindow)
	:m_maxCommands(64),
	m_commands(),
	m_iterator(m_commands.end()),
	m_drawingWindow(&drawingWindow)
{
}


CommandHistory::~CommandHistory(void)
{
}

void CommandHistory::executeAndAddCommand(std::unique_ptr<CanvasCommand> command)
{
	if(m_commands.size() > 0)
	{
		std::list<std::unique_ptr<CanvasCommand>>::iterator nextIt = m_iterator;
		nextIt++;
		m_commands.erase(nextIt, m_commands.end());
	}
	command->execute(*m_drawingWindow);
	m_commands.push_back(std::move(command));
	m_iterator = m_commands.end();
	m_iterator--;
	while(m_commands.size() > m_maxCommands)
	{
		m_commands.pop_front();
	}
}
	
void CommandHistory::moveIndex(int delta)
{
	if(delta == 0 || m_commands.size() == 0)
		return;

	while(delta < 0 && m_iterator != m_commands.begin())
	{
		(*m_iterator)->undo(*m_drawingWindow);
		m_iterator--;
		delta++;
	}

	while(delta > 0 && m_iterator != --m_commands.end())
	{
		m_iterator++;
		delta--;
		(*m_iterator)->execute(*m_drawingWindow);
	}
}

size_t CommandHistory::getMaxCommands() const
{
	return m_maxCommands;
}