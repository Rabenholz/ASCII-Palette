#include "StdAfx.h"
#include "SFMLCursesChar.h"


SFMLCursesChar::SFMLCursesChar(const sf::Window& window, std::string character)
	:SFMLGUIElement(window),
	 m_character(character),
	 m_backRect(sf::Vector2f(8.0,12.0)), 
	 m_charSprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII")+character))
{
	m_backRect.setFillColor(sf::Color::Black);
	m_charSprite.setColor(sf::Color::White);
}


SFMLCursesChar::SFMLCursesChar(const sf::Window& window, std::string character, const sf::Color& textColor, const sf::Color& backgroundColor)
	:SFMLGUIElement(window),
	 m_character(character),
	 m_backRect(sf::Vector2f(8.0,12.0)), m_charSprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII")+character))
{
	m_backRect.setFillColor(backgroundColor);
	m_charSprite.setColor(textColor);
}


SFMLCursesChar::~SFMLCursesChar(void)
{
}

void SFMLCursesChar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_backRect, states);
	target.draw(m_charSprite, states);
}
sf::FloatRect SFMLCursesChar::getLocalBounds() const
{
	return m_backRect.getLocalBounds();
}
sf::FloatRect SFMLCursesChar::getGlobalBounds() const
{
	return getTransform().transformRect(m_backRect.getGlobalBounds());
}

void SFMLCursesChar::setCharColor(const sf::Color& color)
{
	m_charSprite.setColor(color);
}
void SFMLCursesChar::setBackgroundColor(const sf::Color& color)
{
	m_backRect.setFillColor(color);
}
void SFMLCursesChar::setCharacter(char character)
{
	m_character = character;
	sf::Color charColor = m_charSprite.getColor();
	m_charSprite = sf::Sprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII")+character));
	m_charSprite.setColor(charColor);
}
const sf::Color& SFMLCursesChar::getCharColor() const
{
	return m_charSprite.getColor();
}
const sf::Color& SFMLCursesChar::getBackgroundColor() const
{
	return m_backRect.getFillColor();
}
std::string SFMLCursesChar::getCharacter() const
{
	return m_character;
}
