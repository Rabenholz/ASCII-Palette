#pragma once
#include "SFMLCursesWindow.h"
#include "SFML-Template/SFMLGUIElement.h"
class AltCharsWindow : public SFMLGUIElement
{
public:
	AltCharsWindow(const sf::Window& window);
	virtual ~AltCharsWindow(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void updateCharMagnify();

	std::string getCharAtMouse() const;

private:
	SFMLCursesWindow m_cursesWindow;
	sf::RectangleShape m_outline;
	SFMLCursesChar m_charMagnify;

};

