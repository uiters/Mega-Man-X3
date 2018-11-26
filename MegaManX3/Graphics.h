#ifndef __Graphics_H__
#define __Graphics_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "ConstGlobals.h"
class Game;
namespace Graphics {
	class Draw {
	public:
		virtual void draw(int x, int y, bool center = false,  D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void drawFlipX(int x, int y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void drawFlipY(int x, int y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};

	class Render {
		virtual void render(int x, int y, bool center = false , D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void renderFlipX(int x, int y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void renderFlipY(int x, int y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};
};

#endif // !_Graphics.h_
