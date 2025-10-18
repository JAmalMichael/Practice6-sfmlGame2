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
	int playerPoint;
	float bullerSpeed, bulletRadius;
	int bulletLife;
	int enemyMinSides, enemymaxSides, enemySpawnRates;
	float enemyRadius;
	sf::Color enemyMinColor, enemyMaxColor;
	sf::Font font;

	shared_ptr<Entity> player;
	shared_ptr<Entity> enemy;
	shared_ptr<Entity> bullet;
	bool paused = false;

	int m_score = 0;
	int m_lives = 5;

	void spawnPlayer();
	void handleInput();
	void update();
	void render();
	void spawnEnemy();
	void spawnBullet(const sf::Vector2f & target);

	void sCollision();
	void sMovement();


public:
	Game();
	void run();
};


#endif