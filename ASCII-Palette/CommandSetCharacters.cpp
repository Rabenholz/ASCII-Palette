#include "StdAfx.h"
#include "CommandSetCharacters.h"
#include "DrawingWindow.h"


CommandSetCharacters::CommandSetCharacters(const SFMLCursesChar& character, const sf::Vector2i& position)
	:m_characters(),
	 m_oldCharacters(),
	 m_position(position),
	 m_size(1,1)
{
	m_characters.push_back(std::vector<SFMLCursesChar>());
	m_characters.at(0).push_back(character);
}

CommandSetCharacters::CommandSetCharacters(const SFMLCursesCharRect& characterRect, const sf::Vector2i position)
	:m_characters(characterRect),
	 m_oldCharacters(),
	 m_position(position),
	 m_size()
{
	m_size.x = characterRect.size();
	if(characterRect.size() > 0)
		m_size.y = characterRect.at(0).size();
}

CommandSetCharacters::~CommandSetCharacters(void)
{
}


void CommandSetCharacters::execute(DrawingWindow& drawingWindow)
{
	m_oldCharacters = drawingWindow.copyCharactersInRect(m_position, m_size);
	drawingWindow.setCharactersInRect(m_characters, m_position);
}

void CommandSetCharacters::undo(DrawingWindow& drawingWindow)
{
	drawingWindow.setCharactersInRect(m_oldCharacters, m_position);
}

std::string CommandSetCharacters::getText()
{
	std::string str("Set Character");
	if(m_size.x > 1 || m_size.y > 1)
		str += "s";
	return str;
}