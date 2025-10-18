#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <cmath>
#include "Game.h"
#include "CTransform.h"
#include "CShape.h"
#include "CInput.h"
#include "CCollision.h"
#include "CLifespan.h"
#include "CScore.h"



static float randrange(float min, float max) {
	static mt19937 rng(random_device{}());
	uniform_real_distribution<float> dist(min, max);
	return dist(rng);

};


Game::Game() {
	config.load("config.txt");

	//window spec 
	stringstream ws(config.getLine(0));
	ws >> windowWidth >> windowHeight >> title;
	window.create(sf::VideoMode(windowWidth, windowHeight), title);

	//font
	stringstream fs(config.getLine(1));
	fs >> fontfile;
	font.loadFromFile(fontfile);

	//playerspec
	stringstream ps(config.getLine(2));
	ps >> playerSpeed >> playerRadius;

	//bullet spec
	stringstream bs(config.getLine(3));
	bs >> bullerSpeed >> bulletRadius >> bulletLife;

	//Enemy property/spec
	stringstream es(config.getLine(4));
	es >> enemyMinSides >> enemymaxSides >> enemySpawnRates >> enemyRadius;


	spawnPlayer();
	spawnEnemy();
}

void Game::spawnPlayer() {
	player = entities.createEntity();
	player->addComponent<CTransform>(Vec2(windowWidth / 2.f, windowHeight / 2.f));
	player->addComponent<CShape>(playerRadius, 12, sf::Color::Green, sf::Color::Black, 2.f);
	player->addComponent<CCollision>(playerRadius);
	player->addComponent<CInput>();
	player->addComponent<CScore>();
}

void Game::spawnEnemy() {

	enemy = entities.createEntity();
	float x = randrange(enemyRadius, windowWidth - enemyRadius);
	float y = randrange(enemyRadius, windowHeight - enemyRadius);
	
	float vx = randrange(-3, 3);
	float vy = randrange(-3, 3);

	//randomly generatiing shapes and color for enemies
	int points = (int)randrange(enemyMinSides, enemymaxSides);

	sf::Color fill(
		(int)randrange(enemyMinColor.r, enemyMaxColor.r),
		(int)randrange(enemyMinColor.g, enemyMaxColor.g),
		(int)randrange(enemyMinColor.b, enemyMaxColor.b)
	);

	enemy->addComponent<CShape>(enemyRadius, points, fill, sf::Color::Red, 2.f);
	enemy->addComponent<CCollision>(enemyRadius);
	enemy->addComponent<CTransform>(Vec2(windowWidth / 2.f, windowHeight / 2.f));
}

void Game::spawnBullet(const sf::Vector2f& target) {

	auto& p = player->getComponent<CTransform>();
	auto bullet = entities.createEntity();

	Vec2 dir{};

	auto& pos = p.position;
	auto normal = dir.normalized();

	bullet->addComponent<CTransform>();
	bullet->addComponent<CShape>(bulletRadius, 20, sf::Color::Yellow , sf::Color::Black, 1.f);
	bullet->addComponent<CCollision>(bulletRadius);
	bullet->addComponent<CLifespan>(bulletLife);

}


void Game::sMovement() 
{
	for (auto & e:entities.getEntity())
	{
		if (e ->hasComponent<CTransform>())
		{
			e->getComponent<CTransform>().position += e->getComponent<CTransform>().velocity ; 
		}
	}

}


void Game::handleInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();

		auto& input = player->getComponent<CInput>();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::P) paused = !paused;
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::W) input.up = true;
				if (event.key.code == sf::Keyboard::S) input.down = true;
				if (event.key.code == sf::Keyboard::A) input.left = true;
				if (event.key.code == sf::Keyboard::D) input.right = true;
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
			{
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				spawnBullet(mousePos);
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) input.up = false;
				if (event.key.code == sf::Keyboard::S) input.down = false;
				if (event.key.code == sf::Keyboard::A) input.left = false;
				if (event.key.code == sf::Keyboard::D) input.right = false;
			}
	}
}

void Game::sCollision()
{
	player;
	 auto & pPos = player->getComponent<CTransform>().position;
	 float pRad = player->getComponent<CCollision>().radius;

	 for (auto e: entities.getEntity("enemy"))
	 {
		 Vec2 diff = e->getComponent<CTransform>().position - pPos;
		 float dist = sqrt(diff.x * diff .x + diff.y * diff.y);
		 if (dist < e->getComponent<CCollision>().radius + pRad)
		 {
			 m_lives--;
			 if (m_lives <= 0)
			 {
				 player->destroy();
			 }
			 else {
				 player->getComponent<CTransform>().position = { windowWidth / 2.f, windowHeight / 2.f };
			 }
		 }
	 }

}

void Game::update() {
	if (paused) return;

	auto& trans = player->getComponent<CTransform>();
	auto& input = player->getComponent<CInput>();


	Vec2 dir{};
	if (input.up) dir.y -= 1;
	if (input.down) dir.y += 1;
	if (input.left) dir.x -= 1;
	if (input.right) dir.x += 1;

	trans.position = trans.position + dir.normalized() * playerSpeed;

	//keep inside bounds
	trans.position.x = max(playerRadius, min(trans.position.x, (float)windowWidth - playerRadius));
	trans.position.y = max(playerRadius, min(trans.position.y, (float)windowHeight - playerRadius));

	player->getComponent<CShape>().circle.setPosition(trans.position.x, trans.position.y);
}

void Game::render() {
	window.clear(sf::Color::Cyan);
	for (auto& e : entities.getEntity()) {
		if (e->hasComponent<CShape>()) {
			window.draw(e->getComponent<CShape>().circle);
		}
	}
	window.display();
}

void Game::run() {
	sf::Clock clock;
	while (window.isOpen()) {
		handleInput();
		if (!paused)
		{
			sCollision();
		}
		update();
		render();
		entities.refresh();
	}
}