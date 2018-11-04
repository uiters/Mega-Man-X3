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

	Rect() { left = top = right = bottom = 0; }
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
	Speed() { vx = vy = 0; }
	Speed(float vx, float vy) 
	:	vx(vx),
		vy(vy) 
	{}
};

struct Viewport
{
	float x, y;
	float width, height;

	Viewport() { x = y = width = height = 0; }
	Viewport(float x, float y, float width = 0, float height = 0) : x(x), y(y), width(width), height(height) {}


	float left() { return x; }
	float top() { return y; }
	float right() { return x + width; }
	float bottom() { return y + height; }
	void getBox(float &left, float &top, float &right, float &bottom) {
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}

	void setRight(float right) { x = right - width; }
	void setBottom(float bottom) { y = bottom - height; }
};

#endif //  _ConstStruct_
