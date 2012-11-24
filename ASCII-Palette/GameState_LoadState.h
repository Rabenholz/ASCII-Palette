#pragma once
#include "SFML-Template/GameStateBase.h"
#include "SFMLCursesWindow.h"
#include "StateInfo_CursesWindow.h"
class GameState_LoadState : public GameStateBase
{
public:
	GameState_LoadState(const sf::Window& window);
	virtual ~GameState_LoadState(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);

	void loadAPF(const std::string& fileName);

	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);

private:

	SFMLCursesWindow* m_cursesWindow;
};

