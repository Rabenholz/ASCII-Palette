#include "StdAfx.h"
#include "SFMLCursesTextBox.h"


SFMLCursesTextBox::SFMLCursesTextBox(const sf::Window& window, const sf::Vector2i& lCursesSize)
	:SFMLCursesWindow(window, lCursesSize),
	m_text(),
	m_alignment(Alignment::Left)
{
}


SFMLCursesTextBox::~SFMLCursesTextBox(void)
{
}

void SFMLCursesTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	SFMLCursesWindow::draw(target,states);
}
sf::FloatRect SFMLCursesTextBox::getLocalBounds(void) const
{
	return m_rectangle.getLocalBounds();
}
sf::FloatRect SFMLCursesTextBox::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_rectangle.getGlobalBounds());
}

void SFMLCursesTextBox::setText(const std::string& text)
{
	m_text = text;
	updateTextBox();
}
const std::string& SFMLCursesTextBox::getText() const
{
	return m_text;
}
void SFMLCursesTextBox::setAlignment(SFMLCursesTextBox::Alignment::E alignment)
{
	m_alignment = alignment;
	updateTextBox();
}
SFMLCursesTextBox::Alignment::E SFMLCursesTextBox::getAlignment() const
{
	return m_alignment;
}

void SFMLCursesTextBox::updateTextBox()
{
	std::string word = "";
	int col = 0;
	int line = 0;
	for(std::string::iterator stringIt(m_text.begin()); stringIt != m_text.end(); stringIt++)
	{
		if(*stringIt == ' ' || stringIt == m_text.end() - 1) //word is complete
		{
			//WARNING: If a word is longer than the width that word and any after will not be printed
			//needs mid-word linebreaking
			//left justified
			if(stringIt == m_text.end() - 1)
				word += *stringIt;
			if(word.length() > static_cast<unsigned int>(m_cursesSize.y))
				break;
			if(word.length() > static_cast<unsigned int>(m_cursesSize.y - col)) //word too long for this line, move onto next one
			{
				line++;
				col = 0;
			}
			if(line >= m_cursesSize.x) //past the last line
				break;
			for(std::string::iterator wordIt(word.begin()); wordIt != word.end(); wordIt++)
			{
				setTile(SFMLCursesChar(m_window, std::string("") + *wordIt), sf::Vector2i(line,col));
				col++;
			}
			if(col < m_cursesSize.y - 1)
			{
				setTile(SFMLCursesChar(m_window, " "), sf::Vector2i(line,col));
				col++;
			}
			word = "";
		}
		else
		{
			word += *stringIt;
		}

	}
}