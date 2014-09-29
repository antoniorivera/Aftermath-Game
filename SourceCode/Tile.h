#ifndef TILE_H_
#define TILE_H_

#include <SFML/Graphics.hpp>

class Tile{
	public:
		bool isPassable();
		void setPassable(bool);
		Tile();
		Tile(int,int,bool,sf::Texture&);
		virtual sf::Sprite * getSprite();

	protected:
		sf::Texture defaultTexture;
		sf::Sprite sprite;
		sf::Clock timer;
		bool passable;
};

#endif /* TILE_H_ */