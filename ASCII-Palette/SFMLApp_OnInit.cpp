#include "stdafx.h"
#include "SFMLApp.h"
#include <sstream>


bool SFMLApp::OnInit(void)
{
	m_mainWindow.create(sf::VideoMode(800, 600, 32), "ASCII-Palette");

	TextureManager& textureManager = TextureManager::getInstance();
	sf::Image cursesAImage;
	cursesAImage.loadFromFile("assets/graphics/curses_640x300.bmp");
	cursesAImage.createMaskFromColor(sf::Color::Magenta);
	textureManager.addTextureFromImage(cursesAImage,"CursesA");
	const sf::Texture& cursesA = textureManager.getTexture("CursesA");
	SpriteManager& spriteManager = SpriteManager::getInstance();
	char k = 0;
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j< 16; j++)
		{
			std::string str("CursesA_ASCII");
			str += k;
			spriteManager.addSprite(sf::Sprite(textureManager.getTexture("CursesA"),sf::IntRect(j*8, i*12, 8, 12)),str);
			k++;
		}
	}

	ImageManager::getInstance().addImageFromFile("assets/graphics/colorpicker.png", "ColorWheel");
	const sf::Image& colorWheel(ImageManager::getInstance().getImage("ColorWheel"));
	TextureManager::getInstance().addTextureFromImage(colorWheel, "ColorWheel");
	//const sf::Texture& colorWheelTexture(TextureManager::getInstance().getTexture("ColorWheel"));

	sf::Image rectangle;
	rectangle.create(8,12,sf::Color::White);
	TextureManager::getInstance().addTextureFromImage(rectangle, "Rectangle");

	std::unique_ptr<GameState_DrawingState> drawingState(new GameState_DrawingState(m_mainWindow));
	registerState(std::move(drawingState), "Drawing");
	std::unique_ptr<GameState_LoadState> loadState(new GameState_LoadState(m_mainWindow));
	registerState(std::move(loadState), "Load");
	std::unique_ptr<GameState_SaveState> saveState(new GameState_SaveState(m_mainWindow));
	registerState(std::move(saveState), "Save");
	changeState("Drawing", nullptr);

	return true;
}