#include <iostream>
#include "Game.h"
#include "CTransform.h"
#include "CShape.h"
#include "CInput.h"
#include "CCollision.h"
#include "CLifespan.h"
#include <sstream>
#include <string>

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
}

void Game::spawnPlayer() {
	player = entities.createEntity();
	player->addComponent<CTransform>(Vec2(windowWidth / 2.f, windowHeight / 2.f));
	player->addComponent<CShape>(playerRadius, 12, sf::Color::Green, sf::Color::Black, 2.f);
	player->addComponent<CCollision>(playerRadius);
	player->addComponent<CInput>();
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
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) input.up = false;
				if (event.key.code == sf::Keyboard::S) input.down = false;
				if (event.key.code == sf::Keyboard::A) input.left = false;
				if (event.key.code == sf::Keyboard::D) input.right = false;
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
	while (window.isOpen()) {
		handleInput();
		update();
		render();
		entities.refresh();
	}
}