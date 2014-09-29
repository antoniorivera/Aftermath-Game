#include "Entity.h"
#include "PhotoLibrary.h"

//constructor
Entity::Entity(int h, int m, int a, int d, int x, int y, int ts, sf::Texture t){
	HP = h;
	MP = m;
	Atk = a;
	Def = d;
	this->x = x;
	this->y = y;
	tileSize = ts; //useless???
	texture = t;
	sprite.setTexture(texture);
	sprite.setOrigin(16,16);
	sprite.setPosition((x+16) % 640,(y+16) % 640);
	alive = true;
}

int Entity::getHP() const{
	return HP;
}

int Entity::getMP(){
	return MP;
}

int Entity::getAtk(){
	return Atk;
}

int Entity::getDef(){
	return Def;
}

int Entity::getX() const{
	return x;
}

int Entity::getY() const{
	return y;
}

void Entity::heal(int d){
	HP += d;
}

//takeDamage returns "true" if the character is still alive, false if they are now dead
bool Entity::takeDamage(int d){
	HP -= d;
	if (HP <= 0){
		setTexture(PhotoLibrary::bloodstainTex);
		alive = false;
		return false;
	}
	else
		return true;
}

bool Entity::isAlive(){
	return alive;
}

//obsolete now, with the move() method. kept as reference for the Vector2f usage
/*void Entity::left(){
	X -= 4;
	sprite.move(sf::Vector2f(-4, 0));
}*/

void Entity::move(int dx, int dy){
	x += dx;
	y += dy;
	sprite.move(dx, dy);
}

sf::Sprite* Entity::getSprite(){
	return &sprite;
}

void Entity::setTexture(sf::Texture t){
	texture = t;
	//sprite.setTexture(texture);
}

void Entity::setSpritePosition(){
	sprite.setPosition((x+16) % WINDOW_WIDTH, (y+16) % WINDOW_HEIGHT);
}

void Entity::setSpritePosition(int x, int y){
	sprite.setPosition((x+16) % WINDOW_WIDTH, (y+16) % WINDOW_HEIGHT);
}