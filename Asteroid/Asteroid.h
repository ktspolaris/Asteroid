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
class Asteroid
{
public:
	float radius;
	Texture texture;
	float speed;
	Vector2f direction;
	Vector2f position;
	Color color;
	Asteroid(Vector2f position,float radius, float speed, Vector2f direction) {
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
		this->position = position;
	};
	void generate(RenderWindow* window) {

		CircleShape ball(this->radius);
		ball.setPosition(this->position);
		ball.setOrigin(this->radius, this->radius);
		ball.setFillColor(this->color);
		window->draw(ball);
	}

	void update(float dt_ms)
	{
		this->position.x += this->speed * this->direction.x * dt_ms;
		this->position.y += this->speed * this->direction.y * dt_ms;
	}
};

