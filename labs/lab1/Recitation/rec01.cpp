//
//  rec01.cpp
//  Recitation
//
//  Created by Nahom Molla on 9/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]){
    // opening file
    ifstream life("life.txt");
    if(!life){
        cerr << "failed to open life.txt" << endl;
        exit(1);
    }
    
    // putting rows into the grid
    vector<string> grid;
    string rows;
    
    while(getline(life, rows)){
        grid.push_back(rows);
    }
    // closing life.txt && creating new output file
    life.close();
    ofstream output("Generations.txt");
    
    // printing Generation 0
    output << "Initial Generation" << endl;
    for(size_t i=0; i<grid.size(); ++i){
        output << grid[i] << endl;
    }
    output << "=========================\n";
    
    // process...
    int neighbors;
    vector<string> clone;
    
    // creating generations
    for(size_t i=0; i<10; ++i){
        clone = grid;
        for(int j=0; j<grid.size(); ++j){
            for(int k=0; k<grid[j].size(); ++k){
                neighbors = 0;
                // check left
                if(k != 0 && grid[j][k-1] == '*'){
                    ++ neighbors;
                }
                // check right
                if(k + 1 < grid[j].size() && grid[j][k+1] == '*'){
                    ++ neighbors;
                }
                // check top
                if(j != 0 && grid[j-1][k] == '*'){
                    ++ neighbors;
                }
                // check bottom
                if(j + 1 < grid.size() && grid[j+1][k] == '*'){
                    ++ neighbors;
                }
                // check top-left && top-right
                if(j != 0){
                    // top-left
                    if(k != 0 && grid[j-1][k-1] == '*'){
                        ++ neighbors;
                    }
                    // top-right
                    if(k + 1 < grid[j-1].size() && grid[j-1][k+1] == '*'){
                        ++ neighbors;
                    }
                }
                // check bottom-left && bottom-right
                if(j+1 < grid.size()){
                    // bottom-left
                    if(k != 0 && grid[j+1][k-1] == '*'){
                        ++ neighbors;
                    }
                    // bottom-right
                    if(k + 1 < grid[j+1].size() && grid[j+1][k+1] == '*'){
                        ++ neighbors;
                    }
                }
                if(neighbors < 2 || neighbors > 3){
                    clone[j][k] = '-';
                }
                if(neighbors == 3){
                    clone[j][k] = '*';
                }
            }
        }
        grid = clone;
        // printing generations 1-10
        output << "Generation: ";
        output << i + 1 <<  endl;
        for (size_t t=0; t<grid.size(); ++t){
            output << grid[t] << endl;
        }
        output << "=========================" << endl;
    }
        return 0;
}



















