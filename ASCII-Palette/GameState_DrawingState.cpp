#include "StdAfx.h"
#include "GameState_DrawingState.h"
#include "CommandSetCharacters.h"
#include "StateInfo_CursesWindowLoadResult.h"
#include "GameState_NewDocState.h"
#include "StateInfo_NewDocResult.h"


GameState_DrawingState::GameState_DrawingState(const sf::Window& window)
	:GameStateBase(window),
	m_colorPicker(nullptr),
	m_drawingWindow(nullptr),
	m_colorSelector(nullptr),
	m_commandHistoryWindow(nullptr)
{
	m_transparent = true;
}


GameState_DrawingState::~GameState_DrawingState(void)
{
}

void GameState_DrawingState::OnAwake(const SFMLStateInfo* lStateInfo)
{
	std::unique_ptr<SFMLColorPalette> colorPicker(new SFMLColorPalette(*m_window, ImageManager::getInstance().getImage("ColorWheel"), 
		TextureManager::getInstance().getTexture("ColorWheel")));
	m_colorPicker = colorPicker.get();
	colorPicker->addMouseLeftClickedFunction(std::make_shared<TFunctor<GameState_DrawingState>>(this, &GameState_DrawingState::updateColorSelector));
	colorPicker->setPosition(m_window->getSize().x - colorPicker->getLocalBounds().width,
		m_window->getSize().y - colorPicker->getLocalBounds().height);

	//25,80
	std::unique_ptr<DrawingWindow> drawingWindow(new DrawingWindow(*m_window, sf::Vector2i(50,90)));
	m_drawingWindow = drawingWindow.get();
	drawingWindow->setPosition(20.0f,20.0f);

	std::unique_ptr<ColorSelector> colorSelector(new ColorSelector(*m_window));
	m_colorSelector = colorSelector.get();
	colorSelector->setPosition(m_window->getSize().x - colorSelector->getLocalBounds().width-50.0f, 200.0f);

	std::unique_ptr<AltCharsWindow> altCharsWindow(new AltCharsWindow(*m_window));
	m_altCharsWindow = altCharsWindow.get();
	altCharsWindow->addMouseLeftClickedFunction(std::make_shared<TFunctor<GameState_DrawingState>>(
		this, &GameState_DrawingState::onAltCharClick));
	altCharsWindow->setPosition(m_window->getSize().x - altCharsWindow->getLocalBounds().width-10.0f, 40.0f);

	std::unique_ptr<CommandHistoryWindow> commandHistoryWindow(new CommandHistoryWindow(*m_window, *m_drawingWindow));
	m_commandHistoryWindow = commandHistoryWindow.get();
	//commandHistoryWindow->setPosition(m_drawingWindow->getGlobalBounds().left + m_drawingWindow->getGlobalBounds().width + 10.f, m_drawingWindow->getGlobalBounds().top);

	SFMLCursesCharRect blankRect;
	blankRect.resize(m_drawingWindow->getCursesSize().x, std::vector<SFMLCursesChar>());
	for(std::vector<std::vector<SFMLCursesChar>>::iterator yIt(blankRect.begin()); yIt != blankRect.end(); yIt++)
	{
		yIt->resize(m_drawingWindow->getCursesSize().y, SFMLCursesChar(*m_window, " "));
	}
	commandHistoryWindow->executeAndAddCommand(std::unique_ptr<CommandSetCharacters>(new CommandSetCharacters(blankRect, sf::Vector2i(0,0), "New Document")));

	std::unique_ptr<SFMLScrollWindow> undoHistoryScroll(new SFMLScrollWindow(*m_window, sf::Vector2f(commandHistoryWindow->getLocalBounds().width, 15 * 5.2)));
	m_undoHistoryScroll = undoHistoryScroll.get();
	undoHistoryScroll->setChild(std::move(commandHistoryWindow));
	undoHistoryScroll->setPosition(m_drawingWindow->getGlobalBounds().left + m_drawingWindow->getGlobalBounds().width + 10.f, m_drawingWindow->getGlobalBounds().top);

	//std::unique_ptr<SFMLCursesTextBox> textBox(new SFMLCursesTextBox(m_window, sf::Vector2i(10,20)));
	//textBox->setPosition(200.0f, 200.0f);
	//textBox->setAlignment(SFMLCursesTextBox::Alignment::Left);
	//textBox->setText(//"This is an awesome sentence and no one can tell you otherwise. If theyyy try to they are lying and deserve to be beaten.");
	//	"I am typing an average sentence that contains many words, both short and long. " 
	//	"The p90 is a world renowned gun, known for its fast fire rate.");
	addGUIElement(std::move(colorPicker));
	addGUIElement(std::move(drawingWindow));
	addGUIElement(std::move(colorSelector));
	addGUIElement(std::move(altCharsWindow));
	addGUIElement(std::move(undoHistoryScroll));
	//addGUIElement(std::move(commandHistoryWindow));
	//addGUIElement(std::move(textBox));
}
void GameState_DrawingState::OnUpdate(void)
{
	GameStateBase::updateGUIElements();
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
void GameState_DrawingState::OnResume(const SFMLStateInfo* stateInfo)
{
	if(const StateInfo_CursesWindowLoadResult* stateInfoLoad = dynamic_cast<const StateInfo_CursesWindowLoadResult*>(stateInfo))
	{
		if(stateInfoLoad->m_result)
		{
			m_commandHistoryWindow->executeAndAddCommand(std::unique_ptr<CanvasCommand>(new CommandSetCharacters(stateInfoLoad->m_cursesWindow->copyTiles(sf::Vector2i(0,0), stateInfoLoad->m_cursesWindow->getCursesSize()), 
		sf::Vector2i(0,0), "Load")));
		}
	}
	else if(const StateInfo_NewDocResult* stateInfoNewDoc = dynamic_cast<const StateInfo_NewDocResult*>(stateInfo))
	{
		if(stateInfoNewDoc->m_result)
		{
			SFMLCursesCharRect blankRect;
			blankRect.resize(m_drawingWindow->getCursesSize().x, std::vector<SFMLCursesChar>());
			for(std::vector<std::vector<SFMLCursesChar>>::iterator yIt(blankRect.begin()); yIt != blankRect.end(); yIt++)
			{
				yIt->resize(m_drawingWindow->getCursesSize().y, SFMLCursesChar(*m_window, " "));
			}
			m_commandHistoryWindow->executeAndAddCommand(std::unique_ptr<CommandSetCharacters>(new CommandSetCharacters(blankRect, sf::Vector2i(0,0), "New Document")));

		}
	}
}

void GameState_DrawingState::updateColorSelector()
{
	m_colorSelector->setPrimaryColor(m_colorPicker->getSelectedColor());
}

void GameState_DrawingState::onAltCharClick()
{
	m_commandHistoryWindow->executeAndAddCommand(std::unique_ptr<CanvasCommand>(new CommandSetCharacters(
		SFMLCursesChar(*m_window, m_altCharsWindow->getCharAtMouse(), m_colorSelector->getPrimaryColor(), m_colorSelector->getSecondaryColor()), 
		sf::Vector2i(m_drawingWindow->getCursorPosition()), "Insert Special")));
	//m_drawingWindow->setCursorCharacter(SFMLCursesChar(*m_window,m_altCharsWindow->getCharAtMouse(),
	//	m_colorSelector->getPrimaryColor(), m_colorSelector->getSecondaryColor()));
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
	case sf::Keyboard::Back:
		m_drawingWindow->setCursorCharacter(SFMLCursesChar(*m_window," ",m_colorSelector->getPrimaryColor(), 
			m_colorSelector->getSecondaryColor()));
		break;
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_Close());
		m_messages.push_back(new SFMLStateMessage_PushState("Save",
				std::unique_ptr<StateInfo_CursesWindow>(new StateInfo_CursesWindow(m_drawingWindow->getCursesWindow()))));
		break;
	case sf::Keyboard::N:
		if(control)
		{
			m_messages.push_back(new SFMLStateMessage_PushState("NewDoc",nullptr));
			m_messages.push_back(new SFMLStateMessage_PushState("Save",
				std::unique_ptr<StateInfo_CursesWindow>(new StateInfo_CursesWindow(m_drawingWindow->getCursesWindow()))));
		}
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
			m_messages.push_back(new SFMLStateMessage_PushState("Load", nullptr));
			//m_messages.push_back(new SFMLStateMessage_PushState("Load",
			//std::unique_ptr<StateInfo_CursesWindow>(new StateInfo_CursesWindow(m_drawingWindow->getCursesWindow()))));
		}
		break;
	case sf::Keyboard::Y:
		if(control)
		{
			m_commandHistoryWindow->moveIndex(1);
		}
		break;
	case sf::Keyboard::Z:
		if(control && shift)
			m_commandHistoryWindow->moveIndex(1);
		else if(control)
			m_commandHistoryWindow->moveIndex(-1);
		break;
	}
}

void GameState_DrawingState::OnTextEntered(sf::Uint32 text)
{
	if(text < 32)
		return;
	//m_drawingWindow->setCursorCharacter(SFMLCursesChar(*m_window,std::string(sf::String(text)),
	//	m_colorSelector->getPrimaryColor(), m_colorSelector->getSecondaryColor()));
	m_commandHistoryWindow->executeAndAddCommand(std::unique_ptr<CanvasCommand>(new CommandSetCharacters(
		SFMLCursesChar(*m_window,std::string(sf::String(text)), m_colorSelector->getPrimaryColor(), m_colorSelector->getSecondaryColor()), 
		sf::Vector2i(m_drawingWindow->getCursorPosition()))));
}