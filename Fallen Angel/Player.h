#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Animation.h"
#include "Pillar.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Sprite playerSprite;
	sf::Texture swordTexture;
	sf::Sprite sword;
	Animation playerAnimation;
	void loadSword();
	int killCount;
public: 
	Player();
	void move(Pillar&);
	void handleAnimation(sf::RenderWindow&, Pillar&, sf::Vector2i, std::vector<Enemy*>);
	void drawSword(sf::RenderWindow&, sf::Vector2i, std::vector<Enemy*>);
	
	sf::Sprite getSprite()
	{ return playerSprite; }

	int getKillCount()
	{ return killCount; }

	void incrementKill()
	{ killCount ++ ; }

	Animation getPlayerAni()
	{ return playerAnimation; }
};

#endif 