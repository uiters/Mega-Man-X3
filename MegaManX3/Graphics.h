#ifndef __Graphics_H__
#define __Graphics_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "ConstGlobals.h"
namespace Graphics {
	class Draw {
	public:
		virtual void draw(float x, float y, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void drawFlip(int x, int y, bool isLeft, float width, float height, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};
	class Render {
		virtual void render(float x, float y, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void renderFlip(int x, int y, bool isLeft, float width, float height, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};
};

#endif // !_Graphics.h_
