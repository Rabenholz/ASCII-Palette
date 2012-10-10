#include "StdAfx.h"
#include "SFMLGUIElement.h"


SFMLGUIElement::SFMLGUIElement(const sf::Window& window)
	:sf::Drawable(), sf::Transformable(),
	 m_leftPressed(false), m_rightPressed(false), m_middlePressed(false),
	 m_window(window),
	 m_MouseLeftPressedfunc(nullptr), m_MouseLeftReleasedfunc(nullptr),
	 m_MouseRightPressedfunc(nullptr), m_MouseRightReleasedfunc(nullptr),
	 m_MouseMiddlePressedfunc(nullptr), m_MouseMiddleReleasedfunc(nullptr),
	 m_MouseLeftClickedfunc(nullptr), m_MouseRightClickedfunc(nullptr), m_MouseMiddleClickedfunc(nullptr)
{
}

SFMLGUIElement::~SFMLGUIElement(void)
{
}

void SFMLGUIElement::update()
{
	//empty
}

sf::Vector2f SFMLGUIElement::getLocalPoint(float x, float y) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(sf::Vector2f(x,y)))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2f(x - getPosition().x, y - getPosition().y);
}

sf::Vector2f SFMLGUIElement::getLocalPoint(const sf::Vector2f& point) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(point))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2f(point.x - getPosition().x, point.y - getPosition().y);
}
sf::Vector2i SFMLGUIElement::getLocalPoint(int x, int y) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(sf::Vector2f(static_cast<float>(x),static_cast<float>(y))))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2i(x - static_cast<int>(getPosition().x), y - static_cast<int>(getPosition().y));
}
sf::Vector2i SFMLGUIElement::getLocalPoint(const sf::Vector2i& point) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(sf::Vector2f(point)))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2i(point.x - static_cast<int>(getPosition().x), point.y - static_cast<int>(getPosition().y));
}

void SFMLGUIElement::OnMouseLeftPressed()
{
	m_leftPressed = true;
	if(m_MouseLeftPressedfunc != nullptr)
		(*m_MouseLeftPressedfunc)();

}

void SFMLGUIElement::OnMouseLeftReleased()
{
	if(m_leftPressed)
	{	
		if(m_MouseLeftClickedfunc != nullptr)
			(*m_MouseLeftClickedfunc)();
	}
	else if(m_MouseLeftReleasedfunc != nullptr)
		(*m_MouseLeftReleasedfunc)();
}

void SFMLGUIElement::OnMouseRightPressed()
{
	m_rightPressed = true;
	if(m_MouseRightPressedfunc != nullptr)
		(*m_MouseRightPressedfunc)();
}

void SFMLGUIElement::OnMouseRightReleased()
{
	if(m_rightPressed)
	{	
		if(m_MouseRightClickedfunc != nullptr)
			(*m_MouseRightClickedfunc)();
	}
	else if(m_MouseRightReleasedfunc != nullptr)
		(*m_MouseRightReleasedfunc)();
}

void SFMLGUIElement::OnMouseMiddlePressed()
{
	m_middlePressed = true;
	if(m_MouseMiddlePressedfunc != nullptr)
		(*m_MouseMiddlePressedfunc)();
}

void SFMLGUIElement::OnMouseMiddleReleased()
{
	if(m_middlePressed)
	{	
		if(m_MouseMiddleClickedfunc != nullptr)
			(*m_MouseMiddleClickedfunc)();
	}
	else if(m_MouseMiddleReleasedfunc != nullptr)
		(*m_MouseMiddleReleasedfunc)();
}

void SFMLGUIElement::OnMouseRollover()
{
	if(m_MouseRolloverfunc)
	{
		(*m_MouseRolloverfunc)();
	}
}

void SFMLGUIElement::OnGlobalMouseLeftReleased()
{
	m_leftPressed = false;
}

void SFMLGUIElement::OnGlobalMouseRightReleased()
{
	m_rightPressed = false;
}

void SFMLGUIElement::OnGlobalMouseMiddleReleased()
{
	m_middlePressed = false;
}
