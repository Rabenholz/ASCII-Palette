#pragma once
#include "SFML-Template/GameStateBase.h"
#include "StateInfo_CursesWindow.h"
#include "SFMLCursesWindow.h"
class GameState_SaveState : public GameStateBase
{
public:
	GameState_SaveState(const sf::Window& window);
	virtual ~GameState_SaveState(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);

	void saveAPF(const std::string& fileName);

	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);

private:
	SFMLCursesWindow* m_cursesWindow;
};

