#pragma once
#include <fstream>
#include "Genre.h"
#include "HelpFunctions.h"
#include "Constants.h"


class Song
{
private:
	char name[MAX_SONG_NAME_LEN + 1] = "";
	char content[MAX_SONG_CONTENT_LEN + 1] = "";
	char genre = 0;
	size_t contentSize = 0;
	size_t duration = 0;

public:

	Song() = default;
	Song(const char* name, const char* content,
		 const char* genre, size_t duration);
	
	//getters
	const char* getName() const;
	size_t getDuration() const;
	size_t getContentSize() const;
 	char getGenre() const;
	const char* getContent() const;

	//setters
	bool setName(const char* nameToBe);
	void setDuration(size_t durationToBe);
	bool setGenre(const char* genre);
	bool setContent(const char* contentToBe);


	//other 
	bool mix(const Song& other);
	bool changeRhythm(unsigned int index);
	void printSong() const;

private:
	void printGenre() const;
};