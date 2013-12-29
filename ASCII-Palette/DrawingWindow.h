#pragma once
#include "SFMLCursesWindow.h"
#include "SFML-Template/AnimatedSprite.h"
class DrawingWindow : public SFMLGUIElement
{
public:
	DrawingWindow(const sf::Window& window, const sf::Vector2i& lCursesSize);
	virtual ~DrawingWindow(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void setCharacter(const SFMLCursesChar& character, sf::Vector2i position);
	void setCharactersInRect(const SFMLCursesCharRect& characterRect, sf::Vector2i position);

	SFMLCursesChar copyCharacter(sf::Vector2i position) const;
	SFMLCursesCharRect copyCharactersInRect(sf::Vector2i position, sf::Vector2i size) const;

	//cursor control
	void setCursorCharacter(const SFMLCursesChar& character);
	void moveCursorToPosition(sf::Vector2i position);
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();

	sf::Vector2i getCursorPosition() const;
	sf::Vector2i getCursesSize() const;
	SFMLCursesWindow& getCursesWindow(); //for saving - easier this way

	void onLeftClick();

private:
	void updateCursorSprite();

	SFMLCursesWindow m_cursesWindow;
	sf::Vector2i m_cursorPosition;
	AnimatedSprite m_cursorSprite;
	AnimatedSprite m_cursorBackRect;
	sf::RectangleShape m_outline;

};

