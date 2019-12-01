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
#include "Asteroid.h"
#include "Character.h"
//#include "UI.h"
#include <vector>
#include <algorithm>
//#include "Soundeffects.h"
using namespace sf;
using namespace std;
int main() {
	RenderWindow window(VideoMode(800, 600), "Asteroid");
	Clock clock;

	Time dt;
	Character player1(Vector2f(400.f,300.f), 10.f, 400.f, Vector2f(0.f,0.f));
	while (window.isOpen())
	{
		dt = clock.getElapsedTime();
		clock.restart();
		Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//control player1
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player1.update(dt.asSeconds());
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player1.update(-dt.asSeconds());
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player1.rotation += 5*dt.asSeconds() ;
	
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player1.rotation += -5*dt.asSeconds();
			
		}

		//handle screen
		window.clear();
		player1.generate(&window);
		
		window.display();
	}
	return 0;
}