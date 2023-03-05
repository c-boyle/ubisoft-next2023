//---------------------------------------------------------------------------------
// Scoreboard.h
//---------------------------------------------------------------------------------
#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include "..\stdafx.h"

class CScoreboard {
public:

	CScoreboard(float x, float y) : m_x(x), m_y(y) {}
	void Render(int timeLeft, int score, int livesLeft, int currentLevel);

private:
	float m_x;
	float m_y;
	
};

#endif