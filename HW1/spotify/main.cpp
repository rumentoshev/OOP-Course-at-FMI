#include <iostream>
#include <cstring>
#include <fstream>
#include "Playlist.h"
#include "Genre.h"
#pragma warning(disable : 4996)



int main()
{
	Playlist pl;

	int firstCommand;
	do{
		std::cout << "PLAYLIST controls" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "To add song, press: 1" << std::endl;
		std::cout << "To print all songs, press: 2" << std::endl;
		std::cout << "To search song by name, press: 3" << std::endl;
		std::cout << "To search songs by genre, press: 4 " << std::endl;
		std::cout << "To sort songs by name, press: 5" << std::endl;
		std::cout << "To sort songs by duration, press 6" << std::endl;
		std::cout << "To mix 2 songs, press: 7" << std::endl;
		std::cout << "To change rhythm to song, press 8" << std::endl;
		std::cout << "To save song to .dat file, press: 9" << std::endl;
		std::cout << "To close, press 0" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cin >> firstCommand;

		if (firstCommand == 1)
		{
			std::cout << "Please enter the song name:" << std::endl;
			char tempName[MAX_BUFFER_LEN];
			std::cin.ignore();
			std::cin.getline(tempName, MAX_BUFFER_LEN);

			std::cout << "Please enter duration in seconds:" << std::endl;
			size_t duration;
			std::cin >> duration;
			std::cin.ignore();

			std::cout << "Please enter genres:" << std::endl;
			char tempGenre[MAX_BUFFER_LEN];
			std::cin.getline(tempGenre, MAX_BUFFER_LEN);

			std::cout << "Please enter file name to load content:" << std::endl;
			char tempFileName[MAX_BUFFER_LEN];
			std::cin.getline(tempFileName, MAX_BUFFER_LEN);
			std::cout << std::endl;

			if (pl.addSong(tempName, duration, tempGenre, tempFileName))
			{
				std::cout << "//success" << std::endl;
			}
			else
			{
				std::cout << "//fail" << std::endl;
			}

			
		}
		else if (firstCommand == 2)
		{
			pl.printPlaylist();
		}
		else if (firstCommand == 3)
		{
			std::cout << "Please enter the song name:" << std::endl;
			char tempName[MAX_BUFFER_LEN];
			std::cin.ignore();
			std::cin.getline(tempName, MAX_BUFFER_LEN);

			if (pl.findByName(tempName))
			{
				std::cout << "//success" << std::endl;
			}
			else
			{
				std::cout << "//fail" << std::endl;
			}
		}
		else if (firstCommand == 4)
		{
			std::cout << "Please enter genres:" << std::endl;
			char tempGenre;
			std::cin.ignore();
			std::cin >> tempGenre;

			pl.findByGenre(tempGenre);

		}
		else if (firstCommand == 5)
		{
			pl.sortByName();
		}
		else if (firstCommand == 6)
		{
			pl.sortByDuration();
		}
		else if (firstCommand == 7)
		{
			std::cout << "Please enter the first song name:" << std::endl;
			char tempName1[MAX_BUFFER_LEN];
			std::cin.ignore();
			std::cin.getline(tempName1, MAX_BUFFER_LEN);

			std::cout << "Please enter the second song name:" << std::endl;
			char tempName2[MAX_BUFFER_LEN];
			std::cin.getline(tempName2, MAX_BUFFER_LEN);

			if (pl.mixSongs(tempName1, tempName2))
			{
				std::cout << "//success" << std::endl;
			}
			else
			{
				std::cout << "//fail" << std::endl;
			}
		}
		else if (firstCommand == 8)
		{
			std::cout << "Please enter the song name:" << std::endl;
			char tempName[MAX_BUFFER_LEN];
			std::cin.ignore();
			std::cin.getline(tempName, MAX_BUFFER_LEN);

			std::cout << "Please enter which bit to be changed:" << std::endl;
			unsigned int tempIndex;
			std::cin >> tempIndex;
			
			if (pl.changeSongRhythm(tempName, tempIndex))
			{
				std::cout << "//success" << std::endl;
			}
			else
			{
				std::cout << "//fail" << std::endl;
			}
		}
		else if (firstCommand == 9)
		{
			std::cout << "Please enter the song name:" << std::endl;
			char tempName[MAX_BUFFER_LEN];
			std::cin.ignore();
			std::cin.getline(tempName, MAX_BUFFER_LEN);

			std::cout << "Please enter the file name:" << std::endl;
			char tempFileName[MAX_BUFFER_LEN];
			std::cin.getline(tempFileName, MAX_BUFFER_LEN);

			if (pl.saveSongToFile(tempName, tempFileName))
			{
				std::cout << "//success" << std::endl;
			}
			else
			{
				std::cout << "//fail" << std::endl;
			}
		}


	} while (firstCommand != 0);


	return 0;
}
