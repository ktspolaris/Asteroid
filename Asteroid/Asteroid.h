#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp> 
#include <SFML/Main.hpp>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "GameObject.h"
using namespace sf;
using namespace std;


class Asteroid:public GameObject
{
public:

	Texture texture;

	float speed;
	bool active = true;

	Color color = Color(255,255,255);
	Asteroid(Vector2f position,float radius, float speed, Vector2f direction) {
		texture.loadFromFile("Asteroid.png");
		kind = 3;
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
		this->position = position;
	};
	void generate(RenderWindow* window) {

		Sprite ball;
		ball.setPosition(this->position);
		ball.setOrigin(this->radius, this->radius);
		ball.setTexture(this->texture);
		window->draw(ball);
	}
	~Asteroid() {};

	void update(float dt_ms)
	{
		this->position.x += this->speed * this->direction.x * dt_ms;
		this->position.y += this->speed * this->direction.y * dt_ms;
		if (this->position.x < 0 - this->radius) {
			this->position.x = 800.f + this->radius;
		}
		if (this->position.y < 0 - this->radius) {
			this->position.y = 600.f + this->radius;
		}
		if (this->position.x > 800.f + this->radius && this->position.x < 1000) {
			this->position.x = 0.f - this->radius;
		}
		if (this->position.y > 600.f + this->radius) {
			this->position.y = 0.f - this->radius;
		}
	}

	bool Isalive() {
	
	}

	void explosion(Sprite explosion) {
		
		explosion.setPosition(this->position);

	}

};

class MediumAsteroid : public Asteroid {
public:
	MediumAsteroid() :Asteroid(Vector2f(), 25.f, 300.f,Vector2f()) {
		texture.loadFromFile("MediumAsteroid.png");
	}

};

class SmallAsteroid : public Asteroid {
public:
	SmallAsteroid() :Asteroid(Vector2f(), 13.f, 300.f, Vector2f()) {
		texture.loadFromFile("SmallAsteroid.png");

	}

};