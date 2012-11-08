#include "StdAfx.h"
#include "ColorSelector.h"


ColorSelector::ColorSelector(const sf::Window& window)
	:SFMLGUIElement(window),
	m_primaryRect(sf::Vector2f(40.0f, 40.0f)), m_secondaryRect(sf::Vector2f(40.0f, 40.0f)),
	m_bounds(sf::Vector2f(60.0f, 60.0f))
{
	m_primaryRect.setOutlineThickness(3.0f);
	m_primaryRect.setOutlineColor(sf::Color(130,130,130,255));
	m_primaryRect.setFillColor(sf::Color::White);
	m_secondaryRect.setPosition(20.0f, 20.0f);
	m_secondaryRect.setOutlineThickness(3.0f);
	m_secondaryRect.setOutlineColor(sf::Color(130,130,130,255));
	m_secondaryRect.setFillColor(sf::Color::Black);

	setMouseLeftClickedFunction(std::make_shared<TFunctor<ColorSelector>>(this, &ColorSelector::swapColors));
}


ColorSelector::~ColorSelector(void)
{
}

void ColorSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_secondaryRect, states);
	target.draw(m_primaryRect, states);

}
sf::FloatRect ColorSelector::getLocalBounds(void) const
{
	return m_bounds.getLocalBounds();
}
sf::FloatRect ColorSelector::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_bounds.getGlobalBounds());
}

void ColorSelector::swapColors()
{
	sf::Color primaryColor(getPrimaryColor());
	setPrimaryColor(getSecondaryColor());
	setSecondaryColor(primaryColor);
}

void ColorSelector::setPrimaryColor(const sf::Color& color)
{
	m_primaryRect.setFillColor(color);
}

void ColorSelector::setSecondaryColor(const sf::Color& color)
{
	m_secondaryRect.setFillColor(color);
}

const sf::Color& ColorSelector::getPrimaryColor() const
{
	return m_primaryRect.getFillColor();
}

const sf::Color& ColorSelector::getSecondaryColor() const
{
	return m_secondaryRect.getFillColor();
}