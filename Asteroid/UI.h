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

class UI {
public:

	string content;
	Vector2f position;
	int size;
	Text text;
	Font font;
	UI(string content, Vector2f position, int size) {

		this->position = position;
		this->size = size;
		this->content = content;
		font.loadFromFile("arial.ttf");
	}

	void generateUI(RenderWindow* window) {



		text.setFont(font);
		text.setString(content);
		text.setCharacterSize(size);
		text.setPosition(this->position);
		text.setFillColor(Color(255, 255, 255));

		window->draw(text);
	}

};

class UIofScore
{
public:

	string content;
	Vector2f position;
	int size;
	Text text;
	Font font;
	UIofScore(Vector2f position, int size) {
		font.loadFromFile("arial.ttf");
		this->position = position;
		this->size = size;
	}

	void generateUIofScore(RenderWindow* window, int scores) {

		this->content = to_string(scores);

		text.setFont(font);
		text.setString(to_string(scores));
		text.setCharacterSize(size);
		text.setPosition(this->position);
		text.setFillColor(Color(255, 255, 255));

		window->draw(text);
	}

};
