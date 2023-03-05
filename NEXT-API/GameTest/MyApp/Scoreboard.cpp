//---------------------------------------------------------------------------------
// Scoreboard.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Scoreboard.h"
#include "../App/app.h"

void CScoreboard::Render(int timeLeft, int score, int livesLeft, int currentLevel)
{
	char textBuffer[128];
	sprintf(textBuffer, "TIME: %d    SCORE: %d    LEFT: %d    LEVEL: %d", timeLeft, score, livesLeft, currentLevel);
	App::Print(m_x, m_y, textBuffer, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
}
