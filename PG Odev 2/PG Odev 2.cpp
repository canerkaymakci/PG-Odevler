#include <iostream>
#include <Windows.h>
#include <cstdlib>

using namespace std;

//Created our set cursor function.
void GoToXY(int x, int y);

//Created our "Roof" class.
class Roof
{
	//Set our variables in private.
private:
	int width;
	int height;
	char symbol;
	int x, y;
	int baseHeight;

	//Set our functions in public.
public:

	//Constructor of "Roof". Set values here.
	Roof(int hght, int wdth, int xcoord, int ycoord, int baseHght)
	{
		height = hght;
		width = wdth;
		x = xcoord;
		y = ycoord;
		symbol = '*';
		baseHeight = baseHght;
	}

	//Default Constructor of "Roof".
	Roof()
	{
		height = 0;
		width = 0;
		symbol = '/';
	}

	//Set cursor function.
	void GoToXY(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	//Symbol Changer of "Roof".
	void changeSymbol()
	{
		cout << "Enter New Symbol for Roof..:"; cin >> symbol;
	}

	//Draw Function of "Roof".
	void DrawRoof()
	{
		//Loop for each line.
		for (int i = 0; i < height; i++)
		{
			//Loop for each "Symbol" for a line.
			for (int j = x + i; j < x + width - i; j++)
			{
				GoToXY(j - 1, y - baseHeight - 1 - i);
				cout << symbol;
			}
		}
	}
};

//Created our "Base" class.
class Base
{
	//Set our variables in private.
private:
	int height;
	int width;
	char symbol;
	int x, y;

	//Set our functions in public.
public:

	//Constructor of "Base".
	Base(int hght, int wdth, int xcoord, int ycoord)
	{
		height = hght;
		width = wdth;
		x = xcoord;
		y = ycoord;
		symbol = 219;
	}

	//Default constructor of "Base".
	Base()
	{
		height = 0;
		width = 0;
		symbol = '/';
	}

	//Set cursor function.
	void GoToXY(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	//Get Height function for later time usage on our project.
	int GetHeight()
	{
		return height;
	}

	//Get Y function for end of the project.
	int GetY()
	{
		return y;
	}

	//Symbol Changer of "Base".
	void changeSymbol()
	{
		cout << "Enter New Symbol for Base..:"; cin >> this->symbol;
	}

	//Draw function of "Base".
	void DrawBase()
	{
		//Draw loop for top of "Base".
		for (int i = x; i < x + width - 1; i++)
		{
			GoToXY(i - 1, y - height);
			cout << symbol;
		}

		//Draw loop for right side of "Base".
		for (int i = y - height; i < y; i++)
		{
			GoToXY(x + width - 2, i);
			cout << symbol;
		}

		//Draw loop for bottom of "Base".
		for (int i = x + width; x < i; i--)
		{
			GoToXY(i - 2, y - 1);
			cout << symbol;
		}

		//Draw loop for left side of "Base".
		for (int i = y - height; i < y; i++)
		{
			GoToXY(x - 1, i);
			cout << symbol;
		}
	}
};

//Created our "Door" class.
class Door
{
	//Set our variables in private.
private:
	int height;
	int width;
	char symbol = '$';
	int x, y;
	int baseWidth;

	//Set our functions in public.
public:

	//Constructor of "Door".
	Door(int xcoord, int ycoord, int baseWdth)
	{
		x = xcoord;
		y = ycoord;
		symbol = '#';
		baseWidth = baseWdth;
	}

	//Default constructor of "Door".
	Door()
	{
		x = 0;
		y = 0;
	}

	//Symbol Changer of "Door".
	void changeSymbol()
	{
		cout << "Enter New Symbol for Door..:"; cin >> symbol;
	}

	//Set "Door" height and width values here.
	void setValues(int x, int y)
	{
		this->height = y;
		this->width = x;
	}

	//Set cursor function.
	void GoToXY(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	//Draw function of "Door".
	void DrawDoor()
	{
		//Used random values for random X spawn point.
		srand(time(0));
		int line = rand() % (baseWidth - 3 - width) + (x + 2);

		//Loop for each line.
		for (int i = height; 0 < i; i--)
		{
			//Loop for each "Symbol" for a line.
			for (int j = 0; j < width; j++)
			{
				GoToXY(line + j, y - i);
				cout << symbol;
			}
		}
	}

};

//Created our main "House" class.
class House
{
	//Set our objects in private.
private:
	Roof roof;
	Base base;
	Door door;

	//Set our functions in public.
public:

	//Call function for all Symbol Changer functions.
	void setSymbols()
	{
		roof.changeSymbol();
		base.changeSymbol();
		door.changeSymbol();
	}

	//Set "Door" height and width function. Used our GetHeight function i mentioned before here.
	void doorValue()
	{
		int x, y, hght = base.GetHeight();
		if (hght == 10)
		{
			y = 5;
		}
		else if (hght == 20)
		{
			y = 7;
		}
		else
		{
			y = 6;
		}
		x = y + 2;

		//Used our "Door" Set Value function here.
		door.setValues(x, y);
	}

	//Call function for all "Draw" functions. Cleans console before work.
	void DrawHouse()
	{
		system("CLS");
		roof.DrawRoof();
		base.DrawBase();
		door.DrawDoor();
	}

	//Used Get Y function here too for end of our project.
	int GetY()
	{
		return base.GetY();
	}

	//Control function for valid or invalid input values.
	void Controlling(int temp1, int temp2, int temp3)
	{
		//"Base" height controller.
		if (temp1 < 10 || 20 < temp1)
		{
			cout << "Invalid Values. Please Try Again.";
			Sleep(1000);
			system("CLS");

			//Starts project from the start.
			Draw();
		}
		//"Base" width controller.
		else if (temp2 < 30 || 60 < temp2)
		{
			cout << "Invalid Values. Please Try Again.";
			Sleep(1000);
			system("CLS");

			//Starts project from the start.
			Draw();
		}
		//"Roof" Height controller.
		else if (temp3 < 5 || 10 < temp3)
		{
			cout << "Invalid Values. Please Try Again.";
			Sleep(1000);
			system("CLS");

			//Starts project from the start.
			Draw();
		}

	}

	//Informs user about default Symbols of each class. Asks user if they want to change symbols.
	void SymbolChange()
	{
		char temp = 219;
		char answer;
		cout << "Symbols of Roof, Base and Door has been set to '*' , '" << temp << "' and '#' as default. Would you like to change it? Y/N "; cin >> answer;

		//Answer checker. If it's true there will be worked.
		if (answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N')
		{
			//Used switch for answer.
			switch (answer)
			{
				//Case for positive answer.
			case 'y':
				setSymbols();
				break;
				//Case for positive answer.
			case 'Y':
				setSymbols();
				break;
				//Case for negative answer.
			case 'n':
				break;
				//Case for negative answer.
			case 'N':
				break;
			}
		}
		//If answer is invalid there will be worked.
		else
		{
			cout << "Wrong answer..." << endl << endl;
			//Used our Symbol Changer here.
			SymbolChange();
		}
	}

	//Created a function to use in main code block.
	void Draw()
	{
		//Asks user to get values of each temporary variables and (x,y) coords.
		int tempWidth, tempHeigh, tempRoof, x, y;
		cout << "Enter Base Height Between 10-20..: "; cin >> tempHeigh;
		cout << "Enter Base Width Between 30-60..: "; cin >> tempWidth;
		cout << "Enter Roof Height Between 5-10..: "; cin >> tempRoof;
		cout << endl;

		//Used our Control function.
		Controlling(tempHeigh, tempWidth, tempRoof);

		//Asked for X and Y spawn location. If locations are invalid commands will ask user for coords again.
		cout << "Enter X and Y Spawn Location." << endl;
		cout << "House Draw Function will be start from bottom left of house." << endl;
		cout << "Y location must be higher than (Roof Height + Base Height)..: "; cin >> x >> y; cout << endl;
		//First controller of x and y.
		if (y <= tempRoof + tempHeigh)
		{
			cout << "Invalid Y Value. Please Enter Valid Values of X and Y..:";

			//Secont controller of x and y. This is loop.
			while (y <= tempRoof + tempHeigh)
			{
				cin >> x >> y;
				cout << endl;
				if (y <= tempRoof + tempHeigh) {
					cout << "Invalid Y Value. Please Enter Valid Values of X and Y..:";
				}
			}
		}


		//Used constructors here for set each object' values in "House" class.
		roof = Roof(tempRoof, tempWidth, x, y, tempHeigh);
		base = Base(tempHeigh, tempWidth, x, y);
		door = Door(x, y, tempWidth);

		//Used "Door" width and height set value function here.
		doorValue();

		//Asked user if they want to change symbols of each class.
		SymbolChange();

		//Called our all function of "Draw" here.
		DrawHouse();

		//Used here Get Y to write console' Debug writings bottom of our project.
		int end = GetY();
		GoToXY(30, end + 2);
	}

};


int main()
{

	//Created an object for "House" class.
	House home;

	//Called our main code block of "House" class to draw our house.
	home.Draw();

}

//Set cursor function.
void GoToXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}