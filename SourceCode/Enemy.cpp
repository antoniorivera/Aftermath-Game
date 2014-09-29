#include "Enemy.h"
#include "PhotoLibrary.h"
#include "CollisionDetection.h"

Enemy::Enemy(int h, int m, int a, int d, int xin, int yin, int ts):Entity(h,m,a,d,xin,yin,ts,PhotoLibrary::robotTex1){
	dx = 0;
	dy = 0;
	intelligentMovements = false;
	left = false;
	up = false;
	direction = LEFT;
}

Enemy::Enemy(Enemy const& other):Entity(other.getHP(), 1, 1, 1,other.getX(),other.getY(),32,PhotoLibrary::robotTex1){
	dx = 0;
	dy = 0;
	intelligentMovements = false;
	left = false;
	up = false;
	direction = LEFT;
}

void Enemy::move(Player *p){
	//if (!intelligentMovements)
	//{
		if (p->getX() == getX())
			dx = 0;
		else //use ternary operator
			(p->getX() < getX()) ? (dx = -ENEMY_SPEED, left = true) : (dx = ENEMY_SPEED, left = false);
		
		if (p->getY() == getY())
			dy = 0;
		else
			(p->getY() < getY()) ? (dy = -ENEMY_SPEED, up = true) : (dy = ENEMY_SPEED, up = false);

		if (up && left)
		{
			if (CollisionDetection::validMove((getX() + dx) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + dx) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(dx, dy);
			else if (CollisionDetection::validMove((getX() + dx) >> 5, (getY()) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY()) >> 5) && CollisionDetection::validMove((getX() + dx) >> 5, (getY() + 32) >> 5))
				Entity::move(dx, 0);
			else if (CollisionDetection::validMove((getX()) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX()) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(0, dy);
			else
				intelligentMovements = true;
		}
		else if (up && !left) //up right
		{
			if (CollisionDetection::validMove((getX() + dx) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(dx, dy);
			else if (CollisionDetection::validMove((getX() + dx) >> 5, (getY()) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY()) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + 32) >> 5))
				Entity::move(dx, 0);
			else if (CollisionDetection::validMove((getX()) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(0, dy);
			else
				intelligentMovements = true;
		}
		else if (!up && left) //down left
		{
			if (CollisionDetection::validMove((getX() + dx) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + 32 + dy) >> 5) && CollisionDetection::validMove((getX() + dx) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(dx, dy);
			else if (CollisionDetection::validMove((getX() + dx) >> 5, (getY()) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + 32) >> 5) && CollisionDetection::validMove((getX() + dx) >> 5, (getY() + 32) >> 5))
				Entity::move(dx, 0);
			else if (CollisionDetection::validMove((getX()) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + 32) >> 5, (getY() + 32 + dy) >> 5) && CollisionDetection::validMove((getX()) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(0, dy);
			else
				intelligentMovements = true;
		}
		else //down right
		{
			if (CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + 32 + dy) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX() + dx) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(dx, dy);
			else if (CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY() + 32) >> 5) && CollisionDetection::validMove((getX() + 32 + dx) >> 5, (getY()) >> 5) && CollisionDetection::validMove((getX() + dx) >> 5, (getY() + 32) >> 5))
				Entity::move(dx, 0);
			else if (CollisionDetection::validMove((getX() + 32) >> 5, (getY() + 32+ dy) >> 5) && CollisionDetection::validMove((getX() + 32) >> 5, (getY() + dy) >> 5) && CollisionDetection::validMove((getX()) >> 5, (getY() + 32 + dy) >> 5))
				Entity::move(0, dy);
			else
				intelligentMovements = true;
		}

		if (dx > 0 && direction != RIGHT)
		{
			direction = RIGHT;
			setTexture(PhotoLibrary::robotTex1R);
		}
		else if (dx < 0 && direction != LEFT)
		{
			direction = LEFT;
			setTexture(PhotoLibrary::robotTex1);
		}
	//}
	//time for some A* planning. Last resort, since it's resource-heavy
	/*else
	{

	}*/
}

/*bool Enemy::isAlive(){
	if (getHP() <= 0)
	{
		Enemy::setTexture(PhotoLibrary::bloodstainTex);
		return false;
	}
	else
		return true;
}*/

//global rectangle
sf::Rect<int> Enemy::getRect(){ 
	return sf::Rect<int>(getX(), getY(), 32, 32);
}

sf::Rect<int> Enemy::getLocalRect(){
	return sf::Rect<int>(getX() % WINDOW_WIDTH, getY() % WINDOW_HEIGHT, 32, 32);
}

sf::Rect<int> Enemy::getPotRect(Player* p){
	if (p->getX() % WINDOW_WIDTH == getX())
		dx = 0;
	else
		(p->getX() < getX()) ? dx = -ENEMY_SPEED : dx = ENEMY_SPEED;

	if (p->getY() == getY())
		dy = 0;
	else
		(p->getY() < getY()) ? dy = -ENEMY_SPEED : dy = ENEMY_SPEED;

	return sf::Rect<int>(getX() + dx, getY() + dy, 32, 32);
}