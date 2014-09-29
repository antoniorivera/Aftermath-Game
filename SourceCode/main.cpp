#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include "Entity.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "CollisionDetection.h"
#include "Bullet.h"
#include "PhotoLibrary.h"
#include "Smoke.h"

void interpretKeysMap(Player*,Camera*); //prototype function
void interpretKeysBattle(Player*, Enemy*); //prototype function
void interpretMouse(Player*, sf::RenderWindow*);
void loadAssets(sf::RenderWindow*, Camera*, Player*);

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 32;

int i = 0; //for any general for loops (NOT for vectors; use iterators there)
int j = 0; //same as above
int x = 0; //for bullet checks
int y = 0; //for bullet checks
int mouseX = 0;
int mouseY = 0;

bool bulletHit = false;
bool areaClear = false;
bool validEnemyMove = false;

enum gamestates_t {MAP, BATTLE, LOADING};
gamestates_t currentState = LOADING;

//bullet vector and iterator
std::vector<Bullet> bullets;
std::vector<Bullet>::iterator it;

//enemy vector and iterator
std::vector<Enemy> enemies;
std::vector<Enemy>::iterator enemiesIt;

std::vector<Enemy> deadEnemies;

//next 2 lines for testing purposes; REMOVE before release
sf::Clock timer;
sf::Time t;

sf::Clock bulletTimer;
sf::Sprite reticle;
sf::Sprite extinguisherSprite;
sf::RectangleShape progressBar;
sf::RectangleShape progressBarContainer;
Player* player;
sf::Clock startupTimer;

int main()
{
	sf::Texture loadTex;
	sf::Texture playerTex;
	if (!loadTex.loadFromFile("loading_screen.png"))
		std::cout << "Error loading loading_screen.png" << std::endl;
	if (!playerTex.loadFromFile("enemyArmless.png"))
		std::cout << "Error loading enemyArmless.png" << std::endl;
	sf::Sprite loadSprite;
	loadSprite.setTexture(loadTex);
	currentState = LOADING;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Aftermath -- By Antonio Rivera, 2014", sf::Style::Close);
	window.setMouseCursorVisible(false);
	Player p(100, 1, 1, 1, 192, 256, 32, playerTex);
	Camera c(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, CollisionDetection::MAP_WIDTH * 32, CollisionDetection::MAP_HEIGHT * 32);
	
	//progress bar for loading screen
	progressBar.setSize(sf::Vector2f(20, 50));
	progressBar.setPosition(20, 500);
	progressBar.setFillColor(sf::Color::Green);
	
	progressBarContainer.setSize(sf::Vector2f(604,54));
	progressBarContainer.setPosition(18, 498);
	progressBarContainer.setOutlineColor(sf::Color::Black);
	progressBarContainer.setOutlineThickness(2);
	progressBarContainer.setFillColor(sf::Color::White);

	//starts thread to load everything
	std::thread loadThread(loadAssets, &window, &c, &p);
	//std::cout << "Starting thread " << loadThread.get_id() << std::endl;
	/*enemies.push_back(Enemy(10, 3, 2, 1, 32, 32, 32));
	enemies.push_back(Enemy(10, 3, 2, 1, 400, 50, 32));
	enemies.push_back(Enemy(10, 3, 2, 1, 40, 500, 32));
	enemies.push_back(Enemy(10, 3, 2, 1, 100, 500, 32));
	enemies.push_back(Enemy(10, 3, 2, 1, 100,30, 32));
	enemies.push_back(Enemy(10, 3, 2, 1, 150, 500, 32));*/

	//can use either vsync or you can manually set framerate. note: This affects thread update speed!
	//for release version, to assure the game runs at the same speed on all computers, set the 
	//framerate manually! monitors refresh at different speeds, and this will affect how fast the player moves
	//and how fast the game updates
	//set to 60 and comment out "window.setVerticalSyncEnabled(true);"
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	//shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) //game loop
	{
		sf::Event event;

		//handles key events
		//add conditions later for menus, if desired
		//if (sf::Event::KeyPressed)
			//interpretKeysMap(&p, &c);

		if (p.isAlive())
		{
			interpretKeysMap(&p, &c);
			interpretMouse(&p, &window);

			if (areaClear == false)
			{
				areaClear = true;
				for (i = enemies.size(); --i >= 0;)
				{
					validEnemyMove = true;
					if (enemies[i].isAlive())
					{
						for (j = enemies.size(); --j >= 0;)
						{
							if (j == i || !enemies[j].isAlive())
								continue;
							else
							{
								if (enemies[j].getRect().intersects(enemies[i].getPotRect(&p)))
								{
									validEnemyMove = false;
									break;
								}
							}
						}
						if (validEnemyMove)
							enemies[i].move(&p);
						if (p.getRect().intersects(enemies[i].getLocalRect()))
							p.takeDamage(1);
						areaClear = false;
					}
				}
			}

			for (it = bullets.begin(); it != bullets.end();)
			{
				it->move();
				x = it->getX();
				y = it->getY();

				if (!it->isHarmful() && CollisionDetection::getLocation() == CollisionDetection::SURFACE && !CollisionDetection::animationMap[it->getY() >> 5][it->getX() >> 5].ignorable() && CollisionDetection::animationMap[it->getY() >> 5][it->getX() >> 5].isFire())
				{
					CollisionDetection::animationMap[it->getY() >> 5][it->getX() >> 5].ignorable() = true;
					CollisionDetection::map[it->getY() >> 5][it->getX() >> 5].setPassable(true);
					it = bullets.erase(it);
				}
				else if (!it->isHarmful() && CollisionDetection::getLocation() == CollisionDetection::UNDERGROUND && !CollisionDetection::undergroundAnimationMap[it->getY() >> 5][it->getX() >> 5].ignorable() && CollisionDetection::undergroundAnimationMap[it->getY() >> 5][it->getX() >> 5].isFire())
				{
					CollisionDetection::undergroundAnimationMap[it->getY() >> 5][it->getX() >> 5].ignorable() = true;
					CollisionDetection::undergroundMap[it->getY() >> 5][it->getX() >> 5].setPassable(true);
					it = bullets.erase(it);
				}
				else if (x > c.getX() + c.getWidth() || x < c.getX() || y > c.getY() + c.getHeight() || y < c.getY() || !CollisionDetection::validMove(it->getX() >> 5, it->getY() >> 5))
					it = bullets.erase(it);
				else
				{
					bulletHit = false;
					for (i = enemies.size(); --i >= 0;)
					{
						//std::cout << "Left: " << enemies[i].getRect()->left << " Top: " << enemies[i].getRect()->top << " Width: " << enemies[i].getRect()->width << " Height: " << enemies[i].getRect()->height << std::endl;
						if (enemies[i].isAlive() && it->getRect().intersects(enemies[i].getRect()))
						{
							if (it->isHarmful()) //fire extinguisher smoke doesn't do damage
								enemies[i].takeDamage(1);
							it = bullets.erase(it);
							bulletHit = true;
							break;
						}
					}
					if (!bulletHit)
						it++;
				}
			}

			//event trigger: player gets fire extinguisher
			//fire blocks the doorway, forcing the player to learn how to use the fire extinguisher to escape (right mouse button)
			if (!p.hasFireExtinguisher() && c.getX() == 1920 && c.getY() == 0 && p.getSprite()->getGlobalBounds().intersects(extinguisherSprite.getGlobalBounds()))
			{
				p.hasFireExtinguisher() = true;
				CollisionDetection::animationMap[11][66] = AnimatedTile(66 << 5, 11 << 5, false, PhotoLibrary::fireTex, true);
				CollisionDetection::animationMap[12][66] = AnimatedTile(66 << 5, 12 << 5, false, PhotoLibrary::fireTex, true);
				CollisionDetection::animationMap[13][66] = AnimatedTile(66 << 5, 13 << 5, false, PhotoLibrary::fireTex, true);
				CollisionDetection::animationMap[10][67] = AnimatedTile(67 << 5, 10 << 5, false, PhotoLibrary::fireTex, true);
				CollisionDetection::animationMap[9][68] = AnimatedTile(68 << 5, 9 << 5, false, PhotoLibrary::fireTex, true);

				CollisionDetection::map[11][66].setPassable(false);
				CollisionDetection::map[12][66].setPassable(false);
				CollisionDetection::map[13][66].setPassable(false);
				CollisionDetection::map[10][67].setPassable(false);
				CollisionDetection::map[9][68].setPassable(false);
			}
		}
		//prints to console how many bullets there are
		//std::cout << bullets.size() << std::endl;
		//if (sf::Event::MouseMoved)
			//std::cout << "The mouse moved" << std::endl;

		while (window.pollEvent(event))
		{
			//handles events
			switch (event.type)
			{
				//window closed
				case sf::Event::Closed:
					window.close();
					break;
				
				//MOVED OUTSIDE THIS WHILE LOOP
				//key pressed
				/*case sf::Event::KeyPressed:
					interpretKeysMap(&e);
					break;*/ 

				//MOVED OUTSIDE THIS WHILE LOOP SO IT RUNS CONTINUOUSLY
				//mouse moves
				/*case sf::Event::MouseMoved:
					interpretMouse(&p, &window);*/

				default:
					break;
			}
		}

		window.clear();
		//do all drawing here
		if (currentState == MAP){
			//draws map
			CollisionDetection::drawMap();
			//draws bloodstains
			for (i = enemies.size(); --i >= 0;)
				if (!enemies[i].isAlive())
					window.draw(*enemies[i].getSprite());
			//draws enemies
			for (i = enemies.size(); --i >= 0;)
				if (enemies[i].isAlive())
					window.draw(*enemies[i].getSprite());
			//window.draw(*e.getSprite());
			window.draw(*p.getSprite());
			if (p.isAlive())
				window.draw(*p.getArms());
			window.draw(*p.getText());
			window.draw(reticle);
			//draws fire extinguisher if player is in the correct screen and doesn't yet have the fire extinguisher
			if (!p.hasFireExtinguisher() && c.getX() == 1920 && c.getY() == 0)
				window.draw(extinguisherSprite);
			for (i = 0; i < bullets.size(); i++)
				window.draw(*(bullets[i].getSprite()));
		}
		else if (currentState == BATTLE){
			//GET RID OF THIS CONDITION LATER
			//window.draw(battleSprite1);
			//window.draw(battleSprite2);
		}
		else if (currentState == LOADING){
			window.draw(loadSprite);
			window.draw(progressBarContainer);
			window.draw(progressBar);
		}
		window.display();
		//end of drawing part

		/*for (i = bullets.size(); i >= 0; i--)
		{
			asdf
		}*/

		//std::cout << "Update Rate: " << 1/(timer.restart().asSeconds()) << std::endl;
	} //end of game loop

	//detaches thread
	loadThread.detach();

	return 0;
} //end of main method

//interprets key inputs when the player is walking around the map
void interpretKeysMap(Player * ent, Camera * cam)
{
	//next 4 lines are for testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		currentState = BATTLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		std::cout << "Player X " << ent->getX() << std::endl;
		std::cout << "Player Y " << ent->getY() << std::endl;
		std::cout << "Player Sprite X " << ent->getSprite()->getPosition().x << std::endl;
		std::cout << "Player Sprite Y " << ent->getSprite()->getPosition().y << std::endl;
		for (i = enemies.size(); --i >= 0;)
			std::cout << "(" << enemies[i].getX() << "," << enemies[i].getY() << ")" << std::endl;
	}

	//moves to the underground if the player is standing on the secret trap door
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && CollisionDetection::getLocation() == CollisionDetection::SURFACE && ent->getX() >> 5 == 4 && ent->getY() >> 5 == 30 && areaClear == true)
	{
		enemies.clear();
		areaClear = false;
		CollisionDetection::changeLocation(CollisionDetection::UNDERGROUND);
		CollisionDetection::spawnEnemies(enemies);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (ent->getY() - 4 < cam->getY())
		{
			//moves camera
			if (areaClear && cam->move(0, (0 - WINDOW_HEIGHT)))
			{
				enemies.clear(); //empties enemies list
				CollisionDetection::spawnEnemies(enemies);
				areaClear = false;
				ent->move(0, -4 - PLAYER_HEIGHT);
				ent->setSpritePosition();
			}
		}
		else if (CollisionDetection::validMove((ent->getX()) >> 5, (ent->getY() - 4) >> 5) && CollisionDetection::validMove((ent->getX() + PLAYER_WIDTH - 1) >> 5, (ent->getY() - 4) >> 5))
			ent->move(0,-4);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (ent->getX() - 4 < cam->getX())
		{
			//moves camera
			if (areaClear && cam->move((0 - WINDOW_WIDTH), 0))
			{
				enemies.clear();
				CollisionDetection::spawnEnemies(enemies);
				areaClear = false;
				ent->move(-4 - PLAYER_WIDTH, 0);
				ent->setSpritePosition();
			}
		}
		else if (CollisionDetection::validMove((ent->getX()-4) >> 5, ent->getY() >> 5) && CollisionDetection::validMove((ent->getX() - 4) >> 5, (ent->getY() + PLAYER_HEIGHT - 1) >> 5))
			ent->move(-4,0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (ent->getY() + PLAYER_HEIGHT + 3 > cam->getY() + cam->getHeight())
		{
			//moves camera
			if (areaClear && cam->move(0, WINDOW_HEIGHT))
			{
				enemies.clear();
				CollisionDetection::spawnEnemies(enemies);
				areaClear = false;
				ent->move(0, PLAYER_HEIGHT);
				ent->setSpritePosition();
				//REMOVE the next line later
				//std::cout << ent->getY() << " (y position) " << ((ent->getSprite())->getPosition().y) << " (sprite's y position)" << std::endl;
			}
		}
		else if (CollisionDetection::validMove((ent->getX()) >> 5, (ent->getY() + PLAYER_HEIGHT + 3) >> 5) && CollisionDetection::validMove((ent->getX() + PLAYER_WIDTH - 1) >> 5, (ent->getY() +PLAYER_HEIGHT + 3) >> 5))
			ent->move(0,4);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (ent->getX() + PLAYER_WIDTH + 3 > cam->getX() + cam->getWidth())
		{
			//moves camera
			if (areaClear && cam->move(WINDOW_WIDTH, 0))
			{
				enemies.clear();
				CollisionDetection::spawnEnemies(enemies);
				areaClear = false;
				ent->move(PLAYER_WIDTH + 4, 0);
				ent->setSpritePosition();
				//REMOVE the next line later
				//std::cout << ent->getX() << " (x position) " << ((ent->getSprite())->getPosition().x) << " (sprite's x position)" << std::endl;
			}
		}
		else if (CollisionDetection::validMove((ent->getX() + PLAYER_WIDTH + 3) >> 5, ent->getY() >> 5) && CollisionDetection::validMove((ent->getX() + PLAYER_WIDTH + 3) >> 5, (ent->getY() + PLAYER_HEIGHT - 1) >> 5))
			ent->move(4,0);
	}
}//end of interpretKeysMap

void interpretMouse(Player *player, sf::RenderWindow *rw){
	int mouseX = sf::Mouse::getPosition(*rw).x;
	int mouseY = sf::Mouse::getPosition(*rw).y;
	if (currentState == MAP)
	{
		//rotates player's arms/gun
		player->setArmRotation(mouseX, mouseY);

		//bullets
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseX >= 0 && mouseY >= 0 && bulletTimer.getElapsedTime().asSeconds() >= .1)
		{
			if (!player->isHoldingGun())
			{
				player->isHoldingGun() = true;
				player->setArmTex(PhotoLibrary::armTex);
			}
			bulletTimer.restart();
			bullets.push_back(Bullet(player->getArmX(), player->getArmY(), player->getTheta()));
		}

		//smoke
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && player->hasFireExtinguisher() && bulletTimer.getElapsedTime().asSeconds() >= .3)
		{
			if (player->isHoldingGun())
			{
				player->isHoldingGun() = false;
				player->setArmTex(PhotoLibrary::armTexE);
			}
			bulletTimer.restart();
			bullets.push_back(Smoke(player->getArmX(), player->getArmY(), player->getTheta()));
			//makes more smoke for effect; not that good anyway
			//bullets.push_back(Smoke(player->getArmX(), player->getArmY(), player->getTheta() + 10));
			//bullets.push_back(Smoke(player->getArmX(), player->getArmY(), player->getTheta() - 10));
		}
		//std::cout << bullets.size() << " bullets on the map" << std::endl;
		//reticle
		reticle.setPosition(mouseX, mouseY);
	}
}

void interpretKeysBattle(Player *player, Enemy *enemy){

}

void loadAssets(sf::RenderWindow* window, Camera* c, Player* player){
	std::cout << "Loading assets..." << std::endl;
	PhotoLibrary::initialize(); //sets up all textures
	progressBar.setSize(sf::Vector2f(100, 50));
	std::cout << "Textures initialized" << std::endl;
	reticle.setOrigin(7, 7);
	reticle.setTexture(PhotoLibrary::reticleTex);
	reticle.setPosition(0, 0);
	progressBar.setSize(sf::Vector2f(150, 50));
	std::cout << "Reticle created" << std::endl;
	extinguisherSprite.setTexture(PhotoLibrary::extinguisherTex);
	extinguisherSprite.setPosition(576, 32);
	progressBar.setSize(sf::Vector2f(400, 50));
	std::cout << "Initializing collision detection" << std::endl;
	startupTimer.restart();
	CollisionDetection::initialize(window, c);
	std::cout << startupTimer.getElapsedTime().asSeconds() << std::endl;
	progressBar.setSize(sf::Vector2f(550, 50));
	std::cout << "Initializing arms" << std::endl;
	player->init_arms();
	//loading done!
	progressBar.setSize(sf::Vector2f(600, 50));
	currentState = MAP;
	std::cout << "Finished loading assets" << std::endl;
}