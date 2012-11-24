#include "StdAfx.h"
#include "GameState_SaveState.h"


GameState_SaveState::GameState_SaveState(const sf::Window& window)
	:GameStateBase(window),
	m_cursesWindow(nullptr)
{
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
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_PopState());
	}
}