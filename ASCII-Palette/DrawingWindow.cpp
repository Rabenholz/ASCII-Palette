#include "StdAfx.h"
#include "DrawingWindow.h"


DrawingWindow::DrawingWindow(const sf::Window& window, const sf::Vector2i& lCursesSize)
	:SFMLGUIElement(window),
	m_cursesWindow(window, lCursesSize),
	m_outline(sf::Vector2f(m_cursesWindow.getLocalBounds().width,m_cursesWindow.getLocalBounds().height)),
	m_cursorPosition(0,0),
	m_cursorSprite(), m_cursorBackRect()
{	
	m_cursesWindow.clearTiles(" ",sf::Color::White, sf::Color::Black);

	sf::Sprite cursorSprite(SpriteManager::getInstance().getSprite("CursesA_ASCII_"));
	cursorSprite.setColor(sf::Color(255,255,255,255));
	sf::Sprite blinkSprite(TextureManager::getInstance().getTexture("Rectangle"));
	blinkSprite.setColor(sf::Color(255,255,255,255));

	m_cursorSprite.pushFrame(cursorSprite);
	m_cursorSprite.pushFrame(blinkSprite);
	m_cursorSprite.setFramesPerSecond(1);
	m_cursorSprite.Play();

	blinkSprite.setColor(sf::Color::Transparent);
	m_cursorBackRect.pushFrame(cursorSprite);
	blinkSprite.setColor(sf::Color(255,255,255,255));
	m_cursorBackRect.pushFrame(blinkSprite);
	m_cursorBackRect.setFramesPerSecond(1);
	m_cursorBackRect.Play();

	m_outline.setOutlineColor(sf::Color::White);
	m_outline.setOutlineThickness(2.0f);

	addMouseLeftClickedFunction(std::make_shared<TFunctor<DrawingWindow>>(this,&DrawingWindow::onLeftClick));
}


DrawingWindow::~DrawingWindow(void)
{
}


void DrawingWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_outline, states);
	target.draw(m_cursesWindow, states);
	target.draw(m_cursorBackRect, states);
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
	updateCursorSprite();
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
	updateCursorSprite();
	m_cursorSprite.setPosition(8.0f*static_cast<float>(position.y), 12.0f*static_cast<float>(position.x));
	m_cursorSprite.Reset();
	m_cursorSprite.Play();
	m_cursorBackRect.setPosition(8.0f*static_cast<float>(position.y), 12.0f*static_cast<float>(position.x));
	m_cursorBackRect.Reset();
	m_cursorBackRect.Play();
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

SFMLCursesWindow& DrawingWindow::getCursesWindow()
{
	return m_cursesWindow;
}

void DrawingWindow::onLeftClick()
{
	sf::Vector2i mousePosition = getLocalPoint(sf::Mouse::getPosition(m_window));
	moveCursorToPosition(sf::Vector2i(mousePosition.y/12,mousePosition.x/8));
}

void DrawingWindow::updateCursorSprite()
{
	const SFMLCursesChar& character = m_cursesWindow.getTile(m_cursorPosition);
	sf::Sprite cursorSprite = character.getCharSprite();
	sf::Color charColor = character.getCharColor();
	charColor.r = 255 - charColor.r; 
	charColor.g = 255 - charColor.g;
	charColor.b = 255 - charColor.b;
	cursorSprite.setColor(charColor);
	m_cursorSprite.replaceFrame(cursorSprite, 1);
	sf::Sprite backSprite = character.getBackRect();
	sf::Color backColor = character.getBackgroundColor();
	backColor.r = 255 - backColor.r; 
	backColor.g = 255 - backColor.g;
	backColor.b = 255 - backColor.b;
	sf::Sprite underscoreSprite = m_cursorSprite.getFrameSprite(0);
	underscoreSprite.setColor(backColor);
	m_cursorSprite.replaceFrame(underscoreSprite, 0);
	backSprite.setColor(backColor);
	m_cursorBackRect.replaceFrame(backSprite, 1);
	
}