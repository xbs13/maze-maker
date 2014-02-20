//
//  menufunctions.h
//  Maze Maker
//
//  Created by Michael Pérez on 12/8/13.
//  Copyright (c) 2013 Michael Pérez. All rights reserved.
//

#ifndef Maze_Maker_menufunctions_h
#define Maze_Maker_menufunctions_h
#include "GraphicStruct.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void Howto();
void Menu();
void Header();
void About();
bool LoadMap(char grid[SIZE][SIZE], struct graphic &mapinfo);
void SaveMap(char grid[SIZE][SIZE]);

void Menu()
{
    cout <<"\nN - New Game \tH - How-to Pay"
    << "\nL - Load Game \tM - Map Maker \nA - About\tR - Resume"
    <<"\nQ - Quit" << endl;
}
void Header()
{
    cout << "\n\nNigh Night Gaming presents\n\n\tMaze Maker" <<endl;
}

void About()
{
    cout <<"\nMaze Maker is the first project to come out of Nigh Night Gaming"
    << "\nIt was written in by Michael Perez who also found the company in November 2013."
    << "\nMichael Perez is a Computational Linguistics and AI Development major"
    << "\nat Macualay Honors College at Brooklyn College. He hopes to utilize"
    << "\ncomputer intelligence and human interaction to create a know relationship"
    << "\nwith technology that promotes knowledge rather than wizardery." << endl;
}
void Howto()
{
	char read;
	cout <<"\nObjective:\n"
    <<"Maze Maker is a simple puzzle game that requires the voluptious character '8'"
    << " to escape the constrictions of the grid by reaching 'O.'"
    <<"\nControls:\n"
    <<"a - Left\ts - Down\nd - Right\tw - Up\nq - Quit"<<endl;
	cout << "Enter any key to continue\n";
	cin >> read;
}


bool LoadMap(char grid[SIZE][SIZE], struct graphic &mapinfo)
{
	cout << "\nPlease enter the map pack you would like to load:\n";
	cin >> mapinfo.folder;
	/*use of datatype stringstream allows me use the user inputed data as the folder for
	 * presently printing the title screen for that Map Pack
	 * in the future it will provide the user with the ability to type
	 * in the Number of map he wants or even perhaps select it.
	 */
	stringstream ss;
	ss << "/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/UserMaps/" <<mapinfo.folder<< "/title.txt";
	ifstream infile(ss.str().c_str());
	if (!infile.is_open())
	{
		cout << "\n\nTitle File failed to open! Oh no!\nPerhaps it doesn't exist\nAre you trying to trick me?" << endl << endl;
	}
	for (int y = 0; y <= SIZE; y++)
	{
		for (int x = 0; x <= SIZE; x++)
		{
			infile >> grid[x][y];
		}
	}
	infile.close();
	return true;
}

void SaveMap(char grid[SIZE][SIZE])
{
	string name;
	stringstream file;
	cout << "\nWhat would you like to name the file? (Only letter and numbers)\n";
	cin >> name;
    file << "/Users/admin/GoogleDrive/NighNightGaming/Mazegame/inputmaps/UserMaps/HomebrewMaps/" << name << ".txt";
	ofstream outfile(file.str().c_str());
	for (int y = 0; y <= SIZE; y++)
	{
		for (int x = 0; x <= SIZE; x++)
		{
			outfile << grid[x][y];
		}
	}
	cout << endl;
	outfile.close();
}


#endif
