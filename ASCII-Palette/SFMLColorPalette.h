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

	void updateColorMagnify();

private:
	const sf::Image& m_colorImage;
	sf::Sprite m_display;
	sf::RectangleShape m_colorMagnify;

};

