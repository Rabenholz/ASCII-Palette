#pragma once
#include "SFML-Template/SFMLStateInfo.h"

class SFMLCursesWindow;
class StateInfo_CursesWindow : public SFMLStateInfo
{
public:
	StateInfo_CursesWindow(SFMLCursesWindow& cursesWindow)
		:m_cursesWindow(cursesWindow) {}
	virtual ~StateInfo_CursesWindow() {}
	SFMLCursesWindow& m_cursesWindow;
};