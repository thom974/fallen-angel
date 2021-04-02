#include "Overlay.h"
using namespace std;

// CONSTRUCTOR
Overlay::Overlay()
{
	stageLevel = 0;
	stageProgress = 0;
	timer = 0;
	enemyDelay = 300;
	exitTimer = 0;
	transitionFade = false;
	resetGame = false;
	transitionOpacity = 0;
	gameFont.loadFromFile("data/pokemon.ttf");
	transitionAnimation.loadFrames("data/animations/transition", "transition", { 5,5,5,5,5,5,5 });
	transitionAnimation.setAnimation("transition");
	transitionSprite.setTexture(transitionAnimation.getLib()[transitionAnimation.getTexture()]);
	transitionSprite.setScale(10, 10);
}

sf::Text Overlay::setupText(int size, int yPos, string message)
{
	sf::Text text;
	text.setCharacterSize(size);
	text.setPosition(30, yPos);
	text.setString(message);
	text.setFillColor(sf::Color(20, 199, 184));

	return text;
}

int Overlay::getTimeElapsed()
{
	uint32_t timePassed = overlayClock.getElapsedTime().asMilliseconds();
	return timePassed / 1000 ;
}

int Overlay::getStageProgress(Pillar pillar)
{
	int value = pillar.getPillarCharge() * 1.0 / 3600 * 100;
	if (value > 100)
	{
		value = 100;
	}
	return value;
}

void Overlay::setKillCount(Player& player)
{
	killCount = player.getKillCount();
}

void Overlay::setStage()
{
	// reset variables
	transitionOpacity = 0;
	exitTimer = 0;
	transitionFade = false;
	resetGame = false;
	timer = 0;
	stageLevel++;
	enemyDelay = 300 * pow(0.9,stageLevel);

	// reset overlay animation 
	transitionAnimation.setCurrentFrame(0);

}

void Overlay::handleOverlay(sf::RenderWindow& screen, Pillar pillar, Player& player)
{
	timer++;
	setKillCount(player);
	sf::Text t0 = setupText(25, 385, "level  " + to_string(stageLevel));
	sf::Text t1 = setupText(15, 445, to_string(getTimeElapsed()) + "  seconds elapsed");
	sf::Text t2 = setupText(15, 495, to_string(getStageProgress(pillar)) + "  percent complete");
	sf::Text t3 = setupText(15, 545, to_string(killCount) + "  kills");

	t0.setFont(gameFont);
	t1.setFont(gameFont);
	t2.setFont(gameFont);
	t3.setFont(gameFont);

	screen.draw(t0);
	screen.draw(t1);
	screen.draw(t2);
	screen.draw(t3);

	// handle transition
	if (pillar.isRoundOver())	// start the exit timer
	{
		exitTimer++;
	}
	if (exitTimer >= 180)
	{
		if (transitionOpacity < 255 && !transitionFade)
		{
			transitionOpacity += 3;
		}
		else if (transitionOpacity > 0)
		{
			transitionFade = true;
			transitionOpacity -= 3;
		}
		else if (transitionFade && transitionOpacity <= 30)
		{
			transitionOpacity = 0;
			resetGame = true;
		}

		transitionSprite.setColor(sf::Color(255, 255, 255, transitionOpacity));
		sf::Texture toDisplay = transitionAnimation.getLib()[transitionAnimation.getTexture()];
		transitionSprite.setTexture(toDisplay);
		transitionAnimation.incrementFrame();
		screen.draw(transitionSprite);
	}
}

bool Overlay::restartReady()
{
	if (resetGame)
	{
		return true;
	}

	return false;
}
