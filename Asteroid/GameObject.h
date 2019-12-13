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
using namespace std;
using namespace sf;
class GameObject
{
public:
	Vector2f position;
	Vector2f direction;
	float radius;
	int kind;
	GameObject* lasthit;
	void generate() {};
	void update() {};
};

