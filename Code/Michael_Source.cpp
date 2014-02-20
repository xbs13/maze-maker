//
//  Michael_Source.cpp
//  Maze Maker
//
//  Created by Michael Pérez on 12/8/13.
//  Copyright (c) 2013 Michael Pérez. All rights reserved.
//
#include "GraphicStruct.h"
#include "menufunctions.h"
#include "GameFunctions.h"
#include "Initial_Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    //initializing menu switch
    char opt;
    //initializing variables fort the 2D array grid
    char grid[SIZE][SIZE];
    bool load = false;
    mapinfo.start_mark = 'S';
    mapinfo.exit_mark = 'O';
    mapinfo.wall = 'X';
    mapinfo.player = '8';
	mapinfo.empty = '_';
	mapinfo.hole = 'H';
    mapinfo.box = 'B';
    mapinfo.key = 'K';
    mapinfo.door = 'D';
    
    mapinfo.newmappack = true;
    mapinfo.currentmap = 1;
    mapinfo.dev = false;
    mapinfo.asked = false;
    
    //Entering main game loop
    Header();
    Howto();
    //printing title screen;
    ifstream infile("/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/Title.txt");
    for (int y = 0; y <= SIZE; y++)
	{
		for (int x = 0; x <= SIZE; x++)
			infile >> grid[x][y];
    }
    infile.close();
    PrintMap(grid);
    bool not_done = true;
    
    while(not_done)
    {
    	//Entering the Menu
 	  	Menu();
  	  	cin >> opt;
  	  	//Switch Operaton
  	  	switch(opt)
  	  	{
            case 'd':
            case 'D':
                mapinfo.dev = true;
                cout << "\nYou are now in dev mode\n";
                break;
  	  		case 'r':
  	  		case 'R':
  	  			mapinfo.resume = true;
        		if(!load)
        			mapinfo.folder = "BasicMapPack";
            	cout << "\nThe game is still under development, so exploration is off-limits!\n";
            	NewGame(grid, mapinfo);
            	break;
  	  		case 'h':
  	  		case 'H':
  	  			Howto();
  	  			break;
        	case 'n':
        	case 'N':
        		mapinfo.resume = false;
        		if(!load)
        			mapinfo.folder = "BasicMapPack";
            	cout << "\nThe game is still under development, so exploration is off-limits!\n";
            	NewGame(grid, mapinfo);
            	break;
        	case 'l':
        	case 'L':
            	load = LoadMap(grid, mapinfo);
                PrintMap(grid);
            	break;
                /*
                 case 't':
                 case 'T':
                 Test(grid);
                 break;
                 */
        	case 'a':
        	case 'A':
            	About();
            	PrintMap(grid);
            	break;
        	case 'q':
        	case 'Q':
           		not_done = false;
            	break;
        	case 'M':
        	case 'm':
                mapinfo.resume = false;
                MakeMap(grid);
        		ReadIn(grid, mapinfo);
        		PrintMap(grid);
            	MakeObs(grid, mapinfo);
                SaveMap(grid);
                PrintMap(grid);
                break;
        	default:
            	cout << "Sorry, invalid choice. Retry.";
            	break;
    	}
    }
    cout << "\n\nThank you for playing this game, cheers."<<endl<<endl;
    return 0;
}