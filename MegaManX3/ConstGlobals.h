#ifndef _ConstGlobals_
#define _ConstGlobals_

#include <d3d9.h>
#include <dinput.h>

#include "ConstStruct.h"
#include "ConstColor.h"
#include "ConstEnum.h"
#include "ConstDefine.h"


class GameObject;
typedef GameObject* LPObject;

class Game;
class CKey;
class CTextures;
class CSprites;
class CAnimations;
class Camera;

extern HINSTANCE			hInstanceGlobal;
extern Game*				gameGlobal;
extern HWND					hWndGlobal;
extern CKey*				keyGlobal;
extern CTextures*			texturesGlobal;
extern CSprites*			spritesGlobal;
extern CAnimations*			animationsGlobal;
extern Camera*				cameraGlobal;
extern CRectangle*			viewPortGlobal;
extern LPDIRECTINPUTDEVICE8 didvGlobal;
extern LPDIRECTINPUT8       dinputGlobal;

#endif // _ConstGlobals_

