#pragma once
#include"SFMLCursesWindow.h"

//TODO: Add word-bisection at end of line
class SFMLCursesTextBox : public SFMLCursesWindow
{
public:
	struct Alignment
	{
		enum E
		{
			Left,
			Right,
			Center,
			Justify
		};
	};

	SFMLCursesTextBox(const sf::Window& window, const sf::Vector2i& lCursesSize);
	virtual ~SFMLCursesTextBox(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void setText(const std::string& text);
	const std::string& getText() const;

	void setAlignment(Alignment::E alignment);
	Alignment::E getAlignment() const;

	
protected:
	void updateTextBox();

	std::string m_text;
	Alignment::E m_alignment;
};

