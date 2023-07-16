/*
    testing.cpp
    Author: M00826933
    Created: 16/04/23
    Updated:
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Include your project header files here
#include "track.h"
#include "hashTable.h"
#include "main.h"

TEST_CASE("Track and HashTable class functionality", "[Track][HashTable]")
{
    // Test Track class constructor and getters
    Track track(1, "Title", "Artist", 120);
    REQUIRE(track.getLineNumber() == 1);
    REQUIRE(track.getTitle() == "Title");
    REQUIRE(track.getArtist() == "Artist");
    REQUIRE(track.getDuration() == 120);

    // Test HashTable class constructor, insert, and search
    HashTable hashTable(10);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 200);

    // Test insert and search
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);

    std::vector<Track> tracksArtist1 = hashTable.search("Artist1");
    REQUIRE(tracksArtist1.size() == 2);

    // Test remove
    bool removed = hashTable.remove("Title1", "Artist1");
    REQUIRE(removed);

    // Test getAllTracks
    std::vector<Track> allTracks = hashTable.getAllTracks();
    REQUIRE(allTracks.size() == 2);
}

TEST_CASE("Track class: Test getters")
{
    Track track(1, "TrackTitle", "TrackArtist", 180);

    REQUIRE(track.getLineNumber() == 1);
    REQUIRE(track.getTitle() == "TrackTitle");
    REQUIRE(track.getArtist() == "TrackArtist");
    REQUIRE(track.getDuration() == 180);
}

TEST_CASE("HashTable class: Test Insert and Search")
{
    HashTable hashTable(10);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);

    // Search by artist name
    std::vector<Track> foundTracks = hashTable.search("Artist1");
    REQUIRE(foundTracks.size() == 2);
    REQUIRE(foundTracks[0].getTitle() == "Title1");
    REQUIRE(foundTracks[1].getTitle() == "Title3");
}

TEST_CASE("HashTable class: Test Remove")
{
    HashTable hashTable(10);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);

    // Remove a track
    REQUIRE(hashTable.remove("Title2", "Artist2") == true);

    // Ensure the track is removed
    std::vector<Track> foundTracks = hashTable.search("Artist2");
    REQUIRE(foundTracks.size() == 0);
}

TEST_CASE("HashTable class: Test Insert with collision")
{
    HashTable hashTable(3);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);

    // Search by artist name
    std::vector<Track> foundTracks = hashTable.search("Artist1");
    REQUIRE(foundTracks.size() == 2);
    REQUIRE(foundTracks[0].getTitle() == "Title1");
    REQUIRE(foundTracks[1].getTitle() == "Title3");
}

TEST_CASE("HashTable class: Test Remove non-existent track")
{
    HashTable hashTable(10);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);

    // Attempt to remove a non-existent track
    REQUIRE(hashTable.remove("NonExistentTitle", "NonExistentArtist") == false);
}

TEST_CASE("HashTable class: Test Resize")
{
    HashTable hashTable(2); // Starting with a small capacity
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);
    Track track4(4, "Title4", "Artist3", 300);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);
    hashTable.insert(track4); // This should trigger a resize

    // Search by artist name
    std::vector<Track> foundTracks = hashTable.search("Artist1");
    REQUIRE(foundTracks.size() == 2);
    REQUIRE(foundTracks[0].getTitle() == "Title1");
    REQUIRE(foundTracks[1].getTitle() == "Title3");
}

TEST_CASE("HashTable class: Test Insert, Remove and Search")
{
    HashTable hashTable(10);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);
    Track track4(4, "Title4", "Artist2", 300);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);
    hashTable.insert(track4);

    // Remove a track
    REQUIRE(hashTable.remove("Title2", "Artist2") == true);

    // Search by artist name
    std::vector<Track> foundTracks1 = hashTable.search("Artist1");
    REQUIRE(foundTracks1.size() == 2);
    REQUIRE(foundTracks1[0].getTitle() == "Title1");
    REQUIRE(foundTracks1[1].getTitle() == "Title3");

    // Search for a removed track
    std::vector<Track> foundTracks2 = hashTable.search("Artist2");
    REQUIRE(foundTracks2.size() == 1);
    REQUIRE(foundTracks2[0].getTitle() == "Title4");
}

TEST_CASE("HashTable class: Test Remove track with collision")
{
    HashTable hashTable(3);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);

    // Remove a track with collision
    REQUIRE(hashTable.remove("Title3", "Artist1") == true);

    // Ensure the track is removed, and the other track with the same key remains
    std::vector<Track> foundTracks = hashTable.search("Artist1");
    REQUIRE(foundTracks.size() == 1);
    REQUIRE(foundTracks[0].getTitle() == "Title1");
}

TEST_CASE("HashTable class: Test Search for non-existent artist")
{
    HashTable hashTable(10);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title2", "Artist2", 180);
    Track track3(3, "Title3", "Artist1", 240);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);
    hashTable.insert(track3);

    // Search for a non-existent artist
    std::vector<Track> foundTracks = hashTable.search("NonExistentArtist");
    REQUIRE(foundTracks.size() == 0);
}

TEST_CASE("HashTable class: Test Insert duplicate tracks")
{
    HashTable hashTable(10);
    Track track1(1, "Title1", "Artist1", 120);
    Track track2(2, "Title1", "Artist1", 120);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2); // Duplicate track

    // Ensure only one track is stored
    std::vector<Track> foundTracks = hashTable.search("Artist1");
    REQUIRE(foundTracks.size() == 1);
    REQUIRE(foundTracks[0].getTitle() == "Title1");
    REQUIRE(foundTracks[0].getDuration() == 120);
}

TEST_CASE("HashTable class: Test Insert track with empty artist or title")
{
    HashTable hashTable(10);
    Track track1(1, "Title1", "", 120);
    Track track2(2, "", "Artist2", 180);

    // Insert tracks into the hash table
    hashTable.insert(track1);
    hashTable.insert(track2);

    // Ensure tracks with empty artist or title are stored
    std::vector<Track> foundTracks1 = hashTable.search("");
    REQUIRE(foundTracks1.size() == 1);
    REQUIRE(foundTracks1[0].getTitle() == "Title1");

    std::vector<Track> foundTracks2 = hashTable.search("Artist2");
    REQUIRE(foundTracks2.size() == 1);
    REQUIRE(foundTracks2[0].getArtist() == "Artist2");
}
