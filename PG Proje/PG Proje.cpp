
//Added required libraries.
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <ctime>
#include <cstdio>
#include <sstream>

using namespace std;

//Created variables for readers in Reader class.
class Reader
{
public:
	string idNo;
	string name;
	string lastname;
	string phoneNumber;
	string dateOfBirth;
	string profession;
	int memberNo;
	int avaiableBook;

};

//Created variables for books in Books class.
class Books
{
public:
	string isbn;
	string bookName;
	string writerName;
	string writerLastname;
	string subject;
	string type;
	char status;
	int page;
};

//Created a bool for main menu loop.
const bool loop = true;

//Function prototypes for each menu.
void login();
void menu();
void readerAdd();
void readerUpdate();
void removeReader();
void readerBooks();
void borrowBook();
void bringBook();
void addBook();
void removeBook();
void updateBook();
void exitmenu();
void gotoxy(int x, int y);

int main()
{
	login();

}

//Created "Login" function. Asks user username and password to proceed.
void login()
{

	//Used ctime here for system entry time.
	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* time = ctime(&now);

	//Opened read file here for usernames and passwords.
	ifstream inUsers("users.txt");

	//Bool for avoid errors when we go main menu.
	bool returning;
	//temporary strings.
	string entryUser, entryPass, username, password;
	cout << "Welcome to Library++ !" << endl << endl;
	cout << "Please Login!" << endl << endl;
	cout << "Username..: "; cin >> entryUser; cout << endl;
	cout << "Password..:"; cin >> entryPass; cout << endl;

	//Searching entered username and password in our users file.
	while (!inUsers.eof())
	{

		inUsers >> username >> password;

		//If username is true time counter will count time from 3 to 0 and will let us proceed menu.
		if (username == entryUser && password == entryPass)
		{

			cout << "Welcome " << username << "!" << endl << endl;
			cout << "System Entry Time is: " << time << endl << endl;
			cout << "Going Menu in 3 Sec...";

			//Time counter loop.
			for (int counter = 3; 0 < counter; counter--)
			{
				gotoxy(14, 13);
				cout << counter;
				Sleep(1000);
			}
			system("CLS");
			returning = true;
			break;

		}
		//If user does not exist, login screen won't let us proceed menu.
		else if (inUsers.eof())
		{
			cout << "User doesn't Exist. Returning Login Screen in 3 Sec...";

			//Loop for time counter 3 to 0.
			for (int counter = 3; 0 < counter; counter--)
			{
				gotoxy(46, 8);
				cout << counter;
				Sleep(1000);
			}
			returning = false;
			break;
		}
	}

	//Checking our bool here. If it is true login will let us proceed.
	system("CLS");
	if (returning == true)
	{
		while (loop)menu(); //Used loop here for going menu back.
	}
	else if (returning == false)
	{
		login();
	}


}
//Created "Main Menu" function. It is our main menu.
void menu()
{
	//Created 1 string and 1 int for menu pick. Using "stoi()" for avoid errors.
	string pick;
	int switchPick;

	do
	{
		system("CLS");
		cout << "Library++ made with <3 by Caner Kaymakci" << endl << endl;

		cout << "1. Add Reader" << endl;
		cout << "2. Update Reader" << endl;
		cout << "3. Remove Reader" << endl;
		cout << "4. List Books of a Reader" << endl;
		cout << "5. Borrow Book for a Reader" << endl;
		cout << "6. Bring Book Back From a Reader" << endl;
		cout << "7. Add Book" << endl;
		cout << "8. Remove Book" << endl;
		cout << "9. Update Book" << endl;
		cout << "10. Exit" << endl << endl;

		cout << "Please Pick What Do You Want to Do..:";
		cin >> pick;

		//if pick is incorrect menu will loop itself until it's correct.
		if (pick != "1" && pick != "2" && pick != "3" && pick != "4" && pick != "5" && pick != "6" && pick != "7" && pick != "8" && pick != "9" && pick != "10")
		{
			cout << "Error... Please Try Again in 3 Sec...";
			Sleep(3000);
			system("CLS");
			menu();
		}
		else //if pick is correct, switch will let us use menu which we picked.
		{
			switchPick = stoi(pick);
			switch (switchPick)
			{
			case 1:
				readerAdd();
				break;
			case 2:
				readerUpdate();
				break;
			case 3:
				removeReader();
				break;
			case 4:
				readerBooks();
				break;
			case 5:
				borrowBook();
				break;
			case 6:
				bringBook();
				break;
			case 7:
				addBook();
				break;
			case 8:
				removeBook();
				break;
			case 9:
				updateBook();
				break;
			case 10:
				exitmenu();
				break;
			}
		}

	} while (pick != "1" && pick != "2" && pick != "3" && pick != "4" && pick != "5" && pick != "6" && pick != "7" && pick != "8" && pick != "9" && pick != "10");
}
//Created "Add Reader" function. Adding readers for user.
void readerAdd()
{
	//Opened our readers file for input and output.
	ofstream outReaders("readers.txt", ios_base::app);
	ifstream inReaders("readers.txt");

	Reader reader; //Created an object for readers.
	srand(time(NULL)); //Used random values for member no.

	system("CLS");
	cout << "Add Reader" << endl << endl;

	cout << "Enter Reader ID..: "; cin >> reader.idNo;
	cin.ignore();
	cout << "Enter Reader Name..:"; getline(cin, reader.name);
	cout << "Enter Reader Lastname..:"; cin >> reader.lastname;
	cout << "Enter Reader Phone Number..:"; cin >> reader.phoneNumber;
	cout << "Enter Reader Date of Birth..:"; cin >> reader.dateOfBirth;
	cin.ignore();
	cout << "Enter Reader' Profession..:"; getline(cin, reader.profession);

	//Checking here if entered ID number or phone number registered before. If registered before, "add reader menu" will be closed.
	string tempValue;
	while (!inReaders.eof())
	{
		inReaders >> tempValue;
		if (reader.idNo == tempValue || reader.phoneNumber == tempValue)
		{
			cout << "ID or Phone Number had been registered before. Returning Main Menu in 3 Sec.";
			Sleep(3000);
			system("CLS");
			outReaders.close();
			inReaders.close();
			return;
		}

	}

	//Giving readers random member no and max amount of borrow book.
	reader.memberNo = rand() % 89999 + 10000;
	reader.avaiableBook = 3;

	//Saving our new member here in our readers txt file.
	outReaders << reader.idNo << endl;
	outReaders << reader.name << endl;
	outReaders << reader.lastname << endl;
	outReaders << reader.phoneNumber << endl;
	outReaders << reader.dateOfBirth << endl;
	outReaders << reader.profession << endl;
	outReaders << reader.memberNo << endl;
	outReaders << reader.avaiableBook << endl << endl;

	//closing both files.
	outReaders.close();
	inReaders.close();

	//Asking user if they want to exit library or continue library. if user pick yes library will be returned to main menu.
	string answerexit;
	do {
		cout << "Do You Want to Continue Library++? "; cin >> answerexit;
		if (answerexit == "y" || answerexit == "Y")
		{
			return;
		}
		else if (answerexit == "n" || answerexit == "N")
		{
			exitmenu();
		}
		else
		{
			cout << "Error. Try Again..." << endl << endl;
			Sleep(1500);
		}
	} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");

}
//Created "Update Reader" function. It let us make some changes about a reader.
void readerUpdate()
{
	//Opened readers input file and a temporary output file for readers.
	ifstream inReaders("readers.txt");
	ofstream tempOutReaders("tempreaders.txt", ios_base::app);

	//Created object here.
	Reader reader;
	string tempID;

	system("CLS");
	cout << "Update Reader" << endl << endl;

	cout << "Enter Reader' ID..:"; cin >> tempID;

	//Searching entered ID in our readers file until it find it.
	while (!inReaders.eof())
	{
		inReaders >> reader.idNo;
		inReaders.ignore();
		getline(inReaders, reader.name);
		inReaders >> reader.lastname;
		inReaders >> reader.phoneNumber;
		inReaders >> reader.dateOfBirth;
		inReaders >> reader.profession;
		inReaders >> reader.memberNo;
		inReaders >> reader.avaiableBook;

		if (reader.idNo == tempID) //If member exist informations about entered member will be used after this While loop.
		{
			break;
		}
		else if (inReaders.eof()) //If there is no member with entered ID, main menu will be opened.
		{
			cout << "There is No User Registered With This ID. Returning Main Menu in 3 Sec...";
			Sleep(3000);
			return;
		}
	}

	//Changing member' some informations.
	cout << "Update Reader' Profession..:"; cin >> reader.profession;
	cout << "Update Reader' Phone Number..:"; cin >> reader.phoneNumber;

	//After changes updated informations will be added in our temporary reader file.
	tempOutReaders << reader.idNo << endl;
	tempOutReaders << reader.name << endl;
	tempOutReaders << reader.lastname << endl;
	tempOutReaders << reader.phoneNumber << endl;
	tempOutReaders << reader.dateOfBirth << endl;
	tempOutReaders << reader.profession << endl;
	tempOutReaders << reader.memberNo << endl;
	tempOutReaders << reader.avaiableBook << endl << endl;
	inReaders.close();
	inReaders.open("readers.txt");

	//Searching our member which is not matched with entered ID and adding them in our temporary reader files.
	while (!inReaders.eof()) {


		inReaders >> reader.idNo;
		inReaders.ignore();
		getline(inReaders, reader.name);
		inReaders >> reader.lastname;
		inReaders >> reader.phoneNumber;
		inReaders >> reader.dateOfBirth;
		inReaders >> reader.profession;
		inReaders >> reader.memberNo;
		inReaders >> reader.avaiableBook;

		//If input file comes end loop will stop.
		if (inReaders.eof()) {
			break;
		}

		if (tempID != reader.idNo)
		{
			tempOutReaders << reader.idNo << endl;
			tempOutReaders << reader.name << endl;
			tempOutReaders << reader.lastname << endl;
			tempOutReaders << reader.phoneNumber << endl;
			tempOutReaders << reader.dateOfBirth << endl;
			tempOutReaders << reader.profession << endl;
			tempOutReaders << reader.memberNo << endl;
			tempOutReaders << reader.avaiableBook << endl << endl;

		}
	}

	tempOutReaders.close();
	inReaders.close();

	//Removing our old readers file and rename our temporary file to readers.
	remove("readers.txt");
	rename("tempreaders.txt", "readers.txt");

	//Asking user if they want to exit library or continue library.
	string answerexit;
	do {
		cout << "Do You Want to Continue Library++? "; cin >> answerexit;
		if (answerexit == "y" || answerexit == "Y")
		{
			return;
		}
		else if (answerexit == "n" || answerexit == "N")
		{
			exitmenu();
		}
		else
		{
			cout << "Error. Try Again..." << endl << endl;
			Sleep(1500);
		}
	} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");
}
//Created "Remove Reader" function. It let us remove readers from library.
void removeReader()
{
	//Opened input and temp. output file for readers.
	ifstream inReaders("readers.txt");
	ofstream tempOutReaders("tempreaders.txt", ios_base::app);

	//Used ctime here for book return time.
	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* time = ctime(&now);

	//Created objects for book and reader.
	Reader reader;
	Books book;
	string tempID, tempISBN, borrowID, borrowISBN, tempTime, tempReturn;

	system("CLS");
	cout << "Remove Reader" << endl << endl;

	cout << "Enter Reader' ID..:"; cin >> tempID;

	//Checking if there is a user with entered ID. If yes, code will proceed.
	while (!inReaders.eof())
	{
		inReaders >> reader.idNo;
		inReaders.ignore();
		getline(inReaders, reader.name);
		inReaders >> reader.lastname;
		inReaders >> reader.phoneNumber;
		inReaders >> reader.dateOfBirth;
		inReaders.ignore();
		getline(inReaders, reader.profession);
		inReaders >> reader.memberNo;
		inReaders >> reader.avaiableBook;

		if (inReaders.eof())
		{
			cout << "There is No Reader With This ID. Returning Main Menu in 3 Sec..." << endl;
			Sleep(3000);
			return;
		}

		if (reader.idNo == tempID)
		{
			inReaders.close();
			break;
		}
	}

	//If removed reader had books which he didn't return, books will be returned here.
	if (reader.avaiableBook != 3)
	{
		//Opened inputs and outputs for books and borrow records.
		ifstream inBorrow("borrow.txt");
		ifstream inBook("books.txt");
		ofstream tempOutBorrow("tempborrow.txt", ios_base::app);
		ofstream tempOutBook("tempbooks.txt", ios_base::app);

		//Created temporary ISBN holder and 2 counter.
		string tempBook[3];
		int i = 0;
		int counter = 0;

		//Updating borrow records here.
		while (!inBorrow.eof())
		{
			inBorrow >> borrowID >> borrowISBN;
			inBorrow.ignore();
			getline(inBorrow, tempTime);
			getline(inBorrow, tempReturn);

			if (inBorrow.eof())
			{
				inBorrow.close();
				break;
			}

			if (borrowID == tempID && tempReturn == "none")
			{
				tempOutBorrow << borrowID << " " << borrowISBN << endl;
				tempOutBorrow << tempTime << endl;
				tempOutBorrow << time << endl;
				tempBook[i] = borrowISBN;
				i++;
				counter++;
			}
			else
			{
				tempOutBorrow << borrowID << " " << borrowISBN << endl;
				tempOutBorrow << tempTime << endl;
				tempOutBorrow << tempReturn << endl << endl;
			}
		}

		//Updating book records here.
		while (!inBook.eof())
		{
			inBook >> book.isbn;
			inBook.ignore();
			getline(inBook, book.bookName);
			getline(inBook, book.writerName);
			inBook >> book.writerLastname;
			inBook.ignore();
			getline(inBook, book.subject);
			getline(inBook, book.type);
			inBook >> book.page;
			inBook >> book.status;

			if (inBook.eof())
			{
				break;
			}

			if (book.isbn == tempBook[0] || book.isbn == tempBook[1] || book.isbn == tempBook[2])
			{
				//Making our books available for borrow.
				book.status = '+';
				tempOutBook << book.isbn << endl;
				tempOutBook << book.bookName << endl;
				tempOutBook << book.writerName << endl;
				tempOutBook << book.writerLastname << endl;
				tempOutBook << book.subject << endl;
				tempOutBook << book.type << endl;
				tempOutBook << book.page << endl;
				tempOutBook << book.status << endl << endl;
			}
			else
			{
				tempOutBook << book.isbn << endl;
				tempOutBook << book.bookName << endl;
				tempOutBook << book.writerName << endl;
				tempOutBook << book.writerLastname << endl;
				tempOutBook << book.subject << endl;
				tempOutBook << book.type << endl;
				tempOutBook << book.page << endl;
				tempOutBook << book.status << endl << endl;
			}
		}

		//Closing all book and borrow files.
		tempOutBorrow.close();
		inBorrow.close();
		inBook.close();
		tempOutBook.close();

		//Removed old files and renamed new ones.
		remove("books.txt");
		rename("tempbooks.txt", "books.txt");
		remove("borrow.txt");
		rename("tempborrow.txt", "borrow.txt");

	}

	//Removing our entered ID here.
	inReaders.open("readers.txt");
	while (!inReaders.eof()) {

		inReaders >> reader.idNo;
		inReaders.ignore();
		getline(inReaders, reader.name);
		inReaders >> reader.lastname;
		inReaders >> reader.phoneNumber;
		inReaders >> reader.dateOfBirth;
		inReaders >> reader.profession;
		inReaders >> reader.memberNo;
		inReaders >> reader.avaiableBook;

		if (inReaders.eof())
		{
			break;
		}


		if (tempID != reader.idNo)
		{
			tempOutReaders << reader.idNo << endl;
			tempOutReaders << reader.name << endl;
			tempOutReaders << reader.lastname << endl;
			tempOutReaders << reader.phoneNumber << endl;
			tempOutReaders << reader.dateOfBirth << endl;
			tempOutReaders << reader.profession << endl;
			tempOutReaders << reader.memberNo << endl;
			tempOutReaders << reader.avaiableBook << endl << endl;

		}
	}



	//Closed reader files.
	tempOutReaders.close();
	inReaders.close();

	//Removed and renamed files.
	remove("readers.txt");
	rename("tempreaders.txt", "readers.txt");

	cout << "Reader Successfully Removed." << endl << endl;

	//Asking user if they want to exit library or continue library.
	string answerexit;
	do {
		cout << "Do You Want to Continue Library++? "; cin >> answerexit;
		if (answerexit == "y" || answerexit == "Y")
		{
			return;
		}
		else if (answerexit == "n" || answerexit == "N")
		{
			exitmenu();
		}
		else
		{
			cout << "Error. Try Again..." << endl << endl;
			Sleep(1500);
		}
	} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");
}
//Created "Add Book" function. It let us add books for our library.
void addBook()
{
	//Opened input and output files for books.
	ofstream outBook("books.txt", ios_base::app);
	ifstream inBook("books.txt");

	Books book;

	system("CLS");
	cout << "Add Book" << endl << endl;

	cin.ignore();
	cout << "Enter Book ISBN..:"; getline(cin, book.isbn);
	cout << "Enter Book Name..:"; getline(cin, book.bookName);
	cout << "Enter Writer Name..:"; getline(cin, book.writerName);
	cout << "Enter Writer Lastname..:"; getline(cin, book.writerLastname);
	cout << "Enter Subject of Book..:"; getline(cin, book.subject);
	cout << "Enter Type of Book..:"; getline(cin, book.type);
	cout << "Enter Number of Pages..:"; cin >> book.page; cin.ignore();

	string tempValue;
	string trash;

	//Checking here if ISBN was registered before.
	while (!inBook.eof())
	{
		inBook >> tempValue;
		getline(inBook, trash);
		getline(inBook, trash);
		inBook >> trash;
		inBook >> trash;
		inBook >> trash;
		inBook >> trash;
		inBook >> trash;
		if (tempValue == book.isbn)
		{
			cout << "ISBN had been registered before. Returning Main Menu in 3 Sec.";
			Sleep(3000);
			system("CLS");
			outBook.close();
			inBook.close();
			return;
		}
	}
	//Made our book status available.
	book.status = '+';

	//Added book informations.
	outBook << book.isbn << endl;
	outBook << book.bookName << endl;
	outBook << book.writerName << endl;
	outBook << book.writerLastname << endl;
	outBook << book.subject << endl;
	outBook << book.type << endl;
	outBook << book.page << endl;
	outBook << book.status << endl << endl;

	//Closed files.
	outBook.close();
	inBook.close();

	//Asking user if they want to exit library or continue library.
	string answerexit;
	do {
		cout << "Do You Want to Continue Library++? "; cin >> answerexit;
		if (answerexit == "y" || answerexit == "Y")
		{
			return;
		}
		else if (answerexit == "n" || answerexit == "N")
		{
			exitmenu();
		}
		else
		{
			cout << "Error. Try Again..." << endl << endl;
			Sleep(1500);
		}
	} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");

}
//Created "Remove Book" function. It let us remove books from library.
void removeBook()
{
	//Opened book input file. Opened temporary book output file.
	ifstream inBook("books.txt");
	ofstream tempOutBook("tempbooks.txt", ios_base::app);

	//Created book object
	Books book;
	string tempIsbn;

	system("CLS");
	cout << "Remove Book" << endl << endl;

	cout << "Please Enter Book ISBN..:"; cin >> tempIsbn;

	//Checking and removing book here.
	while (!inBook.eof())
	{
		inBook >> book.isbn;
		inBook.ignore();
		getline(inBook, book.bookName);
		getline(inBook, book.writerName);
		inBook >> book.writerLastname;
		inBook.ignore();
		getline(inBook, book.subject);
		getline(inBook, book.type);
		inBook >> book.page;
		inBook >> book.status;

		if (inBook.eof())
		{
			break;
		}

		if (tempIsbn != book.isbn)
		{
			tempOutBook << book.isbn << endl;
			tempOutBook << book.bookName << endl;
			tempOutBook << book.writerName << endl;
			tempOutBook << book.writerLastname << endl;
			tempOutBook << book.subject << endl;
			tempOutBook << book.type << endl;
			tempOutBook << book.page << endl;
			tempOutBook << book.status << endl << endl;
		}
	}

	//Closed files.
	tempOutBook.close();
	inBook.close();

	//Removed and renamed files.
	remove("books.txt");
	rename("tempbooks.txt", "books.txt");

	//Asking user if they want to exit library or continue library.
	string answerexit;
	do {
		cout << "Do You Want to Continue Library++? "; cin >> answerexit;
		if (answerexit == "y" || answerexit == "Y")
		{
			return;
		}
		else if (answerexit == "n" || answerexit == "N")
		{
			exitmenu();
		}
		else
		{
			cout << "Error. Try Again..." << endl << endl;
			Sleep(1500);
		}
	} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");
}
//Created "Update Book" function. It let us make changes about book.
void updateBook()
{
	//Opened input file for book and output file for temporary book.
	ifstream inBook("books.txt");
	ofstream tempOutBook("tempbooks.txt", ios_base::app);

	//Created book object.
	Books book;
	string tempIsbn;

	system("CLS");
	cout << "Update Book" << endl << endl;

	cout << "Please Enter Book ISBN..:"; cin >> tempIsbn;
	cin.ignore();

	//Searching book whose ISBN was entered.
	do
	{
		inBook >> book.isbn;
		inBook.ignore();
		getline(inBook, book.bookName);
		getline(inBook, book.writerName);
		inBook >> book.writerLastname;
		inBook.ignore();
		getline(inBook, book.subject);
		getline(inBook, book.type);
		inBook >> book.page;
		inBook >> book.status;

	} while (tempIsbn != book.isbn);

	//Updating informations
	cout << "Update Book Name..:"; getline(cin, book.bookName);
	cout << "Update Writer Name..:"; getline(cin, book.writerName);
	cout << "Update Writer Lastname..:"; getline(cin, book.writerLastname);
	cout << "Update Subject of Book..:"; getline(cin, book.subject);
	cout << "Update Type of Book..:"; getline(cin, book.type);
	cout << "Update Number of Pages..:"; cin >> book.page; cin.ignore();

	//Added new book informations in our temp book file.
	tempOutBook << book.isbn << endl;
	tempOutBook << book.bookName << endl;
	tempOutBook << book.writerName << endl;
	tempOutBook << book.writerLastname << endl;
	tempOutBook << book.subject << endl;
	tempOutBook << book.type << endl;
	tempOutBook << book.page << endl;
	tempOutBook << book.status << endl << endl;

	//Closed and opened again for scan books from the start.
	inBook.close();
	inBook.open("books.txt");

	//Adding books which is not updated to our temp book file.
	while (!inBook.eof())
	{
		inBook >> book.isbn;
		inBook.ignore();
		getline(inBook, book.bookName);
		getline(inBook, book.writerName);
		inBook >> book.writerLastname;
		inBook.ignore();
		getline(inBook, book.subject);
		getline(inBook, book.type);
		inBook >> book.page;
		inBook >> book.status;

		if (inBook.eof())
		{
			break;
		}

		if (tempIsbn != book.isbn)
		{
			tempOutBook << book.isbn << endl;
			tempOutBook << book.bookName << endl;
			tempOutBook << book.writerName << endl;
			tempOutBook << book.writerLastname << endl;
			tempOutBook << book.subject << endl;
			tempOutBook << book.type << endl;
			tempOutBook << book.page << endl;
			tempOutBook << book.status << endl << endl;
		}
	}

	//Files closed.
	tempOutBook.close();
	inBook.close();

	//Files removed and renamed.
	remove("books.txt");
	rename("tempbooks.txt", "books.txt");

	//Asking user if they want to exit library or continue library.
	string answerexit;
	do {
		cout << "Do You Want to Continue Library++? "; cin >> answerexit;
		if (answerexit == "y" || answerexit == "Y")
		{
			return;
		}
		else if (answerexit == "n" || answerexit == "N")
		{
			exitmenu();
		}
		else
		{
			cout << "Error. Try Again..." << endl << endl;
			Sleep(1500);
		}
	} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");
}
//Created "Reader Books" function. I let us see a readers books which they borrowed.
void readerBooks()
{
	//Opened input files for books and borrow records.
	ifstream inBook("books.txt");
	ifstream inBorrow("borrow.txt");
	string tempID, borrowID, borrowISBN, tempTime1, tempTime2;
	int counter = 1; //Added counter for list.

	system("CLS");
	cout << "List Books of a Reader" << endl << endl;

	cout << "Please Enter User ID..:"; cin >> tempID;
	cout << endl;

	//Searching books here.
	while (!inBorrow.eof())
	{
		inBorrow >> borrowID >> borrowISBN;
		inBorrow.ignore();
		getline(inBorrow, tempTime1);
		getline(inBorrow, tempTime2);



		//If user doesn't have any book counter will be stay on 1 and main menu will be opened.
		if (inBorrow.eof() && counter == 1)
		{
			cout << "Reader Doesn't Have Any Book. Returning Main Menu in 3 Sec...";
			Sleep(3000);
			inBorrow.close();
			inBook.close();
			return;
		}
		else if (inBorrow.eof() && counter > 1) //If user have books this exit command will be started at the end.
		{
			string answerexit;
			do {
				cout << "Do You Want to Continue Library++? "; cin >> answerexit;
				if (answerexit == "y" || answerexit == "Y")
				{
					return;
				}
				else if (answerexit == "n" || answerexit == "N")
				{
					exitmenu();
				}
				else
				{
					cout << "Error. Try Again..." << endl << endl;
					Sleep(1500);
				}
			} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");
		}
		else if (counter == 4) //If user reach top of counter this exit command will be started at the end.
		{
			string answerexit;
			do {
				cout << "Do You Want to Continue Library++? "; cin >> answerexit;
				if (answerexit == "y" || answerexit == "Y")
				{
					return;
				}
				else if (answerexit == "n" || answerexit == "N")
				{
					exitmenu();
				}
				else
				{
					cout << "Error. Try Again..." << endl << endl;
					Sleep(1500);
				}
			} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");
		}
		else if (tempID == borrowID && tempTime2 == "none") //It is book listing command.
		{
			Books book;
			string trash;

			//Searching book names with ISBN which we get from borrow records.
			while (!inBook.eof())
			{
				//Book file was closed before. Opened again.
				if (1 < counter)
				{
					inBook.open("books.txt");
				}

				//Used variable named "trash". We don't need them.
				inBook >> book.isbn;
				inBook.ignore();
				getline(inBook, book.bookName);
				inBook >> trash;
				inBook >> trash;
				inBook >> trash;
				inBook >> trash;
				inBook >> trash;
				inBook >> trash;

				if (inBook.eof())
				{
					break;
				}

				//Listing book here with borrow date. Increased counter each loop for listing correct.
				if (borrowISBN == book.isbn)
				{
					cout << counter << ". " << book.bookName << " || " << tempTime1 << endl << endl;
					counter++;
					inBook.close();
					break;
				}
			}
		}
	}

}
//Created "Borrow Book" function. It let us borrow book for reader.
void borrowBook()
{
	//Used ctime for borrow date.
	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* time = ctime(&now);

	//Opened reader and book input files.
	ifstream inReaders("readers.txt");
	ifstream inBook("books.txt");

	//Created objects for book and reader.
	Books book;
	Reader reader;

	string tempID, tempIsbn;
	char answer1;

	system("CLS");
	cout << "Borrow Book for a Reader" << endl << endl;

	cout << "Please Enter Your ID..:"; cin >> tempID;

	//Checking reader ID here. If there isn't member with this ID, main menu will be opened. Or if reader borrowed 3 book, main menu will be opened here too.
	while (!inReaders.eof())
	{
		inReaders >> reader.idNo;
		inReaders.ignore();
		getline(inReaders, reader.name);
		inReaders >> reader.lastname;
		inReaders >> reader.phoneNumber;
		inReaders >> reader.dateOfBirth;
		inReaders >> reader.profession;
		inReaders >> reader.memberNo;
		inReaders >> reader.avaiableBook;

		//If reader exist and can borrow a book there will be started.
		if (reader.idNo == tempID && 0 < reader.avaiableBook)
		{
			//Checking ISBN there.
			cout << "Enter Book ISBN..:"; cin >> tempIsbn;
			while (!inBook.eof())
			{
				inBook >> book.isbn; inBook.ignore();
				getline(inBook, book.bookName);
				getline(inBook, book.writerName);
				inBook >> book.writerLastname;
				inBook >> book.subject;
				inBook >> book.type;
				inBook >> book.page;
				inBook >> book.status;

				//If there is a book with this ISBN and it is available there will be started.
				if (tempIsbn == book.isbn && book.status == '+')
				{
					//Asks user if they want to borrow it.
					do {
						cout << "Are You Sure You Want to Borrow It?..Y/N..:"; cin >> answer1;
						//If user answer positively there will be started.
						if (answer1 == 'y' || answer1 == 'Y')
						{
							//Reader' amount of available book will be decreased. Book' status will be "Busy".
							reader.avaiableBook--;
							book.status = '-';

							//Opened temp. output files for book and reader. Opened borrow records output file.
							ofstream tempOutBook("tempbooks.txt", ios_base::app);
							ofstream tempOutReaders("tempreaders.txt", ios_base::app);
							ofstream outBorrow("borrow.txt", ios_base::app);

							//Added borrow records. Return date is "none".
							outBorrow << reader.idNo << " " << book.isbn << endl;
							outBorrow << time;
							outBorrow << "none" << endl << endl;

							//Closed readers and borrow files. Opened readers again.
							outBorrow.close();
							inReaders.close();
							inReaders.open("readers.txt");

							//Adding reader' informations who borrowed book.
							{tempOutReaders << reader.idNo << endl;
							tempOutReaders << reader.name << endl;
							tempOutReaders << reader.lastname << endl;
							tempOutReaders << reader.phoneNumber << endl;
							tempOutReaders << reader.dateOfBirth << endl;
							tempOutReaders << reader.profession << endl;
							tempOutReaders << reader.memberNo << endl;
							tempOutReaders << reader.avaiableBook << endl << endl;

							//Adding rest of readers' informations to temp file.
							while (!inReaders.eof()) {

								inReaders >> reader.idNo;
								inReaders >> reader.name;
								inReaders >> reader.lastname;
								inReaders >> reader.phoneNumber;
								inReaders >> reader.dateOfBirth;
								inReaders >> reader.profession;
								inReaders >> reader.memberNo;
								inReaders >> reader.avaiableBook;

								if (inReaders.eof()) {
									break;
								}

								if (tempID != reader.idNo)
								{
									tempOutReaders << reader.idNo << endl;
									tempOutReaders << reader.name << endl;
									tempOutReaders << reader.lastname << endl;
									tempOutReaders << reader.phoneNumber << endl;
									tempOutReaders << reader.dateOfBirth << endl;
									tempOutReaders << reader.profession << endl;
									tempOutReaders << reader.memberNo << endl;
									tempOutReaders << reader.avaiableBook << endl << endl;

								}
							}
							//Reader files closed.
							tempOutReaders.close();
							inReaders.close();

							//Files removed and renamed.
							remove("readers.txt");
							rename("tempreaders.txt", "readers.txt");
							}

							//Book file closed and opened.
							inBook.close();
							inBook.open("books.txt");

							//Adding book' information which is borrowed.
							{tempOutBook << book.isbn << endl;
							tempOutBook << book.bookName << endl;
							tempOutBook << book.writerName << endl;
							tempOutBook << book.writerLastname << endl;
							tempOutBook << book.subject << endl;
							tempOutBook << book.type << endl;
							tempOutBook << book.page << endl;
							tempOutBook << book.status << endl << endl;

							//Adding rest of books' informations to temp file.
							while (!inBook.eof())
							{
								inBook >> book.isbn; inBook.ignore();
								getline(inBook, book.bookName);
								getline(inBook, book.writerName);
								inBook >> book.writerLastname;
								inBook >> book.subject;
								inBook >> book.type;
								inBook >> book.page;
								inBook >> book.status;

								if (inBook.eof())
								{
									break;
								}

								if (tempIsbn != book.isbn)
								{
									tempOutBook << book.isbn << endl;
									tempOutBook << book.bookName << endl;
									tempOutBook << book.writerName << endl;
									tempOutBook << book.writerLastname << endl;
									tempOutBook << book.subject << endl;
									tempOutBook << book.type << endl;
									tempOutBook << book.page << endl;
									tempOutBook << book.status << endl << endl;
								}
							}
							//Book files closed.
							tempOutBook.close();
							inBook.close();

							//Files removed and renamed.
							remove("books.txt");
							rename("tempbooks.txt", "books.txt");
							}

							//Asking user if they want to exit library or continue library.
							string answerexit;
							do {
								cout << "Do You Want to Continue Library++? "; cin >> answerexit;
								if (answerexit == "y" || answerexit == "Y")
								{
									return;
								}
								else if (answerexit == "n" || answerexit == "N")
								{
									exitmenu();
								}
								else
								{
									cout << "Error. Try Again..." << endl << endl;
									Sleep(1500);
								}
							} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");
						}
						else if (answer1 == 'n' || answer1 == 'N') //If user answer no main menu will be started.
						{
							cout << "Returning Main Menu in 3 Sec...";
							Sleep(3000);
							return;
						}
						else //If user answer wrong question will repeat itself.
						{
							cout << "Wrong Answer..." << endl << endl;
							Sleep(1500);
						}
					} while (answer1 != 'n' || answer1 != 'N' || answer1 != 'y' || answer1 != 'Y');

				}
				else if (tempIsbn == book.isbn && book.status == '-') //If book is not available right now there will be started.
				{
					cout << "The Book You Looking For Not Avaiable Right Now. Returning Main Menu in 3 Sec...";
					Sleep(3000);
					return;
				}
				else if (inBook.eof()) //If there is no book with this ISBN there will be started.
				{
					cout << "There is No Book Registered With This ISBN. Returning Main Menu in 3 Sec...";
					Sleep(3000);
					return;
				}

			}


		}
		else if (reader.idNo == tempID && reader.avaiableBook == 0) //If reader cant borrow a book, there will be started.
		{
			cout << "You Can't Borrow a Book Right Now. Returning Main Menu in 3 Sec...";
			Sleep(3000);
			return;
		}
		else if (inReaders.eof()) //If there is no reader with this ID there will be started.
		{
			cout << "There is No One With This ID. Returning Main Menu in 3 Sec...";
			Sleep(3000);
			return;
		}
	}

}
//Created "Bring Book" function. It let us return book from reader.
void bringBook()
{
	//Used ctime for return time.
	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* time = ctime(&now);

	//Opened input files for books, readers and borrow records.
	ifstream inReaders("readers.txt");
	ifstream inBook("books.txt");
	ifstream inBorrow("borrow.txt");

	//Created objects for book and reader.
	Books book;
	Reader reader;

	string tempID, tempIsbn, tempTime, tempReturn;
	string borrowID, borrowISBN;
	char answer1;
	bool cont = false; //Created bool variable for proceed.
	bool isbncheck = false; //Bool for ISBN checker.

	system("CLS");
	cout << "Bring Book Back From a Reader" << endl << endl;

	cout << "Please Enter Your ID..:"; cin >> tempID;

	//Searching reader here.
	while (!inReaders.eof())
	{
		inReaders >> reader.idNo;
		inReaders.ignore();
		getline(inReaders, reader.name);
		inReaders >> reader.lastname;
		inReaders >> reader.phoneNumber;
		inReaders >> reader.dateOfBirth;
		inReaders.ignore();
		getline(inReaders, reader.profession);
		inReaders >> reader.memberNo;
		inReaders >> reader.avaiableBook;

		//If reader exist and have books there will be started.
		if (reader.idNo == tempID && reader.avaiableBook < 3)
		{
			cout << "Enter ISBN of Book You Returned..: "; cin >> tempIsbn;

			//Checking borrow records here.
			while (!inBorrow.eof())
			{
				inBorrow >> borrowID >> borrowISBN;
				inBorrow.ignore();
				getline(inBorrow, tempTime);
				getline(inBorrow, tempReturn);

				//If entered ISBN is incorrect, main menu will be opened.
				if (inBorrow.eof())
				{
					if (!isbncheck) {
						cout << "Reader Doesn't Have This Book. ";
					}
					break;
				}

				//If reader have the book there will be started.
				if (tempID == borrowID && tempIsbn == borrowISBN)
				{
					//Used ISBN check bool here to don't get false message.
					isbncheck = true;
					//Asking user if they want to return it back.
					do {
						cout << "Are You Sure You Want to Return it Back?"; cin >> answer1;
						if (answer1 == 'Y' || answer1 == 'y')
						{
							inBorrow.close();
							cont = true; //Proceed bool is true here.
							inReaders.close();
							break;
						}
						else if (answer1 == 'N' || answer1 == 'n')
						{
							inBorrow.close();
							cont = false; //Proceed bool is false here.
							break;
						}
						else
						{
							cout << "Error. Try Again...." << endl << endl;
						}
					} while (answer1 != 'Y' || answer1 != 'y' || answer1 != 'n' || answer1 != 'N');
				}
			}

			//If proceed bool is true there will be started.
			if (cont == true)
			{
				//Opened temp output files.
				ofstream tempOutBook("tempbooks.txt", ios_base::app);
				ofstream tempOutReaders("tempreaders.txt", ios_base::app);
				ofstream tempOutBorrow("tempborrow.txt", ios_base::app);
				inBorrow.open("borrow.txt");

				//Updating borrow records here.
				while (!inBorrow.eof())
				{
					inBorrow >> borrowID >> borrowISBN;
					inBorrow.ignore();
					getline(inBorrow, tempTime);
					getline(inBorrow, tempReturn);

					if (inBorrow.eof())break;

					if (tempID == borrowID && tempIsbn == borrowISBN)
					{
						tempOutBorrow << borrowID << " " << borrowISBN << endl;
						tempOutBorrow << tempTime << endl;
						tempOutBorrow << time << endl; //"time" is current time. (from ctime)
					}
					else
					{
						tempOutBorrow << borrowID << " " << borrowISBN << endl;
						tempOutBorrow << tempTime << endl;
						tempOutBorrow << tempReturn << endl << endl;
					}
				}

				//Files closed
				tempOutBorrow.close();
				inBorrow.close();

				//Files removed and renamed.
				remove("borrow.txt");
				rename("tempborrow.txt", "borrow.txt");

				//Updating readers here.
				inReaders.open("readers.txt");
				while (!inReaders.eof())
				{
					inReaders >> reader.idNo;
					inReaders.ignore();
					getline(inReaders, reader.name);
					inReaders >> reader.lastname;
					inReaders >> reader.phoneNumber;
					inReaders >> reader.dateOfBirth;
					inReaders.ignore();
					getline(inReaders, reader.profession);
					inReaders >> reader.memberNo;
					inReaders >> reader.avaiableBook;

					if (inReaders.eof()) {
						break;
					}

					//Reader who returned book is updated here.
					if (tempID == reader.idNo)
					{
						//Book available value increased.
						reader.avaiableBook++;
						tempOutReaders << reader.idNo << endl;
						tempOutReaders << reader.name << endl;
						tempOutReaders << reader.lastname << endl;
						tempOutReaders << reader.phoneNumber << endl;
						tempOutReaders << reader.dateOfBirth << endl;
						tempOutReaders << reader.profession << endl;
						tempOutReaders << reader.memberNo << endl;
						tempOutReaders << reader.avaiableBook << endl << endl;
					}
					else //Readers who isn't book returner updated here.
					{
						tempOutReaders << reader.idNo << endl;
						tempOutReaders << reader.name << endl;
						tempOutReaders << reader.lastname << endl;
						tempOutReaders << reader.phoneNumber << endl;
						tempOutReaders << reader.dateOfBirth << endl;
						tempOutReaders << reader.profession << endl;
						tempOutReaders << reader.memberNo << endl;
						tempOutReaders << reader.avaiableBook << endl << endl;
					}
				}
				//Files closed.
				inReaders.close();
				tempOutReaders.close();

				//Files removed and renamed.
				remove("readers.txt");
				rename("tempreaders.txt", "readers.txt");

				//Updating books here.
				while (!inBook.eof())
				{
					inBook >> book.isbn;
					inBook.ignore();
					getline(inBook, book.bookName);
					getline(inBook, book.writerName);
					inBook >> book.writerLastname;
					inBook.ignore();
					getline(inBook, book.subject);
					getline(inBook, book.type);
					inBook >> book.page;
					inBook >> book.status;

					if (inBook.eof())
					{
						break;
					}

					//Book which is returned is updated here.
					if (tempIsbn == book.isbn)
					{
						//Book status is "available" here.
						book.status = '+';
						tempOutBook << book.isbn << endl;
						tempOutBook << book.bookName << endl;
						tempOutBook << book.writerName << endl;
						tempOutBook << book.writerLastname << endl;
						tempOutBook << book.subject << endl;
						tempOutBook << book.type << endl;
						tempOutBook << book.page << endl;
						tempOutBook << book.status << endl << endl;
					}
					else //Books which isn't returned right now updated here.
					{
						tempOutBook << book.isbn << endl;
						tempOutBook << book.bookName << endl;
						tempOutBook << book.writerName << endl;
						tempOutBook << book.writerLastname << endl;
						tempOutBook << book.subject << endl;
						tempOutBook << book.type << endl;
						tempOutBook << book.page << endl;
						tempOutBook << book.status << endl << endl;
					}
				}
				//Files closed.
				inBook.close();
				tempOutBook.close();

				//Files removed and renamed.
				remove("books.txt");
				rename("tempbooks.txt", "books.txt");

				cout << endl << "Book Successfully Returned." << endl << endl;
			}
			else if (cont == false) //If proceed bool is false main menu will be opened.
			{
				cout << "Returning Main Menu in 3 Sec..." << endl;
				Sleep(3000);
				return;
			}

			//Asking user if they want to exit library or continue library.
			string answerexit;
			do {
				cout << "Do You Want to Continue Library++? "; cin >> answerexit;
				if (answerexit == "y" || answerexit == "Y")
				{
					return;
				}
				else if (answerexit == "n" || answerexit == "N")
				{
					exitmenu();
				}
				else
				{
					cout << "Error. Try Again..." << endl << endl;
					Sleep(1500);
				}
			} while (answerexit != "Y" || answerexit != "y" || answerexit != "N" || answerexit != "n");


		}
		else if (reader.idNo == tempID && reader.avaiableBook == 3) //If reader exist but have no book, main menu will be opened.
		{
			cout << "The Reader Doesn't Have Any Book. Returning Main Menu in 3 Sec...";
			Sleep(3000);
			return;
		}
		else if (inReaders.eof())  //If there is no reader with this ID, main menu will be opened.
		{
			cout << "There is No User With This ID. Returning Main Menu in 3 Sec...";
			Sleep(3000);
			return;
		}
	}
}
//Created "Exit" function. It let us exit from library.
void exitmenu()
{
	//Used ctime for logout time.
	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* time = ctime(&now);
	string answer;

	system("CLS");
	cout << "Exit" << endl << endl;

	//Asking user if they want to exit library or continue library.
	do {
		cout << endl << "Are You Sure You Want to Exit? Y/N "; cin >> answer;

		//If user answer positively library will successfully stop.
		if (answer == "Y" || answer == "y")
		{
			cout << endl << "User Successfully Logged Out..." << endl << endl;
			cout << "Log Out Time..: " << time;
			exit(1);
		}
		else if (answer == "N" || answer == "n") //If user answer negatively main menu will be opened.
		{
			cout << "Returning Main Menu in 3 Sec...";
			Sleep(3000);
			return;
		}
		else //If user answer incorrect question will be asked again.
		{
			cout << "Error. Try Again in 3 Sec...";
			Sleep(3000);
			cout << endl;
			continue;
		}
	} while (answer != "Y" && answer != "y" && answer != "n" && answer != "N");

}
//Used "Go To XY" function. Used it for counter in login screen.
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}