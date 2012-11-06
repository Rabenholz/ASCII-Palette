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

	void setCursorCharacter(const SFMLCursesChar& character);
	void moveCursorToPosition(sf::Vector2i position);
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();

	SFMLCursesWindow& getCursesWindow(); //for saving - easier this way

private:
	SFMLCursesWindow m_cursesWindow;
	sf::Vector2i m_cursorPosition;
	AnimatedSprite m_cursorSprite;

};

