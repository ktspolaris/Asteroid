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
#include "Soundeffects.h"
#include "UI.h"
#include "Powerup.h"
#include "Soundeffect.h"


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
	if (sqrtf((ball1.position.x - ball2.position.x) * (ball1.position.x - ball2.position.x) + (ball1.position.y - ball2.position.y) * (ball1.position.y - ball2.position.y)) < (ball1.radius + ball2.radius )) {
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

void generatepoerup(GameObject astd, bool t1, bool t2, bool t3, Powerup p1, Powerup p2,Powerup p3) {
	double rate = rand() / double(RAND_MAX);
	if (rate > 0 && t1 == false) {
		// case 1
		//cout << "2123" << endl;
		//lengthen.direction = Vector2f(0.f, 1.f);
		p1.position = astd.position;
		t1 = true;

		//cout << p1.position.x << endl;
	}
	if (rate < 0.2 && rate > 0.1&&!t2) {
		//case 2
		p2.position = astd.position;
		t2 = true;
	}
	if (rate < 0.3 && rate > 0.2 && !t3) {
		//case 2
		p3.position = astd.position;
		t3 = true;
	}
}

int main() {
	UIofScore player1score(Vector2f(10.f, 300.f), 24);
	UIofScore hp(Vector2f(750.f, 300.f), 24);
	UI scoreboard("scores", Vector2f(10.f, 280.f), 24);
	UI hpboard("lifes", Vector2f(750.f, 280.f), 24);
	UI menu("Press Enter to start game", Vector2f(0.f, 300.f), 48);
	UI exit("Press X to exit game", Vector2f(0.f, 400.f), 48);
	UI Title("Asteroid", Vector2f(300.f, 200.f), 60);
	UI Gameover("Gameover, Press B return to main menu", Vector2f(0.f, 200.f), 48);
	Soundeffect shot("shot.wav");
	Soundeffect destroy("destroy.wav");
	Soundeffect die("die.wav");
	Soundeffect win("win.wav");
	Soundeffect push("push.wav");






	Clock explosionclock;
	Texture explosiontexture;
	explosiontexture.loadFromFile("explosion.png");
	Sprite explosion;
	//CircleShape ball(this->radius);
	explosion.setTexture(explosiontexture);
	explosion.setOrigin(40.f, 40.f);

	float initialspeed = 100.f;
	RenderWindow window(VideoMode(800, 600), "Asteroid");
	Clock clock;
	Clock cooldown;
	Clock Enemyclock;
	Clock Enemycooldown;
	Clock spreadclock;
	Clock rapidclock;
	Clock inviclock;
	bool pressed = false;
	float shotspeed = 0.2f;
	
	Time dt;
	Character player1(Vector2f(400.f,300.f), 10.f, 0.f, Vector2f(1.f,0.f));
	Fire fire(player1.position, player1.radius, player1.speed, player1.direction);
	Enemy enemy(Vector2f(-100.f,10.f), 40.f, 0.f, Vector2f(1.f, 0.f));
	Powerup spreadshot(Vector2f(1000.f, 595.f), 10.f, 0.f, normalize(Vector2f(0.f, 1.f)));
	spreadshot.color = Color(0, 255, 0);
	bool spreadfall = false;
	bool Isspread = false;
	Powerup rapidshot(Vector2f(1000.f, 595.f), 10.f, 0.f, normalize(Vector2f(0.f, 1.f)));
	rapidshot.color = Color(255, 0, 0);
	bool rapidfall = false;
	bool Israpid = false;

	Powerup invicibility(Vector2f(1000.f, 595.f), 10.f, 0.f, normalize(Vector2f(0.f, 1.f)));
	invicibility.color = Color(0, 0, 255);
	bool invifall = false;
	bool Isinvi = false;


	vector<Asteroid> asteroids;
	vector<MediumAsteroid> mediumasteroids;
	vector<SmallAsteroid> smallasteroids;
	int lifes = 3;
	int scores = 0;
	srand(time(0));
	for (int i = 0; i < 4; ++i) {

		Asteroid a(Vector2f(rand()%800, rand()%600), 40.f, initialspeed, normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX))) );
	
		asteroids.push_back(a);
	}
	enum gamestate{ mainmenu, isplay, gameover };
	gamestate currentstate = mainmenu;
    vector<Bullet> bullets;
	vector<Bullet> enemybullets;

	// create bucket grids 
	vector<GameObject*> grids[10][10];  // create grids
	while (window.isOpen())
	{
		window.clear();
		
		dt = clock.getElapsedTime();
		clock.restart();
		Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter) && currentstate == mainmenu) {
				enemy.position = Vector2f(-100.f, 10.f);
				enemy.speed = 0.f;
				Enemyclock.restart();
				lifes = 3;
				for (int i = 0; i < 1; ++i) {

					Asteroid a(Vector2f(rand() % 800, rand() % 600), 40.f, initialspeed, normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX))));

					asteroids.push_back(a);
				}

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
		/*	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up) ){
				push.playsound();
			}*/
		}

		switch (currentstate)
		{
		case mainmenu:
			Title.generateUI(&window);

			menu.generateUI(&window);
			exit.generateUI(&window);
			break;
			
		case isplay:
		{
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if(!pressed){
					pressed = true;
					push.playsound();
				}
			
				player1.accumlate = 50;
				fire.position = player1.position;

				fire.generate(&window);
			}
		
			
			else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				if (!pressed) {
					pressed = true;
					push.playsound();
				}
				player1.accumlate = -50;
				fire.position = player1.position;

				fire.generate(&window);


			}
			else {
				player1.accumlate = 0;

			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Up)) {
				pressed = false;
			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Down)) {
				pressed = false;
			}
				   if (Keyboard::isKeyPressed(Keyboard::Right)) {
					   if (!pressed) {
						   pressed = true;
						   push.playsound();
					   }
					   player1.rotation += 5 * dt.asSeconds();
					   fire.rotation += 5 * dt.asSeconds();

					   player1.direction.x = cos(player1.rotation);
					   player1.direction.y = sin(player1.rotation);
					   fire.direction = player1.direction;

				   }
				   if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Right)) {
					   pressed = false;
				   }
				   if (Keyboard::isKeyPressed(Keyboard::Left)) {
					   if (!pressed) {
						   pressed = true;
						   push.playsound();
					   }
					   player1.rotation += -5 * dt.asSeconds();
					   fire.rotation += -5 * dt.asSeconds();

					   player1.direction.x = cos(player1.rotation);
					   player1.direction.y = sin(player1.rotation);
					   fire.direction = player1.direction;
				   }
				   if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Left)) {
					   pressed = false;
				   }
				  
				   //player1.accumlate = 0;

				   //generate bullets
				   if (Keyboard::isKeyPressed(Keyboard::Space)) {
					   shot.playsound();
					   if (cooldown.getElapsedTime().asSeconds() > shotspeed) {
						   Bullet b(600.f);
						   b.direction = player1.direction;
						   b.position = player1.position;
						   bullets.push_back(b);
						   if (Isspread) {
							   Bullet b2(600.f);
							   b2.direction = normalize(player1.direction + Vector2f(-1, 0));
							   b2.position = player1.position;
							   bullets.push_back(b2);
							   Bullet b3(600.f);
							   b3.direction = normalize(player1.direction + Vector2f(1, 0));
							   b3.position = player1.position;
							   bullets.push_back(b3);
						   }
						   cooldown.restart();
					   }

				   }
				   if (bullets.size() > 4) {
					   bullets.erase(bullets.begin());
				   }
				   //distribute asteroids into grids
				   vector<Asteroid>::iterator start_asteroids = asteroids.begin();

				   while (start_asteroids != asteroids.end())
				   {
					   for (int i = 0; i < 10; i++) {
						   for (int j = 0; j < 10; j++) {
							   if (start_asteroids->position.x > 80 * i - 0.5 * start_asteroids->radius
								   && start_asteroids->position.x < 80 * i + 80 + 0.5 * start_asteroids->radius
								   && start_asteroids->position.y > 60 * j - 0.5 * start_asteroids->radius
								   && start_asteroids->position.y < 60 * j + 60 + 0.5 * start_asteroids->radius) {
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

									   if (checkballcollsion(*(*fst), *(*scd)) && (*fst)->lasthit != (*scd)) {

										   (*fst)->lasthit = (*scd);
										   (*scd)->lasthit = (*fst);

										   //(*(*fst)).~GameObject();
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

				   vector<Bullet>::iterator b = bullets.begin();
				
				   while (b != bullets.end()) {
					   bool touched = false;

					   start_asteroids = asteroids.begin();
					   while (start_asteroids != asteroids.end()) {

						   if (checkballcollsion(*start_asteroids, *b)) {
							   destroy.playsound();
							   double rate = rand() / double(RAND_MAX);
							   if (rate > 0.1 && rate < 0.2 && spreadfall == false) {

								   spreadshot.position = (*start_asteroids).position;
								   spreadfall = true;


							   }

							   if (rate > 0.2 && rate < 0.3 && rapidfall == false) {

								   rapidshot.position = (*start_asteroids).position;
								   rapidfall = true;

							   }

							   if (rate > 0.3 && rate < 0.4 && invifall == false) {

								   invicibility.position = (*start_asteroids).position;
								   invifall = true;

							   }

							   explosionclock.restart();
							   scores += 1;
							   for (int m = 0; m < 2; ++m) //create medium Asteroid
							   {
								   MediumAsteroid ma;
								   ma.position = start_asteroids->position;
								   ma.speed = start_asteroids->speed;
								   ma.direction = normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX)));
								   mediumasteroids.push_back(ma);
							   }
							   explosion.setPosition(start_asteroids->position);
							   start_asteroids = asteroids.erase(start_asteroids);
							   touched = true;

						   }
						   else
						   {

							   start_asteroids++;

						   }



					   }



					   vector<MediumAsteroid>::iterator start_m = mediumasteroids.begin();
					   while (start_m != mediumasteroids.end()) {

						   if (checkballcollsion(*start_m, *b)) {
							   destroy.playsound();
							   double rate = rand() / double(RAND_MAX);
							   if (rate > 0.1 && rate < 0.2 && spreadfall == false) {

								   spreadshot.position = (*start_m).position;
								   spreadfall = true;


							   }

							   if (rate > 0.2 && rate < 0.3 && rapidfall == false) {

								   rapidshot.position = (*start_m).position;
								   rapidfall = true;

							   }

							   if (rate > 0.3 && rate < 0.4 && invifall == false) {

								   invicibility.position = (*start_m).position;
								   invifall = true;

							   }
							   explosionclock.restart();
							   scores += 1;

							   for (int m = 0; m < 2; ++m) //create medium Asteroid
							   {

								   SmallAsteroid sa;
								   sa.position = start_m->position;
								   sa.speed = start_m->speed;

								   sa.direction = normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX)));
								   smallasteroids.push_back(sa);
							   }
							   explosion.setPosition(start_m->position);

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
							   destroy.playsound();
							   double rate = rand() / double(RAND_MAX);
							   if (rate > 0.1 && rate < 0.2 && spreadfall == false) {

								   spreadshot.position = (*start_s).position;
								   spreadfall = true;


							   }

							   if (rate > 0.2 && rate < 0.3 && rapidfall == false) {

								   rapidshot.position = (*start_s).position;
								   rapidfall = true;

							   }

							   if (rate > 0.3 && rate < 0.4 && invifall == false) {

								   invicibility.position = (*start_s).position;
								   invifall = true;

							   }
							   explosionclock.restart();
							   scores += 1;

							   explosion.setPosition(start_s->position);

							   start_s = smallasteroids.erase(start_s);
							   touched = true;

							   //start_asteroids->~Asteroid();

						   }
						   else
						   {

							   start_s++;

						   }
					   }


					   if (checkballcollsion(enemy, *b)) {
						   destroy.playsound();
						   explosionclock.restart();

						   enemy.speed = 0.f;
						   explosion.setPosition(enemy.position);

						   enemy.position = Vector2f(-100, 10);
						   Enemyclock.restart();
						   touched = true;
					   }

					   if (touched) {
						   b = bullets.erase(b);

					   }
					   else
					   {
						   b++;

					   }

				   }

				   for (vector<Bullet>::iterator eb = enemybullets.begin(); eb != enemybullets.end();)
				   {
					   if (checkballcollsion(*eb, player1)) {
						   die.playsound();
						   explosionclock.restart();
						   explosion.setPosition(player1.position);
						   eb = enemybullets.erase(eb);
						   if (!Isinvi) {
							   lifes -= 1;
							   player1.position = Vector2f(400.f, 300.f);
							   //sounds
						   }
					   }
					   else {
						   eb++;
					   }

				   }
				   for (start_asteroids = asteroids.begin(); start_asteroids != asteroids.end();) {
					   if (checkballcollsion(*start_asteroids, player1)) {
						   die.playsound();
						   explosionclock.restart();
						   explosion.setPosition(start_asteroids->position);
						   start_asteroids = asteroids.erase(start_asteroids);
						   if (!Isinvi) {
							   lifes -= 1;
							   player1.position = Vector2f(400.f, 300.f);
							   //sounds
						   }
					   }
					   else
					   {
						   start_asteroids++;

					   }
				   }
				   for (start_m = mediumasteroids.begin(); start_m != mediumasteroids.end();) {
					   if (checkballcollsion(*start_m, player1)) {
						   die.playsound();
						   explosionclock.restart();
						   explosion.setPosition(start_m->position);
						   start_m = mediumasteroids.erase(start_m);
						   if (!Isinvi) {
							   lifes -= 1;
							   player1.position = Vector2f(400.f, 300.f);
						   }


						   //sounds
					   }
					   else {
						   start_m++;
					   }
				   }
				   for (start_s = smallasteroids.begin(); start_s != smallasteroids.end();) {
					   if (checkballcollsion(*start_s, player1)) {
						   die.playsound();
						   explosionclock.restart();
						   explosion.setPosition(start_s->position);
						   start_s = smallasteroids.erase(start_s);
						   if (!Isinvi) {
							   lifes -= 1;
							   player1.position = Vector2f(400.f, 300.f);
							   //sounds
						   }
					   }
					   else {
						   start_s++;
					   }
				   }


				   //Enemy actions
				   if (Enemyclock.getElapsedTime().asSeconds() >= 10) {
					   enemy.speed = 200.f;
					   if (Enemycooldown.getElapsedTime().asSeconds() > 1) {
						   Bullet b(500.f);
						   b.direction = normalize(player1.position - enemy.position);
						   b.position = enemy.position;
						   enemybullets.push_back(b);
						   Enemycooldown.restart();
					   }
				   }
				   if (enemybullets.size() > 3) {
					   enemybullets.erase(enemybullets.begin());
				   }
				   // handle powerup
				   if (checkballcollsion(spreadshot, player1)) {
					   Isspread = true;
					   spreadclock.restart();
					   spreadfall = false;
					   spreadshot.position.x = 1200;
				   }
				   if (spreadclock.getElapsedTime().asSeconds() >= 3.f) {
					   Isspread = false;
				   }
				   if (checkballcollsion(rapidshot, player1)) {
					   Israpid = true;
					   rapidclock.restart();
					   rapidfall = false;
					   shotspeed = 0.1f;
					   rapidshot.position.x = 1200;

				   }
				   if (rapidclock.getElapsedTime().asSeconds() >= 3.f) {
					   shotspeed = 0.2f;
				   }
				   if (checkballcollsion(invicibility, player1)) {
					   Isinvi = true;
					   inviclock.restart();
					   invifall = false;
					   invicibility.position.x = 1200;

				   }
				   if (inviclock.getElapsedTime().asSeconds() >= 5.f) {
					   Isinvi = false;
				   }
				   // check gameover
				   if (asteroids.size() == 0 && mediumasteroids.size() == 0 && smallasteroids.size() == 0) {
					   for (int i = 0; i < 4; ++i) {

						   initialspeed += 30;
						   Asteroid a(Vector2f(rand() % 800, rand() % 600), 40.f, initialspeed, normalize(Vector2f(rand() / double(RAND_MAX), rand() / double(RAND_MAX))));
						   asteroids.push_back(a);

						   win.playsound();
					   }

				   }

				   for (int i = 0; i < 10; i++) {
					   for (int j = 0; j < 10; j++) {
						   //cout << grids[i][j].size() << endl;
						   grids[i][j].clear();
					   }
				   }

				   if (lifes == 0) {
					 //  asteroids.clear();
					   bullets.clear();
					   enemybullets.clear();
					  // smallasteroids.clear();
					 //  mediumasteroids.clear();

					   currentstate = gameover;
				   }

				   //handle screen
				   if (spreadfall) {
					   //cout << "1111" << endl;
					   spreadshot.generate(&window);
					   spreadshot.update(dt.asSeconds());
				   }
				
				   if (rapidfall) {
					   rapidshot.generate(&window);
					   rapidshot.update(dt.asSeconds());
				   }
				   if (invifall) {
					   invicibility.generate(&window);
					   invicibility.update(dt.asSeconds());
				   }
				   player1.update(dt.asSeconds());
				   fire.update(dt.asSeconds());
				   hpboard.generateUI(&window);
				   hp.generateUIofScore(&window, lifes);
				   player1.generate(&window);
				   for (int i = 0; i < bullets.size(); i++) {
					   bullets[i].generate(&window);
					   bullets[i].update(dt.asSeconds());
				   }
				   for (int i = 0; i < enemybullets.size(); i++) {
					   enemybullets[i].generate(&window);
					   enemybullets[i].update(dt.asSeconds());
				   }
				   for (int i = 0; i < asteroids.size(); ++i) {

					   asteroids[i].generate(&window);
					   asteroids[i].update(dt.asSeconds());
					   //asteroids[i].explosion(&window);

				   }
				   for (int i = 0; i < mediumasteroids.size(); ++i) {
					   mediumasteroids[i].generate(&window);
					   mediumasteroids[i].update(dt.asSeconds());
				   }
				   for (int i = 0; i < smallasteroids.size(); ++i) {
					   smallasteroids[i].generate(&window);
					   smallasteroids[i].update(dt.asSeconds());
				   }
				   if (explosionclock.getElapsedTime().asSeconds() <= 0.3) {
					   window.draw(explosion);
				   }
				   enemy.update(dt.asSeconds());
				   enemy.generate(&window);
				   player1score.generateUIofScore(&window, scores);
				   scoreboard.generateUI(&window);
		}
		break;
		case gameover:
			Gameover.generateUI(&window);
			player1score.generateUIofScore(&window, scores);
			scoreboard.generateUI(&window);
			break;
		}
		
		//control player1
		
		window.display();
	}
	return 0;
}