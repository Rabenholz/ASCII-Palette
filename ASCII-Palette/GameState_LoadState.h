#pragma once
#include "SFML-Template/GameStateBase.h"
#include "SFMLCursesWindow.h"
#include "StateInfo_CursesWindow.h"
#include "SFMLCursesTextBox.h"
class GameState_LoadState : public GameStateBase
{
public:
	GameState_LoadState(const sf::Window& window);
	virtual ~GameState_LoadState(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);

	bool loadAPF(const std::string& fileName);

	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);
	virtual void OnTextEntered(sf::Uint32 text);

private:
	SFMLCursesWindow* m_cursesWindow;
	SFMLCursesWindow* m_border;
	SFMLCursesTextBox* m_filenameBox;
	SFMLCursesWindow* m_fileNotFoundDialog;
	std::string m_filename;
};

