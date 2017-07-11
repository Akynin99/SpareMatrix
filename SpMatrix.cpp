#include "stdafx.h"
#include "SpMatrix.h"
#include <iostream>

/*
*  конструуктор без парам., создает матрицу 2х2
*/
SpMatrix::SpMatrix()
{

	itsNumbColumns = 2;
	itsNumbStrings = 2;
	itsNumbElem = itsNumbColumns*itsNumbStrings;

	

	
}

/*
*  конструктор который задает количество строк и столбцов
*/
SpMatrix::SpMatrix(USHORT numbStrings, USHORT numbColumns)
{
	itsNumbColumns = numbColumns;
	itsNumbStrings = numbStrings;
	itsNumbElem = itsNumbColumns*itsNumbStrings;
	std::vector<float> NonZeroElems(itsNumbElem);
	std::vector<USHORT> Addresses(itsNumbElem);
}
//SpMatrix::SpMatrix(float * massive, USHORT numbStrings = 2, USHORT numbColumns = 2) (НЕ ГОТОВО)
//{
//	itsNumbColumns = numbColumns;
//	itsNumbStrings = numbStrings;
//	itsNumbElem = itsNumbColumns*itsNumbStrings;
//	std::vector<float> NonZeroElems(itsNumbElem);
//	std::vector<USHORT> Addresses(itsNumbElem);
//}

/*
* конструктор копирования
*/
SpMatrix::SpMatrix(const SpMatrix & obj)
{
	this->itsNumbColumns = obj.itsNumbColumns;
	this->itsNumbElem = obj.itsNumbElem;
	this->itsNumbStrings = obj.itsNumbStrings;
	this->Addresses = obj.Addresses;
	this->NonZeroElems = obj.NonZeroElems;
}

/*
* функция отображения матрицы в консоли 
*/
void SpMatrix::Show()
{
	for (int i = 1; i <= itsNumbStrings; i++)
	{
		std::cout << "|  ";
		for (int j = 1; j <= itsNumbColumns; j++)
			std::cout << this->GetElem(i, j)<< "  ";
		std::cout << "|\n";
	}
	std::cout << std::endl;
}

/*
* функция отображения ненулевых элементов (хранимых в памяти)
*/
void SpMatrix::ShowSpare()
{
	// сначала отобразим индексы ненулевых элементов
	std::cout << "Index of elements: { ";  
	int AddressMax = this->Addresses.size();
	for (int i = 1; i <= AddressMax; i++)
	{
		if (i != AddressMax)
			std::cout << Addresses[i - 1] << ", ";
		else
			std::cout << Addresses[i - 1] << " }";
	}
	std::cout << std::endl;

	// теперь отобразим значения этих элементов
	std::cout << "Elements:            { ";
	int NonZeroMax = this->NonZeroElems.size();
	for (int i = 1; i <= NonZeroMax; i++)
	{
		if (i != NonZeroMax)
			std::cout << NonZeroElems[i - 1] << ", ";
		else
			std::cout << NonZeroElems[i - 1] << " }\n";
	}
	std::cout << std::endl;
	return;
}

/*
* функция взятия элемента
*/
float SpMatrix::GetElem(int string, int column)
{
	// сначала проверим матрицу на наличие ненулевых элементов
	if (Addresses.empty() == true)
		return 0;

	USHORT Number = column + (string - 1)*itsNumbColumns ; // формула вычесления номера элемента по его строке и столбцу

	int maxAdress = Addresses.size();
	for (int i = 0; i < maxAdress; i++)
	{
		
		if (Addresses[i] == Number)
			return NonZeroElems[i];
		
	}
	return 0;
}

/*
* функция изменения элемента
*/
void SpMatrix::SetElem(float elem, int string, int column)
{
	for (int i = 0; i < this->NonZeroElems.size(); i++)  
	{
		if (this->NonZeroElems[i] == 0) //проверка на отсутствие нулевых элементов в векторе
		{
			// эта проверка была  введена после обнаружения бага, 
			//когда при создании матрицы первый элемент задается нулевым и матрица хранит его значение как ненулевое
			this->NonZeroElems.erase(NonZeroElems.begin() + i);
			this->Addresses.erase(Addresses.begin() + i);
		}
	}
	
	
	
	//if (Addresses.empty() == true) // если ненулевых элементов нет, то 
	//{
	//	// в вектор индексов добавляем элемент 
	//	Addresses.push_back(1); 
	//	NonZeroElems.push_back(0);
	//}



	USHORT Number = column + (string - 1)*itsNumbColumns ;
	int maxAdress = Addresses.size();
	if (elem == 0)
	{
		for (int i = 0; i < maxAdress; i++)
		{

			if (Addresses[i] == Number)
			{
				for (i; i < maxAdress-1 ; i++)
				{
					NonZeroElems[i] = NonZeroElems[i + 1];
					Addresses[i] = Addresses[i + 1];
				}
				NonZeroElems.pop_back();
				Addresses.pop_back();
				return;
			}
		}
		

				
	}
	if (elem != 0)
	{
		if (Addresses.empty() == true) // если ненулевых элементов нет, то всё просто:
		{
			// в вектор индексов добавляем элемент адрес нового элемента
			Addresses.push_back(Number);
			//а в вектор значений - его значение
			NonZeroElems.push_back(elem);
		}
		else // если енулевые элементы в матрице уже присутствуют
		{

			if (Addresses[maxAdress - 1] < Number) 
			{
				// если последний ненулевой элемент имеет адрес меньше, чем адрес нового элемента
				// то можно просто добавить наш элемент в конец обоих векторов
				Addresses.push_back(Number);
				NonZeroElems.push_back(elem);
				return;
			}
			/*for (int i = 0; i < maxAdress; i++)	// цикл был нужен раньше, когда функция работала так, что
													// если ненулевых элементов нет, то сначала добавляем единичный элемент
													// в вектора, а потом этот цикл бы его изменил, но такой алгоритм 
													// было сложно читать и он вызывал баг указанный выше
			{

				if (Addresses[i] == Number)
				{
					NonZeroElems[i] = elem;
					return;
				}
			}*/
			for (int i = 0; i < maxAdress; i++)
			{
				if (Addresses[i] > Number)
				{
					// сложный алгоритм для того что бы вставить наш новый адрес и значение в середины векторов
					Addresses.push_back(Addresses[maxAdress - 1]);
					NonZeroElems.push_back(NonZeroElems[maxAdress - 1]);
					for (int j = maxAdress - 1; j > i; j--)
					{
						NonZeroElems[j] = NonZeroElems[j - 1];
						Addresses[j] = Addresses[j - 1];
					}
					Addresses[i] = Number;
					NonZeroElems[i] = elem;
					return;
				}
			}
		}


	}

	for (int i = 0; i < this->NonZeroElems.size(); i++)		// проверка на отсутствие нулевых элементов в векторе
															// ввел на всякий случай после того как выловил баг описанный выше
	{
		if (this->NonZeroElems[i] == 0)
		{
			this->NonZeroElems.erase(NonZeroElems.begin() + i);
			this->Addresses.erase(Addresses.begin() + i);
		}
	}

}



//------------------------------------------------------------------------------------------------------
//									ДАЛЕЕ ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ
//------------------------------------------------------------------------------------------------------


/*
* оператор присваивания
*/
void SpMatrix::operator = (const SpMatrix &obj)
{
	this->itsNumbColumns = obj.itsNumbColumns;
	this->itsNumbElem = obj.itsNumbElem;
	this->itsNumbStrings = obj.itsNumbStrings;
	this->Addresses = obj.Addresses;
	this->NonZeroElems = obj.NonZeroElems;
}

/*
* оператор сложения матриц
*/
SpMatrix SpMatrix::operator + (SpMatrix &obj)
{
	try {
		if (this->itsNumbColumns != obj.itsNumbColumns || this->itsNumbStrings != obj.itsNumbStrings) //проверяем размеры матриц
		{
			
			throw 101;
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "ERROR "<< i << ": Noncompliance with addition conditions!\n";
	}
	SpMatrix SumOfMatrix(obj.itsNumbColumns, obj.itsNumbStrings); //создаем новую матицу
	for (int i = 1; i <= SumOfMatrix.itsNumbStrings; i++) //обходим все строки новой матрицы
	{
		
		for (int j = 1; j <= SumOfMatrix.itsNumbColumns; j++) //обходим каждый объект в строке
		{
			SumOfMatrix.SetElem(this->GetElem(i, j) + obj.GetElem(i, j), i, j);
		}
		
	}
	return SumOfMatrix;
}

/*
*	оператор вычитания матриц
*/
SpMatrix SpMatrix::operator - (SpMatrix &obj)
{
	try {
		if (this->itsNumbColumns != obj.itsNumbColumns || this->itsNumbStrings != obj.itsNumbStrings) //проверяем размеры матриц
		{
			throw 102;
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "ERROR " << i << ": Noncompliance with subtraction conditions!\n";
	}
	SpMatrix SubOfMatrix(obj.itsNumbColumns, obj.itsNumbStrings); //создаем новую матицу
	for (int i = 1; i <= SubOfMatrix.itsNumbStrings; i++) //обходим все строки
	{

		for (int j = 1; j <= SubOfMatrix.itsNumbColumns; j++) //обходим каждый объект в строке
		{
			SubOfMatrix.SetElem(this->GetElem(i, j) - obj.GetElem(i, j), i, j);
		}

	}
	return SubOfMatrix;
}

/*
* оператор умножения матрицы на матрицу
*/
SpMatrix SpMatrix::operator * (SpMatrix &obj)
{
	try {
		if (this->itsNumbColumns != obj.itsNumbStrings) //условие умножения матриц
		{
			throw 103;
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "ERROR " << i << ": Noncompliance with multiplication conditions!\n";
	}
	SpMatrix MultOfMatrix(obj.itsNumbColumns, this->itsNumbStrings); // создаем матрицу
	for (int i = 1; i <= MultOfMatrix.itsNumbStrings; i++) //обходим все строки новой матрицы
	{

		for (int j = 1; j <= MultOfMatrix.itsNumbColumns; j++) //обходим каждый объект в строке
		{
			float elem = 0 ; // переменная для значения ячейки (i, j)

			for (int k = 1; k <= obj.itsNumbStrings; k++) //цикл вычисления elem
			{
				elem += this->GetElem(i, k) * obj.GetElem(k, j); 
			}
			
			MultOfMatrix.SetElem(elem, i, j); //вбиваем вычисленное значение в ячейку
		}

	}

	return MultOfMatrix;
}

/*
* оператор умножения матрицы на целое число
*/
SpMatrix SpMatrix::operator * (int number)
{
	SpMatrix MultOfMatrix(*this); // создаем копию матрицы

	for (int i = 1; i <= MultOfMatrix.itsNumbStrings; i++) //обходим все строки новой матрицы
	{

		for (int j = 1; j <= MultOfMatrix.itsNumbColumns; j++) //обходим каждый объект в строке
		{
			MultOfMatrix.SetElem(this->GetElem(i, j) * number , i, j);
		}
	}

	return MultOfMatrix;
}

/*
* оператор умножения матрицы на вещественное число
*/
SpMatrix SpMatrix::operator * (float number)
{
	SpMatrix MultOfMatrix(*this); // создаем копию матрицы

	for (int i = 1; i <= MultOfMatrix.itsNumbStrings; i++) //обходим все строки новой матрицы
	{

		for (int j = 1; j <= MultOfMatrix.itsNumbColumns; j++) //обходим каждый объект в строке
		{
			MultOfMatrix.SetElem(this->GetElem(i, j) * number, i, j);
		}
	}

	return MultOfMatrix;
}

/*
* префиксный оператор инкримента
*/
SpMatrix SpMatrix::operator ++()
{
	for (int i = 1; i <= this->itsNumbStrings; i++) //обходим все строки новой матрицы
	{

		for (int j = 1; j <= this->itsNumbColumns; j++) //обходим каждый объект в строке
		{
			float elem = this->GetElem(i, j);
			this->SetElem(++elem, i, j);
		}
	}
	return *this;
}

/*
* постфиксный оператор инкримента
*/
SpMatrix SpMatrix::operator ++(int)
{
	SpMatrix CopyOfThis(*this); 

	for (int i = 1; i <= CopyOfThis.itsNumbStrings; i++) //обходим все строки новой матрицы
	{

		for (int j = 1; j <= CopyOfThis.itsNumbColumns; j++) //обходим каждый объект в строке
		{
			float elem = CopyOfThis.GetElem(i, j);
			CopyOfThis.SetElem(elem++, i, j);
		}
	}
	return CopyOfThis;
}

/*
* префиксный оператор декремента
*/
SpMatrix SpMatrix::operator --()
{
	for (int i = 1; i <= this->itsNumbStrings; i++) //обходим все строки новой матрицы
	{

		for (int j = 1; j <= this->itsNumbColumns; j++) //обходим каждый объект в строке
		{
			float elem = this->GetElem(i, j);
			this->SetElem( --elem , i, j);
		}
	}
	return *this;
}

/*
* постфиксный оператор декремента
*/
SpMatrix SpMatrix::operator --(int)
{
	SpMatrix CopyOfThis(*this);

	for (int i = 1; i <= CopyOfThis.itsNumbStrings; i++) //обходим все строки новой матрицы
	{

		for (int j = 1; j <= CopyOfThis.itsNumbColumns; j++) //обходим каждый объект в строке
		{
			float elem = CopyOfThis.GetElem(i, j);
			CopyOfThis.SetElem(elem--, i, j);
		}

	}
	return CopyOfThis;
}

/*
* арифметика с накоплением
*/
SpMatrix SpMatrix::operator += (SpMatrix &obj)
{
	*this = *this + obj;
	return *this;
}

/*
* арифметика с накоплением
*/
SpMatrix SpMatrix::operator -= (SpMatrix &obj)
{
	*this = *this - obj;
	return *this;
}

/*
* оператор сравнения
*/
bool SpMatrix::operator == (SpMatrix &obj) const
{
	if ((this->itsNumbColumns == obj.itsNumbColumns) && (this->itsNumbStrings == obj.itsNumbStrings))
	{
		if ((this->Addresses == obj.Addresses) && (this->NonZeroElems == obj.NonZeroElems))
			return true;
	}
	else
	return false;
}

/*
* обратный оператор сравнения
*/
bool SpMatrix::operator != (SpMatrix &obj) const
{
	if ((this->itsNumbColumns == obj.itsNumbColumns) && (this->itsNumbStrings == obj.itsNumbStrings))
	{
		if ((this->Addresses == obj.Addresses) && (this->NonZeroElems == obj.NonZeroElems))
			return false;
	}
	else
	return true;
}

/*
* оператор взятия по номеру элемента
*/
float SpMatrix::operator[] (int number)
{
	try
	{
		if (number < 1 || number > this->itsNumbElem)
		{
			throw  104;
			return 0;
		}
	}
	catch (int i)
	{
		std::cout << "ERROR " << i << ": Access beyond the matrix !\n";
	}
	int maxAdress = this->Addresses.size();
	for (int i = 0; i < maxAdress; i++)
	{

		if (this->Addresses[i] == number)
			return NonZeroElems[i];

	}
	return 0;

}

/*
* оператор для отображения через  cout
*/
ostream& operator <<(ostream & a, SpMatrix  obj)
{
	obj.Show();
	return a;
}



/*
*
*/
SpMatrix::~SpMatrix()
{
	// вектора удаляются автоматически
}
