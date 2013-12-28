#include "StdAfx.h"
#include "CommandHistoryWindow.h"
#include "CanvasCommand.h"

CommandHistoryWindow::CommandHistoryWindow(const sf::Window& window, DrawingWindow& drawingWindow)
	:SFMLGUIElement(window),
	m_commandHistory(drawingWindow),
	m_commandList(),
	m_iterator(m_commandList.end()),
	m_entrySize(150, 30),
	m_rectangle(sf::Vector2f(m_entrySize.x, m_entrySize.y * 5.0f)),
	m_selectedRectangle(m_entrySize),
	m_normalRectangle(m_entrySize),
	m_dullRectangle(m_entrySize)
{
	m_rectangle.setFillColor(sf::Color(200,200,200));
	m_rectangle.setOutlineThickness(1.f);
	m_rectangle.setOutlineColor(sf::Color::White);

	m_selectedRectangle.setFillColor(sf::Color::Yellow);
	m_selectedRectangle.setOutlineThickness(1.f);
	m_selectedRectangle.setOutlineColor(sf::Color::White);

	m_normalRectangle.setFillColor(sf::Color(50,50,50));
	m_normalRectangle.setOutlineThickness(1.f);
	m_normalRectangle.setOutlineColor(sf::Color::White);

	m_dullRectangle.setFillColor(sf::Color::Black);
	m_dullRectangle.setOutlineThickness(1.f);
	m_dullRectangle.setOutlineColor(sf::Color::White);
}


CommandHistoryWindow::~CommandHistoryWindow(void)
{
}

void CommandHistoryWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	bool drawDull = false;
	size_t index = 0;

	states.transform *= getTransform();
	target.draw(m_rectangle, states);

	for(std::list<CommandHistoryEntry>::const_iterator entryIt(m_commandList.begin()); entryIt != m_commandList.end(); entryIt++)
	{
		if(entryIt == m_iterator)
		{
			target.draw(m_selectedRectangle, states);
			drawDull = true;
		}
		else if(drawDull)
		{
			target.draw(m_dullRectangle, states);
		}
		else
		{
			target.draw(m_normalRectangle, states);
		}
		index++;
		states.transform.translate(0, m_entrySize.y);
		//target.draw(entryIt->m_rectangle, states);
	}
}

sf::FloatRect CommandHistoryWindow::getLocalBounds(void) const
{
	return m_rectangle.getLocalBounds();
}

sf::FloatRect CommandHistoryWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_rectangle.getGlobalBounds());
}

void CommandHistoryWindow::executeAndAddCommand(std::unique_ptr<CanvasCommand> command)
{
	if(m_commandList.size() > 0)
	{
		std::list<CommandHistoryEntry>::iterator nextIt = m_iterator;
		nextIt++;
		m_commandList.erase(nextIt, m_commandList.end());
	}
	CommandHistoryEntry commandEntry;
	commandEntry.m_text = command->getText();
	m_commandList.push_back(commandEntry);
	m_iterator = --m_commandList.end();

	m_commandHistory.executeAndAddCommand(std::move(command));

	while(m_commandList.size() > m_commandHistory.getMaxCommands())
	{
		m_commandList.pop_front();
	}
}

void CommandHistoryWindow::moveIndex(int delta)
{
	m_commandHistory.moveIndex(delta);

	if(delta == 0 || m_commandList.size() == 0)
		return;

	while(delta < 0 && m_iterator != m_commandList.begin())
	{
		m_iterator--;
		delta++;
	}

	while(delta > 0 && m_iterator != --m_commandList.end())
	{
		m_iterator++;
		delta--;
	}
}
