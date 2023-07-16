/*
main.cpp
Author: M00826933
Created: 11/04/23
Updated: 16/04/23
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "main.h"
#include "track.h"
#include "hashTable.h"

/*
Check the number of arguments passed to the program
@param programName the name of the program
@param argc the number of command-line arguments
*/
void checkNumberOfArguments(std::string programName, int argc)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << programName << " <filename>" << std::endl;
        exit(1);
    }
}

/*
Load tracks from a file
@param fileName the name of the file containing the tracks
@return a vector of Track objects loaded from the file
*/
std::vector<Track> loadTracksFromFile(const std::string &fileName)
{
    std::vector<Track> tracks;
    std::ifstream inputFile(fileName);

    // Open input file
    if (!inputFile)
    {
        std::cerr << "Error: could not open file " << fileName << std::endl;
        return tracks;
    }

    // Check if file is empty
    if (inputFile.peek() == std::ifstream::traits_type::eof())
    {
        std::cerr << "Error: file " << fileName << " is empty" << std::endl;
        inputFile.close();
        return tracks;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(inputFile, line))
    {
        lineNumber++;
        std::istringstream lineStream(line);
        std::string title, artist, durationStr;
        std::getline(lineStream, title, '\t');
        std::getline(lineStream, artist, '\t');
        std::getline(lineStream, durationStr, '\t');

        try
        {
            int duration = std::stoi(durationStr);
            tracks.emplace_back(lineNumber, title, artist, duration);
        }
        catch (const std::invalid_argument &ex)
        {
            std::cerr << "Warning: Invalid duration value on line " << lineNumber << ": Track \"" << title << "\" by artist \"" << artist << ". Skipping track." << std::endl;
            continue;
        }
    }

    inputFile.close();
    return tracks;
}

// Print a message to prompt the user to press any key to continue
void drawPressAnyKeys()
{
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();
}

// Clean the terminal screen
void cleanScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

/*
Display the main menu and handle user inputs
@param hashTable the HashTable object storing the tracks
*/
void mainMenu(HashTable &hashTable)
{
    std::string choice;
    do
    {
        std::cout << "---------- MAIN MENU ----------\n"
                  << "[1] Add tracks from a file\n"
                  << "[2] Save tracks in the library to a file\n"
                  << "[3] Search for tracks by artist\n"
                  << "[4] Remove a track\n"
                  << "[5] Exit\n"
                  << "\n"
                  << "Enter your choice: ";

        std::cin >> choice;
        std::cin.ignore();

        if (choice == "1")
        {
            addTracksFromFile(hashTable);

            drawPressAnyKeys();
            cleanScreen();
        }
        else if (choice == "2")
        {
            // Generate file name with current timestamp
            std::time_t now = std::time(nullptr);
            std::stringstream ss;
            ss << "tracks_" << std::put_time(std::localtime(&now), "%Y-%m-%d_%H-%M-%S") << ".txt";
            std::string fileName = ss.str();

            // Save tracks to file
            std::cout << "Saving tracks to file: " << fileName << std::endl;
            saveTracksToFile(hashTable, fileName);
            std::cout << std::endl;
        }
        else if (choice == "3")
        {
            std::string artistToSearch = getArtistToSearch();
            searchTracksByArtist(hashTable, artistToSearch);
        }
        else if (choice == "4")
        {
            std::pair<std::string, std::string> trackToRemove = getTrackToRemove();
            removeTrack(hashTable, trackToRemove.first, trackToRemove.second);
        }
        else if (choice == "5")
        {
            std::cout << "Exiting..." << std::endl;
            exit(0);
        }
        else
        {
            std::cout << std::endl
                      << "Invalid choice. Please try again." << std::endl
                      << std::endl;
        }
    } while (choice != "5");
}

/*
Add tracks from a file to the hash table
@param hashTable the HashTable object storing the tracks
@return true if successful, false otherwise
*/
bool addTracksFromFile(HashTable &hashTable)
{
    std::string fileName;
    std::cout << std::endl
              << "Enter the file name containing new tracks: ";
    std::getline(std::cin, fileName);

    std::vector<Track> newTracks = loadTracksFromFile(fileName);
    for (const auto &track : newTracks)
    {
        hashTable.insert(track);
    }

    std::cout << std::endl
              << "Successfully added " << newTracks.size() << " tracks from the file.\n"
              << std::endl;
    return 0;
}

/*
Save tracks from the hash table to a file
@param hashTable the HashTable object storing the tracks
@param fileName the name of the file to save the tracks to
@return true if successful, false otherwise
*/
bool saveTracksToFile(const HashTable &hashTable, const std::string &fileName)
{
    // Request user confirmation
    std::string userConfirmation;
    std::cout << std::endl
              << "Are you sure you want to save the tracks to the file " << fileName << "? (y/n): ";
    std::cin >> userConfirmation;
    std::cin.ignore();

    // If the user does not confirm, return without saving
    if (userConfirmation != "y" && userConfirmation != "Y")
    {
        std::cout << "Save operation cancelled." << std::endl;
        return 1;
    }

    std::ofstream outputFile(fileName);

    if (!outputFile)
    {
        std::cerr << "Error: could not open file " << fileName << " for writing" << std::endl;
        return 1;
    }

    std::vector<Track> tracks = hashTable.getAllTracks();

    for (const auto &track : tracks)
    {
        outputFile << track.getTitle() << "\t" << track.getArtist() << "\t" << track.getDuration() << std::endl;
    }

    outputFile.close();
    std::cout << "Successfully saved " << tracks.size() << " tracks to the file " << fileName << "." << std::endl;
    return 0;
}

/*
Get the artist's name to search for their tracks
@return the artist's name
*/
std::string getArtistToSearch()
{
    std::string artistToSearch;
    std::cout << "Enter the artist/band name to search: ";
    std::getline(std::cin, artistToSearch);
    std::cout << std::endl;
    return artistToSearch;
}

/*
Search for tracks by an artist and display the results
@param hashTable the HashTable object storing the tracks
@param artist the artist's name to search for
*/
void searchTracksByArtist(const HashTable &hashTable, const std::string &artist)
{
    std::vector<Track> foundTracks = hashTable.search(artist);

    if (foundTracks.empty())
    {
        std::cerr << "No tracks found for artist \"" << artist << "\".\n";
        return;
    }

    std::cout << "Tracks found for artist " << artist << ":\n\n";

    // Print table header
    std::cout << std::left << std::setw(35) << "Title" << std::setw(20) << "Duration (seconds)"
              << "\n";
    std::cout << std::setfill('-') << std::setw(57) << ""
              << "\n";
    std::cout << std::setfill(' ');

    // Print table rows
    for (const auto &track : foundTracks)
    {
        std::cout << std::left << std::setw(35) << track.getTitle() << std::setw(20) << track.getDuration() << "\n";
    }

    std::cout << "\n";
}

/*
Get the track title and artist name to remove from the hash table
@return a pair containing the track title and artist name
*/
std::pair<std::string, std::string> getTrackToRemove()
{
    std::string trackToRemove, trackArtist;
    std::cout << "Enter the track title: ";
    std::getline(std::cin, trackToRemove);
    std::cout << "Enter the artist/band name: ";
    std::getline(std::cin, trackArtist);
    std::cout << std::endl;
    return std::make_pair(trackToRemove, trackArtist);
}

/*
Remove a track by title and artist from the hash table
@param hashTable the HashTable object storing the tracks
@param title the track title to remove
@param artist the artist name of the track to remove
*/
void removeTrack(HashTable &hashTable, const std::string &title, const std::string &artist)
{
    bool removed = hashTable.remove(title, artist);
    if (removed)
    {
        std::cout << "Track \"" << title << "\" by " << artist << " has been successfully removed.\n"
                  << std::endl;
    }
    else
    {
        std::cout << "Track \"" << title << "\" by " << artist << " could not be found and therefore not removed.\n"
                  << std::endl;
    }
}

/*
Main function of the program
@param argc the number of command-line arguments
@param argv array of command-line argument strings
@return 0 upon successful completion
*/
int main(int argc, char *argv[])
{
    std::cout << "New Audio Streaming service for linux using c++" << std::endl
              << "Copyright (c) 2023, M00826933" << std::endl
              << std::endl;

    // Check the number of command-line arguments and exit the program with an error message if incorrect
    checkNumberOfArguments(argv[0], argc);

    // Load tracks from the specified file
    std::string fileName = argv[1];
    std::vector<Track> tracks = loadTracksFromFile(fileName);

    // If the file is not found or is empty, exit the program
    if (tracks.size() == 0)
    {
        std::cerr << "Exiting due to empty or invalid file." << std::endl;
        return 1;
    }

    // Create a hash table and insert the loaded tracks
    HashTable hashTable(tracks.size());
    for (const auto &track : tracks)
    {
        hashTable.insert(track);
    }
    std::cout << std::endl;

    // Wait for user input before clearing the screen and displaying the main menu
    drawPressAnyKeys();
    cleanScreen();

    // Run the main menu loop
    mainMenu(hashTable);

    return 0;
}
