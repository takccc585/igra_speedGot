#pragma once
#include "settings.h"

class Player {
private:
	sf::RenderWindow window;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Mouse mouse;
	float angle;
	float speedx, speedy;
	int lives = 2;
	int speedBonusActivateTime;
	bool speedBonusActivate = false;
	sf::Clock timer;

public:
	Player() {
		texture.loadFromFile("images\\spaceShips_002.png");
		sprite.setTexture(texture);
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(WINDOW_WIDTH / 1.1, WINDOW_HEIGHT / 1.1);
	}
	void update() {

		float dX = mouse.getPosition().x - sprite.getPosition().x;
		float dY = mouse.getPosition().y - sprite.getPosition().y;
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
		sprite.setRotation(rotation + 90);
		float distance = std::sqrt(dX * dX + dY * dY);
		if (distance > Pspeed)
		{
			sprite.move(Pspeed * dX / distance, Pspeed * dY / distance);
		}
		int currtime=timer.getElapsedTime().asMilliseconds();
		if (currtime - speedBonusActivateTime > BONUS_OPERATING_TIME) {
			Pspeed = 10;
		}
	}

	void addLives(int live) {
		this->lives += live;
		if (lives > MAX_PLAYER_LIVES) {
			lives = MAX_PLAYER_LIVES;
		}
	}

	void playerMinusLives() {
		lives--;
	}

	int getLives() { return lives; }

	void addSpeed() {
		Pspeed *= 2;
		if (Pspeed > MaxPlayerSpeed) {
			Pspeed= MaxPlayerSpeed;
		}
		speedBonusActivateTime = timer.getElapsedTime().asMilliseconds();
	}
	void SetPosition(float x, float y) {
		sprite.setPosition(x, y);
	};

	sf::Sprite getSprite() { return sprite; }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
};