

#include <assert.h>
#include "Algo.h"
using namespace std;
/*
������ ������: ���������� ������������ ������ �� ��������� ���� T
*/
template <class T>
class Array {

private:
	unsigned FCount;	// ����� ���������
	T* FData;			   // ��������� �� ������ ������� ������� (���� FCount > 0)

public:
	// �������� ������� �� count ���������, �� ��������� 0
	Array(unsigned count = 0)
		: FCount(0)			// �������������� ������� FCount ������������� �����
	{  						   // (������ ������������ �� ���������)
		Resize(count, false);
	}

	// �������� ������� �� count ���������, ������� ����������������
	// count ����������, �� ������� ��������� data
	Array(unsigned count, const T *data)
		: FCount(0)
	{
		Assign(count, data);
	}

	// ����������� �����
	Array(const Array& array)
		: FCount(0)
	{
		Assign(array.FCount, array.FData);
	}

	// ���������� 
	~Array()
	{
		Clear();
	}

	// ���������� ������ �������.
	unsigned Count() const
	{ return FCount; }
	// ������ ������ �������.
	void Count(unsigned count)
	{ Resize(count); }

	// ������������� ������ ������� � count � �������� � ���� count ���������
	// data[0], data[1], ..., data[count - 1].
	void Assign(unsigned count, const T *data);

	// ������������� ������ �������. ������ �������� (������� ������ � ����� ������)
	// �� ��������� �������� (�������� store = true), ���� �������� (store = false).
	void Resize(unsigned count, bool store = true);

	// �������� ���� ���������.
	void Clear()
	{
		Count(0);
	}

	// �������� ������������. ��������������� ����� �� ������ � ���������� ������ �� array.
	Array& operator =(const Array& array)
	{
		// ���� �� ����� ����� ���������������� (Array<T> a; a = a;), ��
		if (this != &array)
			// ��������� ������������.
			Assign(array.FCount, array.FData);
		// ���������� ������ �� ����� �������� �������� ������������, ����� ���������, ��������,
		// ���������� ������������ (Array<T> a, b, c; a = b = c;).
		return *this;
	}

	// �������� ���������� (��� ������������ �������).
	const T& operator [](unsigned index) const
	{
		assert(index < FCount);	// �������� ������������ �������
		return FData[index];	   // � ������� ����������� ������ �� �������
	}

	// �������� ���������� (��� �������������� �������).
	T& operator [](unsigned index)
	{
		assert(index < FCount);	// �������� ������������ �������
		return FData[index];	   // � ������� ������ �� �������
	}

	// �������� ������ � �����.
	void Array<T>::Show();
	



	// �������� ���������.
	friend bool operator ==(const Array& x, const Array& y)
	{
		// ���� ������� �������� ���������� ���������, �� ��������� ���������.
		if (&x != &y)
			// ���� ����� ��������� ���������,
			if (x.FCount == y.FCount)
				// �� ��������� ������������ ���������.
				return Compare(x.FData, y.FData, FCount);
		// �����, ������� �� �����.
			else
				return false;
		// ����� ���������� ������ (�. �. ����� ������ ��� ���� �����).
		return true;
	}

	// �������� �����������.
	friend bool operator !=(const Array& x, const Array& y)
	{
		return !(x == y);
	}

	void Add( T * data);
	void Remove();
	void Search( T *obj);
};
//---------------------------------------------------------------------------
// ����������� �� ������������ �������-���������
//---------------------------------------------------------------------------
template <class T>
void Array<T>::Assign(unsigned count, const T *data)
{
	Resize(count, false);		// ������������� ������, ��� ���������� ���������
	Copy(FData, data, FCount); // � �������� ������
	
}


template <class T>
void Array<T>::Resize(unsigned count, bool store)
{
	// ���� ����� ��������� ����������.
	if (FCount != count) {
		// ���� ����� ����� ��������� �� �������, �� ������������ ������;
		if (count) {
			// ������� ������������ ������ �� count ���������,
			T *p = new T[count];
			// � �������� ���� ������ �������� (������� ������), ���� ���������.
			if (store)
				Copy(p, FData, Min(FCount, count));
			// ���������� ������ ������, ���� �� �� ����.
			if (FCount) delete[] FData;
			// ��������� � ������ ����� ������� �������� ������ �������.
			FData = p;
		}
		// ����� ����������� ������.
		else
			delete[] FData;
		// ��������� ����� ����� ��������� � ������.
		FCount = count;
	}
}

// �������� ������ � �����.
template <class T>
 void Array<T>::Show()
{
	// ����� � ����� �
	 std::cout << "Your Array :" << endl;
	 for (int i = 0; i < (this->FCount); i++)
	 {
		 cout << "Your element #"<<i<<": " << endl;

		 cout << this->operator[](i) << endl;
	}
	// ������� ������ �� �����, ����� ��������� ����������� ����� (���: cout << a << b).

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