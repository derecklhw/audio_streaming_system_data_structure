/*
    hashTable.cpp
    Author: M00826933
    Created: 11/04/23
    Updated: 16/04/23
*/

#include <iostream>
#include "hashTable.h"

// Constructor
HashTable::HashTable(size_t size)
    : tableSize(size), table(new TrackNode *[size]()) {}

// Destructor
HashTable::~HashTable()
{
    // Iterate through the table and delete all nodes
    for (size_t i = 0; i < tableSize; ++i)
    {
        TrackNode *currentNode = table[i];
        while (currentNode)
        {
            TrackNode *nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }
    delete[] table;
}

/*
Case insensitive string comparison
@param str1 the first string to compare
@param str2 the second string to compare
@return true if the strings are equal, ignoring case; false otherwise
*/
bool HashTable::caseInsensitiveStringCompare(const std::string &str1, const std::string &str2) const
{
    // If the lengths differ, return false
    if (str1.size() != str2.size())
    {
        return false;
    }

    // Compare characters case insensitively
    for (size_t i = 0; i < str1.size(); ++i)
    {
        if (tolower(static_cast<unsigned char>(str1[i])) != tolower(static_cast<unsigned char>(str2[i])))
        {
            return false;
        }
    }
    return true;
}

/*
Insert track into the hash table
@param track the track to insert into the hash table
*/
void HashTable::insert(const Track &track)
{
    size_t index = hash(track.getArtist());
    TrackNode *newNode = new TrackNode{track, nullptr};
    // If the index is empty, insert the new node
    if (!table[index])
    {
        table[index] = newNode;
    }
    else
    {
        // If the index is not empty, iterate through the linked list and check for duplicates
        TrackNode *currentNode = table[index];
        TrackNode *prevNode = nullptr;
        int lineNumber = 1;
        while (currentNode)
        {
            // Check for duplicates
            if (caseInsensitiveStringCompare(currentNode->track.getTitle(), track.getTitle()) &&
                caseInsensitiveStringCompare(currentNode->track.getArtist(), track.getArtist()))
            {
                std::cerr << "Error: Duplicate track found on line " << currentNode->track.getLineNumber() << ": Track \"" << track.getTitle() << "\" by artist \"" << track.getArtist() << ". Skipping track." << std::endl;
                delete newNode;
                return;
            }
            prevNode = currentNode;
            currentNode = currentNode->next;
            lineNumber++;
        }
        // Insert new node at the end of the list
        prevNode->next = newNode;
    }
}

/*
Remove track from the hash table
@param title the title of the track to remove
@param artist the artist of the track to remove
@return true if the track was removed, false otherwise
*/
bool HashTable::remove(const std::string &title, const std::string &artist)
{
    size_t index = hash(artist);
    TrackNode *currentNode = table[index];
    TrackNode *prevNode = nullptr;

    // Iterate through the linked list and search for the track
    while (currentNode)
    {
        // If the track is found, remove it
        if (caseInsensitiveStringCompare(currentNode->track.getTitle(), title) &&
            caseInsensitiveStringCompare(currentNode->track.getArtist(), artist))
        {
            // Update the previous node's next pointer
            if (prevNode)
            {
                prevNode->next = currentNode->next;
            }
            else
            {
                table[index] = currentNode->next;
            }
            delete currentNode;
            return true;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    return false;
}

/*
Search for tracks by artist
@param artist the artist name to search for
@return a vector of Track objects that match the given artist
*/
std::vector<Track> HashTable::search(const std::string &artist) const
{
    size_t index = hash(artist);
    std::vector<Track> result;
    TrackNode *currentNode = table[index];
    // Iterate through the linked list and add matching tracks to the result vector
    while (currentNode)
    {
        if (caseInsensitiveStringCompare(currentNode->track.getArtist(), artist))
        {
            result.push_back(currentNode->track);
        }
        currentNode = currentNode->next;
    }
    return result;
}

/*
Hash function for artist string
@param key the artist string to hash
@return the hash value for the given artist string
*/
size_t HashTable::hash(const std::string &key) const
{
    // Convert the key to lowercase
    std::string keyLowerCase = key;
    for (char &c : keyLowerCase)
    {
        c = tolower(static_cast<unsigned char>(c));
    }

    // Implement the djb2 hash function
    size_t hashValue = 5381;
    for (char c : keyLowerCase)
    {
        hashValue = ((hashValue << 5) + hashValue) + c; // hash * 33 + c
    }

    return hashValue % tableSize;
}

/*
Get all tracks in the hash table
@return a vector of all Track objects in the hash table
*/
std::vector<Track> HashTable::getAllTracks() const
{
    std::vector<Track> allTracks;

    // Iterate through the table and collect all tracks
    for (size_t i = 0; i < tableSize; ++i)
    {
        TrackNode *currentNode = table[i];
        while (currentNode)
        {
            allTracks.push_back(currentNode->track);
            currentNode = currentNode->next;
        }
    }

    return allTracks;
}