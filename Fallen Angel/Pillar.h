#pragma once
#ifndef PILLAR_H
#define PILLAR_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

class Pillar
{
private:
	sf::Texture pillarTexture;
	sf::Texture pillarCompleteTexture;
	sf::Texture auraTexture;
	sf::Texture chargebarTexture;
	sf::Sprite pillar;
	sf::Sprite aura;
	sf::Sprite chargebar;
	sf::FloatRect pillarHitbox;
	sf::FloatRect pillarChargeHitbox;
	int internalCounter;
	int pillarCharge;
	int chargebarOffset;
	int chargebarLength;
	int screenOpacity;
	bool screenFade;
	bool pillarComplete;
	bool roundOver;
	void loadAura();
	void loadPillar();
	void loadHitboxes();
	void loadChargebar();
	void moveAura();
	void drawAura(sf::RenderWindow&, sf::Sprite);
	void moveChargebar();
	sf::RectangleShape createChargebar();
public:
	Pillar();
	void handlePillar(sf::RenderWindow&, sf::Sprite);
	bool checkCollision(sf::Sprite&);
	bool checkCharge(sf::Sprite&);
	void pillarFinished(sf::RenderWindow&);
	void resetPillar();
	void deductCharge(int);

	int getPillarCharge()
	{ return pillarCharge; }

	bool isRoundOver()
	{ return roundOver; }
};

#endif 