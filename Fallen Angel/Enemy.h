#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Pillar.h"

class Enemy
{
private:
	sf::Sprite enemySprite;
	void generateSpawn();
	void generateMovement();
	void setDirection();
	int enemySpeed;
	double dX, dY;
	bool isAlive;
	bool isVisible;
	Animation enemyAnimation;
public:
	Enemy();
	void move(Pillar&);
	void killEnemy();
	void handleAnimation(sf::RenderWindow&, Pillar&);
	
	void increaseEnemySpeed(int n)
	{ enemySpeed += n; }
	
	bool getVisibility()
	{ return isVisible; }

	sf::Sprite getSprite()
	{ return enemySprite; }
};

#endif 