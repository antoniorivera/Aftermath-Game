#include "Smoke.h"
#include "PhotoLibrary.h"

Smoke::Smoke(int xPos, int yPos, double dir) : Bullet(xPos, yPos, dir){
	harmful = false;
	sprite.setTexture(PhotoLibrary::smokeTex);
	sprite.setOrigin(8, 8);
	//slows down the smoke
	dx = dx/2;
	dy = dy/2;
}