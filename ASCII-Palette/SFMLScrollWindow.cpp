#include "StdAfx.h"
#include "SFMLScrollWindow.h"

const float SFMLScrollWindow::kScrollbarWidth = 15.0f;

SFMLScrollWindow::SFMLScrollWindow(const sf::Window& window, const sf::Vector2f& size)
	:SFMLGUIElement(window),
	 m_child(nullptr),
	 m_innerRect(size),
	 m_rectangle(sf::Vector2f(size.x + kScrollbarWidth, size.y)),
	 m_verticalScrollbarVisibility(true),
	 m_horizontalScrollbarVisibility(false)
{
	//testing
	m_rectangle.setFillColor(sf::Color::White);
	m_rectangle.setOutlineThickness(1.f);
	m_rectangle.setOutlineColor(sf::Color::Blue);
}


SFMLScrollWindow::~SFMLScrollWindow(void)
{
}

void SFMLScrollWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	//testing
	target.draw(m_rectangle, states);
	//
	if(m_child)
	{
		m_child->draw(target, states);
		//if(getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y)))
		//	target.draw(m_charMagnify, states);
	}
}

sf::FloatRect SFMLScrollWindow::getLocalBounds(void) const
{
	return m_rectangle.getGlobalBounds();
}

sf::FloatRect SFMLScrollWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_rectangle.getGlobalBounds());
}

void SFMLScrollWindow::setChild(SFMLGUIElement& child)
{
	m_child = &child;
}

SFMLGUIElement* SFMLScrollWindow::getChild() const
{
	return m_child;
}

void SFMLScrollWindow::setVerticalScrollbarVisibility(bool b)
{
	m_verticalScrollbarVisibility = b;

	m_rectangle.setSize(sf::Vector2f(m_innerRect.getSize().x + (kScrollbarWidth*m_verticalScrollbarVisibility), m_innerRect.getSize().y + (kScrollbarWidth*m_horizontalScrollbarVisibility)));
}

void SFMLScrollWindow::setHorizontalScrollbarVisibility(bool b)
{
	m_horizontalScrollbarVisibility = b;

	m_rectangle.setSize(sf::Vector2f(m_innerRect.getSize().x + (kScrollbarWidth*m_verticalScrollbarVisibility), m_innerRect.getSize().y + (kScrollbarWidth*m_horizontalScrollbarVisibility)));
}

bool SFMLScrollWindow::getVerticalScrollbarVisibility() const
{
	return m_verticalScrollbarVisibility;
}
bool SFMLScrollWindow::getHorizontalScrollbarVisibility() const
{
	return m_horizontalScrollbarVisibility;
}