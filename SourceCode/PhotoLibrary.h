#ifndef PHOTO_LIBRARY_H_
#define PHOTO_LIBRARY_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class PhotoLibrary{
	public:
		static sf::Texture soldierTex;
		static sf::Texture armTex;
		static sf::Texture armTexE; //arms holding fire extinguisher
		static sf::Texture bulletTex;
		static sf::Texture robotTex1;
		static sf::Texture robotTex2;
		static sf::Texture enemyTex;
		static sf::Texture brickTex;
		static sf::Texture grassTex;
		static sf::Texture reticleTex;
		static sf::Texture bloodstainTex;
		static sf::Texture robotTex1R;
		static sf::Texture fireTex;
		static sf::Texture metalFloor;
		static sf::Texture dust;
		static sf::Texture dustRock;
		static sf::Texture brickBrokenGrass;
		static sf::Texture brickBrokenDust;
		static sf::Texture skeletonTex;
		static sf::Texture trapdoorTex;
		static sf::Texture ss1; //space ship part 1
		static sf::Texture ss2;
		static sf::Texture ss3;
		static sf::Texture ss4;
		static sf::Texture ss5;
		static sf::Texture ss6;
		static sf::Texture smokeTex;
		static sf::Texture extinguisherTex;
		static sf::Texture floorBlood1;
		static sf::Texture floorBlood2;
		static sf::Texture floorBloodR;
		static sf::Texture floorBloodU;
		static sf::Texture floorBloodN;
		static sf::Texture metalWallTex;

		static void initialize();
};

#endif /* PHOTO_LIBRARY_H_ */