#include "stdafx.h"
#include "SpMatrix.h"
#include <iostream>

/*
*  ������������ ��� �����., ������� ������� 2�2
*/
SpMatrix::SpMatrix()
{

	itsNumbColumns = 2;
	itsNumbStrings = 2;
	itsNumbElem = itsNumbColumns*itsNumbStrings;

	

	
}

/*
*  ����������� ������� ������ ���������� ����� � ��������
*/
SpMatrix::SpMatrix(USHORT numbStrings, USHORT numbColumns)
{
	itsNumbColumns = numbColumns;
	itsNumbStrings = numbStrings;
	itsNumbElem = itsNumbColumns*itsNumbStrings;
	std::vector<float> NonZeroElems(itsNumbElem);
	std::vector<USHORT> Addresses(itsNumbElem);
}
//SpMatrix::SpMatrix(float * massive, USHORT numbStrings = 2, USHORT numbColumns = 2) (�� ������)
//{
//	itsNumbColumns = numbColumns;
//	itsNumbStrings = numbStrings;
//	itsNumbElem = itsNumbColumns*itsNumbStrings;
//	std::vector<float> NonZeroElems(itsNumbElem);
//	std::vector<USHORT> Addresses(itsNumbElem);
//}

/*
* ����������� �����������
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
* ������� ����������� ������� � ������� 
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
* ������� ����������� ��������� ��������� (�������� � ������)
*/
void SpMatrix::ShowSpare()
{
	// ������� ��������� ������� ��������� ���������
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

	// ������ ��������� �������� ���� ���������
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
* ������� ������ ��������
*/
float SpMatrix::GetElem(int string, int column)
{
	// ������� �������� ������� �� ������� ��������� ���������
	if (Addresses.empty() == true)
		return 0;

	USHORT Number = column + (string - 1)*itsNumbColumns ; // ������� ���������� ������ �������� �� ��� ������ � �������

	int maxAdress = Addresses.size();
	for (int i = 0; i < maxAdress; i++)
	{
		
		if (Addresses[i] == Number)
			return NonZeroElems[i];
		
	}
	return 0;
}

/*
* ������� ��������� ��������
*/
void SpMatrix::SetElem(float elem, int string, int column)
{
	for (int i = 0; i < this->NonZeroElems.size(); i++)  
	{
		if (this->NonZeroElems[i] == 0) //�������� �� ���������� ������� ��������� � �������
		{
			// ��� �������� ����  ������� ����� ����������� ����, 
			//����� ��� �������� ������� ������ ������� �������� ������� � ������� ������ ��� �������� ��� ���������
			this->NonZeroElems.erase(NonZeroElems.begin() + i);
			this->Addresses.erase(Addresses.begin() + i);
		}
	}
	
	
	
	//if (Addresses.empty() == true) // ���� ��������� ��������� ���, �� 
	//{
	//	// � ������ �������� ��������� ������� 
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
		if (Addresses.empty() == true) // ���� ��������� ��������� ���, �� �� ������:
		{
			// � ������ �������� ��������� ������� ����� ������ ��������
			Addresses.push_back(Number);
			//� � ������ �������� - ��� ��������
			NonZeroElems.push_back(elem);
		}
		else // ���� �������� �������� � ������� ��� ������������
		{

			if (Addresses[maxAdress - 1] < Number) 
			{
				// ���� ��������� ��������� ������� ����� ����� ������, ��� ����� ������ ��������
				// �� ����� ������ �������� ��� ������� � ����� ����� ��������
				Addresses.push_back(Number);
				NonZeroElems.push_back(elem);
				return;
			}
			/*for (int i = 0; i < maxAdress; i++)	// ���� ��� ����� ������, ����� ������� �������� ���, ���
													// ���� ��������� ��������� ���, �� ������� ��������� ��������� �������
													// � �������, � ����� ���� ���� �� ��� �������, �� ����� �������� 
													// ���� ������ ������ � �� ������� ��� ��������� ����
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
					// ������� �������� ��� ���� ��� �� �������� ��� ����� ����� � �������� � �������� ��������
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

	for (int i = 0; i < this->NonZeroElems.size(); i++)		// �������� �� ���������� ������� ��������� � �������
															// ���� �� ������ ������ ����� ���� ��� ������� ��� ��������� ����
	{
		if (this->NonZeroElems[i] == 0)
		{
			this->NonZeroElems.erase(NonZeroElems.begin() + i);
			this->Addresses.erase(Addresses.begin() + i);
		}
	}

}



//------------------------------------------------------------------------------------------------------
//									����� ������������� ���������
//------------------------------------------------------------------------------------------------------


/*
* �������� ������������
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
* �������� �������� ������
*/
SpMatrix SpMatrix::operator + (SpMatrix &obj)
{
	try {
		if (this->itsNumbColumns != obj.itsNumbColumns || this->itsNumbStrings != obj.itsNumbStrings) //��������� ������� ������
		{
			
			throw 101;
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "ERROR "<< i << ": Noncompliance with addition conditions!\n";
	}
	SpMatrix SumOfMatrix(obj.itsNumbColumns, obj.itsNumbStrings); //������� ����� ������
	for (int i = 1; i <= SumOfMatrix.itsNumbStrings; i++) //������� ��� ������ ����� �������
	{
		
		for (int j = 1; j <= SumOfMatrix.itsNumbColumns; j++) //������� ������ ������ � ������
		{
			SumOfMatrix.SetElem(this->GetElem(i, j) + obj.GetElem(i, j), i, j);
		}
		
	}
	return SumOfMatrix;
}

/*
*	�������� ��������� ������
*/
SpMatrix SpMatrix::operator - (SpMatrix &obj)
{
	try {
		if (this->itsNumbColumns != obj.itsNumbColumns || this->itsNumbStrings != obj.itsNumbStrings) //��������� ������� ������
		{
			throw 102;
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "ERROR " << i << ": Noncompliance with subtraction conditions!\n";
	}
	SpMatrix SubOfMatrix(obj.itsNumbColumns, obj.itsNumbStrings); //������� ����� ������
	for (int i = 1; i <= SubOfMatrix.itsNumbStrings; i++) //������� ��� ������
	{

		for (int j = 1; j <= SubOfMatrix.itsNumbColumns; j++) //������� ������ ������ � ������
		{
			SubOfMatrix.SetElem(this->GetElem(i, j) - obj.GetElem(i, j), i, j);
		}

	}
	return SubOfMatrix;
}

/*
* �������� ��������� ������� �� �������
*/
SpMatrix SpMatrix::operator * (SpMatrix &obj)
{
	try {
		if (this->itsNumbColumns != obj.itsNumbStrings) //������� ��������� ������
		{
			throw 103;
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "ERROR " << i << ": Noncompliance with multiplication conditions!\n";
	}
	SpMatrix MultOfMatrix(obj.itsNumbColumns, this->itsNumbStrings); // ������� �������
	for (int i = 1; i <= MultOfMatrix.itsNumbStrings; i++) //������� ��� ������ ����� �������
	{

		for (int j = 1; j <= MultOfMatrix.itsNumbColumns; j++) //������� ������ ������ � ������
		{
			float elem = 0 ; // ���������� ��� �������� ������ (i, j)

			for (int k = 1; k <= obj.itsNumbStrings; k++) //���� ���������� elem
			{
				elem += this->GetElem(i, k) * obj.GetElem(k, j); 
			}
			
			MultOfMatrix.SetElem(elem, i, j); //������� ����������� �������� � ������
		}

	}

	return MultOfMatrix;
}

/*
* �������� ��������� ������� �� ����� �����
*/
SpMatrix SpMatrix::operator * (int number)
{
	SpMatrix MultOfMatrix(*this); // ������� ����� �������

	for (int i = 1; i <= MultOfMatrix.itsNumbStrings; i++) //������� ��� ������ ����� �������
	{

		for (int j = 1; j <= MultOfMatrix.itsNumbColumns; j++) //������� ������ ������ � ������
		{
			MultOfMatrix.SetElem(this->GetElem(i, j) * number , i, j);
		}
	}

	return MultOfMatrix;
}

/*
* �������� ��������� ������� �� ������������ �����
*/
SpMatrix SpMatrix::operator * (float number)
{
	SpMatrix MultOfMatrix(*this); // ������� ����� �������

	for (int i = 1; i <= MultOfMatrix.itsNumbStrings; i++) //������� ��� ������ ����� �������
	{

		for (int j = 1; j <= MultOfMatrix.itsNumbColumns; j++) //������� ������ ������ � ������
		{
			MultOfMatrix.SetElem(this->GetElem(i, j) * number, i, j);
		}
	}

	return MultOfMatrix;
}

/*
* ���������� �������� ����������
*/
SpMatrix SpMatrix::operator ++()
{
	for (int i = 1; i <= this->itsNumbStrings; i++) //������� ��� ������ ����� �������
	{

		for (int j = 1; j <= this->itsNumbColumns; j++) //������� ������ ������ � ������
		{
			float elem = this->GetElem(i, j);
			this->SetElem(++elem, i, j);
		}
	}
	return *this;
}

/*
* ����������� �������� ����������
*/
SpMatrix SpMatrix::operator ++(int)
{
	SpMatrix CopyOfThis(*this); 

	for (int i = 1; i <= CopyOfThis.itsNumbStrings; i++) //������� ��� ������ ����� �������
	{

		for (int j = 1; j <= CopyOfThis.itsNumbColumns; j++) //������� ������ ������ � ������
		{
			float elem = CopyOfThis.GetElem(i, j);
			CopyOfThis.SetElem(elem++, i, j);
		}
	}
	return CopyOfThis;
}

/*
* ���������� �������� ����������
*/
SpMatrix SpMatrix::operator --()
{
	for (int i = 1; i <= this->itsNumbStrings; i++) //������� ��� ������ ����� �������
	{

		for (int j = 1; j <= this->itsNumbColumns; j++) //������� ������ ������ � ������
		{
			float elem = this->GetElem(i, j);
			this->SetElem( --elem , i, j);
		}
	}
	return *this;
}

/*
* ����������� �������� ����������
*/
SpMatrix SpMatrix::operator --(int)
{
	SpMatrix CopyOfThis(*this);

	for (int i = 1; i <= CopyOfThis.itsNumbStrings; i++) //������� ��� ������ ����� �������
	{

		for (int j = 1; j <= CopyOfThis.itsNumbColumns; j++) //������� ������ ������ � ������
		{
			float elem = CopyOfThis.GetElem(i, j);
			CopyOfThis.SetElem(elem--, i, j);
		}

	}
	return CopyOfThis;
}

/*
* ���������� � �����������
*/
SpMatrix SpMatrix::operator += (SpMatrix &obj)
{
	*this = *this + obj;
	return *this;
}

/*
* ���������� � �����������
*/
SpMatrix SpMatrix::operator -= (SpMatrix &obj)
{
	*this = *this - obj;
	return *this;
}

/*
* �������� ���������
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
* �������� �������� ���������
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
* �������� ������ �� ������ ��������
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
* �������� ��� ����������� �����  cout
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
	// ������� ��������� �������������
}
