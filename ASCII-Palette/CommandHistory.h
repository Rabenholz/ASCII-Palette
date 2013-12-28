#pragma once
#include <list>

class CanvasCommand;
class DrawingWindow;

class CommandHistory
{
public:
	CommandHistory(DrawingWindow& drawingWindow);
	~CommandHistory(void);

	void executeAndAddCommand(std::unique_ptr<CanvasCommand> command);
	void moveIndex(int delta); //negative = backwards in history

	size_t getMaxCommands() const;

private:
	size_t m_maxCommands; //TODO: replace with memory usage?

	std::list<std::unique_ptr<CanvasCommand>> m_commands;
	std::list<std::unique_ptr<CanvasCommand>>::iterator m_iterator;

	DrawingWindow* m_drawingWindow;
};

