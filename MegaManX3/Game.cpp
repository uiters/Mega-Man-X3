#include "Game.h"

HWND CreateGameWindow(int nCmdShow);
HRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Game::superRender(DWORD dt)
{
	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(backBuffer, NULL, WHITE(255));
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		render(dt);
		spriteHandler->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void Game::init(int nCmdShow) {

	HWND hWnd =  CreateGameWindow(nCmdShow);

	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	hWndGlobal = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT rectangle;
	GetClientRect(hWnd, &rectangle);
	d3dpp.BackBufferHeight = rectangle.bottom + 1;
	d3dpp.BackBufferWidth = rectangle.right + 1;
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddv);
	if (!d3ddv) return;
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	D3DXCreateSprite(d3ddv, &spriteHandler);

	initKeyboard();
	initGolbals();
	loadResource();
	initOption();
}

void Game::initKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWndGlobal, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&dinputGlobal, NULL
		);

	if (hr != DI_OK)
	{
		debugOut(L"[FAILED] Create Input8");
		return;
	}
	hr = dinputGlobal->CreateDevice(GUID_SysKeyboard, &didvGlobal, NULL);

	if (hr != DI_OK) {
		debugOut(L"[FAILED] Create Key");
		return;
	}
	hr = didvGlobal->SetDataFormat(&c_dfDIKeyboard);

	hr = didvGlobal->SetCooperativeLevel(hWndGlobal, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didvGlobal->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didvGlobal->Acquire();
	if (hr != DI_OK)
	{
		debugOut(L"[FAILED] Require Key");
		return;
	}
}


void Game::run()
{
	MSG msg;
	int done = 0;
	DWORD timeStart = GetTickCount();
	while (!done) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DWORD dt = now - timeStart;
		if (dt >= timePerFarme) {
			timeStart = now;

			update(dt);
			superRender(dt);

		}
		else
			Sleep(timePerFarme - dt);
	}
}

LPDIRECT3DDEVICE9 Game::getDirect3DDevice()
{
	return d3ddv;
}

LPDIRECT3DSURFACE9 Game::getBackBuffer()
{
	return backBuffer;
}

LPD3DXSPRITE Game::getSpriteHandler()
{
	return spriteHandler;
}

HRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HWND CreateGameWindow(int nCmdShow) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstanceGlobal;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//wc.hIcon = 0;//LoadIcon(0, MB_ICONINFORMATION);
	HICON icon = (HICON)LoadImage(NULL, HLOGO, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hIcon = icon;//
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = icon;// LoadIcon(0, IDI_QUESTION);


	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(CLASS_NAME, TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WD_WIDTH, WD_HEIGHT, NULL, NULL, hInstanceGlobal, NULL);

	if (!hWnd) return 0;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

