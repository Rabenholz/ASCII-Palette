#include "StdAfx.h"
#include "GameState_SaveState.h"


GameState_SaveState::GameState_SaveState(const sf::Window& window)
	:GameStateBase(window),
	m_cursesWindow(nullptr),
	m_border(nullptr), m_filenameBox(nullptr),
	m_filename()
{
	m_transparent = true;
}


GameState_SaveState::~GameState_SaveState(void)
{
}

void GameState_SaveState::OnAwake(const SFMLStateInfo* lStateInfo)
{
	if(const StateInfo_CursesWindow* stateInfo = dynamic_cast<const StateInfo_CursesWindow*>(lStateInfo))
	{
		m_cursesWindow = &stateInfo->m_cursesWindow;
	}

	m_filename = "";

	std::unique_ptr<SFMLCursesWindow> border(new SFMLCursesWindow(m_window, sf::Vector2i(3,44)));
	m_border = border.get();
	border->setBorder(SFMLCursesChar(m_window,"-",sf::Color::Blue,sf::Color::Black),SFMLCursesChar(m_window,"-",sf::Color::Blue,sf::Color::Black),
		SFMLCursesChar(m_window,"|",sf::Color::Blue,sf::Color::Black),SFMLCursesChar(m_window,"|",sf::Color::Blue,sf::Color::Black),
		SFMLCursesChar(m_window,"+",sf::Color::Blue,sf::Color::Black),SFMLCursesChar(m_window,"+",sf::Color::Blue,sf::Color::Black),
		SFMLCursesChar(m_window,"+",sf::Color::Blue,sf::Color::Black),SFMLCursesChar(m_window,"+",sf::Color::Blue,sf::Color::Black));
	border->setTiles("Save File", sf::Color(200,200,255,255), sf::Color::Black, sf::Vector2i(0,3));
	border->setTiles("Filename:", sf::Color::White, sf::Color::Black, sf::Vector2i(1,1));
	border->setPosition(m_window.getSize().x/2 - border->getLocalBounds().width/2.0f, 280.0f);

	std::unique_ptr<SFMLCursesTextBox> filenameBox(new SFMLCursesTextBox(m_window, sf::Vector2i(1,32)));
	m_filenameBox = filenameBox.get();
	filenameBox->setPosition(border->getGlobalBounds().left + 11.0f*8.0f, border->getGlobalBounds().top + 12.0f);

	addGUIElement(std::move(border));
	addGUIElement(std::move(filenameBox));
}

void GameState_SaveState::saveAPF(const std::string& fileName)
{
	std::string extFileName(fileName);
	extFileName += ".apf";
	std::ofstream write(extFileName, std::ios::out);
	write<<*m_cursesWindow;
	write.close();
}

void GameState_SaveState::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
	case sf::Keyboard::Return:
		if(m_filename.length() > 0)
		{
			saveAPF(m_filename);
			m_messages.push_back(new SFMLStateMessage_PopState());
		}
		break;
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_PopState());
		break;
	}
}

void GameState_SaveState::OnTextEntered(sf::Uint32 text)
{
	if(text == 8 && m_filename.length() > 0)
	{
		m_filename.pop_back();
		m_filenameBox->setText(m_filename);
	}
	else if(m_filename.length() < 32 && ((text >= 48 && text <= 57) || (text >= 65 && text<= 90) || (text >= 97 && text <= 122)))
	{
		m_filename += static_cast<unsigned char>(text);
		m_filenameBox->setText(m_filename);
	}
}