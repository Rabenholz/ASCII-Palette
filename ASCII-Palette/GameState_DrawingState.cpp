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
	
	std::unique_ptr<SFMLCursesWindow> cursesWindow(new SFMLCursesWindow(m_window, sf::Vector2i(4,10)));
	m_drawingBoard = cursesWindow.get();
	cursesWindow->clearTiles("s", sf::Color::Blue, sf::Color::Green);
	cursesWindow->setTile(SFMLCursesChar(m_window, "a", sf::Color::Red, sf::Color::Cyan), sf::Vector2i(2,6));
	cursesWindow->setPosition(400,200);

	addGUIElement(std::move(colorPicker));
	addDrawable(std::move(colorSelected));
	addGUIElement(std::move(cursesWindow));
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

void GameState_DrawingState::saveAPF(const std::string& fileName)
{
	std::string extFileName(fileName);
	extFileName += ".apf";
	std::ofstream write(extFileName, std::ios::out);
	write<<(*m_drawingBoard);
	write.close();
}

std::unique_ptr<SFMLCursesWindow> GameState_DrawingState::loadAPF(const std::string& fileName)
{
	std::string extFileName(fileName);
	extFileName += ".apf";
	std::ifstream read(extFileName, std::ios::in);
	if(read.is_open())
	{
		std::unique_ptr<SFMLCursesWindow> cursesWindow(new SFMLCursesWindow(m_window, sf::Vector2i(1,1)));
		read>>(*cursesWindow);
		read.close();
		return cursesWindow;
	}
	else
	{
		//throw an exception here instead
		printf("FAILED TO OPEN FILE %s\n", extFileName.c_str());
		return std::unique_ptr<SFMLCursesWindow>(new SFMLCursesWindow(m_window, sf::Vector2i(1,1)));
	}

}

void GameState_DrawingState::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
	case sf::Keyboard::S:
		saveAPF("test");
		break;
	case sf::Keyboard::L:
		{
		std::unique_ptr<SFMLCursesWindow> loadedWindow(loadAPF("test"));
		loadedWindow->setPosition(100.0f,100.0f);
		addGUIElement(std::move(loadedWindow));
		}
		break;
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_Close());
		break;
	}
}