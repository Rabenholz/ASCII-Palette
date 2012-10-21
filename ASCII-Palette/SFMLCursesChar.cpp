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
void SFMLCursesChar::setCharacter(std::string character)
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

std::ostream& operator<<(std::ostream& os, const SFMLCursesChar& cursesChar)
{
	//character char r-g-b-a  back r-g-b-a \n
	sf::Color charColor(cursesChar.getCharColor());
	sf::Color backgroundColor(cursesChar.getBackgroundColor());
	os<<cursesChar.m_character<<" ";
	os<<charColor.r<<" "<<charColor.g<<" "<<charColor.b<<" "<<charColor.a<<" ";
	os<<backgroundColor.r<<" "<<backgroundColor.g<<" "<<backgroundColor.b<<" "<<backgroundColor.a<<"\n";
	return os;
}

std::istream& operator>>(std::istream& is, SFMLCursesChar& cursesChar)
{
	if(is.good())
	{
		std::string character;
		sf::Color charColor;
		sf::Color backgroundColor;
		is>>character;
		is>>charColor.r>>charColor.g>>charColor.b>>charColor.a;
		is>>backgroundColor.r>>backgroundColor.g>>backgroundColor.b>>backgroundColor.a;
		cursesChar.setCharacter(character);
		cursesChar.setCharColor(charColor);
		cursesChar.setBackgroundColor(backgroundColor);
	}
	return is;
}