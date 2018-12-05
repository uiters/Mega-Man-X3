#include "Camera.h"


Camera::Camera(int x, int y, int width, int height) : viewport(x, y, width, height)
{

}

void Camera::update(int x, int y, int height) //center x, center y
{
	int centerScreenX = viewport.width / 2;
	int centerScreenY = viewport.height / 2;

	viewport.x = x - centerScreenX; // hold character center of camera
	viewport.y = y - centerScreenY;

	//if (viewport.x < world.left)
	//	viewport.x = world.left;

	//if (viewport.right() > world.right)
	//	viewport.setX(world.right);

	//if (viewport.y > world.top)
	//	viewport.y = world.top;

	/*if (viewport.bottom() < world.bottom - height / 4)
		viewport.setY(world.bottom - height / 4);*/
}

void Camera::setSizeWorld(int x, int y, int width, int height)
{
	world.left = x;
	world.right = y;
	world.right = width + x;
	world.bottom = height + y;
}

const Point& Camera::transform(const int& x, const int& y) const
{
	return { x - viewport.x, y - viewport.y };
}