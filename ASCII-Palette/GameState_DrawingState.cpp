#include "StdAfx.h"
#include "GameState_DrawingState.h"


GameState_DrawingState::GameState_DrawingState(const sf::Window& window)
	:GameStateBase(window),
	m_colorPicker(nullptr),
	m_drawingWindow(nullptr),
	m_colorSelector(nullptr)
{
	m_transparent = true;
}


GameState_DrawingState::~GameState_DrawingState(void)
{
}

void GameState_DrawingState::OnAwake(const SFMLStateInfo* lStateInfo)
{
	std::unique_ptr<SFMLColorPalette> colorPicker(new SFMLColorPalette(m_window, ImageManager::getInstance().getImage("ColorWheel"), 
		TextureManager::getInstance().getTexture("ColorWheel")));
	m_colorPicker = colorPicker.get();
	colorPicker->addMouseLeftClickedFunction(std::make_shared<TFunctor<GameState_DrawingState>>(this, &GameState_DrawingState::updateColorSelector));
	colorPicker->setPosition(m_window.getSize().x - colorPicker->getLocalBounds().width,
		m_window.getSize().y - colorPicker->getLocalBounds().height);

	std::unique_ptr<DrawingWindow> drawingWindow(new DrawingWindow(m_window, sf::Vector2i(25,80)));
	m_drawingWindow = drawingWindow.get();
	drawingWindow->setPosition(20.0f,20.0f);

	std::unique_ptr<ColorSelector> colorSelector(new ColorSelector(m_window));
	m_colorSelector = colorSelector.get();
	colorSelector->setPosition(m_window.getSize().x - colorSelector->getLocalBounds().width-50.0f, 200.0f);

	std::unique_ptr<AltCharsWindow> altCharsWindow(new AltCharsWindow(m_window));
	m_altCharsWindow = altCharsWindow.get();
	altCharsWindow->addMouseLeftClickedFunction(std::make_shared<TFunctor<GameState_DrawingState>>(this, &GameState_DrawingState::onAltCharClick));
	altCharsWindow->setPosition(m_window.getSize().x - altCharsWindow->getLocalBounds().width-10.0f, 40.0f);

	std::unique_ptr<SFMLCursesTextBox> textBox(new SFMLCursesTextBox(m_window, sf::Vector2i(10,20)));
	textBox->setPosition(200.0f, 200.0f);
	textBox->setText("This is an awesome sentence and no one can tell you otherwise. If they try to they are lying and deserve to be beaten.");

	addGUIElement(std::move(colorPicker));
	addGUIElement(std::move(drawingWindow));
	addGUIElement(std::move(colorSelector));
	addGUIElement(std::move(altCharsWindow));
	addGUIElement(std::move(textBox));
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
	m_colorPicker = nullptr;
	m_drawingWindow = nullptr;
	m_colorSelector = nullptr;
	GameStateBase::Cleanup();
}
void GameState_DrawingState::OnSuspend(void)
{
}
void GameState_DrawingState::OnResume(void)
{
}

void GameState_DrawingState::updateColorSelector()
{
	m_colorSelector->setPrimaryColor(m_colorPicker->getSelectedColor());
}

void GameState_DrawingState::onAltCharClick()
{
	m_drawingWindow->setCursorCharacter(SFMLCursesChar(m_window,m_altCharsWindow->getCharAtMouse(),
		m_colorSelector->getPrimaryColor(), m_colorSelector->getSecondaryColor()));
}

void GameState_DrawingState::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
	case sf::Keyboard::Up:
		m_drawingWindow->moveCursorUp();
		break;
	case sf::Keyboard::Down:
		m_drawingWindow->moveCursorDown();
		break;
	case sf::Keyboard::Left:
		m_drawingWindow->moveCursorLeft();
		break;
	case sf::Keyboard::Right:
		m_drawingWindow->moveCursorRight();
		break;
	case sf::Keyboard::S:
		if(control)
		{
			m_messages.push_back(new SFMLStateMessage_PushState("Save",
			std::unique_ptr<StateInfo_CursesWindow>(new StateInfo_CursesWindow(m_drawingWindow->getCursesWindow()))));
		}
		break;
	case sf::Keyboard::L:
		if(control)
		{
			m_messages.push_back(new SFMLStateMessage_PushState("Load",
			std::unique_ptr<StateInfo_CursesWindow>(new StateInfo_CursesWindow(m_drawingWindow->getCursesWindow()))));
		}
		break;
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_Close());
		break;
	}
}

void GameState_DrawingState::OnTextEntered(sf::Uint32 text)
{
	if(text < 32)
		return;
	m_drawingWindow->setCursorCharacter(SFMLCursesChar(m_window,std::string(sf::String(text)),
		m_colorSelector->getPrimaryColor(), m_colorSelector->getSecondaryColor()));
}