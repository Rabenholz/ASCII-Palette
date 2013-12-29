#pragma once
#include "SFML-Template/SFMLGUIElement.h"
class SFMLScrollWindow : public SFMLGUIElement
{
public:
	SFMLScrollWindow(const sf::Window& window, const sf::Vector2f& innerSize);
	virtual ~SFMLScrollWindow(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void setChild(std::unique_ptr<SFMLGUIElement> child);
	SFMLGUIElement* getChild() const;

	void setVerticalScrollbarVisibility(bool b);
	void setHorizontalScrollbarVisibility(bool b);
	void setStickyBottom(bool b);

	bool getVerticalScrollbarVisibility() const;
	bool getHorizontalScrollbarVisibility() const;
	bool getStickyBottom() const;

	void updateScrollbarHighlight();
	void beginVerticalScroll();
	void updateVerticalScroll();
	void endVerticalScroll();

	void OnChildMouseLeftPressed();
	void OnChildMouseLeftReleased();
	void OnChildMouseRightPressed();
	void OnChildMouseRightReleased();
	void OnChildMouseMiddlePressed();
	void OnChildMouseMiddleReleased();
	void OnChildMouseRollover();
	void OnChildGlobalMouseLeftReleased();
	void OnChildGlobalMouseRightReleased();
	void OnChildGlobalMouseMiddleReleased();

	bool inInnerRect(const sf::Vector2f& point) const;
	bool inInnerRect(const sf::Vector2i& point) const;
	bool mouseInInnerRect() const;

	static const float kScrollbarWidth;

protected:
	std::unique_ptr<SFMLGUIElement> m_child;

	sf::RectangleShape m_rectangle;
	sf::RectangleShape m_innerRect;
	sf::RectangleShape m_verticalScrollbar;

	bool m_verticalScrollbarVisibility;
	bool m_horizontalScrollbarVisibility;

	bool m_verticalScrollEnabled;
	float m_verticalScrollYBegin;

	bool m_stickyBottom;
	bool m_atBottom;
};

