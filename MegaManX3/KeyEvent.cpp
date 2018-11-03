#include "KeyEvent.h"
void KeyEvent::OnKeyUp(int keyCode)
{

	//code here--------------------------------------



	//------------------------------------------------
}
void KeyEvent::OnKeyDown(int keyCode)
{

	//code here--------------------------------------
	if (keyCode == 205)
		main->x -= 100;
	else if(keyCode == 203)
	{
		main->x += 100;
	}
	else if(keyCode == 200)
	{
		main->y += 100;
	}
	else if(keyCode == 208)
	{
		main->y -= 100;
	}


	//------------------------------------------------
}
void KeyEvent::KeyState(BYTE* states)
{

	//code here--------------------------------------



	//------------------------------------------------
}



KeyEvent::~KeyEvent()
{
}
