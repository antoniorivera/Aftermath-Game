#ifndef CAMERA_H_
#define CAMERA_H_

class Camera{
private:
	int x;
	int y;
	int width;
	int height;
	int tileSize;
	int mapWidth;
	int mapHeight;
public:
	Camera(int,int,int,int,int,int,int);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int rangeX1();
	int rangeX2();
	int rangeY1();
	int rangeY2();

	bool move(int,int);
};

#endif /* CAMERA_H_ */