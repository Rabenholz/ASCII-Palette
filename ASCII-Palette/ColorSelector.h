#pragma once
#include "SFML-Template/SFMLGUIElement.h"
class ColorSelector : public SFMLGUIElement
{
public:
	ColorSelector(const sf::Window& window);
	virtual ~ColorSelector(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void swapColors();

	void setPrimaryColor(const sf::Color& color);
	void setSecondaryColor(const sf::Color& color);

	const sf::Color& getPrimaryColor() const;
	const sf::Color& getSecondaryColor() const;

private:
	sf::RectangleShape m_primaryRect;
	sf::RectangleShape m_secondaryRect;
	sf::RectangleShape m_bounds;
};

