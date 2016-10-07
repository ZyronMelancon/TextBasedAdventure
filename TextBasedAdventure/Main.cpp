#include<iostream>
#include<Windows.h>
#include "string.h"

int currentRoom = 0;
bool haveOrb = false;
bool onPedistal = false;
bool win = false;
bool beenThere = false;
char *input = new char[256];
char input2;

//Room drawing strings
string wallroom = "_________________________\n";
string wallroomside = "|                       |\n";
string orb = "o";
string pedistal1 = "___";
string pedistal2 = "|_|";

string arrow[4] = {
arrow[0] = "^",
arrow[1] = "v",
arrow[2] = "<",
arrow[3] = ">"
};

//User input strings
string dir[4] = {
	dir[0] = "north",
	dir[1] = "south",
	dir[2] = "west",
	dir[3] = "east"
};

string act[3] = {
	act[0] = "attack",
	act[1] = "run",
	act[2] = "item"
};

//Dialogue
string dial[17] = {
	dial[0] = "Which door do you take? (north, south, west, east)",
	dial[1] = "I wake up in an eerily empty room.\nThere are two doors.",
	dial[2] = "I return to the empty room, to see that it is still empty.",
	dial[3] = "I walk into the next room.",
	dial[4] = "It's a dead end...\nThere is a pedestal with nothing on it.",
	dial[5] = "There is a strange glowing orb in the center of this room.\nMaybe I should pick it up? (y/n)",
	dial[6] = "The glowing orb is no longer here.\nThe room is empty and dark.",
	dial[7] = "I pick up the orb. I feel a peaceful aura radiating from it.",
	dial[8] = "On closer examination of the pedistal, it seems\nthat the glowing orb may have belonged here.\nPlace it? (y/n)",
	dial[9] = "I decide not to pick it up.\nMaybe it belongs to someone else...\nBut who?",
	dial[10] = "I place the orb on the pedistal.\nSuddenly, a secret door opens!\nI see light!",
	dial[11] = "The secret door is still open.\nMaybe I should go through?",
	dial[12] = "I go through the secret door, and take a\nbreath of the fresh outside air. I am free.",
	dial[13] = "There is not a door that way.",
	dial[14] = "The End",
	dial[15] = "Invalid response",
	dial[16] = "I decide not to place the orb on the pedistal.\nPerhaps I should find the owner?"
};


void cursorPos(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

//Draws the room
void roomDraw(int room)
{
	system("cls");

	std::cout << wallroom.cstyle();
	for (int i = 0; i < 10; i++)
		std::cout << wallroomside.cstyle();
	std::cout << wallroom.cstyle();

	switch (room)
	{
	case 0:
		cursorPos(12, 1);
		std::cout << arrow[0].cstyle();
		cursorPos(23, 5);
		std::cout << arrow[3].cstyle();
		break;
	case 1:
		cursorPos(1, 5);
		std::cout << arrow[2].cstyle();
		cursorPos(12, 5);
		std::cout << pedistal1.cstyle();
		cursorPos(12, 6);
		std::cout << pedistal2.cstyle();
		if (onPedistal)
		{
			cursorPos(13, 5);
			std::cout << orb.cstyle();
			cursorPos(23, 5);
			std::cout << arrow[3].cstyle();
		}
		break;
	case 2:
		cursorPos(12, 10);
		std::cout << arrow[1].cstyle();
		if (!haveOrb)
		{
			cursorPos(12, 5);
			std::cout << orb.cstyle();
		}
	}

	cursorPos(0, 15);

}

//Dialogue writing loop
void dialogue(int room)
{
	switch (room)
	{
	case 0: //In room 0
		if (!beenThere) //If I wasn't already there
		{
			std::cout << dial[1].cstyle(); //Wake up
			beenThere = true;
		}
		else //If I have been there
			std::cout << dial[2].cstyle(); //Return
		printf("\n");
		break;
	case 1:
		if (!haveOrb) //If I don't have the orb
			std::cout << dial[4].cstyle(); //Dead end
		else if (haveOrb && onPedistal) //If it's on the pedistal
		{
			std::cout << dial[11].cstyle(); //Door is open
		}
		else if (haveOrb) //If I do
		{
			std::cout << dial[4].cstyle() << std::endl; //Place on pedistal?
			std::cout << dial[8].cstyle();
		}

		printf("\n");

		break;
	case 2:
		if (!haveOrb) //If I don't have the orb
			std::cout << dial[5].cstyle(); //Pick it up?
		else //If I have it
			std::cout << dial[6].cstyle(); //Empty room
		printf("\n");
		break;
	}
}

void userIn(int room)
{

	/* IO Sequence */

	while (true) //Loop until valid input
	{
		switch (room)
		{
		case 0: //In room 0
			std::cout << dial[0].cstyle() << std::endl; //Choose the room to walk to
			std::cin >> input;
			break;
		case 1: //In room 1
			if (!haveOrb && !onPedistal) //If you don't have the orb
			{
				std::cout << dial[0].cstyle() << std::endl; //Choose room
				std::cin >> input;
				break;
			}
			else if (haveOrb && !onPedistal) //But if you do have the orb
			{
				while (true) //Loop until valid input
				{
					std::cin >> input2; //Place on pedistal?
					if (input2 == 'y' || input2 == 'Y')
					{
						onPedistal = true; //It's on the pedistal now
						std::cout << dial[10].cstyle() << std::endl;
						cursorPos(13, 5);
						std::cout << orb.cstyle();
						cursorPos(23, 5);
						std::cout << arrow[3].cstyle();
						cursorPos(0, 24);
						break;
					}
					else if (input2 == 'n' || input2 == 'N')
					{
						std::cout << dial[16].cstyle() << std::endl; //It's not on the pedistal
						break;
					}
					else
						std::cout << dial[15].cstyle() << std::endl; //Invalid
				}
				std::cout << dial[0].cstyle() << std::endl; //After placing or not placing, choose room
				std::cin >> input;
				break;
			}
			else if (haveOrb && onPedistal) //But if the orb is already on the pedistal
				std::cout << dial[0].cstyle() << std::endl;
				std::cin >> input; //Choose the room the enter
			break;
		case 2: //In room 2
			if (!haveOrb) //If you don't have the orb
			{
				while (true) //Loop until valid input
				{
					std::cin >> input2; //Take the orb?
					if (input2 == 'y' || input2 == 'Y')
					{
						cursorPos(12, 5);
						printf(" ");
						haveOrb = true; //I have the orb now
						cursorPos(0, 18);
						std::cout << dial[7].cstyle() << std::endl;
						break;
					}
					else if (input2 == 'n' || input2 == 'N')
					{
						std::cout << dial[9].cstyle() << std::endl; //I don't have the orb
						break;
					}
					else
						std::cout << dial[15].cstyle() << std::endl; //Invalid
				}

				std::cout << dial[0].cstyle() << std::endl; //After choosing to pick up or leave the orb, choose room
				std::cin >> input;
			}
			else //If you do have the orb
			{
				std::cout << dial[0].cstyle() << std::endl; //Choose room
				std::cin >> input;
			}
		}

		/* Matching sequence */

		if (dir[0].strcomp(input) && room == 0)
		{
			currentRoom = 2;
			break;
		}
		else if (dir[3].strcomp(input) && room == 0)
		{
			currentRoom = 1;
			break;
		}
		else if (dir[2].strcomp(input) && room == 1)
		{
			currentRoom = 0;
			break;
		}
		else if (dir[1].strcomp(input) && room == 2)
		{
			currentRoom = 0;
			break;
		}
		else if (dir[3].strcomp(input) && room == 1 && onPedistal == true)
		{
			std::cout << dial[12].cstyle() << std::endl;
			system("pause");
			system("cls");
			cursorPos(12, 7);
			std::cout << dial[14].cstyle();
			cursorPos(4, 9);
			system("pause");
			win = true;
			break;
		}
		else
			std::cout << dial[13].cstyle() << std::endl;
	}

}

void main()
{
	while (!win)
	{
		roomDraw(currentRoom);
		dialogue(currentRoom);
		userIn(currentRoom);
	}
}