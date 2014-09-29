#ifndef BULLET_H_
#define BULLET_H_

#define PI 3.141592653589793238
#define BULLET_SPEED 16 //in units of pixels/update
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640
#define BULLET_WIDTH 8
#define BULLET_HEIGHT 8
#include <SFML/Graphics.hpp>

class Bullet{
	private:
		float x;
		float y;

	protected:
		bool harmful;
		sf::Sprite sprite;
		float dx;
		float dy;

	public:
		Bullet(int,int,float); //x,y,direction
		void move();
		sf::Sprite *getSprite();
		sf::Rect<int> getRect();
		int getX();
		int getY();
		bool isHarmful();
};

#endif /* BULLET_H_ */