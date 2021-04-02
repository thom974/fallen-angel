#include "Player.h"
#include "Pillar.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// CONSTRUCTOR 
Player::Player()
{
	killCount = 0;
	playerSprite.setPosition(sf::Vector2f(150, 100));
	playerAnimation.loadFrames("data/animations/character/idle", "idle", { 14,14 });
	playerAnimation.loadFrames("data/animations/character/move", "move", { 14,14 });
	playerSprite.setTexture(playerAnimation.getLib()[playerAnimation.getTexture()]);
	int x = playerSprite.getGlobalBounds().width / 2;
	int y = playerSprite.getGlobalBounds().height / 2;
	loadSword();
	playerSprite.setOrigin(sf::Vector2f(x, y));
	playerSprite.setScale(3,3);
}

// MEMBER FUNCTIONS
void Player::move(Pillar& pillar)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerSprite.move(-3, 0);
		playerSprite.setScale(-3, 3);
		playerAnimation.changeAnimation("move");
		if (pillar.checkCollision(playerSprite))
		{
			playerSprite.move(3, 0);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerSprite.move(3, 0);
		playerSprite.setScale(3, 3);
		playerAnimation.changeAnimation("move");
		if (pillar.checkCollision(playerSprite))
		{
			playerSprite.move(-3, 0);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		playerSprite.move(0, -3);
		playerAnimation.changeAnimation("move");
		if (pillar.checkCollision(playerSprite))
		{
			playerSprite.move(0, 3);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerSprite.move(0, 3);
		playerAnimation.changeAnimation("move");
		if (pillar.checkCollision(playerSprite))
		{
			playerSprite.move(0, -3);
		}
	}
	else
	{
		playerAnimation.changeAnimation("idle");
	}
}

void Player::handleAnimation(sf::RenderWindow& screen, Pillar& pillar, sf::Vector2i mousePos, std::vector<Enemy*> enemies)
{
	// MOVING ANIMATION
	move(pillar);

	// DRAWING  ANIMATION TO SCREEN
	sf::Texture toDisplay = playerAnimation.getLib()[playerAnimation.getTexture()];
	playerSprite.setTexture(toDisplay);
	playerAnimation.incrementFrame();
	drawSword(screen, mousePos,enemies);
	screen.draw(playerSprite);
}

void Player::loadSword()
{
	swordTexture.loadFromFile("data/player/sword.png");
	sword.setTexture(swordTexture);
	sword.setOrigin(59, 280);
	sword.setScale(0.3, 0.3);
}

void Player::drawSword(sf::RenderWindow& screen, sf::Vector2i mousePos, std::vector<Enemy*> enemies)
{
	// getting angle 
	double xDist = mousePos.x - playerSprite.getPosition().x;
	double yDist = mousePos.y - playerSprite.getPosition().y;
	
	double swordAngle = atan2(yDist, xDist) * 180 / 3.14;
	sword.setRotation(swordAngle + 90);

	// check for enemy collision
	for (int i = 0; i < enemies.size(); i++)
	{
		if (sword.getGlobalBounds().intersects(enemies[i]->getSprite().getGlobalBounds()))
		{
			enemies[i]->killEnemy();
		}
	}

	sword.setTexture(swordTexture);
	sword.setPosition(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 15));
	screen.draw(sword);
}