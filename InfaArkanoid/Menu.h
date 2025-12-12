//menu.h
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define MAX_LICZBA_POZIOMOW 3


class Menu
{

private:
	sf::Font font;
	std::vector <sf::Text>menu;//tablica elementow Text
	int selectedItem = 0;


public:
	Menu(float width, float height);
	~Menu() {};
	void przesunG();//przesun do gory
	void przesunD();//przesun w dol
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};
