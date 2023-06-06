#include "Board.h"
#include <fstream>
#include "Random.h"
#include <iostream>
using std::vector;
using std::string;
#include <sstream>



void Board::SetBoardWidth(int x) 
{
	boardWidth = x;
}
void Board::SetBoardHeight(int y) 
{
	boardHeight = y;
}
void Board::SetNumMines(int z) 
{
	numMines = z;
}

void Board::Readcfg(string filename)
{
    string path = "boards/";
    path += filename + ".cfg";

    std::ifstream cfgFile(path);
    std::vector<int> xyz;
    if (cfgFile.is_open())
    {
        string token;
        while (getline(cfgFile, token))
        {
            xyz.push_back(stoi(token));
        }
    }
    int x = xyz[0];
    SetBoardWidth(x);
    int y = xyz[1];
    SetBoardHeight(y);
    int z = xyz[2];
    SetNumMines(z);
}

void Board::ReadText(string fileName) 
{
    string path = "boards/";
    path += fileName + ".brd";

    std::ifstream testFile(path);
    string token;
    int tempH = 0;
    int tempW = 0;
    if (testFile.is_open())
    {
        string line;
        while (getline(testFile, line)) 
        {
            for (int i = 0; i < boardWidth; i++) 
            {
                
                char num = line.at(i);
                int n = (int)num;
                
                if (n == 49)
                {
                    numMines += 1;
                    Tiles mine;
                    mine.x = tempW;
                    mine.y = tempH;
                    mine.isMine = true;
                    allMines.push_back(mine);
                }
            
                tempW += 32;
            }
            tempW = 0;
            tempH += 32;
        }
        
    }



}

void Board::SetRandomMines() 
{
  
    int X;
    int Y;
    int i = 1;
    Tiles mine;
    mine.x = 32 * Random::Int(0, boardWidth - 1);
    mine.y = 32 * Random::Int(0, boardHeight - 1);
    mine.isMine = 0;
    allMines.push_back(mine);

    while (i < numMines)
    {
        bool equal = false;
        X = 32 * Random::Int(0, boardWidth - 1);
        Y = 32 * Random::Int(0, boardHeight - 1);

        for (int j = 0; j < allMines.size(); j++) 
        {
            if (X == allMines[j].x) 
            {
                if (Y == allMines[j].y) 
                {
                    equal = true;
                }
            }
        }

        if (not equal)
        {
            Tiles nMine;
            nMine.x = X;
            nMine.y = Y;
            nMine.isMine = true;
            allMines.push_back(nMine);
            i++;
        }
         
    }
    
}

void Board::FindAdjacent()
{

    // load revealed tiles
    int tempHeight = 0;
    int tempWidth = 0;

    // create a vector of all tiles
    for (int i = 0; i < boardHeight; i++) 
    {
        for (int j = 0; j < boardWidth; j++)
        {
            Tiles revealed;
            revealed.x = tempWidth;
            revealed.y = tempHeight;

            for (int k = 0; k < allMines.size(); k++) 
            {
                if (allMines[k].x == tempWidth) 
                {
                    if (allMines[k].y == tempHeight) 
                    {
        
                        revealed.isMine = true;
                    }
                }
            }
            tempWidth += 32;
            allTiles.push_back(revealed);
        }
        tempWidth = 0;
        tempHeight += 32;
    }

    for (int i = 0; i < allTiles.size(); i++) 
    {
        if (allTiles[i].isMine) 
        {
            
            // to the left
            if (i - 1 >= 0) 
            {
                if ((allTiles[i].x % boardWidth) != 0)
                {
                    allTiles[i - 1].adjacent += 1;
                }
            }

            // right
            if (i + 1 < allTiles.size()) 
            {
                if (allTiles[i + 1].x % boardWidth != 0) 
                {
                    allTiles[i + 1].adjacent += 1;
                }
            }
            
            // up 1
            if (i - boardWidth >= 0) 
            {
                allTiles[i - boardWidth].adjacent += 1;
            
            }
            

            // up and to left
            if (i - boardWidth - 1 >= 0) 
            {
                if (allTiles[i].x % boardWidth != 0) 
                {
                    allTiles[i - boardWidth - 1].adjacent += 1;
                }
            }
            

            // up to the right
            if (i - boardWidth + 1 >= 0) 
            {
                if (i + 1 < allTiles.size()) 
                {
                    if (allTiles[i + 1].x % boardWidth != 0) 
                    {
                        allTiles[i - boardWidth + 1].adjacent += 1;
                    }
                }
            }
            

            // down
            if (i + boardWidth < allTiles.size()) 
            {
                allTiles[i + boardWidth].adjacent += 1;
            }
            
            // down to the left
            if (i + boardWidth - 1 < allTiles.size())
            {
                if (allTiles[i].x % boardWidth != 0) 
                {
                    allTiles[i + boardWidth - 1].adjacent += 1;
                }
            }
            
            // down to the right
            if (i + boardWidth + 1 < allTiles.size()) 
            {
                if (allTiles[i + 1].x % boardWidth != 0) 
                {
                    allTiles[i + boardWidth + 1].adjacent += 1;
                }
            }
        }
    
    }
            

  
}


void Board::LoadBoard(sf::RenderWindow& window)
{

    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite revTile(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite number1(TextureManager::GetTexture("number_1"));
    sf::Sprite number2(TextureManager::GetTexture("number_2"));
    sf::Sprite number3(TextureManager::GetTexture("number_3"));
    sf::Sprite number4(TextureManager::GetTexture("number_4"));
    sf::Sprite number5(TextureManager::GetTexture("number_5"));
    sf::Sprite number6(TextureManager::GetTexture("number_6"));
    sf::Sprite number7(TextureManager::GetTexture("number_7"));
    sf::Sprite number8(TextureManager::GetTexture("number_8"));

    for (unsigned int i = 0; i < allTiles.size(); i++)
    {
        revTile.setPosition(allTiles[i].x, allTiles[i].y);
        window.draw(revTile);

       
        if (allTiles[i].adjacent == 1)
        {
            number1.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number1);
        }
        else if (allTiles[i].adjacent == 2)
        {
            number2.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number2);
        }
        else if (allTiles[i].adjacent == 3)
        {
            number3.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number3);
        }
        else if (allTiles[i].adjacent == 4)
        {
            number4.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number4);
        }
        else if (allTiles[i].adjacent == 5)
        {
            number5.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number5);
        }
        else if (allTiles[i].adjacent == 6)
        {
            number6.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number6);
        }
        else if (allTiles[i].adjacent == 7)
        {
            number7.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number7);
        }
        else if (allTiles[i].adjacent == 8)
        {
            number8.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(number8);
        }


    }

}

void Board::LoadButtons(sf::RenderWindow& window) 
{
    sf::Sprite happy(TextureManager::GetTexture("face_happy"));
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));

    happy.setPosition(GetWindowWidth() / 2 - 16, GetWindowHeight() - 100);
    window.draw(happy);

    debug.setPosition((boardWidth * 32) - (32 * 8), GetWindowHeight() - 100);
    window.draw(debug);

    test1.setPosition(boardWidth * 32 - (192), GetWindowHeight() - 100);
    window.draw(test1);

    test2.setPosition(boardWidth * 32 - 128, GetWindowHeight() - 100);
    window.draw(test2);

    test3.setPosition(boardWidth * 32 - 64, GetWindowHeight() - 100);
    window.draw(test3);
}

int Board::GetWindowWidth() 
{
    return (boardWidth * 32);
}
int Board::GetWindowHeight() 
{
    return (boardHeight * 32 + 100);
}
int Board::GetNumMines() 
{
    return numMines;

}

int Board::GetBoardWidth() 
{
    return boardWidth;

}
int Board::GetBoardHeight() 
{
    return boardHeight;

}

void Board::LoadHiddenTiles(sf::RenderWindow& window)
{
    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
    for (unsigned int i = 0; i < allTiles.size(); i++)
    {
        hiddenTile.setPosition(allTiles[i].x, allTiles[i].y);
        window.draw(hiddenTile);
    }
}

void Board::LoadMines(sf::RenderWindow& window)
{
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    for (unsigned int i = 0; i < allTiles.size(); i++)
    {
        if (allTiles[i].isMine == true)
        {
            mine.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(mine);
        }
    }
}

void Board::EndGame(sf::RenderWindow& window) 
{
    sf::Sprite revTile(TextureManager::GetTexture("tile_revealed"));
    for (unsigned int i = 0; i < allTiles.size(); i++)
    {

        if (allTiles[i].isMine == true)
        {
            revTile.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(revTile);
        }
    }
    LoadMines(window);
    sf::Sprite lose(TextureManager::GetTexture("face_lose"));
    lose.setPosition(GetWindowWidth() / 2 - 16, GetWindowHeight() - 100);
    window.draw(lose);
}

bool Board::RevealTiles(int i)
{

    if (allTiles[i].rev)
    {
        return false;
    }

    else if (allTiles[i].flag)
    {
        return false;
    }

    else if (allTiles[i].isMine)
    {
        return false;
    }

    else if (allTiles[i].adjacent > 0)
    {
        allTiles[i].rev = true;
        return false;

    }


    else
    {
        int j = 0;
        allTiles[i].rev = true;
        // to the left
        if (i - 1 >= 0)
        {
            if ((allTiles[i].x % boardWidth) != 0)
            {
                j = i - 1;
                RevealTiles(j);
            }
        }

        // right
        if (i + 1 < allTiles.size())
        {
            if (allTiles[i + 1].x % boardWidth != 0)
            {

                j = i + 1;
                RevealTiles(j);
            }
        }

        // up 1
        if ((i - boardWidth) > 0)
        {
            j = i - boardWidth;
            
            if (j > 0)
            {
                RevealTiles(j);
            }
        }

        // up and to left
        if (i - boardWidth - 1 >= 0)
        {
            if (allTiles[i].x % boardWidth != 0)
            {
                j = i - boardWidth - 1;
                if (j > 0)
                {
                    RevealTiles(j);
                }
            }
        }

        // up to the right
        if (i - boardWidth + 1 >= 0)
        {
            if (i + 1 < allTiles.size())
            {
                if (allTiles[i + 1].x % boardWidth != 0)
                {
                    j = i - boardWidth + 1;
                    if (j > 0) 
                    {
                        RevealTiles(j);
                    
                    }
                }
            }
        }

        // down
        if (i + boardWidth < allTiles.size())
        {
            j = i + boardWidth;
            if (j > 0)
            {
                RevealTiles(j);
            }

        }

        // down to the left
        if (i + boardWidth - 1 < allTiles.size())
        {
            if (allTiles[i].x % boardWidth != 0)
            {
                j = i + boardWidth - 1;
                if (j < allTiles.size())
                    RevealTiles(j);
            }
        }

        // down to the right
        if (i + boardWidth + 1 < allTiles.size())
        {
            if (allTiles[i + 1].x % boardWidth != 0)
            {
                j = i + boardWidth + 1;
                if (j < allTiles.size())
                    RevealTiles(j);
            }
        }
    }
        
    
    
    
   
}

void Board::LoadRevealTiles(sf::RenderWindow& window)
{
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite revTile(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite number1(TextureManager::GetTexture("number_1"));
    sf::Sprite number2(TextureManager::GetTexture("number_2"));
    sf::Sprite number3(TextureManager::GetTexture("number_3"));
    sf::Sprite number4(TextureManager::GetTexture("number_4"));
    sf::Sprite number5(TextureManager::GetTexture("number_5"));
    sf::Sprite number6(TextureManager::GetTexture("number_6"));
    sf::Sprite number7(TextureManager::GetTexture("number_7"));
    sf::Sprite number8(TextureManager::GetTexture("number_8"));

    for (unsigned int i = 0; i < allTiles.size(); i++)
    {
        
        if (allTiles[i].rev) 
        {
            
            revTile.setPosition(allTiles[i].x, allTiles[i].y);
            window.draw(revTile);
            
            
            if (allTiles[i].adjacent == 1)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                
                number1.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number1);
            }
            else if (allTiles[i].adjacent == 2)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                number2.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number2);
            }
            else if (allTiles[i].adjacent == 3)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                number3.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number3);
            }
            else if (allTiles[i].adjacent == 4)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                number4.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number4);
            }
            else if (allTiles[i].adjacent == 5)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                number5.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number5);
            }
            else if (allTiles[i].adjacent == 6)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                number6.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number6);
            }
            else if (allTiles[i].adjacent == 7)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                number7.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number7);
            }
            else if (allTiles[i].adjacent == 8)
            {
                revTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(revTile);
                number8.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(number8);
            }
        }
    }

}

void Board::PlaceFlag(int idx) 
{
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));

    if (allTiles[idx].flag == true) 
    {
        allTiles[idx].flag = false;
        flags--;
    }
    else 
    {
        if (not allTiles[idx].rev) 
        {
            allTiles[idx].flag = true;
            flags += 1;
        }
    }
}

void Board::LoadFlags(sf::RenderWindow& window)
{

    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));



    for (int i = 0; i < allTiles.size(); i++)
    {
        if (allTiles[i].flag == true)
        {
            if (allTiles[i].rev == false)
            {
                hiddenTile.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(hiddenTile);
                flag.setPosition(allTiles[i].x, allTiles[i].y);
                window.draw(flag);
            }
        }
    }

}

void Board::Restart() 
{
    allTiles.clear();
    allTiles.shrink_to_fit();

    allMines.clear();
    allMines.shrink_to_fit();

    flags = 0;

    numMines = 0;
}

void Board::LoadDigit(sf::RenderWindow& window) 
{
    sf::Sprite digit0(TextureManager::GetTexture("digits"));
    digit0.setTextureRect(sf::IntRect(0, 0, 21, 32));

    sf::Sprite digit1(TextureManager::GetTexture("digits"));
    digit1.setTextureRect(sf::IntRect(21, 0, 21, 32));

    sf::Sprite digit2(TextureManager::GetTexture("digits"));
    digit2.setTextureRect(sf::IntRect(42, 0, 21, 32));

    sf::Sprite digit3(TextureManager::GetTexture("digits"));
    digit3.setTextureRect(sf::IntRect(63, 0, 21, 32));

    sf::Sprite digit4(TextureManager::GetTexture("digits"));
    digit4.setTextureRect(sf::IntRect(84, 0, 21, 32));

    sf::Sprite digit5(TextureManager::GetTexture("digits"));
    digit5.setTextureRect(sf::IntRect(105, 0, 21, 32));

    sf::Sprite digit6(TextureManager::GetTexture("digits"));
    digit6.setTextureRect(sf::IntRect(126, 0, 21, 32));

    sf::Sprite digit7(TextureManager::GetTexture("digits"));
    digit7.setTextureRect(sf::IntRect(147, 0, 21, 32));

    sf::Sprite digit8(TextureManager::GetTexture("digits"));
    digit8.setTextureRect(sf::IntRect(168, 0, 21, 32));

    sf::Sprite digit9(TextureManager::GetTexture("digits"));
    digit9.setTextureRect(sf::IntRect(189, 0, 21, 32));

    sf::Sprite digitNeg(TextureManager::GetTexture("digits"));
    digitNeg.setTextureRect(sf::IntRect(210, 0, 21, 32));


    int display = numMines - flags;

    int third = display % 10;
    if (third < 0)
        third *= -1;
    int second = (display / 10) % 10;
    if (second < 0)
        second *= -1;
    int first = display / 100;
    if (first < 0)
        first *= -1;

    if (display < 0) 
    {
        digitNeg.setPosition(0, boardHeight * 32);
        window.draw(digitNeg);
    }

    if (first == 0) 
    {
        digit0.setPosition(21, boardHeight * 32);
        window.draw(digit0);
    }

    else if (first == 1) 
    {
        digit1.setPosition(21, boardHeight * 32);
        window.draw(digit1);
    }

    else if (first == 2)
    {
        digit2.setPosition(21, boardHeight * 32);
        window.draw(digit2);
    }

    else if (first == 3)
    {
        digit3.setPosition(21, boardHeight * 32);
        window.draw(digit3);
    }

    else if (first == 4)
    {
        digit4.setPosition(21, boardHeight * 32);
        window.draw(digit4);
    }

    else if (first == 5)
    {
        digit5.setPosition(21, boardHeight * 32);
        window.draw(digit5);
    }

    else if (first == 6)
    {
        digit6.setPosition(21, boardHeight * 32);
        window.draw(digit6);
    }

    else if (first == 7)
    {
        digit7.setPosition(21, boardHeight * 32);
        window.draw(digit7);
    }

    else if (first == 8)
    {
        digit8.setPosition(21, boardHeight * 32);
        window.draw(digit8);
    }

    else if (first == 9)
    {
        digit9.setPosition(21, boardHeight * 32);
        window.draw(digit9);
    }

    if (second == 0)
    {
        digit0.setPosition(42, boardHeight * 32);
        window.draw(digit0);
    }

    else if (second == 1)
    {
        digit1.setPosition(42, boardHeight * 32);
        window.draw(digit1);
    }

    else if (second == 2)
    {
        digit2.setPosition(42, boardHeight * 32);
        window.draw(digit2);
    }

    else if (second == 3)
    {
        digit3.setPosition(42, boardHeight * 32);
        window.draw(digit3);
    }

    else if (second == 4)
    {
        digit4.setPosition(42, boardHeight * 32);
        window.draw(digit4);
    }

    else if (second == 5)
    {
        digit5.setPosition(42, boardHeight * 32);
        window.draw(digit5);
    }

    else if (second == 6)
    {
        digit6.setPosition(42, boardHeight * 32);
        window.draw(digit6);
    }

    else if (second == 7)
    {
        digit7.setPosition(42, boardHeight * 32);
        window.draw(digit7);
    }

    else if (second == 8)
    {
        digit8.setPosition(42, boardHeight * 32);
        window.draw(digit8);
    }

    else if (second == 9)
    {
        digit9.setPosition(42, boardHeight * 32);
        window.draw(digit9);
    }

    if (third == 0)
    {
        digit0.setPosition(63, boardHeight * 32);
        window.draw(digit0);
    }

    else if (third == 1)
    {
        digit1.setPosition(63, boardHeight * 32);
        window.draw(digit1);
    }

    else if (third == 2)
    {
        digit2.setPosition(63, boardHeight * 32);
        window.draw(digit2);
    }

    else if (third == 3)
    {
        digit3.setPosition(63, boardHeight * 32);
        window.draw(digit3);
    }

    else if (third == 4)
    {
        digit4.setPosition(63, boardHeight * 32);
        window.draw(digit4);
    }

    else if (third == 5)
    {
        digit5.setPosition(63, boardHeight * 32);
        window.draw(digit5);
    }

    else if (third == 6)
    {
        digit6.setPosition(63, boardHeight * 32);
        window.draw(digit6);
    }

    else if (third == 7)
    {
        digit7.setPosition(63, boardHeight * 32);
        window.draw(digit7);
    }

    else if (third == 8)
    {
        digit8.setPosition(63, boardHeight * 32);
        window.draw(digit8);
    }

    else if (third == 9)
    {
        digit9.setPosition(63, boardHeight * 32);
        window.draw(digit9);
    }


}




bool Board::CheckWin(sf::RenderWindow& window)
{
    bool win = true;

    for (int i = 0; i < allTiles.size(); i++)
    {
        if (allTiles[i].rev == false) 
        {
            if (allTiles[i].isMine == false) 
            {
                win = false;
                return false;
            }
        }
    }

    
    if (win) 
    {
        sf::Sprite winFace(TextureManager::GetTexture("face_win"));
        winFace.setPosition(GetWindowWidth() / 2 - 16, GetWindowHeight() - 100);
        window.draw(winFace);

        sf::Sprite digit0(TextureManager::GetTexture("digits"));
        digit0.setTextureRect(sf::IntRect(0, 0, 21, 32));

        flags = 50;
        sf::Sprite flag(TextureManager::GetTexture("flag"));
        sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));

        for (int i = 0; i < allMines.size(); i++) 
        {
            hiddenTile.setPosition(allMines[i].x, allMines[i].y);
            window.draw(hiddenTile);

            flag.setPosition(allMines[i].x, allMines[i].y);
            window.draw(flag);
        }

        digit0.setPosition(21, boardHeight * 32);
        window.draw(digit0);

        digit0.setPosition(42, boardHeight * 32);
        window.draw(digit0);

        digit0.setPosition(63, boardHeight * 32);
        window.draw(digit0);


    }

    return win;
}

