//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"			//tu zawarte include innych klas
#include "Menu.h"


enum class GameState {Menu, DuringTheGame, Scores, GameOver};			//zdefiniowanie mozliweych srtanow gry
const int SZEROKOSC = 1000;
const int WYSOKOSC = 600;


int main() {
	//inicjalizacje okna 
	sf::RenderWindow window(sf::VideoMode(SZEROKOSC, WYSOKOSC), "Arcystonid - super gra polecam z rodzinka");	//m_window - member zmienna 
	window.setFramerateLimit(60);		//ustawia klatki na sekunde i nizej zegar

	Menu menu(window.getSize().x, window.getSize().y);		//obiekt menu
	GameState currentState = GameState::Menu;				//gra otwiera sie w menu
	Game game;												//klasa Game, obiekt game - jedna pojedyncza rozgrywka

	sf::Clock deltaClock;

	while (window.isOpen()) {
		sf::Time dt = deltaClock.restart();	//pobierz czas i zrestartuj zegar
		sf::Event event;							//jakies zdarzemnoie

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();						//jak koniec event to zamknij okno

			//oblsuga menu
			if (currentState == GameState::Menu) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up)   menu.przesunG();
					if (event.key.code == sf::Keyboard::Down) menu.przesunD();

					if (event.key.code == sf::Keyboard::Enter) {
						if (menu.getSelectedItem() == 0) {
							currentState = GameState::DuringTheGame;		//start gry
						}
						else if (menu.getSelectedItem() == 2) {
							window.close();						//wyjdz z gry
						}
					}
				}

			}
			else if (currentState == GameState::DuringTheGame) {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
					currentState = GameState::Menu;			//powrot do menu
				}
			}
		}

		if (currentState == GameState::DuringTheGame) {
			game.update(dt, window);
		}

		//rysowanie 
		window.clear(sf::Color(20, 50, 60));
		if (currentState == GameState::Menu) {			//rysowanie menu
			menu.draw(window);
		}
		else if (currentState == GameState::DuringTheGame) {		//rysowanie rozgrywki
			game.render(window);
		}

		window.display();
	}


	return 0;
}

	

	




