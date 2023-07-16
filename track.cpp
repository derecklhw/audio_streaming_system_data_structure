/*
    track.cpp
    Author: M00826933
    Created: 11/04/23
    Updated: 16/04/23
*/

#include "track.h"

// Constructor
Track::Track(
    int lineNumber,
    const std::string &title,
    const std::string &artist,
    int duration)
{
    this->lineNumber = lineNumber;
    this->title = title;
    this->artist = artist;
    this->duration = duration;
}

// Getter methods
int Track::getLineNumber() const
{
    return lineNumber;
}
const std::string &Track::getTitle() const
{
    return title;
}
const std::string &Track::getArtist() const
{
    return artist;
}
int Track::getDuration() const
{
    return duration;
}
