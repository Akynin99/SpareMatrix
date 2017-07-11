#include "stdafx.h"
typedef unsigned short int USHORT;
using std::istream;
using std::ostream;
//
//								��������!
//
// ������ ������� - ������, ����� - �������! � ������� �������� (���� �� ��������).
// ���� � � ����������, � � ��������� � ������ ������ �������, � � ��� ������ ���!
// 
//
class SpMatrix
{

	USHORT itsNumbColumns;	// ���������� ��������
	USHORT itsNumbStrings;	// ���������� �����
	USHORT itsNumbElem;		// ���������� ��������� (� �������� ����� ���� � �� ��������� ��� ����, � ������������ ������������ �������� � �����)

	std::vector<float> NonZeroElems;	// � ���� ������� �������� �������� ��������� ��������� 
	std::vector<USHORT> Addresses;		// � ���� ������� �������� ������� ��������� ��������� (���� ���������� � 1), 
										// ������ ������� - � ������ ������� � ������ ������, ������ - � ������ ������ � �� ������ ������� � �.�.
public:
	SpMatrix();											// ������������ ��� �����., ������� ������� 2�2
	SpMatrix(USHORT numbStrings, USHORT numbColumns);	// ����������� ������� ������ ���������� ����� � ��������
	//SpMatrix(float * massive, USHORT numbStrings, USHORT numbColumns); // ����������� ������� ������� � �������� ��������, �������� ����� �� ������� (�� ������)
	SpMatrix(const SpMatrix & obj);						// ����������� �����������

	void Show();										// ������� ����������� ������� � ������� 
	void ShowSpare();									// ������� ����������� ��������� ��������� (�������� � ������)
	float GetElem(int string, int column);				// ������� ������ ��������
	void SetElem(float elem, int string, int column);	// ������� ��������� ��������


	void operator = (const SpMatrix &obj);	// �������� ������������
	SpMatrix operator + (SpMatrix &obj);	// �������� �������� ������
	SpMatrix operator - (SpMatrix &obj);	//	�������� ��������� ������
	SpMatrix operator * (SpMatrix &obj);	// �������� ��������� ������� �� �������
	SpMatrix operator * (int number);		// �������� ��������� ������� �� ����� �����
	SpMatrix operator * (float number);		// �������� ��������� ������� �� ������������ �����
	SpMatrix operator ++ ();				// ���������� �������� ����������
	SpMatrix operator ++ (int);				// ����������� �������� ����������
	SpMatrix operator -- ();				// ���������� �������� ����������
	SpMatrix operator -- (int);				// ����������� �������� ����������
	SpMatrix operator += (SpMatrix &obj);	// ���������� � �����������
	SpMatrix operator -= (SpMatrix &obj);
	bool operator == (SpMatrix &obj) const; // ��������� ���������
	bool operator != (SpMatrix &obj) const;
	float operator [] (int number);			// �������� ������ �� ������ ��������
	friend ostream& operator << (ostream& a, const SpMatrix obj); // �������� ��� ����������� �����  cout
	
	~SpMatrix();	// ����������
};

