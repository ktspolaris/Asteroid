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
using namespace sf;
using namespace std;
class Bullet
{
public:
	float speed;
	Vector2f direction;
	Vector2f position;
	Vector2f size = Vector2f(2.f, 1.f);
	Bullet(float speed) {
		this->speed = speed;

	}
	~Bullet() {};

	void generate(RenderWindow* window) {
		RectangleShape bullet;
		bullet.setPosition(this->position);
		bullet.setSize(this->size);
		bullet.setFillColor(Color(255,255,255));
		window->draw(bullet);
	}

	void update(float dt_ms) {
	/*
		this->direction.x = cos(this->rotation);
		this->direction.y = sin(this->rotation);*/
		this->position.x += this->speed * this->direction.x * dt_ms;
		this->position.y += this->speed * this->direction.y * dt_ms;
		if (this->position.x < 0 || this->position.x > 800) {
			this->~Bullet();
		}
	}
};

