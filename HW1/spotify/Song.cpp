#include "Song.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Song::Song(const char* name, const char* content,
	       const char* genre, size_t duration) : duration(duration)
{
	setName(name);
	setGenre(genre);
	setContent(content);
}

//getters
const char* Song::getName() const
{
	return name;
}
size_t Song::getDuration() const
{
	return duration;
}
size_t Song::getContentSize() const
{
	return contentSize;
}
char Song::getGenre() const
{
	return genre;
}
const char* Song::getContent() const
{
	return content;
}

//setters
bool Song::setName(const char* nameToBe)
{
	if (strlen(nameToBe) > MAX_SONG_NAME_LEN)
	{
		strcpy(name, "");
		return false;
	}
	strcpy(name, nameToBe);
	
	return true;
}
void Song::setDuration(size_t durationToBe)
{
	duration = durationToBe;
}
bool Song::setGenre(const char* genreToBe)
{
	size_t genreToBeLen = strlen(genreToBe);
	//If the genreToBe string has length over 5, its invalid.
	if (genreToBeLen > MAX_GENRES_MIX)
	{
		genre = 0;
		return false;
	}

	//If the genreToBe string has valid lenght (under 6 chars),
	//we check for valid genres letters.
	//The invalid ones will not change the gener of the song.
	for (int i = 0; i < genreToBeLen; i++)
	{
		switch (genreToBe[i])
		{
		case 'r': genre = genre | (1 << Genre::r); break;
		case 'p': genre = genre | (1 << Genre::p); break;
		case 'h': genre = genre | (1 << Genre::h); break;
		case 'e': genre = genre | (1 << Genre::e); break;
		case 'j': genre = genre | (1 << Genre::j); break;
		default: break;
		}
	}
	return true;
}
bool Song::setContent(const char* contentToBe)
{
	if (strlen(contentToBe) > MAX_SONG_CONTENT_LEN)
	{
		strcpy(content, "");
		contentSize = 0;
		return false;
	}
	strcpy(content, contentToBe);
	contentSize = strlen(contentToBe);

	return true;
}

//other
void Song::printGenre() const
{
	if (genre == 0)
	{
		std::cout << "No genre";
	}
	else
	{
		bool ampsCheck = false;
		//Rock
		if (genre & (1 << Genre::r))
		{
			std::cout << "Rock";
			ampsCheck = true;
		}
		//Pop
		if (genre & (1 << Genre::p))
		{
			if (ampsCheck)
			{
				std::cout << "&";
				ampsCheck = false;
			}
			std::cout << "Pop";
			ampsCheck = true;
		}
		//Hip-Hop
		if (genre & (1 << Genre::h))
		{
			if (ampsCheck)
			{
				std::cout << "&";
				ampsCheck = false;
			}
			std::cout << "Hip-hop";
			ampsCheck = true;
		}
		//Electronic
		if (genre & (1 << Genre::e))
		{
			if (ampsCheck)
			{
				std::cout << "&";
				ampsCheck = false;
			}
			std::cout << "Electronic";
			ampsCheck = true;
		}
		//Jazz
		if (genre & (1 << Genre::j))
		{
			if (ampsCheck)
			{
				std::cout << "&";
				ampsCheck = false;
			}
			std::cout << "Jazz";
		}
	}
	
}
bool Song::mix(const Song& other)
{
	//maybe make function here
	size_t contentSizeToMix;
	if (contentSize <= other.contentSize)
	{
		contentSizeToMix = contentSize;
	}
	else
	{
		contentSizeToMix = other.contentSize;
	}

	if (contentSizeToMix == 0)
	{
		return false;
	}

	for (size_t i=0; i < contentSizeToMix; i++)
	{
		content[i] = content[i] ^ other.content[i];
	}
	return true;
}
bool Song::changeRhythm(unsigned int index)
{
	char mask;
	size_t currIndexInContent = contentSize - 1;
	size_t currBit = index;
	size_t contentBits = contentSize * 8;
	
	while (currBit<=contentBits)
	{
		unsigned int indexOfContent = (contentSize - 1) - ((currBit - 1) / 8);
		unsigned int bitsToShift = (currBit - 1) % 8;
		mask = (1 << bitsToShift);

		content[indexOfContent] = content[indexOfContent] | mask;

		currBit = currBit + index;
	}
	return true;
}
void Song::printSong() const
{
	std::cout << name << " | ";
	
	size_t hours = duration / 3600;
	size_t mins = (duration / 60) % 60;
	size_t seconds = duration % 60;
	
	printTimeClear(hours);
	std::cout << ":";
	printTimeClear(mins);
	std::cout << ":";
	printTimeClear(seconds);
	std::cout << " | ";
	printGenre();

 }