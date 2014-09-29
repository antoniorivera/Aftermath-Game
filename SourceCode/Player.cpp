#include "Player.h"
#include <cmath>
#include <iostream>
#include "PhotoLibrary.h"

Player::Player(int h, int m, int a, int d, int x, int y, int ts, sf::Texture& tex) : Entity(h, m, a, d, x, y, ts, tex){
	EXP = 0;
	level = 1;
	direction = RIGHT;

	font.loadFromFile("LiberationSans-Regular.ttf");
	text = sf::Text("100", font);
	text.setCharacterSize(20);
	text.setColor(sf::Color::Blue);

	fireExtinguisher = false; //make this false later!
	holdingGun = true;
}

sf::Sprite* Player::getArms(){
	return &armSprite;
}

void Player::move(int dx, int dy){
	Entity::move(dx, dy);
	armSprite.move(dx, dy);
}

void Player::setSpritePosition(){
	Entity::setSpritePosition();
	if (direction == RIGHT)
		armSprite.setPosition((getX() + 5) % WINDOW_WIDTH, (getY() + 16) % WINDOW_HEIGHT);
	else
		armSprite.setPosition((getX() + 27) % WINDOW_WIDTH, (getY() + 16) % WINDOW_HEIGHT);
}

void Player::setArmRotation(int mouseX, int mouseY){
	armX = armSprite.getPosition().x;
	armY = armSprite.getPosition().y;
	base = fabs(mouseX - armX);
	height = fabs(mouseY - armY);
	theta = (atan(height / base) * 180)/PI;
	//std::cout << "MouseX" << mouseX << std::endl;
	//std::cout << mouseY << std::endl;
	//std::cout << "armX" << armX << std::endl;
	//std::cout << armSprite.getPosition().y << std::endl;
	//std::cout << theta << std::endl;
	
	if (mouseX > armX){
		if (direction != RIGHT) //flips arms to face right
		{
			Entity::getSprite()->scale(-1, 1);
			armSprite.scale(-1, 1);
			armSprite.move(-22, 0);
			direction = RIGHT;
		}
		if (mouseY > armY){
			armSprite.setRotation(theta);
		}
		else{ //mouseY <= armY
			theta *= -1;
			armSprite.setRotation(theta);
		}
	}
	else{ //mouseX <= armX
		if (direction != LEFT)
		{
			Entity::getSprite()->scale(-1, 1);
			armSprite.scale(-1, 1);
			armSprite.move(22, 0);
			direction = LEFT;
		}
		if (mouseY > armY){
			theta *= -1;
			armSprite.setRotation(theta);
		}
		else{ //mouseY <= armY
			armSprite.setRotation(theta);
		}
	}
}

float Player::getTheta(){
	if (direction == RIGHT)
		return theta;
	else //direction == LEFT
		return (180 + theta);
}

//returns LOCAL rectangle (i.e. where is the player within the window)
sf::Rect<int> Player::getRect(){
	return sf::Rect<int>(getX() % 640, getY() % 640, 32, 32);
}

sf::Text* Player::getText(){
	return &text;
}

bool Player::takeDamage(int damage){
	HP -= damage;
	text.setString(std::to_string(HP));
	if (HP <= 20)
		text.setColor(sf::Color::Red);
	if (HP <= 0)
	{
		HP = 0;
		alive = false;
		setTexture(PhotoLibrary::bloodstainTex);
		text.setString(std::to_string(HP));
		return false;
	}
	else
		return true;
}

int Player::getArmX(){
	if (direction == LEFT)
		return getX() + 27;
	else
		return getX() + 5;
}

int Player::getArmY(){
	return getY() + 16;
}

bool& Player::hasFireExtinguisher(){ //returns a reference to fireExtinguisher
	return fireExtinguisher;
}

void Player::setArmTex(const sf::Texture& t){
	armSprite.setTexture(t);
}

bool& Player::isHoldingGun(){
	return holdingGun;
}

void Player::init_arms(){
	armSprite.setTexture(PhotoLibrary::armTex);
	armSprite.setOrigin(5, 16);
	armSprite.setPosition(getX() + 5, getY() + 16);
}