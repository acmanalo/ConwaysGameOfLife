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
#include <set>
#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>

const int GRID_WIDTH = 200; // Number of rows / columns in grid
// Overflow on anything higher than 55

const int CELL_WIDTH = 4;

const int WINDOW_SIZE = GRID_WIDTH * CELL_WIDTH;
const int CELLS = GRID_WIDTH * GRID_WIDTH;

const int SLEEP_DELAY = 50;

class Populace
{
private:
	std::set<int>::iterator it;
	std::set<int> updatedLiving;
	std::set<int> updatedDead;

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
	std::set<int> living;
	Populace(int[], int);
	int generation;
	
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
			if (*it > 0)
			{
				int neighborsLiving = livingNeighbors(*it);

				if (neighborsLiving == 2 || neighborsLiving ==3)
					updatedLiving.insert(*it);
			}
		}

		return updatedLiving;
	}

	std::set<int> updateDead(void)
	{
		std::set<int> updatedDead;
		std::set<int> toExamine;
		std::vector<int>::iterator iter;

		for (it = living.begin(); it != living.end(); it++)
		{
			std::vector<int> neighbors = findNeighbors(*it);

			toExamine.insert(neighbors.begin(), neighbors.end());
		}

		for (it = toExamine.begin(); it != toExamine.end(); it++)
			if (*it > 0 && livingNeighbors(*it) == 3)
				updatedDead.insert(*it);

		return updatedDead;
	}

	void increaseGeneration(void)
	{
		generation++;
		updatedLiving = updateLiving();
		updatedDead = updateDead();

		living = updatedLiving;
		living.insert(updatedDead.begin(), updatedDead.end());
	}

	void printout(void)
	{
		for (int row = 0; row < GRID_WIDTH; row++)
		{
			for (int col = 0; col < GRID_WIDTH; col++)
			{
				int cell = row * GRID_WIDTH + col;

				if (isLiving(cell)) { std::cout << "O "; }
				else { std::cout << "X "; }
			}

			std::cout << std::endl;
		}
	}
};

Populace::Populace(int *init, int size)
{
	living.insert(init, init + size);
}

int main(void)
{
	sf::Font font;
	font.loadFromFile("./arial.ttf");
	std::set<int>::iterator it;
	std::set<int> testingSet;
	int i = 10100;
	int init[] = {i, i+1, i+2, i+3, i+4, i+5, i+6, i+7, i+9, i+10, i+11, i+12, i+13,
		i+17, i+18, i+19, i+26, i+27, i+28, i+29, i+30, i+31, i+32, i+34, i+35, i+36, i+37, i+38};

	int size = sizeof(init) / sizeof(int);

	Populace populace(init, size);

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Conway's Game Of Life");
	populace.generation = 0;

	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


		for (it = populace.living.begin(); it != populace.living.end(); it++)
		{
			int col = *it % GRID_WIDTH - 1;
			int row = (*it - col) / GRID_WIDTH;

			int x = col * CELL_WIDTH;
			int y = row * CELL_WIDTH;

			sf::RectangleShape rect(sf::Vector2f(CELL_WIDTH, CELL_WIDTH));
			rect.setPosition(x, y);
			rect.setFillColor(sf::Color::White);

			window.draw(rect);
		}

		sf::Text stats;
		stats.setFont(font);
		stats.setCharacterSize(12);
		stats.setColor(sf::Color::White);
		stats.setPosition(5, 5);
		std::stringstream ss;
		ss << "Generation: " << populace.generation << "  Live Cells: " << populace.living.size();
		stats.setString(ss.str());
		window.draw(stats);

		window.display();

		populace.increaseGeneration();
		populace.generation++;

		Sleep(SLEEP_DELAY);
		window.clear();
	}

	return 0;
}