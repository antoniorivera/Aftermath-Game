#include "Camera.h"

//constructor
Camera::Camera(int inX, int inY, int inWidth, int inHeight, int inTileSize, int inMapWidth, int inMapHeight){
	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	tileSize = inTileSize;
	mapWidth = inMapWidth;
	mapHeight = inMapHeight;
}

bool Camera::move(int dx, int dy){
	bool cameraMoved = true;
	x += dx; 

	//edge cases (camera doesn't actually move)
	if (x < 0){
		x = 0;
		cameraMoved = false;
	}
	else if (x + width > mapWidth){
		x = mapWidth - width;
		cameraMoved = false;
	}

	y += dy;

	//edge cases (camera doesn't actually move)
	if (y < 0){
		y = 0;
		cameraMoved = false;
	}
	else if (y + height > mapHeight){
		y = mapHeight - height;
		cameraMoved = false;
	}
	return cameraMoved;
}

int Camera::getX(){
	return x;
}

int Camera::getY(){
	return y;
}

int Camera::getWidth(){
	return width;
}

int Camera::getHeight(){
	return height;
}

int Camera::rangeX1(){
	return (x >> 5);
}

int Camera::rangeX2(){
	return ((x + width) >> 5);
}

int Camera::rangeY1(){
	return (y >> 5);
}

int Camera::rangeY2(){
	return ((y + height) >> 5);
}