#pragma once
#include "SFML-Template/GameStateBase.h"
#include "SFMLColorPalette.h"
#include "SFMLCursesChar.h"
#include "SFMLCursesWindow.h"
#include "DrawingWindow.h"
#include <fstream>
class GameState_DrawingState : public GameStateBase
{
public:
	GameState_DrawingState(const sf::Window& window);
	virtual ~GameState_DrawingState(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);
	virtual void OnUpdate(void);
	virtual void OnRender(sf::RenderTarget& target);
	virtual void OnCleanup(void);
	virtual void OnSuspend(void);
	virtual void OnResume(void);

	void saveAPF(const std::string& fileName);
	std::unique_ptr<SFMLCursesWindow> loadAPF(const std::string& fileName);

	//SFMLEvent Overrides
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);
	virtual void OnTextEntered(sf::Uint32 text);

private:
	SFMLColorPalette* m_colorPicker;
	sf::Color m_primaryColor;
	sf::Color m_secondaryColor;
	sf::RectangleShape* m_rectangle;
	SFMLCursesWindow* m_drawingBoard;
	DrawingWindow* m_drawingWindow;
};

