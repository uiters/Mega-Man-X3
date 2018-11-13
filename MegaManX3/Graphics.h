#ifndef __Graphics_H__
#define __Graphics_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "ConstGlobals.h"
#include "Game.h"
class Game;
namespace Graphics {
	class Draw {
	protected:
		void _draw(LPDIRECT3DTEXTURE9 texture, RECT *pSrcRect, D3DXVECTOR3* center, D3DXVECTOR3* pos, D3DCOLOR colorBrush = WHITE(255))
		{
			gameGlobal->getSpriteHandler()->Draw(texture, pSrcRect, center, pos, colorBrush);
		}
	public:
		virtual void draw(int x, int y, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void drawCenter(int x, int y, D3DCOLOR colorBrush = WHITE(255)) = 0;

		virtual void drawFlip(int x, int y, bool isX = true, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void drawFlipCenter(int x, int y, bool isX = true, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};

	class Render {
		virtual void render(int x, int y, bool center, D3DCOLOR colorBrush = WHITE(255)) = 0;
		virtual void renderFlip(int x, int y, bool isX = true, bool center = false, D3DCOLOR colorBrush = WHITE(255)) = 0;
	};
};

#endif // !_Graphics.h_
