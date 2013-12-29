#pragma once
#include "SFML-Template/SFMLStateInfo.h"

class SFMLCursesWindow;
class StateInfo_CursesWindowLoadResult : public SFMLStateInfo
{
public:
	StateInfo_CursesWindowLoadResult(bool b, std::unique_ptr<SFMLCursesWindow> cursesWindow)
		:m_result(b), m_cursesWindow(std::move(cursesWindow)) {}
	virtual ~StateInfo_CursesWindowLoadResult() {}
	bool m_result;
	std::unique_ptr<SFMLCursesWindow> m_cursesWindow;
};