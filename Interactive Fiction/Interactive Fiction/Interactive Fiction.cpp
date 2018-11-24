//Interactive fiction.
#include <iostream>
#include <string>
using namespace std;

void displayIntroduction(); //Display a simple opening message.
void displayTime(); //Convert the time into a standard format and display it.
void getUserCommandAndObject(string prompt, string& command, string& object); //Get a command and object from the user with one cin and seperate them.
void didntRecognizeCommand(string command); //Display a simple message when recieveing an unrecoginzed command.

int time = 690; //The start time of the game in minutes where 0 is midnight.

int main()
{
	bool radiatorAttatchedToFloor = true; //Track if radiator is attatched to the floor.
	int emptyHands = 2; //Track how many hands can be used to pick things up.
	bool handcuffed = true; //Track if handcuffs are on the user.
	bool roomExamined = false; //Track if the room has been examined by the user.
	bool bagSearched = false; //Track if the bag has been examined by the user.
	bool carryingRadiator = false; //Track if the user is carrying the radiator.
	bool carryingHandcuffs = false; //Track if the user is carrying the handcuffs.
	bool carryingHandgun = false; //Track if the user is carrying the handgun.
	bool called911 = false; //Track if the user called 911.
	int timeCalledPolice = 32767; //Initially set to a very high default value to indicate that they were not called.

	displayIntroduction();
	displayTime();
	string command; //Stores the command for the object the user wants to interact with.
	string object; //Stores the object the user wants to interact with.
	getUserCommandAndObject("What will you do?\n", command, object); //Get the first command and object from the user.
	//game loop
	bool gameOver = false; //If gameOver is true, the player WINS!!!
	while (time < 730 and gameOver != true) //Reapeat until the time has progressed to 730 or the the game has ended for another reason.

		//Below is a large if, else if logic structure.  It is used to determine what to output for the user and how to change the game's logic state based on the user's command and object inputs.

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
				if (radiatorAttatchedToFloor) //If the user hasn't done this before, detatch the radiator.
				{
					cout << "After significant effort, you manage to break the radiator off of the wall and are now able to move arround the room, dragging it with you.\n";
					time += 15;
					radiatorAttatchedToFloor = false; //This allows the player to use the command, examine room, and move around the room.
				}
				else if (handcuffed) //If the user has done this before, provide a useless message based on if they are handcuffed that tries to lead them towards getting the handcuffs off.
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
				if (radiatorAttatchedToFloor) //If attatched to the floor still, they can't pick it up.
				{
					cout << "The radiator is attatched to the wall and you are unable to pick it up.\n";
					time += 5;
				}
				else if (carryingRadiator) //If already carrying it, they can't pick it up again.
				{
					cout << "You are already carying the radiator.\n";
					time += 1;
				}
				else if (emptyHands < 2) //It requires 2 hands to pick up.  They drop it otherwise.
				{
					cout << "Your attepmt to pick up the radiator, but drop it.  Your hands are too full already.";
					time += 1;
				}
				else //Conditions met to pick up the radiator.
				{
					cout << "You pick up the radiator.\n";
					time += 1;
					emptyHands = 0;
					carryingRadiator = true;
				}
			}
			else if (command == "drop" || command == "put down")
			{
				if (carryingRadiator) //Conditions met to drop the radiator.
				{
					cout << "You put down the radiator.\n";
					emptyHands = 2;
					time += 1;
				}
				else //Provide useless message for trying to drop the radiator when they weren't holding it.
				{
					cout << "You are not carying the radiator.\n";
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for radiator: examine, break, pick up, drop\n"; 
			}
			else //Any other command for radiator is unrecognized.
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
				if (handcuffed) //Can't pick up if still handcuffed.
				{
					cout << "The handcuffs are still attatched to your hands.  You are unable to pick them up.\n";
					time += 1;
				}
				else
				{
					if (carryingHandcuffs) //Can't pick up if already carrying.
					{
						cout << "You are already carrying the handcuffs.\n";
						time += 1;
					}
					else //Meets the conditions to pick up the handcuffs.
					{
						cout << "You pick up the handcuffs\n";
						carryingHandcuffs = true;
						time += 1;
					}
				}
			}
			else if (command == "drop" || command == "put down")
			{
				if (carryingHandcuffs) //Meets the conditions to drop the handcuffs.
				{
					cout << "You put down the handcuffs.\n";
					emptyHands += 1;
					time += 1;
				}
				else //Not carrying them, gives useless message.
				{
					cout << "You are not carying the handcuffs.\n";
					time += 1;
				}
			}
			else if (command == "unlock")
			{
				if (handcuffed)
				{
					if (bagSearched) //Can only unlock the handcuffs if you know where the key is which is inside the bag.
					{
						cout << "You unlock the handcuffs.\n";
						handcuffed = false;
						time += 3;
					}
					else //Otherwise, you have no way to unlock them.
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
			else //Any other command for handcuffs is unrecognized.
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "room")
		{
			if (command == "examine" || command == "look at" || command == "view")
			{
				if (radiatorAttatchedToFloor) //Can't move around the room until the radiator is disconected from the floor.
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
			else //Any other command for room is unrecognized.
			{
				didntRecognizeCommand(command);
			}
		}
		else if (object == "bag" && roomExamined)
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					if (bagSearched)
					{
						cout << "There is nothing else of note in the bag.\n";
						time += 1;
					}
					else
					{
						cout << "The bag contains a gun and a handcuff key.\n";
						bagSearched = true; //Give the player access to the command unlock handcuffs and access to the handgun.
						time += 1;
					}
				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for bag: examine\n";
				}
				else //Any other command for  is unrecognized.
				{
					didntRecognizeCommand(command);
				}

			}
		else if (object == "handgun" && bagSearched)
				{
					if (command == "examine" || command == "look at" || command == "view")
					{
						cout << "Loaded.  Safety off.  Round in the chamber.  Ready to fire.\n";
					}
					else if (command == "pick up" || command == "take")
					{
						if (carryingHandgun) //Already carrying it.
						{
							cout << "You are already carrying the handgun.\n";
							time += 1;
						}
						else
						{
							if (emptyHands >= 1) //If you have enough empty hands, you meet the conditions to pick it up.
							{
								cout << "You pick up the handgun.\n";
								emptyHands -= 1;
								time += 1;
							}
							else //Don't have enough empty hands.
							{
								cout << "Your attepmt to pick up the handgun, but drop it.  Your hands are too full already.";
								time += 1;
							}
						}
					}
					else if (command == "drop" || command == "put down")
					{
						if (carryingHandgun) //Meets the conditions to drop the handgun.
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
					else //Any other command for handgun is unrecognized.
					{
						didntRecognizeCommand(command);
					}

				}
		else if (object == "phone" && roomExamined)
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					cout << "A typical phone found in a hotel room.\n";
					time += 1;
				}
				else if (command == "use" || command == "call")
				{
					bool waitingForValidInput = true;
					while (waitingForValidInput) //Repeats until a valid input is entered.
					{
						cout << "Would you like to call 911 or the front desk? (type 911 or front desk)\n";
						string userAnswer; //Stores the user's answer to the above question.
						cin >> userAnswer;
						// If the user wants to call 911, they will win at the end if the end is >= 20 minutes from the time they called.
						if (userAnswer == "911")
						{
							called911 = true; //Determines if the program will calculate the time the user called 911 at the end of the time limit.
							waitingForValidInput = false;
							cout << "You inform the police of your situation and hang up the phone.\n";
							timeCalledPolice = time; //Used to calculate if 911 was called at least 20 minutes before the game was over.
							time += 5;
							//Note that removing the radiator takes 15 minutes and examining the room takes 5 minutes.  If the user does anything else before calling 911, they will not win from it.
						}
						else if (userAnswer == "front desk") //The user will inform their captor by calling the front desk and will loose immediatly.
						{
							cout << "You inform the front desk of your situation and hang up the phone.\n"
								<< "The front desk clerk informs you that they will be right up to help.\n";
							time = 730; //Changes the time to immediatly end the game.
							waitingForValidInput = false;
						}
						else //If anything other than 911 or front desk is entered, repeat the waitingForValidInput loop.
						{
							cout << "\nInvalid input.\n\n";
						}
					}
				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for phone: examine, use\n";
				}
				else //Any other command for phone is unrecognized.
				{
					didntRecognizeCommand(command);
				}

			}
		else if (object == "door" && roomExamined)
			{
				if (command == "examine" || command == "look at" || command == "view")
				{
					cout << "A typical hotel room door.\n";
					time += 1;
				}
				else if (command == "use" || command == "open")
				{
					if (handcuffed) //If still handcuffed to the radiator and dragging it around, the user can't leave.
					{
						cout << "You won't make it far dragging around a radiator.\n";
						time += 1;
					}
					else //The user wins the game.
					{
						cout << "You leave the hotel and never look back.\n"; //The user wins.
						gameOver = true; //Prevents any of the logic after the game loop from executing.  Aka, prevents other endings.
					}
				}
				else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
				{
					cout << "Available commands for : examine, use\n";
				}
				else //Any other command for door is unrecognized.
				{
					didntRecognizeCommand(command);
				}

			}
		//This is a placeholder for adding new objects into the game.
		else if (object == "" && roomExamined)
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
				if (roomExamined) //Only list the object in the room if they player has examined the room.
				{
					if (bagSearched) //Only list the objects in the bag if it has been searched.
					{
						cout << "objects: room, radiator, handcuffs, bag, phone, door, handgun\n";
					}
					else
					{
						cout << "objects: room, radiator, handcuffs, bag, phone, door\n";
					}
				}
				else //If the room hasn't been searched, list the starting known objects.
				{
					cout << "objects: room, radiator, handcuffs\n";
				}
			}
			else if (command == "list commands for" || command == "list commands" || command == "commands for" || command == "commands")
			{
				cout << "Available commands for objects: list\n";
			}
			else //Any other command for objects is unrecognized.
			{
				didntRecognizeCommand(command);
			}
		}
		//Because of the way commands and objects are determined by the getUserCommandAndObject function, one word actions that you would expect to be alled commands are recognized as objects.
		else if (object == "wait")
		{
			cout << "You paitiently wait a few minutes.";
			time += 5;
		}
		else if (object == "help")
		{
			cout << "To interact with the objects in the room, enter the command for that object followed by the object. (command object)\n"
				<< "To see all objects currently available to you, type \"list objects\".\n"
				<< "To see the commands for an object, type \"commands for \" followed by the objects name.  For example, \"commands for room\".\n"
				<< "Type \"wait\" to wait 5 minutes.\n";
		}
		//This is a placeholder for adding new objects into the game.
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
		else //Any other object is unrecognized.
		{
			cout << "Didn't regognize the object, " << object << ".";
		}

		cout << "----------------------------------------------------\n";

		if (gameOver != true) //If the player did not win yet, get a new command and object.
		{
			displayTime();
			getUserCommandAndObject("What will you do next?\n", command, object); //Get all subsequent commands and objects.  Once each time the game loop repeats.
		}
	}
	if (timeCalledPolice <= 710) //If the player called the police in time, they will win.
	{
		gameOver = true; //Player wins.
		cout << "The police arive and escort you home.\n";
	}
	if (gameOver != true) //If player did not win until now, they will loose.  There is no way to win after the captor enters the room.
	{
		cout << "A tall figure enters the dark room.\n";
		if (carryingHandgun)
		{
			//Ask if they will shoot.  If so, they go to prison for shooting the front desk clerk.  Otherwise they are killed.
			bool waitingForValidInput = true;
			while (waitingForValidInput) //Repeats until a valid input is entered.
			{
				cout << "Will you shoot? (type yes or no)\n";
				string userAnswer; //Stores the user's answer to the above question.
				cin >> userAnswer;
				if (userAnswer == "yes" || userAnswer == "Yes" || userAnswer == "YES") //If yes is entered, they shoot the person who entered the room and they loose.
				{
					cout << "BANG!....The figure drops to the floor in a pool of blood.\n"
						<< "You rush out of the room.  Who did I just shoot?\n"
						<< "Later that week, you are arrested for murder.\n\n";
					waitingForValidInput = false;
				}
				else if (userAnswer == "no" || userAnswer == "No" || userAnswer == "NO") //If they don't shoot, they are killed.
				{
					waitingForValidInput = false;
				}
				else //If anything other than yes or no is entered, repeat the waitingForValidInput loop.
				{
					cout << "\nInvalid input.\n\n";
				}
			}
		}
		cout << "You loose.\n";
	}
	system("pause");
	return 0;
}
//Display a simple opening message.
void displayIntroduction()
{
	cout<< "You wake up in a dark room.\n"
		<< "You aren't sure where you are or how you got there.\n"
		<< "You soon realize that you are in a hotel room.\n"
		<< "You try to get up, but your hands are handcuffed to the radiator.\n\n\n"


		<< "To interact with the objects in the room, enter the command for that object followed by the object. (command object)\n"
		<< "To see all objects currently available to you, type \"list objects\".\n"
		<< "To see the commands for an object, type \"commands for \" followed by the objects name.  For example, \"commands for room\".\n"
		<< "Type \"wait\" to wait 5 minutes.\n"
		<< "Type \"help\" to redisplay this information.\n\n"
		<< "Your only hint is to do things as you would actually do them.\n\n";
}

//Convert the time into a standard format and display it.
void displayTime()
{
	//time is in minutes.
	int days = time / 3600; //calculate the number of days from time. (range from 0-infinite) (not used in this program.)
	int hours = (time % 3600) / 60; //calculate the number of hours from time. (range from 0-23)
	int minutes = time % 60; //calculate the number of minutes. (range from 0-59)
	cout << "The current time is: ";
	if (hours % 12 < 10) //Convert hours from 24 hour to 12 hour time. If it is < 10, output a zero to make it look like a clock would.
	{
		cout << "0";
	}
	cout << hours % 12; //Convert hours from 24 hour to 12 hour time and output it.
	if (minutes < 10) //If minutes are < 10, output a zero to make it look like a clock would.
	{
		cout << "0";
	}
	cout << minutes;
	if (hours > 12) //If hours is > 12, display PM.
	{
		cout << " PM\n";
	}
	else //If <12, display AM.
	{
		cout << " AM\n";
	}
}

//Get a command and object from the user with one cin and seperate them.
void getUserCommandAndObject(string prompt, string& command, string& object)
{
	string userText = "";
	cout << prompt;
	do //Prevents the user from inputting a blank command and an bug that would create a blank command when useing use phone.
	{
		getline(cin, userText, '\n'); //Allows the user to input whitespaces which cin does not.
	} while (userText == "");
	for (int i = 0; i < userText.length(); i++)
	{
		userText[i] = tolower(userText[i]); //Convert each letter in userText to lowercase.
	}
	command = "";
	object = "";
	string backwardsObject = ""; //Stores the object backwards temporarily.
	bool determinedObject = false; //Tracks if a whitespace has been reach in userText.
	int determinedObjectAt; //Tracks where the first whitespace was reached in userText.
	string blank = " "; //Prevents an issue with compairing " ", a const char to another char.
	//The user is asked to input a command followed by an assosiated object.  The user is told that the object can only be one word.  This for loop creates string object and string command from string userText.
	for (int i = userText.length() - 1; i > -1; i--) //Starting from the end of userText, look at each char.  Until a whitespace is found, add the char to backwardsObject.  Once a whitespace is found, make the command and object.
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
			return; //The program has determined the command and object and does not provide any further value by continuing.  End the program.
		}
		else //1st Starting from the end of the string, userText, add characters to backwardsObject until you reach a space.
		{
			backwardsObject += userText[i];
		}
		if (i == 0 && object == "") //Sometimes the user will input 1 word with no whitespaces.  If that happens, the object is userText. (command is blank)
		{
			object = userText;
		}
	}
	return; //The program has evaluated all of the char in userText.  End the program.
}

//Display a simple message when recieveing an unrecoginzed command.
void didntRecognizeCommand(string command)
{
	cout << "Didn't regognize the command, " << command << ".\n";
}