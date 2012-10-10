#include "StdAfx.h"
#include "SFMLColorPalette.h"


SFMLColorPalette::SFMLColorPalette(const sf::Window& window, const sf::Image& colorImage, const sf::Texture& colorTexture)
	:SFMLGUIElement(window),
	 m_colorImage(colorImage), m_display(colorTexture), m_colorMagnify(sf::Vector2f(50.0f,50.0f))
{
	m_colorMagnify.setOutlineThickness(5.0f);
	m_colorMagnify.setOutlineColor(sf::Color::Black);
	setMouseRolloverFunction(std::make_shared<TFunctor<SFMLColorPalette>>(this, &SFMLColorPalette::updateColorMagnify));
	setMouseLeftClickedFunction(std::make_shared<TFunctor<SFMLColorPalette>>(this, &SFMLColorPalette::selectColorAtMouse));
}


SFMLColorPalette::~SFMLColorPalette(void)
{
}

void SFMLColorPalette::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_display, states);
	//only for circular, probably should mitigate this to a subclass or something
	float radius = getLocalBounds().width/2.0f;
	sf::Vector2f center(getGlobalBounds().left + radius, getGlobalBounds().top + radius);
	if(std::pow(radius,2) > std::pow(sf::Mouse::getPosition(m_window).x - center.x,2) + std::pow(sf::Mouse::getPosition(m_window).y - center.y,2))
	{
		target.draw(m_colorMagnify, states);
	}
	
}

sf::FloatRect SFMLColorPalette::getLocalBounds() const
{
	return m_display.getLocalBounds();
}
sf::FloatRect SFMLColorPalette::getGlobalBounds() const
{
	return getTransform().transformRect(m_display.getGlobalBounds());
}

sf::Color SFMLColorPalette::getSelectedColor() const
{
	return m_selectedColor;
}

void SFMLColorPalette::updateColorMagnify()
{
	sf::Vector2f localMouseFloat(getLocalPoint(sf::Mouse::getPosition(m_window)));
	sf::Vector2i localMouse(getLocalPoint(sf::Mouse::getPosition(m_window)));
	m_colorMagnify.setPosition(localMouseFloat.x - m_colorMagnify.getLocalBounds().width - 5.0f, 
		localMouseFloat.y - m_colorMagnify.getLocalBounds().height - 5.0f);
	m_colorMagnify.setFillColor(m_colorImage.getPixel(localMouse.x, localMouse.y));
}

void SFMLColorPalette::selectColorAtMouse()
{
	sf::Vector2i localMouse(getLocalPoint(sf::Mouse::getPosition(m_window)));
	m_selectedColor = m_colorImage.getPixel(localMouse.x, localMouse.y);
}