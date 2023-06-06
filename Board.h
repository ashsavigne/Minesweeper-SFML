#pragma once
#include <string>
using std::string;
#include "TextureManager.h"
using std::vector;

class Board
{
	int boardWidth;
	int boardHeight;
	int numMines;
	int flags = 0;
	

	void SetBoardWidth(int x);
	void SetBoardHeight(int y);
	void SetNumMines(int z);

	struct Tiles 
	{
		int x, y;
		int adjacent = 0;
		bool isMine = false;
		bool rev = false;
		bool flag = false;
	
	};
	

public:

	
	vector<Tiles> allMines;
	vector<Tiles> allTiles;
	void ReadText(string fileName);
	void Readcfg(string filename);
	void FindAdjacent();
	void LoadBoard(sf::RenderWindow& window);
	int GetWindowWidth();
	int GetWindowHeight();
	int GetNumMines();
	int GetBoardWidth();
	int GetBoardHeight();
	void LoadHiddenTiles(sf::RenderWindow& window);
	void SetRandomMines();
	void LoadButtons(sf::RenderWindow& window);
	void LoadMines(sf::RenderWindow& window);
	bool RevealTiles(int index);
	void LoadRevealTiles(sf::RenderWindow& window);
	void PlaceFlag(int idx);
	void EndGame(sf::RenderWindow& window);
	void LoadFlags(sf::RenderWindow& window);
	void Restart();
	bool CheckWin(sf::RenderWindow& window);
	void LoadDigit(sf::RenderWindow& window);


};

