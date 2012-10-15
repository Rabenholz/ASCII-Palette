#include "StdAfx.h"
#include "GameState_DrawingState.h"


GameState_DrawingState::GameState_DrawingState(const sf::Window& window)
	:GameStateBase(window)
{
}


GameState_DrawingState::~GameState_DrawingState(void)
{
}

void GameState_DrawingState::OnAwake(const SFMLStateInfo* lStateInfo)
{
	std::unique_ptr<SFMLColorPalette> colorPicker(new SFMLColorPalette(m_window, ImageManager::getInstance().getImage("ColorWheel"), 
		TextureManager::getInstance().getTexture("ColorWheel")));
	m_colorPicker = colorPicker.get();
	colorPicker->setPosition(0.0f, 300.0f);
	std::unique_ptr<sf::RectangleShape> colorSelected(new sf::RectangleShape(sf::Vector2f(20.0f, 20.0f)));
	m_rectangle = colorSelected.get();
	colorSelected->setPosition(150.0f, 150.0f);
	colorSelected->setOutlineThickness(2.0f);
	colorSelected->setOutlineColor(sf::Color::White);

	std::unique_ptr<SFMLCursesChar> char1(new SFMLCursesChar(m_window, 'a', sf::Color::Blue, sf::Color::Green));
	char1->setPosition(400.0f, 200.0f);

	addGUIElement(std::move(colorPicker));
	addDrawable(std::move(colorSelected));
	addGUIElement(std::move(char1));
}
void GameState_DrawingState::OnUpdate(void)
{
}
void GameState_DrawingState::OnRender(sf::RenderTarget& target)
{
	m_rectangle->setFillColor(m_colorPicker->getSelectedColor());
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