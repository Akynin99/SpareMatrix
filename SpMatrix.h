#include "stdafx.h"
typedef unsigned short int USHORT;
using std::istream;
using std::ostream;
//
//								ВНИМАНИЕ!
//
// Всегда СНАЧАЛА - СТРОКИ, ПОТОМ - СТОЛБЦЫ! И никогда наоборот (чтоб не путаться).
// Речь и о параметрах, и о счетчиках в циклах внутри функций, и о чем угодно еще!
// 
//
class SpMatrix
{

	USHORT itsNumbColumns;	// количество столбцов
	USHORT itsNumbStrings;	// количество строк
	USHORT itsNumbElem;		// количество элементов (в принцепе можно было и не создавать это поле, а использовать произведение столбцов и строк)

	std::vector<float> NonZeroElems;	// в этом векторе хранятся значения ненулевых элементов 
	std::vector<USHORT> Addresses;		// в этом векторе хранятся адресса ненулевых элементов (счет начинается с 1), 
										// первый элемент - в первом столбце и первой строке, второй - в первой строке и во втором столбце и т.д.
public:
	SpMatrix();											// конструуктор без парам., создает матрицу 2х2
	SpMatrix(USHORT numbStrings, USHORT numbColumns);	// конструктор который задает количество строк и столбцов
	//SpMatrix(float * massive, USHORT numbStrings, USHORT numbColumns); // конструктор создает матрицу с заданным размером, элементы берет из массива (НЕ ГОТОВО)
	SpMatrix(const SpMatrix & obj);						// конструктор копирования

	void Show();										// функция отображения матрицы в консоли 
	void ShowSpare();									// функция отображения ненулевых элементов (хранимых в памяти)
	float GetElem(int string, int column);				// функция взятия элемента
	void SetElem(float elem, int string, int column);	// функция изменения элемента


	void operator = (const SpMatrix &obj);	// оператор присваивания
	SpMatrix operator + (SpMatrix &obj);	// оператор сложения матриц
	SpMatrix operator - (SpMatrix &obj);	//	оператор вычитания матриц
	SpMatrix operator * (SpMatrix &obj);	// оператор умножения матрицы на матрицу
	SpMatrix operator * (int number);		// оператор умножения матрицы на целое число
	SpMatrix operator * (float number);		// оператор умножения матрицы на вещественное число
	SpMatrix operator ++ ();				// префиксный оператор инкримента
	SpMatrix operator ++ (int);				// постфиксный оператор инкримента
	SpMatrix operator -- ();				// префиксный оператор декремента
	SpMatrix operator -- (int);				// постфиксный оператор декремента
	SpMatrix operator += (SpMatrix &obj);	// арифметика с накоплением
	SpMatrix operator -= (SpMatrix &obj);
	bool operator == (SpMatrix &obj) const; // операторы сравнения
	bool operator != (SpMatrix &obj) const;
	float operator [] (int number);			// оператор взятия по номеру элемента
	friend ostream& operator << (ostream& a, const SpMatrix obj); // оператор для отображения через  cout
	
	~SpMatrix();	// деструктор
};

