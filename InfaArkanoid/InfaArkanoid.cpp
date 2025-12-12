//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"			//tu zawarte include innych klas
#include "Menu.h"
#include "GameState.h"


enum class AppState {Menu, DuringTheGame, Scores, Win, Loss, GameOver};			//zdefiniowanie mozliweych srtanow gry
const int SZEROKOSC = 1000;
const int WYSOKOSC = 600;


int main() {
	//inicjalizacje okna 
	sf::RenderWindow window(sf::VideoMode(SZEROKOSC, WYSOKOSC), "Arcystonid - super gra polecam z rodzinka");	//m_window - member zmienna 
	window.setFramerateLimit(60);		//ustawia klatki na sekunde i nizej zegar

	Menu menu(window.getSize().x, window.getSize().y);		//obiekt menu
	AppState currentState = AppState::Menu;				//gra otwiera sie w menu
	Game game;												//klasa Game, obiekt game - jedna pojedyncza rozgrywka

	sf::Clock deltaClock;





	sf::Texture titleTex, winTex, lossTex;
	titleTex.loadFromFile("title.png");
	winTex.loadFromFile("win.png");
	lossTex.loadFromFile("gameover.png");

	sf::RectangleShape titleRect, winRect, lossRect;
	titleRect.setSize(sf::Vector2f(SZEROKOSC, WYSOKOSC));
	winRect.setSize(sf::Vector2f(SZEROKOSC, WYSOKOSC));
	lossRect.setSize(sf::Vector2f(SZEROKOSC, WYSOKOSC));

	titleRect.setTexture(&titleTex);
	winRect.setTexture(&winTex);
	lossRect.setTexture(&lossTex);

	titleRect.setPosition(0.f, 0.f);
	winRect.setPosition(0.f, 0.f);
	lossRect.setPosition(0.f, 0.f);





	while (window.isOpen()) {
		sf::Time dt = deltaClock.restart();	//pobierz czas i zrestartuj zegar
		sf::Event event;							//jakies zdarzemnoie

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();						//jak koniec event to zamknij okno

			else if (currentState == AppState::DuringTheGame) {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
					currentState = AppState::Menu;			//powrot do menu
				}
				
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
					//zapis stanu gry -  s od save`a
					GameState zapis;
					zapis.capture(game.getPaddle(), game.getBall(), game.getBricks());
					if (zapis.saveToFile("zapis.txt")) {
						std::cout << "Gra zapisana!\n";
					}
					else {
						std::cout << "Blad zapisu gry!\n";
					}
				}
			}



			if (currentState == AppState::Menu) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up)   menu.przesunG();
					if (event.key.code == sf::Keyboard::Down) menu.przesunD();

					if (event.key.code == sf::Keyboard::Enter) {
						if (menu.getSelectedItem() == 0) {
							// Nowa gra
							currentState = AppState::DuringTheGame;
						}
						else if (menu.getSelectedItem() == 1) {
							// Wczytaj grę
							GameState zapis;
							if (zapis.loadFromFile("zapis.txt")) {
								zapis.load(game.getPaddle(), game.getBall(), game.getBricks());
								currentState = AppState::DuringTheGame;
								std::cout << "Gra wczytana!\n";
							}
							else {
								std::cout << "Brak zapisu lub blad odczytu\n";
							}
						}
						else if (menu.getSelectedItem() == 2) {
							window.close();
						}
					}
				}
			}
			}


		if (currentState == AppState::DuringTheGame) {
			game.update(dt, window);
			if (game.hasLost()) {
				currentState = AppState::Loss;
			}
			else if (game.hasWon()) {
				currentState = AppState::Win;
			}
		}

		// rysowanie 
		window.clear(sf::Color(20, 50, 60));

		if (currentState == AppState::Menu) {
			// najpierw tło tytułu
			window.draw(titleRect);
			// potem (opcjonalnie) tekstowe menu
			menu.draw(window);
		}
		else if (currentState == AppState::DuringTheGame) {
			game.render(window);
		}
		else if (currentState == AppState::Win) {
			window.draw(winRect);
		}
		else if (currentState == AppState::Loss) {
			window.draw(lossRect);
		}

		window.display();
	}





	return 0;
}

	

	



