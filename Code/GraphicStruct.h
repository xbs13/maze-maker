//
//  GraphicStruct.h
//  Maze Maker
//
//  Created by Michael Pérez on 12/8/13.
//  Copyright (c) 2013 Michael Pérez. All rights reserved.
//

#ifndef Maze_Maker_GraphicStruct_h
#define Maze_Maker_GraphicStruct_h

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
//to change size change this (remember, to add 2 for the scale.)
const int SIZE = 13;

//initializing game variables
struct graphic
{
    bool newmappack;
	bool pass;
	bool resume;
	bool quit;
	bool asked;
    bool dev;
    bool havekey;
    int currentmap;
    int map;
    int start_x;
    int start_y;
    int exit_x;
    int exit_y;
    int playloc_x;
    int playloc_y;
    int box_x;
    int box_y;
    string folder;
    char start_mark;
    char exit_mark;
    char player;
    char wall;
    char empty;
    char temp;
    char temp2;
    char hole;
    char box;
    char key;
    char door;
    
} mapinfo;



#endif
