#include "Game.h"
Game* Game::__instance = NULL;

HWND CreateGameWindow(int nCmdShow);

void Game::Init(int nCmdShow) {

	HWND hWnd =  CreateGameWindow(nCmdShow);

	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->hWnd = hWnd;

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

}

Game::Game()
{
}

int Game::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void Game::ProcessKeyboard()
{
	if (keyHandler == NULL) return;
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates),(LPVOID) & keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h != DI_OK)
				return;
		}
		else
		{
			return;
		}
	}

	keyHandler->KeyState((BYTE *)&keyStates);



	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

void Game::InitKeyboard(LPKeyEventHandler handler)
{
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		return;
	}
	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	if (hr != DI_OK) {
		return;
	}







	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		return;
	}

	this->keyHandler = handler;


}




Game *Game::GetInstance()
{
	if (__instance == NULL) __instance = new Game();
	return __instance;
}

void Game::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, D3DCOLOR colorBrush) {
	D3DXVECTOR3 p(x, y, 0);
	spriteHandler->Draw(texture, NULL, NULL, &p, colorBrush);
}

void Game::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DCOLOR colorBrush)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	spriteHandler->Draw(texture, &r, NULL, &p, colorBrush);
}

void Game::DrawFlipX(int x, int y,LPDIRECT3DTEXTURE9 texture, float width, float height, D3DCOLOR colorBrush)
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + width / 2, y + height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	spriteHandler->SetTransform(&finalMt);

	x += width;
	Draw(x, y, texture, colorBrush);

	spriteHandler->SetTransform(&oldMt);
}

Game::~Game()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
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
	wc.hInstance = G_hInstance;

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

	HWND hWnd = CreateWindow(CLASS_NAME, TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WD_WIDTH, WD_HEIGHT, NULL, NULL, G_hInstance, NULL);

	if (!hWnd) return 0;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

