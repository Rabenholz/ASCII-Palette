#include "StdAfx.h"
#include "AltCharsWindow.h"


AltCharsWindow::AltCharsWindow(const sf::Window& window)
:SFMLGUIElement(window),
	m_cursesWindow(window, sf::Vector2i(10,16)),
	m_outline(sf::Vector2f(m_cursesWindow.getLocalBounds().width,m_cursesWindow.getLocalBounds().height)),
	m_charMagnify(m_window, "a", sf::Color::White, sf::Color(1,1,1,255))
{
	unsigned char k = 1;
	for(int i = 0; i<m_cursesWindow.getCursesSize().x; i++)
	{
		for(int j = 0; j<m_cursesWindow.getCursesSize().y; j++)
		{
			if(k == 32)
				k = 127;
			else if(k == 255)
			{
				break;
			}
			std::string str("");
			str += k;
			m_cursesWindow.setTile(SFMLCursesChar(m_window,str), sf::Vector2i(i,j));
			k++;
		}
		if(k == 255)
			break;
	}

	m_outline.setOutlineColor(sf::Color::White);
	m_outline.setOutlineThickness(2.0f);

	m_charMagnify.setScale(4.0f, 4.0f);
	addMouseLeftClickedFunction(std::make_shared<TFunctor<AltCharsWindow>>(this,&AltCharsWindow::onLeftClick));
	addMouseRolloverFunction(std::make_shared<TFunctor<AltCharsWindow>>(this,&AltCharsWindow::updateCharMagnify));
}


AltCharsWindow::~AltCharsWindow(void)
{
}

void AltCharsWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_outline, states);
	target.draw(m_cursesWindow, states);
	if(getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y)))
		target.draw(m_charMagnify, states);
}
sf::FloatRect AltCharsWindow::getLocalBounds(void) const
{
	return m_cursesWindow.getLocalBounds();
}
sf::FloatRect AltCharsWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_cursesWindow.getGlobalBounds());
}

void AltCharsWindow::onLeftClick()
{
}

void AltCharsWindow::updateCharMagnify()
{
	sf::Vector2f localMouseFloat(getLocalPoint(sf::Mouse::getPosition(m_window)));
	sf::Vector2i localMouse(getLocalPoint(sf::Mouse::getPosition(m_window)));
	m_charMagnify.setPosition(localMouseFloat.x - m_charMagnify.getLocalBounds().width*m_charMagnify.getScale().x - 5.0f, 
		localMouseFloat.y - m_charMagnify.getLocalBounds().height*m_charMagnify.getScale().y - 5.0f);

	m_charMagnify.setCharacter(m_cursesWindow.getTile(sf::Vector2i(localMouse.y/12,localMouse.x/8)).getCharacter());
}