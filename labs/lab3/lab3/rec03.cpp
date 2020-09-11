//
//  rec03.cpp
//  lab3
//
//  Created by Nahom Molla on 9/21/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
    struct Square{
        bool visible;
        bool isBomb;
        int bombNeighbors;
        Square(const bool theVisiblity, const bool theStatus, int theNeighbors) :
        visible(theVisiblity), isBomb(theStatus), bombNeighbors(theNeighbors) {}
    };
    
public:
    Minesweeper() {
        createGrid(board);
        checkNeighbors(board);
    }
    
    bool done(){
        bool done = true;
        for (const vector<Square>& row : board){
            for (const Square& someSquare : row){
                if (!someSquare.isBomb && !someSquare.visible){
                    done = false;
                }
            }
        }
        return done;
    }
    
    void display(bool someBool){
        cout << "    0  1  2  3  4  5  6  7  8  9 " << endl; // margins for the columns
        for (size_t row=0; row<board.size(); ++row){
            cout << ' ' << row << ' '; // margins for the rows
            for (size_t column=0; column<board[row].size(); ++column){
                if (!someBool){
                    if (board[row][column].visible){
                        if (board[row][column].bombNeighbors != 0){
                            cout << '|' << board[row][column].bombNeighbors << '|';
                        }
                        else {
                            cout << "| |";
                        }
                    }
                    else {
                        cout << "|▇|";
                    }
                }
                else {
                    if (board[row][column].isBomb){
                        cout << "|¤|";
                    }
                    else {
                        cout << "| |";
                    }
                }
            }
            cout << '\n';
        }
    }
    
    bool play(const int row, const int column){
        if (validCol(column) && validRow(row)){
            //check if current coordinate has already been looked at
            for (const vector<int>& coord : toDoList){
                if (coord[0] == row && coord[1] == column){
                    return false;
                }
            }
            coordinates.clear();
            if (board[row][column].isBomb){
                return false;
            }
            else { //notBomb
                board[row][column].visible = true;
                if (board[row][column].bombNeighbors == 0){
                    coordinates.push_back(row);
                    coordinates.push_back(column);
                    toDoList.push_back(coordinates);
                    play(row-1, column);
                    play(row+1, column);
                    play(row, column-1);
                    play(row, column+1);
                    play(row-1, column-1);
                    play(row-1, column+1);
                    play(row+1, column-1);
                    play(row+1, column+1);
                }
                return true;
            }
        }
        else { //if coordinate out of bounds
            return false;
        }
    }
    
    bool validCol(const int column){
        return (column >= 0 && column < COLUMNS);
    }
    
    bool validRow(const int row){
        return  (row >=0 && row < ROWS);
    }
    
    bool isVisible(const int row, const int column){
        return (board[row][column].visible);
    }
    
private:
    vector<vector<Square>> board;
    vector<int> coordinates;
    vector<vector<int>> toDoList;
    const int ROWS = 10;
    const int COLUMNS = 10;
    const int BOMB_PROBABILITY = 10;
    
    // creates a grid with bombs placed randomly
    void createGrid(vector<vector<Square>>& grid){
        srand(time(NULL));
        for (size_t r=0; r<ROWS; ++r){
            vector<Square> currRow;
            for (size_t c=0; c<COLUMNS; ++c){
                Square mySquare(false, false, 0);
                if ((rand() % 100) < BOMB_PROBABILITY){
                    mySquare.isBomb = true;
                }
                currRow.push_back(mySquare);
            }
            grid.push_back(currRow);
        }
    }
    
    // checks neighbors and saves the coordinates which contain Bombs
    void checkNeighbors(vector<vector<Square>>& grid){
        for (size_t r=0; r<grid.size(); ++r){
            for (size_t c=0; c<grid[r].size(); ++c){
                // left Square
                if (c!=0 && grid[r][c-1].isBomb){
                    ++grid[r][c].bombNeighbors;
                }
                // right Square
                if (c + 1 < grid[r].size() && grid[r][c+1].isBomb){
                    ++grid[r][c].bombNeighbors;
                }
                // top Square
                if (r!=0 && grid[r-1][c].isBomb){
                    ++grid[r][c].bombNeighbors;
                }
                // bottom Square
                if (r + 1 < grid.size() && grid[r+1][c].isBomb){
                    ++grid[r][c].bombNeighbors;
                }
                // top-left && top-right Squares
                if (r!=0){
                    if (c!=0 && grid[r-1][c-1].isBomb){
                        ++grid[r][c].bombNeighbors;
                    }
                    if (c + 1 < grid[r-1].size() && grid[r-1][c+1].isBomb){
                        ++grid[r][c].bombNeighbors;                    }
                }
                // bottom-left && bottom-right Squares
                if (r + 1 < grid.size()){
                    if (c!=0 && grid[r+1][c-1].isBomb){
                        ++grid[r][c].bombNeighbors;
                    }
                    if (c + 1 < grid[r+1].size() && grid[r+1][c+1].isBomb){
                        ++grid[r][c].bombNeighbors;
                    }
                }
            }
        }
    }
};


int main(int argc, const char * argv[]) {
    Minesweeper sweeper;
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs
        
        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}
