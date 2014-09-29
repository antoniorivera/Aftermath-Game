#include "PhotoLibrary.h"

sf::Texture PhotoLibrary::soldierTex;
sf::Texture PhotoLibrary::armTex;
sf::Texture PhotoLibrary::armTexE;
sf::Texture PhotoLibrary::bulletTex;
sf::Texture PhotoLibrary::robotTex1;
sf::Texture PhotoLibrary::robotTex2;
sf::Texture PhotoLibrary::enemyTex;
sf::Texture PhotoLibrary::brickTex;
sf::Texture PhotoLibrary::grassTex;
sf::Texture PhotoLibrary::reticleTex;
sf::Texture PhotoLibrary::bloodstainTex;
sf::Texture PhotoLibrary::robotTex1R;
sf::Texture PhotoLibrary::fireTex;
sf::Texture PhotoLibrary::metalFloor;
sf::Texture PhotoLibrary::dust;
sf::Texture PhotoLibrary::dustRock;
sf::Texture PhotoLibrary::brickBrokenDust;
sf::Texture PhotoLibrary::brickBrokenGrass;
sf::Texture PhotoLibrary::skeletonTex;
sf::Texture PhotoLibrary::trapdoorTex;
sf::Texture PhotoLibrary::ss1;
sf::Texture PhotoLibrary::ss2;
sf::Texture PhotoLibrary::ss3;
sf::Texture PhotoLibrary::ss4;
sf::Texture PhotoLibrary::ss5;
sf::Texture PhotoLibrary::ss6;
sf::Texture PhotoLibrary::smokeTex;
sf::Texture PhotoLibrary::extinguisherTex;
sf::Texture PhotoLibrary::floorBlood1;
sf::Texture PhotoLibrary::floorBlood2;
sf::Texture PhotoLibrary::floorBloodR;
sf::Texture PhotoLibrary::floorBloodU;
sf::Texture PhotoLibrary::floorBloodN;
sf::Texture PhotoLibrary::metalWallTex;

void PhotoLibrary::initialize(){
	/*if (!soldierTex.loadFromFile("enemyArmless.png"))
		std::cout << "Error loading enemyArmless.png" << std::endl;*/
	if (!armTex.loadFromFile("arms.png"))
		std::cout << "Error loading arms.png" << std::endl;
	if (!armTexE.loadFromFile("arms_with_extinguisher.png"))
		std::cout << "Error loading arms_with_extinguisher.png" << std::endl;
	if (!bulletTex.loadFromFile("bulletPic.png"))
		std::cout << "Error loading bulletPic.png" << std::endl;
	if (!robotTex1.loadFromFile("robot.png"))
		std::cout << "Error loading robot.png" << std::endl;
	if (!robotTex2.loadFromFile("robot2.png"))
		std::cout << "Error loading robot2.png" << std::endl;
	if (!enemyTex.loadFromFile("enemy.png"))
		std::cout << "Error loading enemy.png" << std::endl;
	if (!brickTex.loadFromFile("brick.png"))
		std::cout << "Error loading brick.png" << std::endl;
	if (!grassTex.loadFromFile("grass.png"))
		std::cout << "Error loading grass.png" << std::endl;
	if (!reticleTex.loadFromFile("reticlePic.png"))
		std::cout << "Error loading reticlePic.png" << std::endl;
	if (!bloodstainTex.loadFromFile("bloodstain.png"))
		std::cout << "Error loading bloodstain.png" << std::endl;
	if (!robotTex1R.loadFromFile("robotR.png"))
		std::cout << "Error loading robotR.png" << std::endl;
	if (!fireTex.loadFromFile("fireanimation.png"))
		std::cout << "Error loading fireanimation.png" << std::endl;
	if (!metalFloor.loadFromFile("metal_floor.png"))
		std::cout << "Error loading metal_floor.png" << std::endl;
	if (!dust.loadFromFile("dust.png"))
		std::cout << "Error loading dust.png" << std::endl;
	if (!dustRock.loadFromFile("dust_rock.png"))
		std::cout << "Error loading dust_rock.png" << std::endl;
	if (!brickBrokenDust.loadFromFile("brick_broken_dust.png"))
		std::cout << "Error loading brick_broken_dust.png" << std::endl;
	if (!brickBrokenGrass.loadFromFile("brick_broken_grass.png"))
		std::cout << "Error loading brick_broken_grass.png" << std::endl;
	if (!skeletonTex.loadFromFile("skeletonanimation.png"))
		std::cout << "Error loading skeletonanimation.png" << std::endl;
	if (!trapdoorTex.loadFromFile("trapdoor.png"))
		std::cout << "Error loading trapdoor.png" << std::endl;
	if (!ss1.loadFromFile("space_capsule_1.png"))
		std::cout << "Error loading space_capsule_1.png" << std::endl;
	if (!ss2.loadFromFile("space_capsule_2.png"))
		std::cout << "Error loading space_capsule_2.png" << std::endl;
	if (!ss3.loadFromFile("space_capsule_3.png"))
		std::cout << "Error loading space_capsule_3.png" << std::endl;
	if (!ss4.loadFromFile("space_capsule_4.png"))
		std::cout << "Error loading space_capsule_4.png" << std::endl;
	if (!ss5.loadFromFile("space_capsule_5.png"))
		std::cout << "Error loading space_capsule_5.png" << std::endl;
	if (!ss6.loadFromFile("space_capsule_6.png"))
		std::cout << "Error loading space_capsule_6.png" << std::endl;
	if (!smokeTex.loadFromFile("smoke1.png"))
		std::cout << "Error loading smoke1.png" << std::endl;
	if (!extinguisherTex.loadFromFile("fire_extinguisher.png"))
		std::cout << "Error loading fire_extinguisher.png" << std::endl;
	if (!floorBlood1.loadFromFile("floor_blood1.png"))
		std::cout << "Error loading floor_blood1.png" << std::endl;
	if (!floorBlood2.loadFromFile("floor_blood2.png"))
		std::cout << "Error loading floor_blood2.png" << std::endl;
	if (!floorBloodR.loadFromFile("floorR.png"))
		std::cout << "Error loading floorR.png" << std::endl;
	if (!floorBloodU.loadFromFile("floorU.png"))
		std::cout << "Error loading floorU.png" << std::endl;
	if (!floorBloodN.loadFromFile("floorN.png"))
		std::cout << "Error loading floorN.png" << std::endl;
	if (!metalWallTex.loadFromFile("metal_wall.png"))
		std::cout << "Error loading metal_wall.png" << std::endl;
}