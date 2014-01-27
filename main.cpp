/*
Conway's Game Of Life

Rules:
	Any live cell with fewer than two live neighbours dies.
	Any live cell with more than three live neighbours dies.
	Any live cell with two or three live neighbours lives on to the next generation.
	Any dead cell with exactly three live neighbours becomes a live cell.
*/

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <array>
#include <forward_list>
#include <set>
#include <iostream>

const int GRID_WIDTH = 10; // Number of rows / columns in grid
// Overflow on anything higher than 55

const int CELL_WIDTH = 10;

const int WINDOW_SIZE = GRID_WIDTH * CELL_WIDTH;
const int CELLS = GRID_WIDTH * GRID_WIDTH;

class Populace
{
private:
	std::set<int>::iterator it;
	std::set<int> living;

	std::vector<int> findNeighbors(int cell)
	{
		std::array<int, 8> init = {cell + 1, cell - 1, cell + GRID_WIDTH,
			cell - GRID_WIDTH, cell + GRID_WIDTH- 1,
			cell + GRID_WIDTH + 1, cell - GRID_WIDTH -1,
			cell- GRID_WIDTH + 1};

		std::vector<int> neighbors(init.begin(), init.end());

		return neighbors;
	}
	
public:
	Populace(int[], int);
	
	bool isLiving(int cellNumber)
	{
		if (living.find(cellNumber)!= living.end())
			return true;
		return false;
	}

	

	int livingNeighbors(int cellNumber)
	{
		std::vector<int> neighbors = findNeighbors(cellNumber);

		int neighborsLiving = 0;

		for (int i = 0; i < 8; i++)
			if (isLiving(neighbors[i])) { neighborsLiving++; }

		return neighborsLiving;
	}

	std::set<int> updateLiving(void)
	{
		std::set<int> updatedLiving;

		for (it = living.begin(); it != living.end(); it++)
		{
			int neighborsLiving = livingNeighbors(*it);

			if (neighborsLiving == 2 || neighborsLiving ==3)
				updatedLiving.insert(*it);
		}

		return updatedLiving;
	}

	std::set<int> updateDead(void)
	{

	}
};

Populace::Populace(int *init, int size)
{
	living.insert(init, init + size);
}

int main(void)
{
	std::set<int>::iterator it2;
	int init[] = {3, 4, 5, 13, 15, 23, 24, 25};
	int size = sizeof(init) / sizeof(int);

	Populace populace(init, size);

	std::set<int> updated = populace.updateLiving();

	for (it2 = updated.begin(); it2 != updated.end(); it2++)
		std::cout << *it2 << " is alive!" << std::endl;

	return 0;
}

/*sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), 
		"Conway's Game of Life");

	bool isAlive[CELLS];
	std::fill_n(isAlive, CELLS, false);*/

	//sf::RectangleShape rectangles[CELLS];

	//std::fill_n(rectangles, CELLS, sf::RectangleShape(sf::Vector2f(CELL_WIDTH, CELL_WIDTH)));

	//rectangles[50].setFillColor(sf::Color::Blue);
	//rectangles[50].setPosition(100,100);

	//while (window.isOpen())
 //   {
 //       sf::Event event;
 //       while (window.pollEvent(event))
 //       {
 //           if (event.type == sf::Event::Closed)
 //               window.close();
 //       }

	//	window.clear();

	//	window.draw(rectangles[0]);
	//	window.draw(rectangles[50]);

	//	window.display();
	//}