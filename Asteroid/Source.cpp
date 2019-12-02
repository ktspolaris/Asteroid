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
#include "Bullet.h"

//#include "UI.h"
#include <vector>
#include <algorithm>
#include <ctime>
//#include "Soundeffects.h"
using namespace sf;
using namespace std;

bool checkCollsion(Asteroid& ball, Bullet & bullet) {
	if (ball.position.y > bullet.position.y&&
		ball.position.y < bullet.position.y + bullet.size.y &&
		fabsf(ball.position.x - bullet.position.x) < ball.radius
		/*ball.position.x > bullet.position.x*/)
	{


		return true;
	}

	if (ball.position.y > bullet.position.y&&
		ball.position.y < bullet.position.y + bullet.size.y &&

		fabsf(ball.position.x - bullet.position.x) < ball.radius)
	{
		return true;
	}

	if (fabsf(ball.position.y - bullet.position.y) < ball.radius &&
		ball.position.x < bullet.position.x + bullet.size.x &&
		ball.position.x > bullet.position.x)
	{

		return true;
	}

	if (fabsf(ball.position.y - bullet.position.y - bullet.size.y) < ball.radius &&
		ball.position.x < bullet.position.x + bullet.size.x &&
		ball.position.x > bullet.position.x)
	{

		return true;
	}

	if (sqrt((ball.position.x - bullet.position.x) * (ball.position.x - bullet.position.x) + (ball.position.y - bullet.position.y) * (ball.position.y - bullet.position.y)) < ball.radius)

	{

		
		return true;

	}


	if (sqrt((ball.position.x - (bullet.position.x + bullet.size.x)) * (ball.position.x - (bullet.position.x + bullet.size.x)) + (ball.position.y - bullet.position.y) * (ball.position.y - bullet.position.y)) < ball.radius)

	{

	
		return true;

	}

	if (sqrt((ball.position.x - (bullet.position.x + bullet.size.x)) * (ball.position.x - (bullet.position.x + bullet.size.x)) + (ball.position.y - (bullet.position.y + bullet.size.y)) * (ball.position.y - (bullet.position.y + bullet.size.y))) < ball.radius)

	{

		
		return true;

	}

	if (sqrt((ball.position.x - bullet.position.x) * (ball.position.x - bullet.position.x) + (ball.position.y - (bullet.position.y + bullet.size.y)) * (ball.position.y - (bullet.position.y + bullet.size.y))) < ball.radius)

	{

		return true;

	}

	return false;
}

Vector2f normalize(Vector2f vector) {
	Vector2f result;
	result = Vector2f(vector.x / sqrt(vector.x * vector.x + vector.y * vector.y), vector.y / sqrt(vector.x * vector.x + vector.y * vector.y));
	return result;

}

int main() {
	RenderWindow window(VideoMode(800, 600), "Asteroid");
	Clock clock;
	Clock cooldown;
	Time dt;
	Character player1(Vector2f(400.f,300.f), 10.f, 400.f, Vector2f(0.f,0.f));
	vector<Asteroid> asteroids;
	vector<MediumAsteroid> mediumasteroids;
	srand(time(0));
	for (int i = 0; i < 4; ++i) {

		Asteroid a(Vector2f(rand()%800, rand()%600), 40.f, 300.f, normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX))) );
	
		asteroids.push_back(a);
	}
	bool isplay = false;
	vector<Bullet> bullets;
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

			player1.direction.x = cos(player1.rotation);
			player1.direction.y = sin(player1.rotation);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player1  .rotation += -5*dt.asSeconds();
			player1.direction.x = cos(player1.rotation);
			player1.direction.y = sin(player1.rotation);
		}

		//generate bullets
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			
			if (cooldown.getElapsedTime().asSeconds() > 0.5f) {
				Bullet b(600.f);
				b.direction = player1.direction;
				b.position = player1.position;
				bullets.push_back(b);
				cooldown.restart();
			}
		
		}
		
		// handle collsion
		for (int i = 0; i < bullets.size(); i++) {
			for (int j = 0; j < asteroids.size(); j++ ) {
				if (checkCollsion(asteroids[j], bullets[i])) {
					
					for(int i = 0; i < 3; ++i) //create medium Asteroid
					{
						MediumAsteroid m;
						m.position = asteroids[j].position;
						m.direction = normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX)));
						mediumasteroids.push_back(m);
					}
					asteroids[j].position.x = 1500.f;
					asteroids[j].speed = 0.f;
				}
					
			}
		}

		//handle screen
		window.clear();
		player1.generate(&window);
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].generate(&window);
			bullets[i].update(dt.asSeconds());
		}

		for (int i = 0; i < asteroids.size(); ++i) {
			asteroids[i].generate(&window);
			asteroids[i].update(dt.asSeconds());
		}

		for (int i = 0; i < mediumasteroids.size(); ++i) {
		mediumasteroids[i].generate(&window);
		mediumasteroids[i].update(dt.asSeconds());
		}
		window.display();
	}
	return 0;
}