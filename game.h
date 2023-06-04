#pragma once
#include "settings.h"
#include "meteor.h"
#include "player.h"
#include "background.h"
#include "enemy.h"
#include "bonus.h"
#include "lives_indicator.h"


class Game {
private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteors;
	Player player;
	Enemy enemy;
	Background background;
	std::list<Bonus*> bonuses;
	std::list<LivesIndicator*> livesIndicator;
	int prevTime = 0, nowTime;
	sf::Clock timer;
public:
	Game() {
		window.create(sf::VideoMode{ (size_t)WINDOW_WIDTH, (size_t)WINDOW_HEIGHT }, "game", sf::Style::Fullscreen);
		window.setFramerateLimit(FPS);
		for (size_t i = 0; i < player.getLives(); i++) {
			float xPos = WINDOW_WIDTH / 2 - 64.f;
			float yPos = 10.f;
			LivesIndicator* life = new LivesIndicator(sf::Vector2f{ xPos + i * 48.f, yPos });
			livesIndicator.push_back(life);
		}
		timer.restart();
	}
	void Timer() {
		timer.getElapsedTime().asMilliseconds();
	}

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}
	}
	void SpawnBonuses() {
		int currtime=timer.getElapsedTime().asMilliseconds();
		if ( currtime > 1000) {
			float x = rand() % 1921;
			float y = rand() % 1081;
			sf::Vector2f BonusPosition(x, y);
			int chance = rand() % 1;
			int bonusType = rand() % Bonus::BonusType::MAX_BONUS_TYPE;
			if (chance < 15000) {
				Bonus* bonus = new Bonus(BonusPosition, (Bonus::BonusType)bonusType);
				bonuses.push_back(bonus);
			}
			timer.restart();
			prevTime = nowTime;
		}
	}
	void update() {
		player.update();
		enemy.update(player.getPosition());
		for (auto& bonus : bonuses) {
			bonus->update();
		}
		SpawnBonuses();
	}

	void checkColisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		sf::FloatRect enemyBounds = enemy.getHitBox();
		if (enemyBounds.intersects(playerBounds)) {
			player.playerMinusLives();
			livesIndicator.pop_back();
			player.SetPosition(WINDOW_WIDTH / 1.1, WINDOW_HEIGHT / 1.1);
			enemy.SetPosition(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8);
		}
		for (auto& bonus : bonuses) {
			sf::FloatRect bonusBounds = bonus->getHitBox();
			if (bonusBounds.intersects(playerBounds)) {
				bonus->act(player);
				bonus->setDel();
			}
		}
		bonuses.remove_if([](Bonus* bonus) { return bonus->isToDel(); });
	}

	void draw() {
		window.clear();
		window.draw(background.getSprite());
		window.draw(enemy.getSprite());
		window.draw(player.getSprite());
		for (auto& bonus : bonuses) {
			bonus->draw(window);
		}
		for (auto& life : livesIndicator) {
			life->draw(window);
		}
		window.display();
	}

	void play() {
		while (window.isOpen())
		{
			checkEvents();
			update();
			checkColisions();
			draw();
		}
	}
};