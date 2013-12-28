#pragma once
#include "SFML-Template/SFMLGUIElement.h"
class SFMLScrollWindow : public SFMLGUIElement
{
public:
	SFMLScrollWindow(const sf::Window& window, const sf::Vector2f& innerSize);
	virtual ~SFMLScrollWindow(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void setChild(SFMLGUIElement& child);
	SFMLGUIElement* getChild() const;

	void setVerticalScrollbarVisibility(bool b);
	void setHorizontalScrollbarVisibility(bool b);

	bool getVerticalScrollbarVisibility() const;
	bool getHorizontalScrollbarVisibility() const;

	static const float kScrollbarWidth;

protected:
	SFMLGUIElement* m_child;

	sf::RectangleShape m_rectangle;
	sf::RectangleShape m_innerRect;

	bool m_verticalScrollbarVisibility;
	bool m_horizontalScrollbarVisibility;
};

