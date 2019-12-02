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
class Character
{
public:
	float radius;
	Texture texture;
	float speed;
	Vector2f direction;
	Vector2f position;
	Color color = Color(255,0,0);
	double rotation = 0;
	Character(Vector2f position, float radius, float speed, Vector2f direction) {
		texture.loadFromFile("Player1.png");
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
		this->position = position;
	};
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
		
		this->position.x += this->speed * this->direction.x * dt_ms;
		this->position.y += this->speed * this->direction.y * dt_ms;
		if (this->position.x < 0) {
			this->position.x = 800.f;
		}
		if (this->position.y < 0) {
			this->position.y = 600.f;
		}
		if (this->position.x > 800.f) {
			this->position.x = 0.f;
		}
		if (this->position.y > 600.f) {
			this->position.y = 0.f;
		}
	}
};


