/*
 * ��� ���������� ������ ������������ [n,m], ����������� ��������� �������. 
 * ������� � ��� ���� �������, ������ ������� �������� ������ ����������.
 */

#include <iostream>
#include <iomanip>
#include <ctime>

// ������������� �������
int** initMatrix(const int CountRows, const int CountColumns)
{
	int** array = new int* [CountRows];
	for (int i = 0; i < CountRows; ++i)
		array[i] = new int[CountColumns];

	return array;
}
// ������������� �������
int* initVector(const int CountColumns)
{
	int* array = new int [CountColumns];

	return array;
}
// ����� �� ����� �������
void printMatrix(int** array, const int CountRows, const int CountColumns)
{
	std::cout << "\nMatrix:\n";
	for (int i = 0; i < CountRows; ++i, std::cout << std::endl)
		for (int j = 0; j < CountColumns; ++j)
			std::cout << std::setw(5) << array[i][j];
	std::cout << "\n";
}
// ����� �� ����� �������
void printVector(int* array, const int CountColumns)
{
	std::cout << "\nVector:\n";
	for (int i = 0; i < CountColumns; ++i, std::cout << std::endl)
		std::cout << std::setw(5) << array[i];
	std::cout << "\n";
}
// ��������� ��������� �������� � �������� �������
void setRandMatrix(int** array, const int CountRows, const int CountColumns)
{
	for (int i = 0; i < CountRows; ++i, std::cout << std::endl)
		for (int j = 0; j < CountColumns; ++j)
			// ��������� �������� (�� 0 �� 99)
			array[i][j] = rand() % 100;
}
// ������������ ������ ��� �������
void destroy(int** array, const int CountRows)
{
	for (int i = 0; i < CountRows; ++i)
		delete[]array[i];
	delete[] array;
}
// ������������ ������ ��� �������
void destroy(int* array)
{
	delete[] array;
}
// ����������� �������
int copyMatrix(int* vector, const int CountColumnsVector, int* copyed, const int CountColumnsCopyed)
{
	if (CountColumnsCopyed > CountColumnsVector)
	{
		return -1;
	}

	for (int i = 0; i < CountColumnsCopyed; ++i)
	{
		copyed[i] = vector[i];
	}

	return 0;
}
// ������� ��� ������ ������� ��������
int* findColumnErasePosition(int** array, const int CountRows, const int CountColumns, int &findedColumns)
{
	int columnErasePosition = 0;
	int* vector = initVector(CountColumns);

	for (int j = 0; j < CountColumns; ++j)
	{
		if (array[0][j] > array[CountRows - 1][j])
		{
			vector[++findedColumns] = j;
		}
	}

	if (findedColumns < 0)
	{
		// ������ �� �����
		return nullptr;
	}

	int* result = new int[++findedColumns];

	if (copyMatrix(vector, CountColumns, result, findedColumns) == -1)
	{
		// ���-�� �� ���
		return nullptr;
	}

	destroy(vector);

	return result;
}
// ������� ��� �������� ������
/*int** eraseRow(int*** array, int& CountRow, int nDelCol) {
	int** tempArray = new int* [--CountRow];

	bool bFlag;
	for (int i = 0, bFlag = false; i < CountRow; ++i) 
	{
		if (nDelCol == i) 
		{ 
			bFlag = true; 
			delete[](*array)[i]; 
		}
		tempArray[i] = (bFlag) ? (*array)[i + 1] : (*array)[i];
	}
	delete[](*array);
	return (*array = tempArray);
}*/
// ������ ��� �������� �������
int** eraseColumn(int*** Array, int CountRows, int& CountColumns, int nDelRow) {
	int* tempArray;
	bool bFlag = false; 
	--CountColumns;

	for (int i = 0; i < CountRows; ++i, bFlag = false)
	{
		tempArray = new int[CountColumns];
		for (int j = 0; j < CountColumns; ++j)
		{
			if (nDelRow == j) 
			{ 
				bFlag = true; 
			}
			tempArray[j] = (bFlag) ? (*Array)[i][j + 1] : (*Array)[i][j];
		}
		delete[](*Array)[i];
		(*Array)[i] = tempArray;
	}
	return *Array;
}

int main()
{
	srand(time(NULL));
	// ���������� ��� �������� ���-�� ����� � ��������
	int CountRows, CountColumns;
	std::cout << "Enter the size of the matrix (example: 5 6): ";
	std::cin >> CountRows >> CountColumns;
	// ��������� ������
	int** array = initMatrix(CountRows, CountColumns);
	setRandMatrix(array, CountRows, CountColumns);
	printMatrix(array, CountRows, CountColumns);
	// ����� ������� ��� ��������
	int findedColumns = -1;
	int* eraseVector = findColumnErasePosition(array, CountRows, CountColumns, findedColumns);
	if (eraseVector == nullptr)
	{
		// ���-�� ����� �� ���
		return -1;
	}
	printVector(eraseVector, findedColumns);
	// �������� ������
	int** result = eraseColumn(&array, CountRows, CountColumns, eraseVector[findedColumns - 1]);
	for (int i = findedColumns - 2; i > -1; --i)
	{
		result = eraseColumn(&result, CountRows, CountColumns, eraseVector[i]);
	}
	// ����� �������������� �������
	printMatrix(result, CountRows, CountColumns);
	// ����������� ������
	destroy(array, CountRows); destroy(eraseVector); 

	return 0;
}