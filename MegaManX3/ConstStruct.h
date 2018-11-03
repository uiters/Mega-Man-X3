#ifndef  _ConstStruct_
#define _ConstStruct_

struct Speed;
struct Rect;

typedef Speed* LPSpeed;
typedef Rect* LPRect;

struct Rect
{
	float left;
	float top;
	float right;
	float bottom;

	Rect(float left, float top, float right, float bottom) 
	:	left(left), 
		top(top), 
		right(right), 
		bottom(bottom) {}
};


struct Speed
{
	float vx;
	float vy;

	Speed(float vx, float vy) 
	:	vx(vx),
		vy(vy) 
	{}
};


#endif //  _ConstStruct_
