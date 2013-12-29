#pragma once
#include "SFML-Template/GameStateBase.h"
#include "StateInfo_CursesWindow.h"
#include "SFMLCursesTextBox.h"
class GameState_NewDocState : public GameStateBase
{
public:
	GameState_NewDocState(const sf::Window& window);
	virtual ~GameState_NewDocState(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);

	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);
	virtual void OnTextEntered(sf::Uint32 text);

private:
	SFMLCursesWindow* m_cursesWindow;
	SFMLCursesWindow* m_border;
	SFMLCursesTextBox* m_filenameBox;
	std::string m_filename;
};

