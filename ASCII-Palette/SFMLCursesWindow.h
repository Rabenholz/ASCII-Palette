#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "SFML-Template/SpriteManager.h"
#include "SFMLCursesChar.h"
class SFMLCursesWindow
	:public SFMLGUIElement
{
public:
	SFMLCursesWindow(const sf::Window& window, const sf::Vector2i& lCursesSize);
	~SFMLCursesWindow(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void clearTiles();
	void clearTiles(std::string character, const sf::Color& textColor, const sf::Color& backgroundColor);
	void setTile(const SFMLCursesChar& cursesChar, const sf::Vector2i& tilePos);

	const SFMLCursesChar& getTile(const sf::Vector2i& lTilePos) const;

	void setCursesSize(const sf::Vector2i& lCursesSize);
	sf::Vector2i getCursesSize() const;

private:
	sf::RectangleShape m_rectangle;
	std::vector<std::vector<std::unique_ptr<SFMLCursesChar>>> m_tiles; //[lines, columns]
	sf::Vector2i m_cursesSize;
};

