#include "CKey.h"



int CKey::isKeyDown(int keyCode)
{
	return (keyStates[keyCode] & 0x80) > 0;
}


void CKey::processKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didvGlobal->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didvGlobal->Acquire();
			if (h != DI_OK)
				return;
		}
		else
		{
			return;
		}
	}

	keyState((BYTE *)&keyStates);


	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didvGlobal->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
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
			onKeyDown(KeyCode);
		else
			onKeyUp(KeyCode);
	}
}

