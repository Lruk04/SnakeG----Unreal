#include "Grid.h"


Tile::Tile(int x, int y, char symbol) : x(x), y(y), symbol(symbol), occupied(false), hCost(0), gCost(0), fCost(0), parent(nullptr)
{
}

int Tile::GetX() const { return x; }
int Tile::GetY() const { return y; }
int Tile::GetFCost() const
{
	return fCost + hCost;
}

Tile* Tile::GetCameFrom() const { return parent; }
void Tile::SetCameFrom(Tile* previousTile) { parent = previousTile; }

char Tile::GetSymbol() const { return symbol; }
void Tile::SetSymbol(char newSymbol) { symbol = newSymbol; }

bool Tile::IsOccupied() const { return occupied; }
void Tile::SetOccupied(bool isOccupied) {
	occupied = isOccupied;
	symbol = occupied ? 'X' : 'O';
}

bool Tile::IsSnake() const { return snake; }
void Tile::SetSnake(bool isSnake) {
	snake = isSnake;
	symbol = snake ? 'S' : symbol;
}

bool Tile::IsFood() const { return food; }
void Tile::SetFood(bool isFood) {
	food = isFood;
	symbol = food ? 'F' : symbol;
}


Grid::Grid(int width, int height) : width(width), height(height) {
	grid.resize(height, std::vector<Tile>(width, Tile(0, 0, 'O')));
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			grid[y][x] = Tile(x, y, 'O');
		}
	}
}

Tile& Grid::GetTile(int x, int y) {
	return grid[y][x];
}

void Grid::SetTile(int x, int y, bool occupied) {
	grid[y][x].SetOccupied(occupied);
}

void Grid::SetTileFood(int x, int y, bool food) {
	grid[y][x].SetFood(food);
}

void Grid::SetTileSnake(int x, int y, bool snake) {
	grid[y][x].SetSnake(snake);
}

void Grid::ClearGrid()
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			grid[y][x].SetOccupied(false);
			grid[y][x].SetFood(false);
			grid[y][x].SetSnake(false);
		}
	}
}

Grid* Grid::GetGrid() {
	return this;
}

std::vector<Tile*> Grid::GetTileList()
{
	std::vector<Tile*> tiles;
	for (auto& row : grid) {
		for (auto& tile : row) {
			tiles.push_back(&tile);
		}
	}
	return tiles;
}


void Grid::printGrid() const {
	for (const auto& row : grid) {
		for (const auto& tile : row) {
			std::cout << tile.GetSymbol() << ' ';
		}
		std::cout << std::endl;
	}
}

Tile& Grid::GetRandomUnoccupiedTile() {

	int randomX = 0;
	int randomY = 0;

	do {
		randomX = rand() % (width - 2) + 1;
		randomY = rand() % (height - 2) + 1;
	} while (grid[randomY][randomX].IsOccupied()  || grid[randomY][randomX].IsSnake() || grid[randomY][randomX].IsFood());
	
	return grid[randomY][randomX];
}

Tile& Grid::GetRandomAppleTile() {
	std::vector<Tile*> appleTiles;

	for (auto& row : grid) {
		for (auto& tile : row) {
			if (tile.IsFood()) {
				appleTiles.push_back(&tile);
			}
		}
	}

	if (appleTiles.empty()) {
		throw std::runtime_error("No apple tile found");
	}

	std::srand(std::time(nullptr));
	int randomIndex = std::rand() % appleTiles.size();
	return *appleTiles[randomIndex];
}
