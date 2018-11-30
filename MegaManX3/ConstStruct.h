#ifndef  _ConstStruct_
#define _ConstStruct_

struct Size;
struct Point;
struct Retangle;
struct Speed;
struct Rect;
struct Viewport;
typedef Speed* LPSpeed;
typedef Rect* LPRect;




struct Size
{
	static const Size empty;
	int width = 0;
	int height = 0;

	Size(int width, int height)
		: width(width),
		height(height) {}
};

struct Point
{
	static const Point empty;
	int x = 0;
	int y = 0;

	Point(int x, int y)
		: x(x),
		y(y) {}
};

typedef struct Rectangle
{
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;

	Rectangle() { }

	Rectangle(Point location, Size size)
		: x(location.x),
		y(location.y),
		width(size.width),
		height(size.height) {}

	Rectangle(int x, int y, int width, int height)
		: x(x),
		y(y),
		width(width),
		height(height) {}

	int left() { return x; }
	int top() { return y; }
	int right() { return x + width; }
	int bottom() { return y + height; }
	int centerX() { return x + width / 2; }
	int centerY() { return y + height / 2; }
	void setRight(int right) { x = right - width; }
	void setBottom(int bottom) { y = bottom - height; }
	Size getSize() { return { width, height }; }
#pragma region contains
	bool contains(Point pt)
	{
		return contains(pt.x, pt.y, 0, 0);
	}
	bool contains(Point* pt)
	{
		return contains(pt->x, pt->y, 0, 0);
	}
	bool contains(Rectangle *rect)
	{
		return contains(rect->x, rect->y, rect->width, rect->height);
	}
	bool contains(Rectangle rect)
	{
		return contains(rect.x, rect.y, rect.width, rect.height);
	}
	bool contains(int x, int y, int width, int height)
	{
		return this->x < x && this->y < y && this->right() > x + width && this->bottom() > x + height;
	}
#pragma endregion

#pragma region Intersect
	bool intersectsWith(Rectangle* rect)
	{
		int top = max(this->y, rect->y);
		int bottom = min(this->bottom(), rect->bottom());
		int left = max(this->x, rect->x);
		int right = min(this->right(), rect->right());
		return bottom > top && right > left;
	}
	Rectangle intersect(Rectangle* rect)
	{
		int top = max(this->y, rect->y);
		int bottom = min(this->bottom(), rect->bottom());
		int left = max(this->x, rect->x);
		int right = min(this->right(), rect->right());
		if (bottom > top && right > left)
		{
			return { 0,0,0,0 };
		}
		else return Rectangle::fromLTRB(left, top, right, bottom);
	}

	static bool intersects(Rectangle* r1, Rectangle* r2)
	{
		int top = max(r1->y, r2->y);
		int bottom = min(r1->bottom(), r2->bottom());
		int left = max(r1->x, r2->x);
		int right = min(r1->right(), r2->right());
		return bottom > top && right > left;
	}
#pragma endregion

	static Rectangle fromLTRB(int left, int top, int right, int bottom)
	{
		return Rectangle(left, top, abs(right - left), abs(bottom - top));
	}
	RECT getRECT() {
		return { x, y, x + width, y + height };
	}
} CRectangle;

typedef struct Viewport {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;

	Viewport(int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	int left() { return x; }
	int right() { return x + width; }
	int top() { return y; }
	int bottom() { return y - height; }

	CRectangle getRectangle() {
		return { x, y - height, x + width,  y };
	}

	void setRight(int right) { x = right - width; }
	void setBottom(int bottom) { y = bottom + height; }
};




struct Rect
{
	int left;
	int top;
	int right;
	int bottom;

	Rect() { left = top = right = bottom = 0; }
	Rect(int left, int top, int right, int bottom)
		: left(left),
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
		: vx(vx),
		vy(vy) {}
};


#endif //  _ConstStruct_
