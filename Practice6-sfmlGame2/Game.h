#ifndef GAME_h
#define GAME_h


#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "ConfigReader.h"

class Game {
	sf::RenderWindow window;
	EntityManager entities;
	ConfigReader config;

	int windowWidth, windowHeight;
	string title, fontfile;
	float playerSpeed, playerRadius;
	float bullerSpeed, bulletRadius;
	int bulletLife;
	int enemyMinSides, enemymaxSides, enemySpawnRates;
	float enemyRadius;
	sf::Font font;

	shared_ptr<Entity> player;
	bool paused = false;

	void spawnPlayer();
	void handleInput();
	void update();
	void render();

public:
	Game();
	void run();
};


#endif