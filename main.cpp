#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>

const int GRID_WIDTH = 55; // Number of rows / columns in grid
// Overflow on anything higher than 55

const int CELL_WIDTH = 10;

const int WINDOW_SIZE = GRID_WIDTH * CELL_WIDTH;
const int CELLS = GRID_WIDTH * GRID_WIDTH;

int main(void)
{

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), 
		"Conway's Game of Life");

	sf::RectangleShape rectangles[CELLS];

	std::fill_n(rectangles, CELLS, sf::RectangleShape(sf::Vector2f(CELL_WIDTH, CELL_WIDTH)));

	rectangles[50].setFillColor(sf::Color::Blue);
	rectangles[50].setPosition(100,100);

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		window.clear();

		window.draw(rectangles[0]);
		window.draw(rectangles[50]);

		window.display();
	}


	return 0;
}