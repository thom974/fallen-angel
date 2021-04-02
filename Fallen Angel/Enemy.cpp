#include "Enemy.h"
#include <iostream>
using namespace std;

// CONSTRUCTOR
Enemy::Enemy()
{
	isAlive = true;
	isVisible = true;
	enemySpeed = 1;
	generateSpawn();
	generateMovement();
	enemyAnimation.setAnimation("move");
	enemyAnimation.loadFrames("data/animations/enemy/move", "move", { 14,14 });
	enemyAnimation.loadFrames("data/animations/enemy/death", "death", { 8,8,8,8,8,8,8,8,8,8 });
	enemySprite.setTexture(enemyAnimation.getLib()[enemyAnimation.getTexture()]);
	int x = enemySprite.getGlobalBounds().width / 2;
	int y = enemySprite.getGlobalBounds().height / 2;
	enemySprite.setOrigin(sf::Vector2f(x, y));
	setDirection();
}

void Enemy::setDirection()
{
	if (enemySprite.getPosition().x <= 400)
	{
		enemySprite.setScale(3, 3);
	}
	else
	{
		enemySprite.setScale(-3, 3);
	}
}

void Enemy::generateSpawn()
{
	int quadrant = rand() % 4;
	int x, y;

	if (quadrant == 0)
	{
		x = rand() % 801;
		y = rand() % 51 - 50;
	}
	else if (quadrant == 1)
	{
		x = rand() % 51 - 50;
		y = rand() % 601;
	}
	else if (quadrant == 2)
	{
		x = rand() % 51 + 800;
		y = rand() % 601;
	}
	else 
	{
		x = rand() % 801;
		y = rand() % 51 + 600;
	}

	enemySprite.setPosition(sf::Vector2f(x, y));
}

void Enemy::generateMovement()
{
	double xDist = 400 - enemySprite.getPosition().x;
	double yDist = 300 - enemySprite.getPosition().y;

	double angle = atan2(yDist, xDist);

	dX = cos(angle);
	dY = sin(angle);
}

void Enemy::move(Pillar& pillar)
{
	if (isAlive)
	{
		enemySprite.move(dX * enemySpeed, dY * enemySpeed);
	}
	
	if (pillar.checkCollision(enemySprite))
	{
		isAlive = false;
		pillar.deductCharge(1800);
		enemyAnimation.changeAnimation("death");
	}
}

void Enemy::handleAnimation(sf::RenderWindow& screen, Pillar& pillar)
{
	// MOVING ENEMY
	move(pillar);

	// DRAWING ENEMY TO SCREEN
	sf::Texture toDisplay = enemyAnimation.getLib()[enemyAnimation.getTexture()];
	enemySprite.setTexture(toDisplay);
	enemyAnimation.incrementFrame();

	if (!isAlive && enemyAnimation.getCurrentFrame() == enemyAnimation.getCyc()[enemyAnimation.getAnimation()].size() - 1)
	{
		isVisible = false;
	}

	if (isVisible)
	{
		screen.draw(enemySprite);
	}
}

void Enemy::killEnemy()
{
	isAlive = false;
	enemyAnimation.changeAnimation("death");
}