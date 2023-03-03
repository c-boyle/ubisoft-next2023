//------------------------------------------------------------------------
// MyApp.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "MyApp.h"
#include "../App/app.h"

namespace MyApp 
{

	void DrawBox(float sx, float sy, float h, float w, float r, float g, float b) {
		float ex = sx + w;
		float ey = sy + w;
		for (float c = sx; c <= sx + w; c += 1.0F) {
			App::DrawLine(c, sy, c, ey, r, g, b);
		}
	}

};
