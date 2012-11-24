#include "StdAfx.h"
#include "GameState_LoadState.h"


GameState_LoadState::GameState_LoadState(const sf::Window& window)
	:GameStateBase(window),
	m_cursesWindow(nullptr)
{
}


GameState_LoadState::~GameState_LoadState(void)
{
}

void GameState_LoadState::OnAwake(const SFMLStateInfo* lStateInfo)
{
	if(const StateInfo_CursesWindow* stateInfo = dynamic_cast<const StateInfo_CursesWindow*>(lStateInfo))
	{
		m_cursesWindow = &stateInfo->m_cursesWindow;
	}
}

void GameState_LoadState::loadAPF(const std::string& fileName)
{
	std::string extFileName(fileName);
	extFileName += ".apf";
	std::ifstream read(extFileName, std::ios::in);
	if(read.is_open())
	{
		read>>*m_cursesWindow;
		read.close();
	}
	else
	{
		//throw an exception here instead
		printf("FAILED TO OPEN FILE %s\n", extFileName.c_str());
	}

}

void GameState_LoadState::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_PopState());
	}
}