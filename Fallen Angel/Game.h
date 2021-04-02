#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Overlay.h"
#include "Enemy.h"

class Game
{
private:
	void generateEnemies();
	void handleEnemies(sf::RenderWindow&);
	void setupNextRound();

	Player player;
	Overlay gameOverlay;
	sf::Texture mapTexture;
	sf::Sprite map;
	std::vector<Enemy*> currentEnemies;
	Pillar gamePillar;
	sf::Mouse mouse;
public:
	Game();
	void gameLoop();
};

#endif 