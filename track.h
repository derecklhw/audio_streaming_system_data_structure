#ifndef __AUDIOTRACK_H_
#define __AUDIOTRACK_H_

/*
    track.h
    Author: M00826933
    Created: 11/04/23
    Updated: 16/04/23
*/

#include <string>

// Track class definition
class Track
{

private:
    // Member datas
    int lineNumber;
    std::string title;
    std::string artist;
    int duration;

public:
    // Constructor
    Track(
        int lineNumber,
        const std::string &title,
        const std::string &artist,
        int duration);

    // Getter methods
    int getLineNumber() const;
    const std::string &getTitle() const;
    const std::string &getArtist() const;
    int getDuration() const;
};

#endif