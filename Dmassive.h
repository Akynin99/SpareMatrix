

#include <assert.h>
#include "Algo.h"
using namespace std;
/*
Шаблон класса: одномерный динамический массив из элементов типа T
*/
template <class T>
class Array {

private:
	unsigned FCount;	// число элементов
	T* FData;			   // указатель на первый элемент массива (если FCount > 0)

public:
	// Создание массива из count элементов, по умолчанию 0
	Array(unsigned count = 0)
		: FCount(0)			// инициализируем элемент FCount конструктором копии
	{  						   // (вместо конструктора по умолчанию)
		Resize(count, false);
	}

	// Создание массива из count элементов, которые инициализируются
	// count элементами, на которые указывает data
	Array(unsigned count, const T *data)
		: FCount(0)
	{
		Assign(count, data);
	}

	// Конструктор копии
	Array(const Array& array)
		: FCount(0)
	{
		Assign(array.FCount, array.FData);
	}

	// Деструктор 
	~Array()
	{
		Clear();
	}

	// Возвращает размер массива.
	unsigned Count() const
	{ return FCount; }
	// Задает размер массива.
	void Count(unsigned count)
	{ Resize(count); }

	// Устанавливает размер массива в count и копирует в него count элементов
	// data[0], data[1], ..., data[count - 1].
	void Assign(unsigned count, const T *data);

	// Устанавливает размер массива. Старые элементы (сколько влезут в новый размер)
	// по умолчанию остаются (параметр store = true), либо теряются (store = false).
	void Resize(unsigned count, bool store = true);

	// Удаление всех элементов.
	void Clear()
	{
		Count(0);
	}

	// Операция присваивания. Устанавливается такой же размер и копируются данные из array.
	Array& operator =(const Array& array)
	{
		// Если не имеет место самоприсваивание (Array<T> a; a = a;), то
		if (this != &array)
			// выполняем присваивание.
			Assign(array.FCount, array.FData);
		// Возвращаем ссылку на левый аргумент операции присваивания, чтобы позволить, например,
		// дальнейшее присваивание (Array<T> a, b, c; a = b = c;).
		return *this;
	}

	// Операция индексации (для константного массива).
	const T& operator [](unsigned index) const
	{
		assert(index < FCount);	// проверка корректности индекса
		return FData[index];	   // и возврат константной ссылки на элемент
	}

	// Операция индексации (для неконстантного массива).
	T& operator [](unsigned index)
	{
		assert(index < FCount);	// проверка корректности индекса
		return FData[index];	   // и возврат ссылки на элемент
	}

	// Операция вывода в поток.
	void Array<T>::Show();
	



	// Операция равенства.
	friend bool operator ==(const Array& x, const Array& y)
	{
		// Если массивы являются различными объектами, то выполняем сравнение.
		if (&x != &y)
			// Если число элементов одинаково,
			if (x.FCount == y.FCount)
				// то выполняем поэлементное сравнение.
				return Compare(x.FData, y.FData, FCount);
		// Иначе, массивы не равны.
			else
				return false;
		// Иначе возвращаем истину (т. к. любой массив сам себе равен).
		return true;
	}

	// Операция неравенства.
	friend bool operator !=(const Array& x, const Array& y)
	{
		return !(x == y);
	}

	void Add( T * data);
	void Remove();
	void Search( T *obj);
};
//---------------------------------------------------------------------------
// Определение не встраиваемых функций-элементов
//---------------------------------------------------------------------------
template <class T>
void Array<T>::Assign(unsigned count, const T *data)
{
	Resize(count, false);		// устанавливаем размер, без сохранения элементов
	Copy(FData, data, FCount); // и копируем данные
	
}


template <class T>
void Array<T>::Resize(unsigned count, bool store)
{
	// Если число элементов изменяется.
	if (FCount != count) {
		// Если новое число элементов не нулевое, то распределяем память;
		if (count) {
			// Создаем динамический массив из count элементов,
			T *p = new T[count];
			// и копируем туда старые элементы (сколько влезет), если требуется.
			if (store)
				Copy(p, FData, Min(FCount, count));
			// Уничтожаем старый массив, если он не пуст.
			if (FCount) delete[] FData;
			// Сохраняем в классе адрес первого элемента нового массива.
			FData = p;
		}
		// иначе освобождаем память.
		else
			delete[] FData;
		// Сохраняем новое число элементов в классе.
		FCount = count;
	}
}

// Операция вывода в поток.
template <class T>
 void Array<T>::Show()
{
	// Вывод в поток и
	 std::cout << "Your Array :" << endl;
	 for (int i = 0; i < (this->FCount); i++)
	 {
		 cout << "Your element #"<<i<<": " << endl;

		 cout << this->operator[](i) << endl;
	}
	// возврат ссылки на поток, чтобы позволить последующий вывод (нап: cout << a << b).

}
 template <class T>
 void Array<T>::Add( T * data)
 {
	 int oldCount = FCount;

	 Resize(oldCount + 1, true);
	 this->operator[](oldCount) = *data;
	
 }

 template <class T>
 void Array<T>::Remove()
 {

	// FData[FCount-1] = T(NULL);
	 FCount--;
 }

 template <class T>
 void Array<T>::Search( T* obj)
 {
	 int count = 0;
	 for (int i = 0; i< FCount;i++)
	 {
		 T* temp(&this->operator[](i));
		
		 if (*temp == *obj)
		 {
			 cout << "Your element in index " << i << endl;
			 count++;
		 }
	 }

	 if (!count)
		 cout << "No matches" << endl;
 }