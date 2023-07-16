#ifndef __HASHTABLE_H_
#define __HASHTABLE_H_

/*
    hashtable.h
    Author: M00826933
    Created: 11/04/23
    Updated:
*/

#include <string>
#include <vector>

#include "track.h"

// TrackNode struct is used to store individual tracks in the HashTable
struct TrackNode
{
    Track track;
    TrackNode *next;
};

// HashTable class definition
class HashTable
{
private:
    // Member datas
    size_t tableSize;
    TrackNode **table; // Pointer to an array of pointers to linked list nodes (TrackNode)
    // Method to compute the hash value for a given key
    size_t hash(const std::string &key) const;

public:
    // Constructor and destructor
    HashTable(size_t size);
    ~HashTable();

    /*
    Insert track into the hash table
    @param track the track to insert into the hash table
    */
    void insert(const Track &track);

    /*
   Remove track from the hash table
   @param title the title of the track to remove
   @param artist the artist of the track to remove
   @return true if the track was removed, false otherwise
   */
    bool remove(const std::string &title, const std::string &artist);

    /*
  Search for tracks by artist
  @param artist the artist name to search for
  @return a vector of Track objects that match the given artist
  */
    std::vector<Track> search(const std::string &artist) const;

    /*
   Case insensitive string comparison
   @param str1 the first string to compare
   @param str2 the second string to compare
   @return true if the strings are equal, ignoring case; false otherwise
   */
    bool caseInsensitiveStringCompare(const std::string &str1, const std::string &str2) const;

    /*
    Get all tracks in the hash table
    @return a vector of all Track objects in the hash table
    */
    std::vector<Track> getAllTracks() const;
};

#endif
