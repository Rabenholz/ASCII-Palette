#include "StdAfx.h"
#include "SFMLColorPalette.h"


SFMLColorPalette::SFMLColorPalette(const sf::Image& colorImage, const sf::Texture& colorTexture)
	:m_colorImage(colorImage), m_display(colorTexture), m_colorMagnify(sf::Vector2f(50.0f,50.0f))
{
	m_colorMagnify.setOutlineThickness(5.0f);
	m_colorMagnify.setOutlineColor(sf::Color::Black);
	setMouseRolloverFunction(std::make_shared<TFunctor<SFMLColorPalette>>(this, &SFMLColorPalette::updateColorMagnify));
}


SFMLColorPalette::~SFMLColorPalette(void)
{
}

void SFMLColorPalette::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_display, states);
	if(getGlobalBounds().contains(sf::Vector2f(static_cast<float>(m_mouseX), static_cast<float>(m_mouseY))))
		target.draw(m_colorMagnify, states);
}

sf::FloatRect SFMLColorPalette::getLocalBounds() const
{
	return m_display.getLocalBounds();
}
sf::FloatRect SFMLColorPalette::getGlobalBounds() const
{
	return getTransform().transformRect(m_display.getGlobalBounds());
}

void SFMLColorPalette::updateColorMagnify()
{
	sf::Vector2f localMouseFloat(getLocalPoint(static_cast<float>(m_mouseX), static_cast<float>(m_mouseY)));
	sf::Vector2i localMouse(static_cast<int>(localMouseFloat.x),static_cast<int>(localMouseFloat.y));
	m_colorMagnify.setPosition(localMouseFloat.x - m_colorMagnify.getLocalBounds().width - 5.0f, 
		localMouseFloat.y - m_colorMagnify.getLocalBounds().height - 5.0f);
	m_colorMagnify.setFillColor(m_colorImage.getPixel(localMouse.x, localMouse.y));
}