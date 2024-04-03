#include "Playlist.h"
#include "HelpFunctions.h"
#include <iostream>
#include <fstream>

bool Playlist::addSong(const char* name,size_t duration,
					   const char* genre, const char* fileName)
{
	if (songsInPlaylist >= MAX_SONGS_IN_PLAYLIST)
	{
		return false;
	}

	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) 
	{
		return false;
	}

	size_t fileSize = getFileSize(file);
	char* buffer = new char[fileSize + 1];
	file.read(buffer, fileSize);
	buffer[fileSize] = '\0';

	playlist[songsInPlaylist].setContent(buffer);
	playlist[songsInPlaylist].setName(name);
	playlist[songsInPlaylist].setDuration(duration);
	playlist[songsInPlaylist].setGenre(genre);
	songsInPlaylist++;

	delete[] buffer;
	file.close();
	return true;
}

void Playlist::printPlaylist() const
{
	for (short i = 0; i < songsInPlaylist; i++)
	{
		std::cout << '[' << i + 1 << "] ";
		playlist[i].printSong();
		std::cout << '\n';
	}
}

bool Playlist::searchByName(const char* name) const
{
	for (short i = 0; i < songsInPlaylist; i++)
	{
		if (!strcmp(playlist[i].getName(), name))
		{
			playlist[i].printSong();
			return true;
		}
	}

	return false;
}

void Playlist::sortDatabase(bool(*isLess)(const Song& lhs, const Song& rhs))
{
	for (short i = 0; i < songsInPlaylist; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < songsInPlaylist; j++)
		{
			if (isLess(playlist[j], playlist[minIndex]))
				minIndex = j;

		}
		if (i != minIndex)
			std::swap(playlist[i], playlist[minIndex]);
	}
}

void Playlist::sortByName()
{
	sortDatabase([](const Song& lhs, const Song& rhs) { return strcmp(lhs.getName(), rhs.getName()) < 0;});
}

void Playlist::sortByDuration()
{
	sortDatabase([](const Song& lhs, const Song& rhs) { return lhs.getDuration() < rhs.getDuration(); });
}

bool Playlist::findByName(const char* name) const
{
	for (short i = 0; i < songsInPlaylist; i++)
	{
		if (!strcmp(playlist[i].getName(), name))
		{
			playlist[i].printSong();
			std::cout << '\n';
			return true;
			break;
		}
	}

	return false;
}

void Playlist::findByGenre(char genre) const
{
	char mask = 0;
	switch (genre)
	{
		case 'r': mask = mask | (1 << Genre::r); break;
		case 'p': mask = mask | (1 << Genre::p); break;
		case 'h': mask = mask | (1 << Genre::h); break;
		case 'e': mask = mask | (1 << Genre::e); break;
		case 'j': mask = mask | (1 << Genre::j); break;
		default: break;
	}

	if (mask != 0)
	{
		for (short i = 0; i < songsInPlaylist; i++)
		{
			if ((playlist[i].getGenre() & mask) != 0)
			{
				playlist[i].printSong();
				std::cout << '\n';
			}
		}

	}
}

short Playlist::getSongIndexByName(const char* name) const
{
	for (short i = 0; i < songsInPlaylist; i++)
	{
		if (!strcmp(playlist[i].getName(), name))
		{
			return i;
			break;
		}
	}

	return -1;
}

bool Playlist::mixSongs(const char* name1, const char* name2)
{
	short song1index = getSongIndexByName(name1);
	short song2index = getSongIndexByName(name2);

	if (song1index != -1 && song2index != -1)
	{
		if (playlist[song1index].mix(playlist[song2index]))
		{
			return true;
		}
	}

	return false;
}

bool Playlist::changeSongRhythm(const char* name, unsigned int index)
{
	short songIndex = getSongIndexByName(name);

	if (songIndex != -1)
	{
		if (playlist[songIndex].changeRhythm(index))
		{
			return true;
		}
	}

	return false;
}

bool Playlist::saveSongToFile(const char* song, const char* fileName) const
{
	short songIndex = getSongIndexByName(song);

	std::ofstream file(fileName,std::ios::binary);

	if (!file.is_open()) {
		return false;
	}

	file.write((const char*)playlist[songIndex].getContent(),sizeof(char)*(playlist[songIndex].getContentSize()));
	file.close();
	return true;
}