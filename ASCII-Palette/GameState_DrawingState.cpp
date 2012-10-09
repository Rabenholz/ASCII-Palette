#include "StdAfx.h"
#include "GameState_DrawingState.h"


GameState_DrawingState::GameState_DrawingState(void)
{
}


GameState_DrawingState::~GameState_DrawingState(void)
{
}

void GameState_DrawingState::OnAwake(const SFMLStateInfo* lStateInfo)
{
}
void GameState_DrawingState::OnUpdate(void)
{
}
void GameState_DrawingState::OnRender(sf::RenderTarget& target)
{
	GameStateBase::drawDisplayList(target);
}
void GameState_DrawingState::OnCleanup(void)
{
	GameStateBase::Cleanup();
}
void GameState_DrawingState::OnSuspend(void)
{
}
void GameState_DrawingState::OnResume(void)
{
}

void GameState_DrawingState::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_Close());
		break;
	}
}