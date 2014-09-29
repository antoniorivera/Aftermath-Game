#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_SPEED 2

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include <string>

class Enemy: public Entity{
	
	public:
		Enemy(int, int, int, int, int, int, int);
		Enemy(Enemy const& other); //copy constructor
		void move(Player*);
		//bool isAlive();
		sf::Rect<int> getRect();
		sf::Rect<int>getLocalRect();
		sf::Rect<int> getPotRect(Player*);//potential new position rectangle
	private:
		int dx;
		int dy;
		bool intelligentMovements;
		bool left;
		bool up;
		std::vector<std::string> path;
		enum direction_t {LEFT, RIGHT};
		direction_t direction;
};

#endif /* ENEMY_H_ */