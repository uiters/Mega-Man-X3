#ifndef _ConstGlobals_
#define _ConstGlobals_

#include <d3d9.h>

#include "ConstStruct.h"
#include "ConstColor.h"
#include "ConstEnum.h"
#include "dinput.h"

#define CLASS_NAME L"MegaManX3"
#define TITLE L"Mega Man X3"

#define HLOGO L"icon.ico"
#define MAP L"map1.log"

#define WD_WIDTH 1240
#define WD_HEIGHT 700

#define WIDTH_QUADTREE 177;
#define HEIGHT_QUATREE 175;
#define MAX_LEVEL 5
#define FPS 60

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
extern Viewport*			viewPortGlobal;
extern LPDIRECTINPUTDEVICE8 didvGlobal;
extern LPDIRECTINPUT8       dinputGlobal;
#endif // _ConstGlobals_

