
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
class Soundeffects
{

public:
	string file;
	Sound sound;
	SoundBuffer buffer;
	Soundeffects(string file) {
		this->file = file;
		buffer.loadFromFile(file);

	}
	void playsound() {

		this->sound.setBuffer(this->buffer);
		this->sound.play();
	}
};

