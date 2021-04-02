#include "Game.h"

// CONSTANTS
int FPS = 60;

// MAIN GAME CONSTRUCTOR
Game::Game()
{
	// randomize 
	srand(time(0));

	// load in map
	mapTexture.loadFromFile("data/map/map.png");
	map.setTexture(mapTexture);
	map.setScale(5,5);
}

void Game::gameLoop()
{
	// game window 
	sf::RenderWindow screen(sf::VideoMode(800, 600), "Game");
	screen.setFramerateLimit(FPS);

	// game loop
	while (screen.isOpen())
	{

		// event listener 
		sf::Event event;
		while (screen.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				screen.close();
			}
		}

		// display game elements 
		screen.clear();

		// draw map
		screen.draw(map);

		// handle player animations
		player.handleAnimation(screen, gamePillar, mouse.getPosition(screen), currentEnemies);

		// display enemies + enemy clean-up IF the round is still active
		handleEnemies(screen);

		// handle game pillar related actions 
		gamePillar.handlePillar(screen, player.getSprite());

		// handle overlay related actions 
		gameOverlay.handleOverlay(screen, gamePillar, player);

		// display everything on screen
		screen.display();

		// generate an enemy depending on the timer 
		generateEnemies();

		// check for if the round has finished 
		if (gameOverlay.restartReady())
		{
			setupNextRound();
		}
	}
}

// GAME FUNCTIONS
void Game::generateEnemies()
{
	if (gameOverlay.getTimer() % gameOverlay.getEnemyDelay() == 0)
	{
		Enemy *enemy = new Enemy;
		enemy->increaseEnemySpeed(gameOverlay.getStageLevel());
		currentEnemies.push_back(enemy);
	}
}

void Game::setupNextRound()
{
	// change overlay variables
	gameOverlay.setStage();

	// reset pillar stats 
	gamePillar.resetPillar();

	// reset other variables
	for (int i = 0; i < currentEnemies.size(); i++)
	{
		delete currentEnemies[i];
		currentEnemies.erase(currentEnemies.begin() + i);
	}
}

void Game::handleEnemies(sf::RenderWindow& screen)
{
	// display enemies + enemy clean-up IF the round is still active
	if (!gamePillar.isRoundOver())
	{
		for (int i = 0; i < currentEnemies.size(); i++)
		{
			currentEnemies[i]->handleAnimation(screen, gamePillar);

			if (!currentEnemies[i]->getVisibility())
			{
				delete currentEnemies[i];
				player.incrementKill();
				currentEnemies.erase(currentEnemies.begin() + i);
			}
		}
	}
}