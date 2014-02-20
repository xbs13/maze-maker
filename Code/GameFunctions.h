//
//  GameFunctions.h
//  Maze Maker
//
//  Created by Michael Pérez on 12/8/13.
//  Copyright (c) 2013 Michael Pérez. All rights reserved.
//

#ifndef Maze_Maker_GameFunctions_h
#define Maze_Maker_GameFunctions_h

#include "GraphicStruct.h"
#include "Initial_Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

bool ReadMap(char grid[SIZE][SIZE], struct graphic &mapinfo)
{
	bool congrats;
	int levelnum = 0;
	stringstream path;
	stringstream info;
	
	info <<"/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/UserMaps/"
    << mapinfo.folder << "/info.txt";
	ifstream max(info.str().c_str());
	max >> levelnum;
    max.close();
	if((mapinfo.resume== true && mapinfo.asked == false) || mapinfo.dev == true)
	{
		mapinfo.asked = true;
		cout << endl << "What map would you like to play? ";
		cin >> mapinfo.map;
        if(mapinfo.dev == true)
        {
            path << "/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/UserMaps/"
                << mapinfo.folder << "/inputmap" << mapinfo.map << ".txt";
        }
        else
        {
            while(mapinfo.map > mapinfo.currentmap)
            {
                cout << "\nSorry you haven't unlocked said map, yet captain!\nPlease Reenter: ";
                cin >> mapinfo.map;
            }
            if(mapinfo.map == 0)
            {
                path << "/Users/admin/GoogleDrive/MNighNightGaming/Mazegame/inputmaps/UserMaps/"
                << mapinfo.folder << "/title.txt";
            }
            else
                path << "/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/UserMaps/"
                << mapinfo.folder << "/inputmap" << mapinfo.map << ".txt";
        }
	}
	else if(mapinfo.currentmap == levelnum)
	{
		path << "/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/UserMaps/"
        << mapinfo.folder << "/fin.txt";
		congrats = true;
	}
	else
	{
		path << "/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/UserMaps/"
        << mapinfo.folder << "/inputmap" << mapinfo.currentmap << ".txt";
	}
	
	//reading in the exact map
	ifstream infile(path.str().c_str());
	for (int y = 0; y <= SIZE; y++)
	{
		for (int x = 0; x <= SIZE; x++)
		{
			infile >> grid[x][y];
			if(grid[x][y] == mapinfo.start_mark)
			{
				mapinfo.start_x = x;
				mapinfo.start_y = y;
				mapinfo.playloc_x = x;
				mapinfo.playloc_y = y;
			}
			else if(grid[x][y] == mapinfo.exit_mark)
			{
				mapinfo.exit_x = x;
				mapinfo.exit_y = y;
			}
		}
	}
	cout << endl;
	infile.close();
	if(congrats == true)
	{
		return true;
	}
	else
		return false;
}

bool Game(char grid[SIZE][SIZE], struct graphic &mapinfo)
{
	char input;
	bool done =false;
	char y;
	
	do {
    	PrintMap(grid);
    	cin >> input;
    	switch(input)
    	{
            case 'a':
                
                if(grid[mapinfo.playloc_x-1][mapinfo.playloc_y] != mapinfo.wall && grid[mapinfo.playloc_x-1][mapinfo.playloc_y] != mapinfo.door)
                {
                    if(grid[mapinfo.playloc_x-1][mapinfo.playloc_y] == mapinfo.box && (grid[mapinfo.playloc_x-2][mapinfo.playloc_y] == mapinfo.wall || grid[mapinfo.playloc_x-2][mapinfo.playloc_y] == mapinfo.exit_mark || grid[mapinfo.playloc_x-2][mapinfo.playloc_y] == mapinfo.box || grid[mapinfo.playloc_x-2][mapinfo.playloc_y] == mapinfo.door))
                        continue;
                    else
                    {
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.temp;
                        mapinfo.playloc_x -=1;
                        mapinfo.temp = grid[mapinfo.playloc_x][mapinfo.playloc_y];
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.player;
                    }
                }
                else if(grid[mapinfo.playloc_x-1][mapinfo.playloc_y] == mapinfo.door)
                {
                    char opt;
                    if(!mapinfo.havekey)
                    {
                        cout << "\nYou don't have the key!!\nPress any key to continue: "<< endl;
                        cin >> opt;
                    }
                    else
                        grid[mapinfo.playloc_x-1][mapinfo.playloc_y] = mapinfo.empty;
                }
                if(mapinfo.temp == mapinfo.box)
                {
                    mapinfo.box_x = mapinfo.playloc_x;
                    mapinfo.box_y = mapinfo.playloc_y;
                    if(grid[mapinfo.box_x-1][mapinfo.box_y] != mapinfo.wall && grid[mapinfo.box_x+1][mapinfo.box_y] != mapinfo.exit_mark && grid[mapinfo.playloc_x-1][mapinfo.playloc_y] != mapinfo.door)
                    {
                        mapinfo.box_x -=1;
                        mapinfo.temp = grid[mapinfo.box_x][mapinfo.box_y];
                        grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.box;
                        if(mapinfo.temp == mapinfo.hole)
                        {
                            mapinfo.temp = mapinfo.empty;
                            grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.empty;
                        }
                    }
                }
                break;
            case 's':
                if(grid[mapinfo.playloc_x][mapinfo.playloc_y+1] != mapinfo.wall&& grid[mapinfo.playloc_x][mapinfo.playloc_y+1] != mapinfo.door)
                {
                    if(grid[mapinfo.playloc_x][mapinfo.playloc_y+1] == mapinfo.box && (grid[mapinfo.playloc_x][mapinfo.playloc_y+2] == mapinfo.wall || grid[mapinfo.playloc_x][mapinfo.playloc_y+2] == mapinfo.exit_mark || grid[mapinfo.playloc_x][mapinfo.playloc_y+2] == mapinfo.box || grid[mapinfo.playloc_x][mapinfo.playloc_y+2] == mapinfo.door))
                        continue;
                    else
                    {
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.temp;
                        mapinfo.playloc_y +=1;
                        mapinfo.temp = grid[mapinfo.playloc_x][mapinfo.playloc_y];
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.player;
                    }
                }
                else if(grid[mapinfo.playloc_x][mapinfo.playloc_y+1] == mapinfo.door)
                {
                    char opt;
                    if(!mapinfo.havekey)
                    {
                        cout << "\nYou don't have the key!!\nPress any key to continue: "<< endl;
                        cin >> opt;
                    }
                    else
                        grid[mapinfo.playloc_x][mapinfo.playloc_y+1] = mapinfo.empty;
                }
                if(mapinfo.temp == mapinfo.box)
                {
                    mapinfo.box_x = mapinfo.playloc_x;
                    mapinfo.box_y = mapinfo.playloc_y;
                    if(grid[mapinfo.box_x][mapinfo.box_y+1] != mapinfo.wall&& grid[mapinfo.playloc_x][mapinfo.playloc_y+1] != mapinfo.door)
                    {
                        mapinfo.box_y +=1;
                        mapinfo.temp = grid[mapinfo.box_x][mapinfo.box_y];
                        grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.box;
                        if(mapinfo.temp == mapinfo.hole)
                        {
                            mapinfo.temp = mapinfo.empty;
                            grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.empty;
                        }
                        
                    }
                }
                break;
            case 'd':
                if(grid[mapinfo.playloc_x+1][mapinfo.playloc_y] != mapinfo.wall && grid[mapinfo.playloc_x+1][mapinfo.playloc_y] !=  mapinfo.door)
                {
                    if(grid[mapinfo.playloc_x+1][mapinfo.playloc_y] == mapinfo.box && (grid[mapinfo.playloc_x+2][mapinfo.playloc_y] == mapinfo.wall || grid[mapinfo.playloc_x+2][mapinfo.playloc_y] == mapinfo.exit_mark || grid[mapinfo.playloc_x+2][mapinfo.playloc_y] == mapinfo.box || grid[mapinfo.playloc_x+2][mapinfo.playloc_y] == mapinfo.door))
                        continue;
                    else
                    {
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.temp;
                        mapinfo.playloc_x +=1;
                        mapinfo.temp = grid[mapinfo.playloc_x][mapinfo.playloc_y];
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.player;
                    }
                    
                }
                else if(grid[mapinfo.playloc_x+1][mapinfo.playloc_y] == mapinfo.door)
                {
                    char opt;
                    if(!mapinfo.havekey)
                    {
                        cout << "\nYou don't have the key!!\nPress any key to continue: "<< endl;
                        cin >> opt;
                    }
                    else
                        grid[mapinfo.playloc_x+1][mapinfo.playloc_y] = mapinfo.empty;
                }
                if(mapinfo.temp == mapinfo.box)
                {
                    mapinfo.box_x = mapinfo.playloc_x;
                    mapinfo.box_y = mapinfo.playloc_y;
                    if(grid[mapinfo.box_x+1][mapinfo.box_y] != mapinfo.wall && grid[mapinfo.playloc_x+1][mapinfo.playloc_y] !=  mapinfo.door)
                    {
                        mapinfo.box_x +=1;
                        mapinfo.temp = grid[mapinfo.box_x][mapinfo.box_y];
                        grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.box;
                        if(mapinfo.temp == mapinfo.hole)
                        {
                            mapinfo.temp = mapinfo.empty;
                            grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.empty;
                        }
                    }
                }
                break;
            case 'w':
                if(grid[mapinfo.playloc_x][mapinfo.playloc_y-1] != mapinfo.wall && grid[mapinfo.playloc_x][mapinfo.playloc_y-1] !=mapinfo.door)
                {
                    if(grid[mapinfo.playloc_x][mapinfo.playloc_y-1] == mapinfo.box && (grid[mapinfo.playloc_x][mapinfo.playloc_y-2] == mapinfo.wall || grid[mapinfo.playloc_x][mapinfo.playloc_y-2] == mapinfo.exit_mark || grid[mapinfo.playloc_x][mapinfo.playloc_y-2] == mapinfo.box || grid[mapinfo.playloc_x][mapinfo.playloc_y-2] == mapinfo.door))
                        continue;
                    else
                    {
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.temp;
                        mapinfo.playloc_y -=1;
                        mapinfo.temp = grid[mapinfo.playloc_x][mapinfo.playloc_y];
                        grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.player;
                    }
                }
                else if(grid[mapinfo.playloc_x][mapinfo.playloc_y-1] == mapinfo.door)
                {
                    char opt;
                    if(!mapinfo.havekey)
                    {
                        cout << "\nYou don't have the key!!\nPress any key to continue: "<< endl;
                        cin >> opt;
                    }
                    else
                        grid[mapinfo.playloc_x][mapinfo.playloc_y-1] = mapinfo.empty;
                }
                
                if(mapinfo.temp == mapinfo.box)
                {
                    mapinfo.box_x = mapinfo.playloc_x;
                    mapinfo.box_y = mapinfo.playloc_y;
                    if(grid[mapinfo.box_x][mapinfo.box_y-1] != mapinfo.wall && grid[mapinfo.box_x+1][mapinfo.box_y] != mapinfo.exit_mark && grid[mapinfo.playloc_x][mapinfo.playloc_y-1] != mapinfo.door)
                    {
                        mapinfo.box_y -=1;
                        mapinfo.temp = grid[mapinfo.box_x][mapinfo.box_y];
                        grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.box;
                        if(mapinfo.temp == mapinfo.hole)
                        {
                            mapinfo.temp = mapinfo.empty;
                            grid[mapinfo.box_x][mapinfo.box_y] = mapinfo.empty;
                        }
                    }
                }
                break;
            case 'q':
            case 'Q':
                cout << "Are you sure you want to quit? (y/n) ";
                cin >> y;
                if(y == 'y' || y == 'Y')
                {
                    mapinfo.quit = true;
                    break;
                }
                else if(y == 'n' || y == 'N')
                {
                    break;
                }
                else
                {
                    cout << "Not a valid entry! ErRor!" << endl;
                    break;
                }
        }
        if(mapinfo.playloc_x == mapinfo.exit_x && mapinfo.playloc_y == mapinfo.exit_y)
    	{
    		return true;
    	}
        if(mapinfo.temp == mapinfo.key)
        {
            mapinfo.havekey = true;
            mapinfo.temp = mapinfo.empty;
        }
    	else if(mapinfo.quit)
    		return false;
    	else if(mapinfo.temp == mapinfo.hole)
    	{
    		char read;
    		cout << "You fell into a hole and died,\nusing your last moments to contemplate"
            << " never seeing your loved ones again."
            << "....\nLuckily you respawned"<<endl;
    		cout << "Enter any key to continue\n";
    		cin >> read;

    		grid[mapinfo.playloc_x][mapinfo.playloc_y] = mapinfo.temp;
    		mapinfo.temp = grid[mapinfo.start_x][mapinfo.start_y];
			grid[mapinfo.start_x][mapinfo.start_y] = mapinfo.player;
			mapinfo.playloc_x = mapinfo.start_x;
			mapinfo.playloc_y = mapinfo.start_y;
            
    	}
    }while(!done || mapinfo.quit);
    return false;
}

void NewGame(char grid[SIZE][SIZE], struct graphic &mapinfo)
{
   
	mapinfo.pass=false;
	bool end_game = false;
	mapinfo.quit = false;
    mapinfo.havekey = false;
	
	do{
        end_game = ReadMap(grid, mapinfo);
        
        if(end_game == true)
            break;
        mapinfo.temp = mapinfo.empty;
        grid[mapinfo.start_x][mapinfo.start_y] = mapinfo.player;
        mapinfo.pass = Game(grid, mapinfo);
        
        if(mapinfo.quit == true)
            break;
        else if(mapinfo.pass == true && mapinfo.quit == false)
        {
            mapinfo.currentmap++;
            continue;
        }
        
	}while(!end_game);
	
	if(end_game == true)
		cout << "Congratulations! You have finished the Map Pack!" << endl;
	mapinfo.newmappack = false;
}

#endif
