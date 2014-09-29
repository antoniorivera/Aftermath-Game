#include "Bullet.h"
#include "PhotoLibrary.h"
#include <iostream>
#include <cmath>

Bullet::Bullet(int xPos, int yPos, float dir){
	dx = BULLET_SPEED * cos((dir * PI)/180); //converts from degrees to radians, makes dx how far left/right the bullet should travel
	dy = BULLET_SPEED * sin((dir * PI)/180);
	sprite.setTexture(PhotoLibrary::bulletTex);
	x = xPos + dx;
	y = yPos + dy;
	sprite.setOrigin(4, 4);
	sprite.setPosition(int(x) % WINDOW_WIDTH, int(y) % WINDOW_HEIGHT);
	harmful = true;
	//std::cout << "Bullet x " << x << std::endl;
	//std::cout << "Bullet y " << y << std::endl;
}

void Bullet::move(){
	sprite.move(dx, dy);
	x += dx;
	y += dy;
}

sf::Sprite* Bullet::getSprite(){
	return &sprite;
}

sf::Rect<int> Bullet::getRect(){
	return sf::Rect<int>(x, y, BULLET_WIDTH, BULLET_HEIGHT);
}

int Bullet::getX(){
	return x;
}

int Bullet::getY(){
	return y;
}

bool Bullet::isHarmful(){
	return harmful;
}