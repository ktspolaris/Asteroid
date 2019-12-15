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

class Powerup : public GameObject
{
public:
	float speed;
	Color color;
	Powerup(Vector2f position, float radius, float speed, Vector2f direction) {
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
		this->position = position;
	};

	void generate(RenderWindow* window) {

		CircleShape ball;
		ball.setPosition(this->position);
		ball.setRadius(this->radius);
		ball.setFillColor(color);
		window->draw(ball);
	}

	void update(float dt_ms) {
		/*
			this->direction.x = cos(this->rotation);
			this->direction.y = sin(this->rotation);*/
		this->position.x += this->speed * this->direction.x * dt_ms;
		this->position.y += this->speed * this->direction.y * dt_ms;
	/*	if (this->position.x > 800.f || this->position.x < 0.f || this->position.y > 600.f || this->position.y < 0.f) {
			this->~Powerup();
		}*/

	}


private:

};



