#pragma once
#include "SFML-Template\SFMLGUIElement.h"
#include "CommandHistory.h"

struct CommandHistoryEntry
{
	//id
	std::string m_text;
};

class CommandHistoryWindow : public SFMLGUIElement
{
public:
	CommandHistoryWindow(const sf::Window& window, DrawingWindow& drawingWindow);
	virtual ~CommandHistoryWindow(void);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void executeAndAddCommand(std::unique_ptr<CanvasCommand> command);
	void moveIndex(int delta); //negative = backwards in history

protected:
	CommandHistory m_commandHistory;
	std::list<CommandHistoryEntry> m_commandList;
	std::list<CommandHistoryEntry>::iterator m_iterator;
	sf::Vector2f m_entrySize;

	sf::RectangleShape m_selectedRectangle;
	sf::RectangleShape m_normalRectangle;
	sf::RectangleShape m_dullRectangle;

	sf::RectangleShape m_rectangle;
};

