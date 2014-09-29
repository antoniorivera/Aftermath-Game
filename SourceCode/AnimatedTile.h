#ifndef ANIMATED_TILE_H_
#define ANIMATED_TILE_H_

#include "Tile.h"
#include "PhotoLibrary.h"

class AnimatedTile: public Tile{
private:
	sf::Clock timer;
	sf::Rect<int> r1;
	sf::Rect<int> r2;
	bool frame1;
	bool ignore;
	bool fire;

public:
	AnimatedTile();
	AnimatedTile(int, int, bool, sf::Texture&, bool);
	sf::Sprite* getSprite();
	bool& ignorable();
	bool isFire();
};

#endif /* ANIMATED_TILE_H_ */