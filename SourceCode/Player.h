#ifndef PLAYER_H_
#define PLAYER_H_

#define PI 3.141592653589793238

#include "Entity.h"

class Player: public Entity{
	private:
		enum direction_t {LEFT, RIGHT};
		direction_t direction;
		int EXP, level; //add weapon and armor later
		float armX, armY, base, height, theta; //just for calculation purposes, not for drawing
		sf::Sprite armSprite;
		sf::Font font;
		sf::Text text;
		bool fireExtinguisher;
		bool holdingGun;
	public:
		Player(int, int, int, int, int, int, int, sf::Texture&);
		sf::Sprite* getArms();
		sf::Rect<int> getRect();
		sf::Text *getText();
		void move(int, int); //overriding parent method
		void setSpritePosition(); //overriding parent method
		void setArmRotation(int,int);
		void setArmTex(const sf::Texture&);
		void init_arms();
		float getTheta();
		bool takeDamage(int);
		bool& hasFireExtinguisher(); //returns a reference
		bool& isHoldingGun(); //returns a reference
		int getArmX();
		int getArmY();
};

#endif /* PLAYER_H_ */