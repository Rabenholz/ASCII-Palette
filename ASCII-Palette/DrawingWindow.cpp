#include "StdAfx.h"
#include "DrawingWindow.h"


DrawingWindow::DrawingWindow(const sf::Window& window, const sf::Vector2i& lCursesSize)
	:SFMLGUIElement(window),
	m_cursesWindow(window, lCursesSize),
	m_cursorPosition(0,0),
	m_cursorSprite()
{
	sf::Sprite cursorSprite(SpriteManager::getInstance().getSprite("CursesA_ASCII_"));
	cursorSprite.setColor(sf::Color(sf::Uint8(200),sf::Uint8(200),sf::Uint8(200),sf::Uint8(255)));
	m_cursorSprite.pushFrame(cursorSprite);
	sf::Sprite blinkSprite(SpriteManager::getInstance().getSprite("CursesA_ASCII "));
	blinkSprite.setColor(sf::Color::Transparent);
	m_cursorSprite.pushFrame(blinkSprite);
	m_cursesWindow.clearTiles(".",sf::Color::White, sf::Color::Black);
	m_cursorSprite.setFramesPerSecond(1);
	m_cursorSprite.Play();
}


DrawingWindow::~DrawingWindow(void)
{
}


void DrawingWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_cursesWindow, states);
	target.draw(m_cursorSprite, states);
	
}
sf::FloatRect DrawingWindow::getLocalBounds(void) const
{
	return m_cursesWindow.getLocalBounds();
}
sf::FloatRect DrawingWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_cursesWindow.getGlobalBounds());
}

void DrawingWindow::setCursorCharacter(const SFMLCursesChar& character)
{
	m_cursesWindow.setTile(character, m_cursorPosition);
}
void DrawingWindow::moveCursorToPosition(sf::Vector2i position)
{
	if(position.x < 0)
		position.x = m_cursesWindow.getCursesSize().x - 1;
	else if(position.x > m_cursesWindow.getCursesSize().x - 1)
		position.x = 0;
	if(position.y < 0)
		position.y = m_cursesWindow.getCursesSize().y - 1;
	else if(position.y > m_cursesWindow.getCursesSize().y - 1)
		position.y = 0;

	m_cursorPosition = position;
	m_cursorSprite.setPosition(8.0f*static_cast<float>(position.y), 12.0f*static_cast<float>(position.x));
	m_cursorSprite.Reset();
	m_cursorSprite.Play();
}
void DrawingWindow::moveCursorUp()
{
	moveCursorToPosition(sf::Vector2i(m_cursorPosition.x-1, m_cursorPosition.y));
}
void DrawingWindow::moveCursorDown()
{
	moveCursorToPosition(sf::Vector2i(m_cursorPosition.x+1, m_cursorPosition.y));
}
void DrawingWindow::moveCursorLeft()
{
	moveCursorToPosition(sf::Vector2i(m_cursorPosition.x, m_cursorPosition.y-1));
}
void DrawingWindow::moveCursorRight()
{
	moveCursorToPosition(sf::Vector2i(m_cursorPosition.x, m_cursorPosition.y+1));
}