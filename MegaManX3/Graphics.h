#ifndef __Graphics_H__
#define __Graphics_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "ConstGlobals.h"
class Game;
namespace Graphics {
	class Draw {
	public:
		virtual void draw(float x, float y, bool center = false,  D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void drawFlipX(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void drawFlipY(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};

	class Render {
		virtual void render(float x, float y, bool center = false , D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void renderFlipX(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void renderFlipY(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};
};

#endif // !_Graphics.h_
