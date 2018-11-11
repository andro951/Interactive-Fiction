//Interactive fiction.
#include <iostream>
#include <string>
using namespace std;

void displayIntroduction();
void displayTime();
string getUserCommandAndObject(string prompt, string& command, string& object);
void didntRecognizeCommand(string command);

int time = 690; //The start time of the game in minutes where 0 is midnight.

int main()
{
	bool radiatorAttatchedToFloor = true;
	int emptyHands = 2;
	bool handcuffed = true;
	bool roomExamined = false;
	bool bagSearched = false;
	bool carryingRadiator = false;
	bool carryingHandcuffs = false;
	bool carryingHandgun = false;

	displayIntroduction();
	displayTime();
	string command;
	string object;
	getUserCommandAndObject("What will you do next?\n", command, object);
	//game loop
	bool gameOver = false;
	while (time < 730 and gameOver != true)
	{
		if (object == "radiator")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << "The radiator is old and slightly rusted.\n";
				time += 1;
			}
			else if (command == "move" || command == "remove" || command == "break")
			{
				if (radiatorAttatchedToFloor)
				{
					cout << "After significant effort, you manage to break the radiator off of the wall and are now able to move arround the room, dragging it with you.\n";
					time += 15;
					radiatorAttatchedToFloor = false;
				}
				else if (handcuffed)
				{
					cout << "The radiator is already detatched from the wall and you are dragging it with you.\n";
					time += 1;
				}
				else
				{
					cout << "The radiator is already detatched from the wall and you are able to move around the room freely.\n";
					time += 1;
				}
			}
			else if (command == "pick up")
			{
				if (radiatorAttatchedToFloor)
				{
					cout << "The radiator is attatched to the wall and you are unable to pick it up.\n";
					time += 5;
				}
				else if (carryingRadiator)
				{
					cout << "You are already carying the radiator.\n";
					time += 1;
				}
				else if (emptyHands < 2)
				{
					cout << "Your attepmt to pick up the radiator, but drop it.  Your hands are too full already.";
					time += 1;
				}
				else
				{
					cout << "You pick up the radiator.\n";
					time += 1;
					emptyHands = 0;
				}
			}
			else if (command == "drop" || command == "put down")
			{
				if (carryingRadiator)
				{
					cout << "You put down the radiator.\n";
					emptyHands = 2;
					time += 1;
				}
				else
				{
					cout << "You are not carying the radiator.\n";
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for radiator: examine, break, pick up, drop\n"; 
			}
			else
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "handcuffs")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << "A standard pair of handcuffs.\n";
				time += 1;
			}
			else if (command == "pick up" || command == "take")
			{
				if (handcuffed)
				{
					cout << "The handcuffs are still attatched to your hands.  You are unable to pick them up.\n";
				}
				else
				{
					if (carryingHandcuffs)
					{
						cout << "You are already carrying the handcuffs.\n";
						time += 1;
					}
					else
					{
						cout << "You pick up the handcuffs\n";
						carryingHandcuffs = true;
						time += 1;
					}
				}
			}
			else if (command == "drop" || command == "put down")
			{
				if (carryingHandcuffs)
				{
					cout << "You put down the handcuffs.\n";
					emptyHands += 1;
					time += 1;
				}
				else
				{
					cout << "You are not carying the handcuffs.\n";
					time += 1;
				}
			}
			else if (command == "unlock")
			{
				if (handcuffed)
				{
					if (bagSearched)
					{
						cout << "You unlock the handcuffs.\n";
						handcuffed = false;
						time += 3;
					}
					else
					{
						cout << "You have no way of unlocking the handcuffs.\n";
						time += 1;
					}
				}
				else
				{
					cout << "The handcuffs are already unlocked.\n";
					time += 1;
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for handcuffs: examine, pick up, drop, unlock\n";
			}
			else
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "room")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				if (radiatorAttatchedToFloor)
				{
					cout << "You can not see or reach the rest of the room.\n";
					time += 1;
				}
				else
				{
					cout << "In the room, there is a phone, a bag and a door.\n";
					roomExamined = true;
					time += 5;
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for room: examine\n";
			}
			else
			{
				didntRecognizeCommand(command);
			}
		}
		else if (roomExamined)
		{
			if (object == "bag")
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					if (bagSearched)
					{
						cout << "There is nothing else of note in the bag.\n";
					}
					else
					{
						cout << "The bag contains a gun and a handcuff key.\n";
						bagSearched = true;
					}
				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for bag: examine\n";
				}
				else
				{
					didntRecognizeCommand(command);
				}

			}
			else if (object == "handgun")
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					cout << "Loaded.  Safety off.  Round in the chamber.  Ready to fire.\n";
				}
				else if (command == "pick up" || command == "take")
				{
					if (carryingHandgun)
					{
						cout << "You are already carrying the handgun.\n";
						time += 1;
					}
					else
					{
						if (emptyHands >= 1)
						{
							cout << "You pick up the handgun.\n";
							emptyHands -= 1;
							time += 1;
						}
						else
						{
							cout << "Your attepmt to pick up the handgun, but drop it.  Your hands are too full already.";
							time += 1;
						}
					}
				}
				else if (command == "drop" || command == "put down")
				{
					if (carryingHandgun)
					{
						cout << "You put down the handgun.\n";
						emptyHands += 1;
						time += 1;
					}
					else
					{
						cout << "You are not carying the handgun.\n";
						time += 1;
					}
				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for handgun: examine, pick up, drop\n"; //List the currently available commands for the object.
				}
				else
				{
					didntRecognizeCommand(command);
				}

			}
			else if (object == "phone")
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					cout << "A typical phone found in a hotel room.\n";
					time += 1;
				}
				else if (command == "use" || command == "call")
				{
					cout << "Would you like to call 911 or the front desk?\n";
				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for phone: examine, use\n";
				}
				else
				{
					didntRecognizeCommand(command);
				}

			}
			else if (object == "door")
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					cout << "A typical hotel room door.\n";
					time += 1;
				}
				else if (command == "use" || command == "open")
				{
					if (handcuffed)
					{
						cout << "You won't make it far dragging around a radiator.\n";
						time += 1;
					}
					else
					{
						cout << "You leave the hotel and never look back.\n";
						gameOver = true;
					}
				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for : examine, use\n";
				}
				else
				{
					didntRecognizeCommand(command);
				}

			}
			else if (object == "")
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					cout << ".\n";
					time += 1;
				}
				else if (command == "pick up" || command == "take")
				{

				}
				else if (command == "drop" || command == "put down")
				{

				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for : examine, pick up, drop\n";
				}
				else
				{
					didntRecognizeCommand(command);
				}

			}
		}
		else if (object == "")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				cout << ".\n";
				time += 1;
			}
			else if (command == "pick up" || command == "take")
			{

			}
			else if (command == "drop" || command == "put down")
			{

			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for : examine, pick up, drop\n";
			}
			else
			{
				didntRecognizeCommand(command);
			}

		}
		else if (object == "objects")
		{
			if (command == "list" || command == "list of")
			{
				if (roomExamined)
				{
					cout << "objects: room, radiator, handcuffs, bag, gun, phone, door\n";
				}
				else
				{
					cout << "objects: room, radiator, handcuffs\n";
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for objects: list\n";
			}
			else
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "wait")
		{
			cout << "You paitiently wait a few minutes.";
			time += 5;
		}
		else
		{
			cout << "Didn't regognize the object, " << object << ".";
		}

		cout << "----------------------------------------------------\n";

		if (gameOver != true)
		{
			displayTime();
			getUserCommandAndObject("What will you do next?\n", command, object);
		}
	}
	if (gameOver != true)
	{
		cout << "A tall figure enters the dark room.\n";
		if (carryingHandgun)
		{
			//Ask if they will shoot.  If so, they go to prison for shooting a cleaning lady.  Otherwise they are killed.
		}
	}
	else
	{
		cout << "Game over.  You loose.";
	}
}

void displayIntroduction()
{
	cout << "Your only hint is to do things as you would actually do them.\n";
}

void displayTime()
{
	int days = time / 3600;
	int hours = (time % 3600) / 60;
	int minutes = time % 60;
	cout << "The current time is: ";
	if (hours % 12 < 10)
	{
		cout << "0";
	}
	cout << hours % 12;
	if (time % 60 < 10)
	{
		cout << "0";
	}
	cout << time % 60;
	if (hours / 12 == 1)
	{
		cout << " PM\n";
	}
	else
	{
		cout << " AM\n";
	}
}

string getUserCommandAndObject(string prompt, string& command, string& object)
{
	string userText = "";
	cout << prompt;
	getline (cin, userText, '\n');
	//int k = userText.length(); //Prevents an error when changing the userText withing the for loop when userText.length() is the number of times the for loop runs.
	for (int i = 0; i < userText.length(); i++)
	{
		userText[i] = tolower(userText[i]);
	}
	//int i = 0;
	//while (i < k)
	//{
	//	userText[i] = tolower(userText[i]);
	//	i++;
	//}
	command = "";
	object = "";
	string backwardsObject = "";
	bool determinedObject = false;
	int determinedObjectAt;
	string blank = " ";
	//The user is asked to input a command followed by an assosiated object.  The user is told that the object can only be one word.  This for loop creates string object and string command from string userText.
	for (int i = userText.length() - 1; i > -1; i--)
	{
		if (userText[i] == blank[0] && determinedObject != true) //2nd Once you reach a space, the object has been determined.  Stop adding characters to backwardsObject.
		{
			determinedObject = true;
			determinedObjectAt = i;
		}
		else if (determinedObject == true) //3rd 
		{
			for (int k = backwardsObject.length() -1; k > -1; k--) //use backwardsObject to make object.
			{
				object += backwardsObject[k];
			}
			for (int j = 0; j < determinedObjectAt; j++) //The rest of userText is used to make command.
			{
				command += userText[j];
			}
				return command, object; //return is used here because the purpose of the for loop is to determine where the object stops and the command starts.  It is not necesary to iterate through the entire userText.
		}
		else //1st Starting from the end of the string, userText, add characters to backwardsObject until you reach a space.
		{
			backwardsObject += userText[i];
		}
		
	}
	return command, object; //If there are no spaces in userText, object = userText and command = "".  The obove logic structure only provides a return value if there is a space.
}

void didntRecognizeCommand(string command)
{
	cout << "Didn't regognize the command, " << command << ".\n";
}