#include "Tile.h"

Tile::Tile(){
	defaultTexture.loadFromFile("brick.png");
	sprite.setTexture(defaultTexture);
	passable = true;
	sprite.setPosition(0, 0);
}

Tile::Tile(int x, int y, bool p, sf::Texture & t){
	passable = p;
	sprite.setTexture(t);
	sprite.setPosition(x%640, y%640);
}

sf::Sprite * Tile::getSprite(){
	return &sprite;
}

bool Tile::isPassable(){
	return passable;
}

void Tile::setPassable(bool b){
	passable = b;
}