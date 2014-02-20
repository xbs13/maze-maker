//
//  Initial_Map.h
//  Maze Maker
//
//  Created by Michael Pérez on 12/8/13.
//  Copyright (c) 2013 Michael Pérez. All rights reserved.
//

#ifndef Maze_Maker_Initial_Map_h
#define Maze_Maker_Initial_Map_h

#include "GraphicStruct.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


void ReadIn(char grid[SIZE][SIZE], struct graphic &mapinfo);
void MakeObs(char grid[SIZE][SIZE], struct graphic &mapinfo);
void PrintMap(char grid[SIZE][SIZE]);
void MakeMap(char grid[SIZE][SIZE]);
//void Test(char grid[SIZE][SIZE]);

/* Function: void ReadIn()
 * Input: Int in coordinates, int out Coordinates, char grid array, char staring point, char ending point
 * Output: Prompts for coordinate input, error messages.
 * Process: Reads in the coordinates for in/out points and marks them on the grid
 */
void ReadIn(char grid[SIZE][SIZE], struct graphic &mapinfo)
{
    // Removed sx & sy & ex & ey
    //reading in coordinates
    cout << "\nWhere're you, my captain? (x y) ";
    cin >> mapinfo.start_x >> mapinfo.start_y;
    while((mapinfo.start_x > SIZE && mapinfo.start_y > SIZE) || grid[mapinfo.exit_x][mapinfo.exit_y] == mapinfo.wall)
    {
    	cout << "\nYou can't be there, captain! \n\nWhere are you?? ";
    	cin >> mapinfo.start_x >> mapinfo.start_y;
    }
    cout<< "Where're we headed to, captain oh captain? (x y) ";
    cin >> mapinfo.exit_x >> mapinfo.exit_y;
    while((mapinfo.exit_x > SIZE && mapinfo.exit_y > SIZE) || grid[mapinfo.exit_x][mapinfo.exit_y] == mapinfo.wall)
    {
    	// adding one to put within boundaries
   		cout << "\nCaptain, sorry but that's beyond this world... \nWhere else could we go? ";
    	cin >> mapinfo.exit_x >> mapinfo.exit_y;
    }
    //Marking the start/end points on the grid
    grid[mapinfo.start_x+1][mapinfo.start_y+1] = mapinfo.start_mark;
    grid[mapinfo.exit_x+1][mapinfo.exit_y+1] = mapinfo.exit_mark;
    
   	
}

/* Function: void MakeObs()
 * Input: Int obstical coordinates, char grid array
 * Output: Prompts for coordinate input
 * Process: Reads in the coordinates for wall and marks it on the grid
 */
void MakeObs(char grid[SIZE][SIZE], struct graphic &mapinfo)
{
    //allows users to make walls
    int wall_x, wall_y, hole_x, hole_y, box_x, box_y, key_x, key_y;
    do{
        cout << "\nWhere do you want put walls? (x y) (Finish with 0 0)\n";
        cin >> wall_x >> wall_y;
        if(wall_x == 0 || wall_y == 0)
            continue;
        while(grid[wall_x+1][wall_y+1] == mapinfo.start_mark ||  grid[wall_x+1][wall_y+1] == mapinfo.exit_mark)
        {
            cout << "Sorry, you can't put a wall there.\n Please renter: ";
            cin >> wall_x >> wall_y;
        }
        grid[wall_x+1][wall_y+1] = mapinfo.wall;
        PrintMap(grid);
    }while(wall_x != 0 || wall_y != 0);
    do{
        cout << "\nWhere do you want put holes? (x y) (Finish with 0 0)\n";
        cin >> hole_x >> hole_y;
        if(hole_x == 0 || hole_y == 0)
            continue;
        while(grid[hole_x+1][hole_y+1] == mapinfo.start_mark ||  grid[hole_x+1][hole_y+1] == mapinfo.exit_mark)
        {
            cout << "Sorry, you can't put a hole there.\n Please renter: ";
            cin >> hole_x >> hole_y;
        }
        grid[hole_x+1][hole_y+1] = mapinfo.hole;
        PrintMap(grid);
    }while(hole_x != 0 || hole_y != 0);
    do{
        cout << "\nWhere do you want put boxes? (x y) (Finish with 0 0)\n";
        cin >> box_x >> box_y;
        if(box_x == 0 || box_y == 0)
            break;
        while(grid[box_x+1][box_y+1] == mapinfo.start_mark ||  grid[box_x+1][box_y+1] == mapinfo.exit_mark)
        {
            cout << "Sorry, you can't put a box there.\n Please renter: ";
            cin >> box_x >> box_y;
        }
        grid[box_x+1][box_y+1] = mapinfo.box;
        PrintMap(grid);
    }while(box_x != 0 || box_y != 0);
    do{
        cout << "\nWhere do you want put keys? (x y) (Finish with 0 0)\n";
        cin >> key_x >> key_y;
        if(key_x == 0 || key_y == 0)
            break;
        while(grid[key_x+1][key_y+1] == mapinfo.start_mark ||  grid[key_x+1][key_y+1] == mapinfo.exit_mark)
        {
            cout << "Sorry, you can't put a key there.\n Please renter: ";
            cin >> key_x >> key_y;
        }
        grid[key_x+1][key_y+1] = mapinfo.key;
        PrintMap(grid);
    }while(key_x != 0 || key_y != 0);
}

/* Function: void PrintMap()
 * Input: char grid array
 * Output: prints the map
 * Process: Iterates through the array Ys, then iterates through that column's rows, printing.
 */
void PrintMap(char grid[SIZE][SIZE])
{
    for (int y= 0; y<=SIZE; y++)
    {
        for(int x=0; x<=SIZE; x++)
        {
            cout << grid[x][y] << ' ';
        }
        cout << endl;
    }
}

/* Function: void  MakeMap()
 * Input: char grid array
 * Output: void
 * Process: Iterates through the array Ys, then iterates through that column's rows,
 * filling it with it's appropriate starting position
 */
void MakeMap(char grid[SIZE][SIZE])
{
	cout << endl;
    //setting up the borders
    // unary plus before increment variable is like do x, then do x while.
    // unary plus after increment variable is like do x while.
    for (int y = 0; y <=SIZE; ++y)
    {
        for(int x = 0; x <= SIZE; ++x)  // C - Could be one big bool, but now have edge control.
        {
            if((y == 1 && (x > 0 && x < SIZE)))  // Top Border.
            {
                grid[x][y] = 'X';
            }
            else if((y == SIZE -1 && (x > 0 && x < SIZE)))  // Bottom Border.
            {
                grid[x][y] = 'X';
            }
            else if((x == 1 && (y > 0 &&  y < SIZE)))  // Left Border.
            {
                grid[x][y] = 'X';
            }
            else if((x == SIZE - 1 && (y > 0 && y < SIZE)))  // Right Border.
            {
                grid[x][y] = 'X';
            }
            else
                grid[x][y] = '_';
        }
    }
    
}

/*
 void Test(char grid[SIZE][SIZE])
 {
 int tx, ty\\\\\\\
 ]=
 
 cout<< "Enter your test marker: ";
 cin >> tx >> ty;
 // adding one to put within boundaries
 grid[tx][ty] = 'M';
 PrintMap(grid);
 }
 */


#endif
