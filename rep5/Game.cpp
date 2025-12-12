//Game.cpp
#include "Game.h"
#include <iostream>

const int SZEROKOSC = 1000;
const int WYSOKOSC = 600;

Game::Game() :
	//inicjalizacje okna i obiektow gry
	m_window(sf::VideoMode(SZEROKOSC, WYSOKOSC), "Arcystonid - super gra polecam z rodzinka"),	//buduje okn
	//towrzenie obiektow gry
	m_paddle({ SZEROKOSC / 2.f, WYSOKOSC - 40.f }, { 200.f, 20.f }, { 50.f, 0.f }),
	m_ball({ SZEROKOSC / 2.f, WYSOKOSC / 2.f }, 20.f, { -100.f, 250.f })

	{
		m_window.setFramerateLimit(60);		//ustawia klatki na sekunde i nizej zegar

		//tworzenie cegielek std::vector<Brick> bloki; juz nie potzrbne bo pole klasy istnieje
		const int ILOSC_KOLUMN = 12;	//wlasciwy poziom blokow
		const int ILOSC_WIERSZY = 4;
		float ROZMIAR_BLOKU_X = (SZEROKOSC - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
		float ROZMIAR_BLOKU_Y = 20.f;

		//rysowanie blokow
		for (int y = 0; y < ILOSC_WIERSZY; y++) {
			for (int x = 0; x < ILOSC_KOLUMN; x++) {
				float posX = x * (ROZMIAR_BLOKU_X + 2.f); //przewraw miedzy blokami 2px
				float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
				//kolor bloku - ilosc zyc
				int zycie = 0;
				if (y == 0)
					zycie = 1;
				if (y >= 1)
					zycie = 2;

				m_bricks.emplace_back(
					sf::Vector2f(posX, posY), 
					sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), zycie);
			}
		}

	}

	void Game::run() {
		while (m_window.isOpen()) {
			sf::Time dt = m_deltaClock.restart();	//pobierz czas i zrestartuj zegar
			processEvents();
			update(dt);
			render();
		}
	}

	//do runa
	// podzial na 3
	// processEvents - obsluga zdarzen (pollevent,  zamkniecie okna)
	// update(dt) - sterowanie i logika gry (ruch paletki, ruch pilki, kolizje, zakonczenie)
	// render() - rysowanie(clear, draw, display)
	// 
	
	void Game::processEvents() {		////obsluga eventow
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
	}

	void Game::update(sf::Time dt) {
		//updateowanie - logika
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_paddle.moveLeft();           //dt to roznica czasu miedzy klatkami a dt.asSseconds zwraca te roznice w sekundach wiec jako float, tzw banger
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			m_paddle.moveRight();
		}
		m_paddle.clampToBounds(SZEROKOSC);

		//aktualizacja logiki
		m_ball.ruch(dt, { SZEROKOSC, WYSOKOSC }, m_paddle);
		if (m_ball.getPosition().y - m_ball.getRadius() > WYSOKOSC) {
			std::cout << "MISS! KONIEC GRY!\n";
			m_window.close();
		}

		//kolizja pilki z blokami
		for (auto& blk : m_bricks) {
			if (!blk.czyZniszczony() && m_ball.getGlobalBounds().intersects(blk.getGlobalBounds())) {
				blk.trafienie(); //zmiana kolorwu
				m_ball.odbijY(); //odbcie duh
			}
		}

		//usuwanie zniszczonych blokow
		//iterowanie od konca wektora (i=bloki.size()-1; i>=0; i--)
		for (int i = m_bricks.size() - 1; i >= 0; i--) {
			if (m_bricks[i].czyZniszczony()) {
				m_bricks.erase(m_bricks.begin() + i);
			}
		}
	}


	void Game::render() {					//render - rysowanie
		//rysowanie
		m_window.clear(sf::Color(40, 30, 20));
		m_paddle.draw(m_window);
		m_ball.draw(m_window);

		//bloki rysowanie
		for (auto& blk : m_bricks) {
			m_window.draw(blk);
		}

		m_window.display();
	};
	

