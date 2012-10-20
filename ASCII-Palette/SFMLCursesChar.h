#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "SFML-Template/SpriteManager.h"
class SFMLCursesChar : public SFMLGUIElement
{
public:
	SFMLCursesChar(const sf::Window& window, std::string character);
	SFMLCursesChar(const sf::Window& window, std::string character, const sf::Color& textColor, const sf::Color& backgroundColor);
	~SFMLCursesChar(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds() const;
	virtual sf::FloatRect getGlobalBounds() const;

	void setCharColor(const sf::Color& color);
	void setBackgroundColor(const sf::Color& color);
	void setCharacter(char character);

	const sf::Color& getCharColor() const;
	const sf::Color& getBackgroundColor() const;
	std::string getCharacter() const;

private:
	std::string m_character;
	sf::RectangleShape m_backRect;
	sf::Sprite m_charSprite;
};

