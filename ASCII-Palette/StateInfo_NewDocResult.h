#pragma once
#include "SFML-Template/SFMLStateInfo.h"

class SFMLCursesWindow;

class StateInfo_NewDocResult : public SFMLStateInfo
{
public:
	StateInfo_NewDocResult(bool b)
		:m_result(b) {}
	virtual ~StateInfo_NewDocResult() {}
	bool m_result;
};