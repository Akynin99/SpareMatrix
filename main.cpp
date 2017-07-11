

#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>

using namespace std;


int main()
{
	
	int testChoice = 1;
	while (testChoice)
	{
		cout << "What do you want to test?" << endl << " (1 - Spare Matrix, 2 - Dynamic Array, 0 - Exit) " << endl;
		cin >> testChoice;
		if (testChoice == 1)
		{
			UserInterface Alpha;
			Alpha.GoInterface_Matrix(); // запускаем интерфейс проверки матрицы
		}
		if (testChoice == 2)
		{
			UserInterface Betta;
			Betta.GoInterface_Array(); // запускаем интерфейс проверки массива
		}

		


	}


	system("pause");
	return 0;
}

