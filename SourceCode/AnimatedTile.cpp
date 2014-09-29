#include "AnimatedTile.h"

AnimatedTile::AnimatedTile() :Tile(){
	//just empty space; will be ignored when drawing
	ignore = true;
}

AnimatedTile::AnimatedTile(int x, int y, bool p, sf::Texture& t, bool inFire):Tile(x,y,p,t){
	r1 = sf::Rect<int>(0, 0, 32, 32);
	r2 = sf::Rect<int>(32, 0, 32, 32);
	frame1 = true;
	ignore = false;
	fire = inFire;
}

sf::Sprite* AnimatedTile::getSprite(){
	if (frame1 && timer.getElapsedTime().asSeconds() > .5)
	{
		timer.restart();
		sprite.setTextureRect(r2);
		frame1 = false;
	}
	else if (!frame1 && timer.getElapsedTime().asSeconds() > .5)
	{
		timer.restart();
		sprite.setTextureRect(r1);
		frame1 = true;
	}

	return &sprite;
}

bool& AnimatedTile::ignorable(){
	return ignore;
}

bool AnimatedTile::isFire(){
	return fire;
}