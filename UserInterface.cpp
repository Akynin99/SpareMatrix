#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>

/*
* конструктор без параметров
*/
UserInterface::UserInterface()
{
	
}

/*
* функция запускает интерфейс проверки матриц в консоли
*/
void UserInterface::GoInterface_Matrix()
{
	bool exit = false;
	RefreshMatrix();
	for(;;)
	{
		int choice = Menu_Matrix(); //переменная выбора пользователя
		switch (choice)
		{
		case (12):
			RefreshMatrix();
			break;
		case(1):
			TestAdd();
			break;
		case(2):
			TestSub();
			break;
		case(3):
			TestMult2();
			break;
		case(4):
			TestMult();
			break;
		case(5):
			TestIncr();
			break;
		case(6):
			TestDecr();
			break;
		case(7):
			TestEqual();
			break;
		case(8):
			TestIndex();
			break;
		case(9):
			ChangeElem();
			break;
		case(10):
			ShowMatrix();
			break;
		case(11):
			ShowSpare();
			break;
		case(0):
			exit = true;
			break;
		default:
			std::cout << "\nPlease select again\n";
			break;
		}
		if (exit)
			break;
	}
	return ;
}

/*
* функция отображает меню проверки матриц и принимает выбор пользователя
*/
int UserInterface::Menu_Matrix()
{
	int choice;

	std::cout << "\n______________Menu_____________\n";
	std::cout << "|                             |\n";
	std::cout << "|         1. New Array         |\n";
	std::cout << "|       2. Add matrix        |\n";
	std::cout << "|3. Multiplication by a number|\n";
	std::cout << "|4. Multiplication by a matrix|\n";
	std::cout << "|         5. Increment        |\n";
	std::cout << "|         6. Decrement        |\n";
	std::cout << "|         7. Equality         |\n";
	std::cout << "|          8. Index           |\n";
	std::cout << "|      9. Change element      |\n";
	std::cout << "|      10. Show matrix        |\n";
	std::cout << "| 11. Show Non-zero elements  |\n";
	std::cout << "|   12. Create new matrix     |\n";
	std::cout << "|                             |\n";
	std::cout << "|          0. Exit            |\n";
	std::cout << "|_____________________________|\n";

	std::cin >> choice;
	return choice;
}

//------------------------------------------------------------------------------------------------------
//									 ФУНКЦИИ ТЕСТОВ РАЗРЯЖЕННОЙ МАТРИЦЫ
//------------------------------------------------------------------------------------------------------


/*
* функция обновляет (по сути создает новую) матрицу 
*/
void UserInterface::RefreshMatrix()
{
	int strings = 0;
	int colums = 0;
	std::cout << "\nCreating new spare matrix...\n";
	std::cout << "How many strings do you want? ";
	std::cin >> strings ;
	std::cout << "\nHow many colums do you want? ";
	std::cin >> colums;
	SpMatrix NewMatrix(strings, colums);
	YourMatrix = NewMatrix;
	for (int i = 1; i <= strings; i++)
	{
		for (int j = 1; j <= colums; j++)
		{
			float elem = 0;
			std::cout << "\nElement " << i << ", " << j << " = ";
			std::cin >> elem;
			YourMatrix.SetElem(elem, i, j);
		}
	}
	//for (int i=0; i< YourMatrix)

	std::cout << "\nYour matrix is ready for  work \n";
	YourMatrix.Show();
	YourMatrix.ShowSpare();
	
	
} 

/*
* тест сложения матриц
*/
void UserInterface::TestAdd()
{
	int strings = 0;
	int colums = 0;
	std::cout << "\nCreating second spare matrix for addition...\n";
	std::cout << "How many strings do you want? ";
	std::cin >> strings;
	std::cout << "\nHow many colums do you want? ";
	std::cin >> colums;
	SpMatrix SecondMatrix(strings, colums);

	for (int i = 1; i <= strings; i++)
	{
		for (int j = 1; j <= colums; j++)
		{
			float elem = 0;
			std::cout << "\nElement " << i << ", " << j << " = ";
			std::cin >> elem;
			SecondMatrix.SetElem(elem, i, j);
		}
	}
	std::cout << "\nYour matrix is ready for  addition: \n";
	SecondMatrix.Show();
	YourMatrix += SecondMatrix;
	std::cout << "Your matrix + second matrix = \n";
	YourMatrix.Show();

}

/*
* тест вычитания матриц
*/
void UserInterface::TestSub()
{
	int strings = 0;
	int colums = 0;
	std::cout << "\nCreating second spare matrix for subtraction...\n";
	std::cout << "How many strings do you want? ";
	std::cin >> strings;
	std::cout << "\nHow many colums do you want? ";
	std::cin >> colums;
	SpMatrix SecondMatrix(strings, colums);

	for (int i = 1; i <= strings; i++)
	{
		for (int j = 1; j <= colums; j++)
		{
			float elem = 0;
			std::cout << "\nElement " << i << ", " << j << " = ";
			std::cin >> elem;
			SecondMatrix.SetElem(elem, i, j);
		}
	}
	std::cout << "\nYour matrix is ready for  subtraction: \n";
	SecondMatrix.Show();
	YourMatrix -= SecondMatrix;
	std::cout << "Your matrix - second matrix = \n";
	YourMatrix.Show();
	
}

/*
* тест умножения матрицы на матрицу
*/
void UserInterface::TestMult()
{
	int strings = 0;
	int colums = 0;
	std::cout << "\nCreating second spare matrix for multiplication...\n";
	std::cout << "How many strings do you want? ";
	std::cin >> strings;
	std::cout << "\nHow many colums do you want? ";
	std::cin >> colums;
	SpMatrix SecondMatrix(strings, colums);

	for (int i = 1; i <= strings; i++)
	{
		for (int j = 1; j <= colums; j++)
		{
			float elem = 0;
			std::cout << "\nElement " << i << ", " << j << " = ";
			std::cin >> elem;
			SecondMatrix.SetElem(elem, i, j);
		}
	}
	std::cout << "\nYour matrix is ready for  multiplication: \n";
	SecondMatrix.Show();
	YourMatrix = YourMatrix * SecondMatrix;
	std::cout << "Your matrix * second matrix = \n";
	YourMatrix.Show();
	
}

/*
* тест умножения матрицы на число
*/
void UserInterface::TestMult2()
{
	float number = 1;
	std::cout << "Your matrix * ";
	std::cin >> number;
	std::cout << " =\n";
	YourMatrix = YourMatrix * number;
	YourMatrix.Show();
}

/*
* тест инкримента
*/
void UserInterface::TestIncr()
{
	++YourMatrix;
	YourMatrix.Show();
}

/*
* тест декримента
*/
void UserInterface::TestDecr()
{
	--YourMatrix;
	YourMatrix.Show();
}

/*
* тест приравнивания
*/
void UserInterface::TestEqual()
{
	int strings = 0;
	int colums = 0;
	std::cout << "\nCreating second spare matrix for comparsion...\n";
	std::cout << "How many strings do you want? ";
	std::cin >> strings;
	std::cout << "\nHow many colums do you want? ";
	std::cin >> colums;
	SpMatrix SecondMatrix(strings, colums);

	for (int i = 1; i <= strings; i++)
	{
		for (int j = 1; j <= colums; j++)
		{
			float elem = 0;
			std::cout << "\nElement " << i << ", " << j << " = ";
			std::cin >> elem;
			SecondMatrix.SetElem(elem, i, j);
		}
	}
	std::cout << "\nYour matrix is ready for  comparsion: \n";
	SecondMatrix.Show();
	if (YourMatrix == SecondMatrix)
		std::cout << "They are equal!\n";
	else
		std::cout << "Sorry, these are different matrices\n";

	
}

/*
* тест взятия элемента по индексу
*/
void UserInterface::TestIndex()
{
	int number = 1;
	std::cout << "I want take element number...";
	std::cin >> number;
	std::cout << std::endl;
	std::cout << "It is " << YourMatrix[number] << std::endl;
}

/*
* тест изменения элемента матрицы
*/
void UserInterface::ChangeElem()
{
	int string = 1;
	int column = 1;
	float elem = 0;
	std::cout << "I want change element in string ";
	std::cin >> string;
	std::cout << " and column ";
	std::cin >> column;
	std::cout << " to ";
	std::cin >> elem;
	YourMatrix.SetElem(elem, string, column);

}

/*
* тест отображения матрицы в консоли
*/
void UserInterface::ShowMatrix()
{
	YourMatrix.Show();
}

/*
* тест отображения ненулевых элементов (хранимых в памяти)
*/
void UserInterface::ShowSpare()
{
	YourMatrix.ShowSpare();
}

//------------------------------------------------------------------------------------------------------
//									 ФУНКЦИИ ТЕСТОВ ДИНАМИЧЕСКОГО МАССИВА МАТРИЦ
//------------------------------------------------------------------------------------------------------

/*
* функция запускает интерфейс проверки матриц в консоли
*/
void UserInterface::GoInterface_Array()
{
	bool exit = false;
	RefreshArray();
	for (;;)
	{
		int choice = Menu_Array(); //переменная выбора пользователя
		switch (choice)
		{
		
		case(1):
			TestAdd_Array();
			break;
		case(2):
			TestRemove();
			break;
		case(3):
			TestIndex_Array();
			break;
		case(4):
			TestSearch();
			break;
		case(5):
			TestChangeElem();
			break;
		case(6):
			RefreshArray();
			break;
		case(0):
			exit = true;
			break;
		default:
			std::cout << "\nPlease select again\n";
			break;
		}
		if (exit)
			break;
	}
	return;
}

/*
* функция отображает меню проверки матриц и принимает выбор пользователя
*/
int UserInterface::Menu_Array()
{
	int choice;

	std::cout << "\n______________Menu_____________\n";
	std::cout << "|                             |\n";
	std::cout << "|         1. Addition         |\n";
	std::cout << "|         2. Remove           |\n";
	std::cout << "|         3. Show Array[i]    |\n";
	std::cout << "|         4. Search           |\n";
	std::cout << "|         5. Set Array[i] =   |\n";
	std::cout << "|         6. New Array        |\n";
	std::cout << "|          0. Exit            |\n";
	std::cout << "|_____________________________|\n";

	std::cin >> choice;
	return choice;
}

// создаем заного массив
void UserInterface::RefreshArray() 
{
	int elems = 0;
	
	std::cout << "\nCreating new Array...\n";
	std::cout << "How many elements do you want? ";
	std::cin >> elems;
	YourArray.Resize(elems, false);
	for (int i = 1; i <= elems; i++)
	{
		
		RefreshMatrix();
		YourArray[i - 1] = YourMatrix;
		
	}
	

	std::cout << "\nYour Array is ready for  work \n";
	YourArray.Show();
	


}

// функция тестирует добавление элемента в конец массива
void UserInterface::TestAdd_Array()
{
	RefreshMatrix();
	YourArray.Add(&YourMatrix);
	YourArray.Show();
}

// функция тестирует удаление последнего элемента массива
void UserInterface::TestRemove()
{
	YourArray.Remove();
	YourArray.Show();
}

// функция-тест берет элемент по индексу
void UserInterface::TestIndex_Array()
{
	unsigned index = 0;
	std::cout << "Index? ";
	std::cin >> index ;
	YourMatrix = YourArray[index];
	YourMatrix.Show();
}

// функция тестирует изменение элемента по индексу
void UserInterface::TestChangeElem()
{
	unsigned index = 0;
	std::cout << "Index? ";
	std::cin >> index;
	RefreshMatrix();
	YourArray[index] = YourMatrix;
	YourArray.Show();
}

// функция находит элемент в массиве (показывает индексы элементов)
void UserInterface::TestSearch()
{
	RefreshMatrix();
	YourArray.Search(&YourMatrix);
}








/*
* просто деструктор
*/
UserInterface::~UserInterface()
{
	
}
