/*
 * Дан двухмерный массив разрядностью [n,m], заполненный случайным образом. 
 * Удалить в нем вссе столбцы, первый элемент которого больше последнего.
 */

#include <iostream>
#include <iomanip>
#include <ctime>

// инициализация матрицы
int** initMatrix(const int CountRows, const int CountColumns)
{
	int** array = new int* [CountRows];
	for (int i = 0; i < CountRows; ++i)
		array[i] = new int[CountColumns];

	return array;
}
// инициализация вектора
int* initVector(const int CountColumns)
{
	int* array = new int [CountColumns];

	return array;
}
// вывод на экран матрицы
void printMatrix(int** array, const int CountRows, const int CountColumns)
{
	std::cout << "\nMatrix:\n";
	for (int i = 0; i < CountRows; ++i, std::cout << std::endl)
		for (int j = 0; j < CountColumns; ++j)
			std::cout << std::setw(5) << array[i][j];
	std::cout << "\n";
}
// вывод на экран вектора
void printVector(int* array, const int CountColumns)
{
	std::cout << "\nVector:\n";
	for (int i = 0; i < CountColumns; ++i, std::cout << std::endl)
		std::cout << std::setw(5) << array[i];
	std::cout << "\n";
}
// установка случайных значений в элементы матрицы
void setRandMatrix(int** array, const int CountRows, const int CountColumns)
{
	for (int i = 0; i < CountRows; ++i, std::cout << std::endl)
		for (int j = 0; j < CountColumns; ++j)
			// рандомное значение (от 0 до 99)
			array[i][j] = rand() % 100;
}
// освобождение памяти для матрицы
void destroy(int** array, const int CountRows)
{
	for (int i = 0; i < CountRows; ++i)
		delete[]array[i];
	delete[] array;
}
// освобождение памяти для вектора
void destroy(int* array)
{
	delete[] array;
}
// копирование матрицы
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
// функция для поиска позиции удаления
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
		// ничего не нашли
		return nullptr;
	}

	int* result = new int[++findedColumns];

	if (copyMatrix(vector, CountColumns, result, findedColumns) == -1)
	{
		// что-то не так
		return nullptr;
	}

	destroy(vector);

	return result;
}
// функция для удаления строки
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
// фнкция для удаления колонны
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
	// Переменные для хранения кол-ва строк и столбцов
	int CountRows, CountColumns;
	std::cout << "Enter the size of the matrix (example: 5 6): ";
	std::cin >> CountRows >> CountColumns;
	// Выделение памяти
	int** array = initMatrix(CountRows, CountColumns);
	setRandMatrix(array, CountRows, CountColumns);
	printMatrix(array, CountRows, CountColumns);
	// Поиск столбца для удаления
	int findedColumns = -1;
	int* eraseVector = findColumnErasePosition(array, CountRows, CountColumns, findedColumns);
	if (eraseVector == nullptr)
	{
		// что-то пошло не так
		return -1;
	}
	printVector(eraseVector, findedColumns);
	// Удаление колонн
	int** result = eraseColumn(&array, CountRows, CountColumns, eraseVector[findedColumns - 1]);
	for (int i = findedColumns - 2; i > -1; --i)
	{
		result = eraseColumn(&result, CountRows, CountColumns, eraseVector[i]);
	}
	// Вывод результирующей матрицы
	printMatrix(result, CountRows, CountColumns);
	// Освобождаем память
	destroy(array, CountRows); destroy(eraseVector); 

	return 0;
}