#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>

class Entity {
	protected:
		int HP;
		bool alive;

	private:
		int MP, Atk, Def, x, y,tileSize;
		sf::Sprite sprite;
		sf::Texture texture;
	public:
		Entity(int, int, int, int, int, int, int, sf::Texture);

		int getHP() const;
		int getMP();
		int getAtk();
		int getDef();
		int getX() const;
		int getY() const;
		const unsigned int WINDOW_WIDTH = 640;
		const unsigned int WINDOW_HEIGHT = 640;

		void heal(int);
		virtual void move(int,int);
		void setTexture(sf::Texture);
		virtual void setSpritePosition();
		void setSpritePosition(int,int);

		virtual bool takeDamage(int);
		virtual bool isAlive(); //may be redundant; figured I'd add it just in case

		sf::Sprite * getSprite();
};

#endif /* ENTITY_H_ */