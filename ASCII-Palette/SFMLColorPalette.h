#pragma once
#include "SFML-Template/SFMLGUIElement.h"
class SFMLColorPalette : public SFMLGUIElement
{
public:
	SFMLColorPalette(const sf::Window& window, const sf::Image& colorImage, const sf::Texture& colorTexture);
	virtual ~SFMLColorPalette(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds() const;
	virtual sf::FloatRect getGlobalBounds() const;

	sf::Color getSelectedColor() const;

	void onLeftClick();
	void updateColorMagnify();
	void selectColorAtMouse();
	void selectBrightnessAtMouse();

private:
	const sf::Image* m_colorImage;
	sf::Sprite m_display;
	sf::RectangleShape m_backing;
	sf::RectangleShape m_colorMagnify;
	sf::Color m_selectedColor;
	sf::RectangleShape m_brightnessRect;
	sf::VertexArray m_brightnessQuad;
	sf::RectangleShape m_brightnessSlider;
	float m_brightness;

};

