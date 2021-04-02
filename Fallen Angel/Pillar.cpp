#include "Pillar.h"
#include "Enemy.h"
#include <cmath>
using namespace std;

// CONSTRUCTOR
Pillar::Pillar()
{
	internalCounter = 0;
	pillarCharge = 0;
	chargebarLength = 0;
	screenOpacity = 0;
	screenFade = false;
	pillarComplete = false;
	roundOver = false;
	loadPillar();
	loadAura();
	loadHitboxes();
	loadChargebar();
}

void Pillar::loadChargebar()
{
	chargebarOffset = 0;
	chargebarTexture.loadFromFile("data/map/chargebar.png");
	chargebar.setTexture(chargebarTexture);
	chargebar.setOrigin(chargebar.getGlobalBounds().width / 2, chargebar.getGlobalBounds().height / 2);
	chargebar.setPosition(sf::Vector2f(400, 125));
	chargebar.setScale(3, 3);
}

void Pillar::loadHitboxes()
{
	pillarHitbox.width = 100;
	pillarHitbox.height = 100;
	pillarHitbox.left = 400 - pillarHitbox.width / 2;
	pillarHitbox.top = 325 - pillarHitbox.height / 2;

	pillarChargeHitbox.width = 175;
	pillarChargeHitbox.height = 175;
	pillarChargeHitbox.left = 400 - pillarChargeHitbox.width / 2;
	pillarChargeHitbox.top = 325 - pillarChargeHitbox.height / 2;
}

void Pillar::loadAura()
{
	auraTexture.loadFromFile("data/map/aura.png");

	aura.setTexture(auraTexture);
	aura.setOrigin(aura.getGlobalBounds().width / 2, aura.getGlobalBounds().height / 2);
	aura.setPosition(sf::Vector2f(400,330));
}

void Pillar::drawAura(sf::RenderWindow& screen, sf::Sprite player)
{
	screen.draw(aura);
	if (checkCharge(player))
	{
 		pillarCharge++;
	}
}

void Pillar::loadPillar()
{
	pillarTexture.loadFromFile("data/map/pillar.png");
	pillar.setTexture(pillarTexture);
	pillarCompleteTexture.loadFromFile("data/map/finishedpillar.png");
	pillar.setOrigin(sf::Vector2f(pillar.getGlobalBounds().width / 2, pillar.getGlobalBounds().height - 18));
	pillar.setPosition(sf::Vector2f(400, 300));
	pillar.setScale(5, 5);
}	

sf::RectangleShape Pillar::createChargebar()
{
	sf::RectangleShape charge;
	double progressBarLength = pillarCharge / 25 * 1.0;
	double x = chargebar.getGlobalBounds().left + 75;
	double y = chargebar.getGlobalBounds().top + 15;
	charge.setPosition(sf::Vector2f(x, y));
	charge.setSize(sf::Vector2f(progressBarLength, 24));
	charge.setOrigin(sf::Vector2f(progressBarLength / 2, 12));
	charge.setFillColor(sf::Color(150, 251, 199));
	return charge;
}

void Pillar::handlePillar(sf::RenderWindow& screen, sf::Sprite player)
{
	if (!pillarComplete)
	{
		pillar.setTexture(pillarTexture);
	}
	else
	{
		pillar.setTexture(pillarCompleteTexture);
	}

	chargebar.setTexture(chargebarTexture);
	
	if (pillarCharge >= 0 && !pillarComplete)
	{
		drawAura(screen, player);
	}
	
	screen.draw(pillar);

	if (pillarCharge > 0 && !pillarComplete)
	{
		screen.draw(chargebar);
		screen.draw(createChargebar());
	}
	if (pillarCharge > 3600 && screenOpacity >= 0)
	{
		pillarFinished(screen);
		roundOver = true;
	}

	moveAura();
	moveChargebar();
}

void Pillar::moveAura()
{
	double radians = internalCounter * atan(1) * 4 / 180;
	double scale = 3 * sin(radians) + 5;
	aura.rotate(1);
	aura.setScale(scale, scale);
	internalCounter++;
}

void Pillar::moveChargebar()
{
	double radians = chargebarOffset * atan(1) * 4 / 180;
	double yOffset = 10 * sin(radians);
	chargebar.setPosition(sf::Vector2f(400, 125 + yOffset));
	chargebarOffset++;
}

bool Pillar::checkCharge(sf::Sprite& sprite)
{
	if (pillarChargeHitbox.intersects(sprite.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

bool Pillar::checkCollision(sf::Sprite& sprite)
{
	if (pillarHitbox.intersects(sprite.getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void Pillar::pillarFinished(sf::RenderWindow& screen)
{
	sf::RectangleShape flash(sf::Vector2f(800, 600));
	flash.setFillColor(sf::Color(255, 255, 255, screenOpacity));
	screen.draw(flash);

	if (screenOpacity < 255 && !screenFade)
	{
		screenOpacity += 3;
	}
	else if (screenOpacity > 200 && !screenFade && !pillarComplete)
	{
		pillarComplete = true;
	}
	else 
	{
		screenFade = true;
		screenOpacity -= 5;
	}
}

void Pillar::deductCharge(int n)
{
	if (pillarCharge - n < 0)
	{
		pillarCharge = 0;
	}
	else
	{
		pillarCharge -= n;
	}
}

void Pillar::resetPillar()
{
	internalCounter = 0;
	pillarCharge = 0;
	chargebarLength = 0;
	screenOpacity = 0;
	screenFade = false;
	pillarComplete = false;
	roundOver = false;
}