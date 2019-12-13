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


class Bullet: public GameObject{
public:
	float speed;
	

	Bullet(float speed) {
		radius = 2.f;
		this->speed = speed;
		kind = 2;

	}
	~Bullet() {};

	void generate(RenderWindow* window) {
		
		CircleShape bullet;
		bullet.setPosition(this->position);
		bullet.setRadius(this->radius);
		bullet.setFillColor(Color(255,255,255));
		window->draw(bullet);
	}

	void update(float dt_ms) {
	/*
		this->direction.x = cos(this->rotation);
		this->direction.y = sin(this->rotation);*/
		this->position.x += this->speed * this->direction.x * dt_ms;
		this->position.y += this->speed * this->direction.y * dt_ms;
		
	}
};

