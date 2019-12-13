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
#include "GameObject.h"

//#include "UI.h"
#include <vector>
#include <algorithm>
#include <ctime>
//#include "Soundeffects.h"
using namespace sf;
using namespace std;

//bool checkCollsion(Asteroid& ball, Bullet & bullet) {
//	if (ball.position.y > bullet.position.y&&
//		ball.position.y < bullet.position.y + bullet.size.y &&
//		fabsf(ball.position.x - bullet.position.x) < ball.radius
//		/*ball.position.x > bullet.position.x*/)
//	{
//
//
//		return true;
//	}
//
//	if (ball.position.y > bullet.position.y&&
//		ball.position.y < bullet.position.y + bullet.size.y &&
//
//		fabsf(ball.position.x - bullet.position.x) < ball.radius)
//	{
//		return true;
//	}
//
//	if (fabsf(ball.position.y - bullet.position.y) < ball.radius &&
//		ball.position.x < bullet.position.x + bullet.size.x &&
//		ball.position.x > bullet.position.x)
//	{
//
//		return true;
//	}
//
//	if (fabsf(ball.position.y - bullet.position.y - bullet.size.y) < ball.radius &&
//		ball.position.x < bullet.position.x + bullet.size.x &&
//		ball.position.x > bullet.position.x)
//	{
//
//		return true;
//	}
//
//	if (sqrt((ball.position.x - bullet.position.x) * (ball.position.x - bullet.position.x) + (ball.position.y - bullet.position.y) * (ball.position.y - bullet.position.y)) < ball.radius)
//
//	{
//
//		
//		return true;
//
//	}
//
//
//	if (sqrt((ball.position.x - (bullet.position.x + bullet.size.x)) * (ball.position.x - (bullet.position.x + bullet.size.x)) + (ball.position.y - bullet.position.y) * (ball.position.y - bullet.position.y)) < ball.radius)
//
//	{
//
//	
//		return true;
//
//	}
//
//	if (sqrt((ball.position.x - (bullet.position.x + bullet.size.x)) * (ball.position.x - (bullet.position.x + bullet.size.x)) + (ball.position.y - (bullet.position.y + bullet.size.y)) * (ball.position.y - (bullet.position.y + bullet.size.y))) < ball.radius)
//
//	{
//
//		
//		return true;
//
//	}
//
//	if (sqrt((ball.position.x - bullet.position.x) * (ball.position.x - bullet.position.x) + (ball.position.y - (bullet.position.y + bullet.size.y)) * (ball.position.y - (bullet.position.y + bullet.size.y))) < ball.radius)
//
//	{
//
//		return true;
//
//	}
//
//	return false;
//}

bool checkballcollsion(GameObject& ball1, GameObject& ball2) {
	if (sqrtf((ball1.position.x - ball2.position.x) * (ball1.position.x - ball2.position.x) + (ball1.position.y - ball2.position.y) * (ball1.position.y - ball2.position.y)) < (ball1.radius + ball2.radius + 0.1f)) {
		return true;
	}
	else
	{
		return false;
	}
}

Vector2f normalize(Vector2f vector) {
	Vector2f result;
	result = Vector2f(vector.x / sqrt(vector.x * vector.x + vector.y * vector.y), vector.y / sqrt(vector.x * vector.x + vector.y * vector.y));
	return result;

}

Vector2f Beone(Vector2f vector) {
	Vector2f result;
	result = Vector2f(vector.x / vector.x, vector.y / vector.y);
		return result;
}



int main() {

	// create bucket grids 
	vector<GameObject*> grids[10][10];  // create grids

	float initialspeed = 300.f;
	RenderWindow window(VideoMode(800, 600), "Asteroid");
	Clock clock;
	Clock cooldown;
	Time dt;
	Character player1(Vector2f(400.f,300.f), 10.f, 400.f, Vector2f(0.f,0.f));
	vector<Asteroid> asteroids;
	vector<MediumAsteroid> mediumasteroids;
	vector<SmallAsteroid> smallasteroids;
	int lifes = 3;
	srand(time(0));
	for (int i = 0; i < 4; ++i) {

		Asteroid a(Vector2f(rand()%800, rand()%600), 40.f, initialspeed, normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX))) );
	
		asteroids.push_back(a);
	}
	enum gamestate{ mainmenu, isplay, gameover };
	gamestate currentstate;

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
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter) && currentstate == mainmenu) {
				currentstate = isplay;
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::B ) && currentstate == gameover) {
				currentstate = mainmenu;
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape )&& currentstate == isplay) {
				currentstate = mainmenu;
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::X) && currentstate == mainmenu) {
				window.close();
			}
		}

		//switch (currentstate)
		//{
		//case mainmenu:
		//	break;

		//case isplay:
		//	break;
		//case gameover:
		//	break;
		//}
		
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
			
			if (cooldown.getElapsedTime().asSeconds() > 0.1f) {
				Bullet b(600.f);
				b.direction = player1.direction;
				b.position = player1.position;
				bullets.push_back(b);
				cooldown.restart();
			}
			cout << bullets.size() << endl;
		}
		
	
		//distribute asteroids into grids
		vector<Asteroid>::iterator start_asteroids = asteroids.begin();

		while (start_asteroids != asteroids.end()) 
		{
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if ( start_asteroids->position.x > 80 * i - 0.5*start_asteroids->radius
						&& start_asteroids->position.x < 80 * i + 80 + 0.5 * start_asteroids->radius
						&& start_asteroids->position.y > 60 * j - 0.5 * start_asteroids->radius
						&& start_asteroids->position.y < 60 * j + 60 + 0.5*start_asteroids->radius) {
						grids[i][j].push_back(&*start_asteroids);
					}


				}
		    }
			++start_asteroids;
		}

		vector<MediumAsteroid>::iterator start_m = mediumasteroids.begin();

		while (start_m != mediumasteroids.end())
		{
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (start_m->position.x > 80 * i - 0.5 * start_m->radius
						&& start_m->position.x < 80 * i + 80 + 0.5 * start_m->radius
						&& start_m->position.y > 60 * j - 0.5 * start_m->radius
						&& start_m->position.y < 60 * j + 60 + 0.5 * start_m->radius) {
						grids[i][j].push_back(&*start_m);
					}


				}
			}
			++start_m;
		}

		vector<SmallAsteroid>::iterator start_s = smallasteroids.begin();

		while (start_s != smallasteroids.end())
		{
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (start_s->position.x > 80 * i - 0.5 * start_s->radius
						&& start_s->position.x < 80 * i + 80 + 0.5 * start_s->radius
						&& start_s->position.y > 60 * j - 0.5 * start_s->radius
						&& start_s->position.y < 60 * j + 60 + 0.5 * start_s->radius) {
						grids[i][j].push_back(&*start_s);
					}


				}
			}
			++start_s;
		}

		// handle collsion within asteroids by grids
	    for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (grids[i][j].size() != 0) {
					vector<GameObject*>::iterator fst = grids[i][j].begin();
					while (fst != grids[i][j].end())
					{
						vector<GameObject*>::iterator scd = grids[i][j].begin() + 1;
						while (scd != grids[i][j].end())
						{

							if (checkballcollsion(*(*fst), *(*scd))&& (*fst)->lasthit != (*scd) ) {

								(*fst)->lasthit = (*scd);
								(*scd)->lasthit = (*fst);
							   /* (*fst)->position = (*fst)->position +  normalize((*fst)->position - (*scd)->position);
								(*scd)->position = (*scd)->position +  normalize((*scd)->position - (*fst)->position);*/

								(*fst)->direction = -(*fst)->direction;

								(*scd)->direction = -(*scd)->direction;

								if ((*fst)->kind == 1 || (*scd)->kind == 1) {
								
								}
								
							}
							
								scd++;
							
						}

						
						fst++;
					}
				}
			}
		}
		

		
		vector<Bullet>:: iterator b = bullets.begin();
		while (b != bullets.end()) {
			bool touched = false;
		
				start_asteroids = asteroids.begin();
				while (start_asteroids != asteroids.end()) {

					if (checkballcollsion(*start_asteroids, *b)) {

						for (int m = 0; m < 2; ++m) //create medium Asteroid
						{
							MediumAsteroid ma;
							ma.position = start_asteroids->position;
							ma.speed = start_asteroids->speed;
							ma.direction = normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX)));
							mediumasteroids.push_back(ma);
						}
						/*		asteroids[j].position.x = 1500.f;
								asteroids[j].speed = 0.f;*/
						start_asteroids = asteroids.erase(start_asteroids);
						touched = true;
						//start_asteroids->~Asteroid();

					}
					else
					{

						start_asteroids++;

					}
					


				}

			

				vector<MediumAsteroid>::iterator start_m = mediumasteroids.begin();
				while (start_m != mediumasteroids.end()) {

					if (checkballcollsion(*start_m, *b)) {

						for (int m = 0; m < 2; ++m) //create medium Asteroid
						{
							SmallAsteroid sa;
							sa.position = start_m->position;
							sa.speed = start_m->speed;

							sa.direction = normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX)));
							smallasteroids.push_back(sa);
						}
						/*		asteroids[j].position.x = 1500.f;
								asteroids[j].speed = 0.f;*/
						start_m = mediumasteroids.erase(start_m);
						touched = true;
						//start_asteroids->~Asteroid();

					}
					else
					{

						start_m++;

					}



				}
	

				vector<SmallAsteroid>::iterator start_s = smallasteroids.begin();
				while (start_s != smallasteroids.end()) {

					if (checkballcollsion(*start_s, *b)) {

					
						start_s = smallasteroids.erase(start_s);
						touched = true;
						//start_asteroids->~Asteroid();

					}
					else
					{

						start_s++;

					}
				}

				if (touched) {
					b = bullets.erase(b);

				}
				else
				{
					b++;

				}
			
		}



		// check gameover
		if (asteroids.size() == 0 && mediumasteroids.size() == 0 && smallasteroids.size() == 0) {
			for (int i = 0; i < 4; ++i) {
				
				initialspeed += 30;
				Asteroid a(Vector2f(rand() % 800, rand() % 600), 40.f, initialspeed , normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX))));
				asteroids.push_back(a);

				//play music
			}
		
		}
		
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				//cout << grids[i][j].size() << endl;
				grids[i][j].clear();
			}
		}

		if (lifes == 0) {
			currentstate = gameover;
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

		/*for (auto i : asteroids) {
			i.generate(&window);
			i.update(dt.asSeconds());
		}*/

		for (int i = 0; i < mediumasteroids.size(); ++i) {
		mediumasteroids[i].generate(&window);
		mediumasteroids[i].update(dt.asSeconds());
		}

		for (int i = 0; i < smallasteroids.size(); ++i) {
			smallasteroids[i].generate(&window);
			smallasteroids[i].update(dt.asSeconds());
		}
		window.display();
	}
	return 0;
}