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
class Character:public GameObject
{
public:

	Texture texture;
	float speed;
	float accumlate;
	Color color = Color(255,0,0);
	double rotation = 0;
	Character(Vector2f position, float radius, float speed, Vector2f direction) {
		kind = 1;
		texture.loadFromFile("Player1.png");
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
		this->position = position;
	}
	void generate(RenderWindow* window) {
		Sprite character;
		//CircleShape ball(this->radius);
		character.setTexture(texture);
		character.setPosition(this->position);
		character.setOrigin(this->radius, this->radius);
		character.setRotation(rotation*180/3.1415926);
		//window->draw(ball);
		
		window->draw(character);
	}

	void update(float dt_ms)
	{
		this->speed += this->accumlate * dt_ms;
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
};

class Fire :public GameObject {

public:

	Texture texture;
	float speed;
	float accumlate;

	Color color = Color(255, 0, 0);
	double rotation = 0;
	Fire(Vector2f position, float radius, float speed, Vector2f direction) {
		kind = 1;
		texture.loadFromFile("Fire.png");
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
		this->position = position;
	};
	void generate(RenderWindow* window) {
		Sprite Fire;
		//CircleShape ball(this->radius);
		Fire.setTexture(texture);
		Fire.setPosition(this->position);
		Fire.setOrigin(3*this->radius, this->radius);

		Fire.setRotation(rotation * 180 / 3.1415926);

		//window->draw(ball);

		window->draw(Fire);
	}

	void update(float dt_ms)
	{
		speed += accumlate * dt_ms;
		this->speed += this->accumlate * dt_ms;

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
};

class Enemy :public GameObject {

public:

	Texture texture;
	float speed;
	double rotation = 0;


	Enemy(Vector2f position, float radius, float speed, Vector2f direction) {
		
		texture.loadFromFile("Enemy.png");
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
		this->position = position;
	};


	void generate(RenderWindow* window) {

		Sprite enemy;
		//CircleShape ball(this->radius);
		enemy.setTexture(texture);
		enemy.setPosition(this->position);
		enemy.setOrigin(this->radius, this->radius);
	
		//Fire.setRotation(rotation * 180 / 3.1415926);

		//window->draw(ball);

		window->draw(enemy);
	}

	void update(float dt_ms)
	{

		this->position.x += this->speed * this->direction.x * dt_ms;
		this->position.y += this->speed * this->direction.y * dt_ms;

		if (this->position.x < 0 - this->radius && this->position.x > -50.f) {
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
};




