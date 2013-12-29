#pragma once
#include <string>
class DrawingWindow;
class CanvasCommand
{
public:
	CanvasCommand(void) {}
	virtual ~CanvasCommand(void) {}

	virtual void execute(DrawingWindow& drawingWindow) = 0;
	virtual void undo(DrawingWindow& drawingWindow) = 0;
	virtual std::string getText() const = 0;
};

