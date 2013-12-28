#pragma once
#include "CanvasCommand.h"
#include <vector>
#include "SFMLCursesChar.h"

class CommandSetCharacters :
	public CanvasCommand
{
public:
	CommandSetCharacters(const SFMLCursesChar& character, const sf::Vector2i& position);
	CommandSetCharacters(const SFMLCursesCharRect& characterRect, const sf::Vector2i position);
	virtual ~CommandSetCharacters(void);

	virtual void execute(DrawingWindow& drawingWindow);
	virtual void undo( DrawingWindow& drawingWindow);
	virtual std::string getText();

private:
	SFMLCursesCharRect m_characters;
	SFMLCursesCharRect m_oldCharacters;
	sf::Vector2i m_position;
	sf::Vector2i m_size;
};

