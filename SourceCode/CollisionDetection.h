#ifndef COLLISION_DETECTION_
#define COLLISION_DETECTION_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "Camera.h"
#include "AnimatedTile.h"
#include "Enemy.h"

class CollisionDetection{
	private:
		static sf::RenderWindow * window;
		static Camera * camera;
		typedef unsigned char byte;

	public:
		static enum location_t {SURFACE, UNDERGROUND};
		static location_t location;
		static const unsigned int EMPTY_SPACE = 0;
		static const unsigned int MAP_WIDTH = 80;
		static const unsigned int MAP_HEIGHT = 40;
		static Tile map[MAP_HEIGHT][MAP_WIDTH];
		static AnimatedTile animationMap[MAP_HEIGHT][MAP_WIDTH];
		static int spawnMap[MAP_HEIGHT][MAP_WIDTH];
		static Tile undergroundMap[MAP_HEIGHT][MAP_WIDTH];
		static AnimatedTile undergroundAnimationMap[MAP_HEIGHT][MAP_WIDTH];
		static int undergroundSpawnMap[MAP_HEIGHT][MAP_WIDTH];

		static void changeLocation(location_t);
		static void drawMap();
		static void initialize(sf::RenderWindow *, Camera*);
		static void collisionWithEnemy(std::vector<Entity>, Player);
		static bool validMove(int,int); //takes in map (2D int array) and player 
		static void spawnEnemies(std::vector<Enemy>&);
		static location_t getLocation();
		//add weapon collision detection later
};

#endif /* COLLISION_DETECTION_ */