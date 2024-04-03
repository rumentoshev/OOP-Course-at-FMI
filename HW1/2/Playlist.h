#pragma once
#include "Song.h"
#include "Constants.h"

class Playlist
{
private:
	Song playlist[MAX_SONGS_IN_PLAYLIST];
	short songsInPlaylist = 0;

public:

	Playlist() = default;

	bool addSong(const char* name, size_t duration, const char* genre, const char* fileName);

	void sortByName();
	void sortByDuration();
	bool mixSongs(const char* name1, const char* name2);
	bool changeSongRhythm(const char* name, unsigned int index);

	void printPlaylist() const;
	bool searchByName(const char* name) const;
	bool findByName(const char* name) const;
	void findByGenre(char genre) const;
	bool saveSongToFile(const char* song, const char* fileName) const;

private:
	void sortDatabase(bool(*isLess)(const Song& lhs, const Song& rhs));
	short getSongIndexByName(const char* name) const;
};