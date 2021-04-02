#pragma once
#ifndef OVERLAY_H
#define OVERLAY_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Pillar.h"
#include "Player.h"
using namespace std;

class Overlay
{
private:
	sf::Clock overlayClock;
	sf::Font gameFont;
	int stageLevel;
	int stageProgress;
	int killCount;
	int enemyDelay;
	int timer;
	int exitTimer;
	int transitionOpacity;
	bool transitionFade;
	bool resetGame;
	sf::Sprite transitionSprite;
	Animation transitionAnimation;
	sf::Text setupText(int, int, string);
public:
	Overlay();
	int getTimeElapsed();
	int getStageProgress(Pillar);
	void setStage();
	void setKillCount(Player&);
	void handleOverlay(sf::RenderWindow&, Pillar, Player&);
	bool restartReady();

	int getStageLevel()
	{ return stageLevel; }

	int getTimer()
	{ return timer; }

	int getEnemyDelay()
	{ return enemyDelay; }
};


#endif 