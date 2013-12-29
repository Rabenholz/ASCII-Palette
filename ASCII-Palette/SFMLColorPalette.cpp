#include "StdAfx.h"
#include "SFMLColorPalette.h"


SFMLColorPalette::SFMLColorPalette(const sf::Window& window, const sf::Image& colorImage, const sf::Texture& colorTexture)
	:SFMLGUIElement(window),
	 m_colorImage(&colorImage), m_display(colorTexture), 
	 m_backing(sf::Vector2f(static_cast<float>(colorTexture.getSize().x + 27.0f), static_cast<float>(colorTexture.getSize().y-1))), 
	 m_colorMagnify(sf::Vector2f(50.0f,50.0f)),
	 m_brightnessRect(sf::Vector2f(15.0f, colorTexture.getSize().y - 5.0f)),
	 m_selectedColor(sf::Color::White),
	 m_brightnessQuad(sf::TrianglesFan, 4),
	 m_brightness(1.0f),
	 m_brightnessSlider(sf::Vector2f(15.0f, 2.0f))
{
	m_backing.setFillColor(sf::Color::Blue);

	m_colorMagnify.setOutlineThickness(5.0f);
	m_colorMagnify.setOutlineColor(sf::Color::Black);

	m_brightnessRect.setOutlineThickness(2.0f);
	m_brightnessRect.setOutlineColor(sf::Color::White);
	m_brightnessRect.setPosition(colorTexture.getSize().x + 10.0f, 2.0f);
	m_brightnessRect.setFillColor(sf::Color::Black);

	
	m_brightnessQuad[0].position = m_brightnessRect.getPosition() + sf::Vector2f(m_brightnessRect.getSize().x, 0);
	m_brightnessQuad[1].position = m_brightnessRect.getPosition();
	m_brightnessQuad[2].position = m_brightnessRect.getPosition() + sf::Vector2f(0,m_brightnessRect.getSize().y);
	m_brightnessQuad[3].position = m_brightnessRect.getPosition()  + sf::Vector2f(m_brightnessRect.getSize().x, m_brightnessRect.getSize().y);

	m_brightnessQuad[0].color = sf::Color::White;
	m_brightnessQuad[1].color = sf::Color::White;
	m_brightnessQuad[2].color = sf::Color::Black;
	m_brightnessQuad[3].color = sf::Color::Black;

	m_brightnessSlider.setPosition(m_brightnessRect.getGlobalBounds().left + m_brightnessRect.getOutlineThickness(), 0.0f);
	m_brightnessSlider.setFillColor(sf::Color(static_cast<sf::Uint8>((1.0f-m_brightness)*255),
		static_cast<sf::Uint8>((1.0f-m_brightness)*255),static_cast<sf::Uint8>((1.0f-m_brightness)*255), 255));

	addMouseRolloverFunction(std::make_shared<TFunctor<SFMLColorPalette>>(this, &SFMLColorPalette::updateColorMagnify));
	addMouseLeftClickedFunction(std::make_shared<TFunctor<SFMLColorPalette>>(this, &SFMLColorPalette::onLeftClick));
}


SFMLColorPalette::~SFMLColorPalette(void)
{
}

void SFMLColorPalette::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_display, states);
	//target.draw(m_backing, states);
	target.draw(m_brightnessRect, states);
	target.draw(m_brightnessQuad, states);
	target.draw(m_brightnessSlider, states);
	//only for circular, probably should mitigate this to a subclass or something
	float radius = m_display.getLocalBounds().width/2.0f;
	sf::Vector2f center(getTransform().transformPoint(m_display.getGlobalBounds().left,0).x + radius, 
		getTransform().transformPoint(0,m_display.getGlobalBounds().top).y + radius);
	if(std::pow(radius,2) > std::pow(sf::Mouse::getPosition(m_window).x - center.x,2) + std::pow(sf::Mouse::getPosition(m_window).y - center.y,2))
	{
		target.draw(m_colorMagnify, states);
	}
	
}

sf::FloatRect SFMLColorPalette::getLocalBounds() const
{
	return m_backing.getLocalBounds();
}
sf::FloatRect SFMLColorPalette::getGlobalBounds() const
{
	return getTransform().transformRect(m_backing.getGlobalBounds());
}

sf::Color SFMLColorPalette::getSelectedColor() const
{
	return m_selectedColor  * 
		sf::Color(static_cast<sf::Uint8>(m_brightness*255),static_cast<sf::Uint8>(m_brightness*255),static_cast<sf::Uint8>(m_brightness*255), 255);;
}

void SFMLColorPalette::updateColorMagnify()
{
	sf::Vector2f localMouseFloat(getLocalPoint(sf::Mouse::getPosition(m_window)));
	sf::Vector2i localMouse(getLocalPoint(sf::Mouse::getPosition(m_window)));
	if(!getLocalBounds().contains(localMouseFloat)) //SFML BUG: SOMETIMES MOUSE IS NOT IN BOUNDS
		return;
	m_colorMagnify.setPosition(localMouseFloat.x - m_colorMagnify.getLocalBounds().width - 5.0f, 
		localMouseFloat.y - m_colorMagnify.getLocalBounds().height - 5.0f);
	m_colorMagnify.setFillColor(m_colorImage->getPixel(localMouse.x, localMouse.y) * 
		sf::Color(static_cast<sf::Uint8>(m_brightness*255),static_cast<sf::Uint8>(m_brightness*255),static_cast<sf::Uint8>(m_brightness*255), 255));
}

void SFMLColorPalette::onLeftClick()
{
	float radius = m_display.getLocalBounds().width/2.0f;
	sf::Vector2f center(getTransform().transformPoint(m_display.getGlobalBounds().left,0).x + radius, 
		getTransform().transformPoint(0,m_display.getGlobalBounds().top).y + radius);
	if(std::pow(radius,2) > std::pow(sf::Mouse::getPosition(m_window).x - center.x,2) + std::pow(sf::Mouse::getPosition(m_window).y - center.y,2))
	{
		selectColorAtMouse();
	}
	else if(getTransform().transformRect(m_brightnessRect.getGlobalBounds()).contains(sf::Vector2f(sf::Mouse::getPosition(m_window))))
	{
		selectBrightnessAtMouse();
	}
}

void SFMLColorPalette::selectColorAtMouse()
{
	sf::Vector2i localMouse(getLocalPoint(sf::Mouse::getPosition(m_window)));
	m_selectedColor = m_colorImage->getPixel(localMouse.x, localMouse.y);
	m_brightnessQuad[0].color = m_selectedColor;
	m_brightnessQuad[1].color = m_selectedColor;

}

void SFMLColorPalette::selectBrightnessAtMouse()
{
	sf::Vector2i localMouse(getLocalPoint(sf::Mouse::getPosition(m_window)));
	m_brightness = 1 - localMouse.y/m_brightnessRect.getLocalBounds().height;
	
	m_brightnessSlider.setPosition(m_brightnessRect.getGlobalBounds().left + m_brightnessRect.getOutlineThickness(),
		static_cast<float>(localMouse.y));
	m_brightnessSlider.setFillColor(sf::Color(static_cast<sf::Uint8>((1.0f-m_brightness)*255),
		static_cast<sf::Uint8>((1.0f-m_brightness)*255),static_cast<sf::Uint8>((1.0f-m_brightness)*255), 255));
}