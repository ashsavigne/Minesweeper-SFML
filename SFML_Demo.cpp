#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <fstream>
#include <iostream>
using std::unordered_map;
using std::string;
#include <vector>
#include <cmath>
#include "Board.h"


int main()
{

 
    Board initBoard;
    initBoard.Readcfg("config");
    initBoard.SetRandomMines();
    initBoard.FindAdjacent();
    sf::RenderWindow window(sf::VideoMode(initBoard.GetWindowWidth(), initBoard.GetWindowHeight()), "Minesweeper");
    bool hidden = true;
    bool game = true;

    window.clear();
    initBoard.LoadBoard(window);
    initBoard.LoadButtons(window);
    initBoard.LoadMines(window);
    initBoard.LoadHiddenTiles(window);
    initBoard.LoadDigit(window);
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouseLoca = sf::Mouse::getPosition(window);

                sf::Rect<int> smileBound((initBoard.GetBoardWidth() / 2) * 32, initBoard.GetBoardHeight() * 32, 64, 64);
                sf::Rect<int> Test1Bound((initBoard.GetBoardWidth() - (initBoard.GetBoardWidth() / 4)) * 32, initBoard.GetBoardHeight() * 32, 64, 64);
                sf::Rect<int> Test2Bound((initBoard.GetBoardWidth() - (initBoard.GetBoardWidth() / 6)) * 32, initBoard.GetBoardHeight() * 32, 64, 64);
                sf::Rect<int> Test3Bound((initBoard.GetBoardWidth() - (initBoard.GetBoardWidth() / 9)) * 32, initBoard.GetBoardHeight() * 32, 64, 64);
                sf::Rect<int> debugBound((initBoard.GetBoardWidth() - (initBoard.GetBoardWidth() / 3)) * 32, initBoard.GetBoardHeight() * 32, 64, 64);

               
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    // smile button
                    if (smileBound.contains(mouseLoca))
                    {
                        game = true;
                        if (hidden)
                        {

                            window.clear();
                            initBoard.Restart();
                            initBoard.Readcfg("config");
                            initBoard.SetRandomMines();
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            window.display();
                        }
                        else
                        {
                            window.clear();
                            initBoard.Restart();
                            initBoard.Readcfg("config");
                            initBoard.SetRandomMines();
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            window.display();

                        }

                    }

                    // test 1
                    else if (Test1Bound.contains(mouseLoca))
                    {
                        if (hidden)
                        {
                            game = true;
                            window.clear();
                            initBoard.Restart();
                            initBoard.ReadText("testboard1");
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            window.display();
                        }
                        else
                        {
                            game = true;
                            window.clear();
                            initBoard.Restart();
                            initBoard.ReadText("testboard1");
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            window.display();
                        }
                    }

                    // test 2
                    else if (Test2Bound.contains(mouseLoca))
                    {
                        if (hidden)
                        {
                            game = true;
                            window.clear();
                            initBoard.Restart();
                            initBoard.ReadText("testboard2");
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            initBoard.LoadDigit(window);
                            window.display();
                        }
                        else
                        {
                            game = true;
                            window.clear();
                            initBoard.Restart();
                            initBoard.ReadText("testboard2");
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            initBoard.LoadDigit(window);
                            window.display();
                        }
                    }

                    // test 3
                    else if (Test3Bound.contains(mouseLoca))
                    {
                        if (hidden)
                        {
                            game = true;
                            window.clear();
                            initBoard.Restart();
                            initBoard.ReadText("testboard3");
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            window.display();
                        }
                        else
                        {
                            game = true;
                            window.clear();
                            initBoard.Restart();
                            initBoard.ReadText("testboard3");
                            initBoard.FindAdjacent();
                            initBoard.LoadBoard(window);
                            initBoard.LoadHiddenTiles(window);
                            initBoard.LoadMines(window);
                            initBoard.LoadButtons(window);
                            initBoard.LoadDigit(window);
                            window.display();
                        }
                    }

                    // debug
                    else if (debugBound.contains(mouseLoca))
                    {
                        if (game)
                        {

                            if (hidden == true)
                            {
                                window.clear();

                                initBoard.LoadBoard(window);
                                initBoard.LoadHiddenTiles(window);
                                initBoard.LoadMines(window);
                                initBoard.LoadButtons(window);
                                initBoard.LoadRevealTiles(window);
                                initBoard.LoadFlags(window);
                                initBoard.LoadDigit(window);
                                window.display();
                                hidden = false;

                            }
                            else
                            {
                                window.clear();
                                initBoard.LoadBoard(window);
                                initBoard.LoadMines(window);
                                initBoard.LoadHiddenTiles(window);
                                initBoard.LoadButtons(window);
                                initBoard.LoadRevealTiles(window);
                                initBoard.LoadDigit(window);
                                initBoard.LoadFlags(window);
                                window.display();
                                hidden = true;
                            }
                        }
                    }

                    // tile
                    else
                    {
                        if (game)
                        {
                           
                            
                            for (int i = 0; i < initBoard.allTiles.size(); i++)
                            {
                                sf::Rect<int> bounds(initBoard.allTiles[i].x, initBoard.allTiles[i].y, 32, 32);

                                if (bounds.contains(mouseLoca))
                                {
                                    // if flag
                                    if (initBoard.allTiles[i].flag) 
                                    {
                                       
                                    }

                                    // if mine
                                    else if (initBoard.allTiles[i].isMine) 
                                    {
                                        if (bounds.contains(mouseLoca))
                                        {
                                            if (hidden)
                                            {
                                                window.clear();
                                                initBoard.LoadButtons(window);
                                                initBoard.LoadHiddenTiles(window);
                                                initBoard.LoadRevealTiles(window);
                                                initBoard.EndGame(window);
                                                initBoard.Restart();
                                                window.display();
                                                game = false;
                                            }
                                            else
                                            {
                                                window.clear();
                                                initBoard.LoadButtons(window);
                                                initBoard.LoadHiddenTiles(window);
                                                initBoard.LoadRevealTiles(window);
                                                initBoard.EndGame(window);
                                                initBoard.Restart();
                                                window.display();
                                                game = false;
                                            }
                                        }
                                    
                                    }
                                    // if safe tile
                                    else 
                                    {
                                        if (hidden)
                                        {

                                            window.clear();
                                            initBoard.LoadButtons(window);
                                            initBoard.LoadHiddenTiles(window);
                                            initBoard.RevealTiles(i);
                                            initBoard.LoadRevealTiles(window);
                                            if (initBoard.CheckWin(window))
                                            {
                                                game = false;
                                                window.display();
                                                initBoard.Restart();

                                            }
                                            else
                                            {
                                                initBoard.LoadFlags(window);
                                                initBoard.LoadDigit(window);
                                                window.display();
                                            }
                                        }
                                        else
                                        {
                                            window.clear();
                                            initBoard.LoadButtons(window);
                                            initBoard.LoadHiddenTiles(window);
                                            initBoard.RevealTiles(i);
                                            initBoard.LoadRevealTiles(window);
                                            if (initBoard.CheckWin(window))
                                            {
                                                game = false;
                                                window.display();
                                                initBoard.Restart();
                                            }
                                            else
                                            {

                                                initBoard.LoadMines(window);
                                                initBoard.LoadFlags(window);
                                                initBoard.LoadDigit(window);
                                                window.display();
                                            }
                                        }
                                    
                                    }
                                }
                            }
                        }
                        }
                }
                // place flag
                else if ((event.mouseButton.button == sf::Mouse::Right))
                {
                    for (int i = 0; i < initBoard.allTiles.size(); i++)
                    {
                        sf::Rect<int> bounds(initBoard.allTiles[i].x, initBoard.allTiles[i].y, 32, 32);

                        
                        if (bounds.contains(mouseLoca))
                        {
                            if (game) 
                            {
                                if (hidden)
                                {
                                    window.clear();
                                    initBoard.LoadButtons(window);
                                    initBoard.LoadHiddenTiles(window);
                                    initBoard.LoadRevealTiles(window);
                                    initBoard.PlaceFlag(i);
                                    initBoard.LoadFlags(window);
                                    initBoard.LoadDigit(window);
                                    window.display();
                                }
                                else
                                {
                                    window.clear();
                                    initBoard.LoadButtons(window);
                                    initBoard.LoadHiddenTiles(window);
                                    initBoard.LoadRevealTiles(window);
                                    initBoard.LoadMines(window);
                                    initBoard.PlaceFlag(i);
                                    initBoard.LoadFlags(window);
                                    initBoard.LoadDigit(window);
                                    window.display();
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    

    
   return 0;
}