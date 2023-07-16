#ifndef MAIN_H
#define MAIN_H

/*
main.h
Author: M00826933
Created: 11/04/23
Updated: 16/04/23
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "track.h"
#include "hashTable.h"

/*
Check the number of arguments passed to the program
@param programName the name of the program
@param argc the number of command-line arguments
*/
void checkNumberOfArguments(std::string programName, int argc);

/*
Load tracks from a file
@param fileName the name of the file containing the tracks
@return a vector of Track objects loaded from the file
*/
std::vector<Track> loadTracksFromFile(const std::string &fileName);

// Print a message to prompt the user to press any key to continue
void drawPressAnyKeys();

// Clean the terminal screen
void cleanScreen();

/*
Display the main menu and handle user inputs
@param hashTable the HashTable object storing the tracks
*/
void mainMenu(HashTable &hashTable);

/*
Add tracks from a file to the hash table
@param hashTable the HashTable object storing the tracks
@return true if successful, false otherwise
*/
bool addTracksFromFile(HashTable &hashTable);

/*
Save tracks from the hash table to a file
@param hashTable the HashTable object storing the tracks
@param fileName the name of the file to save the tracks to
@return true if successful, false otherwise
*/
bool saveTracksToFile(const HashTable &hashTable, const std::string &fileName);

/*
Get the artist's name to search for their tracks
@return the artist's name
*/
std::string getArtistToSearch();

/*
Search for tracks by an artist and display the results
@param hashTable the HashTable object storing the tracks
@param artist the artist's name to search for
*/
void searchTracksByArtist(const HashTable &hashTable, const std::string &artist);

/*
Get the track title and artist name to remove from the hash table
@return a pair containing the track title and artist name
*/
std::pair<std::string, std::string> getTrackToRemove();


/*
Remove a track by title and artist from the hash table
@param hashTable the HashTable object storing the tracks
@param title the track title to remove
@param artist the artist name of the track to remove
*/
void removeTrack(HashTable &hashTable, const std::string &title, const std::string &artist);

#endif