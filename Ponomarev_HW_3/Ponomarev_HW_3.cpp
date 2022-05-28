// Ponomarev_HW_3.cpp

#include <iostream>
#include <list>
#include <cstddef>
#include <iomanip>
#include <random>
#include <math.h>

using namespace std;

void pushBackList(list<int> &a)
{
    int sum = 0;

	for (const int &value : a)
	{
		sum += value;
	}

	a.push_back(sum / a.size());
}

void printList(list<int>& a)
{
	for (list<int>::const_iterator i = a.begin(); i != a.end(); ++i)
	{
		cout << *i << (next(i, 1) == a.end() ? " " : ", ");
	}

	cout << endl;
}

void task_1()
{
	list<int> a{ 1, 5, 7, 13 };
	size_t count = 1;

	for (size_t i = 0; i < count; ++i)
	{
		if (i % 5 == 0)
		{
			printList(a);
		}

		pushBackList(a);
	}

	printList(a);
}

//===========================================================================================

class Matrix
{
	const size_t SIZE;
	const size_t capacity;
	double* array;
	double matrixDeterminant = 0.0;

public:
	Matrix(const int size) : SIZE(size), capacity(size * size)
	{
		array = new double[capacity];
	}

	size_t size() const
	{
		return SIZE;
	}

	double determinant() const
	{
		return matrixDeterminant;
	}

	Matrix getMatrix(Matrix& arr, const size_t item)
	{
		Matrix newArray(arr.size() - 1);
		size_t currentRow = 0;

		for (size_t i = 0; i < arr.size(); ++i)
		{
			if (item == i)
			{
				currentRow = i;
				continue;
			}

			//for (size_t j = 0; j < newArray.size(); ++j)
			//{
			//	newArray[currentRow][j] = arr[i][j + 1];
			//}

			++currentRow;
		}

		return newArray;
	}

	double calculateDeterminant(Matrix& arr)
	{
		double determinant = 0.0;

		if (arr.size() == 1 )
		{
			determinant = arr[0][0];
		}
		else if (arr.size() == 2)
		{
			determinant = arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];
		}
		else
		{
			int sign = 1;

			for (size_t i = 0; i < arr.size(); ++i)
			{
				Matrix newArray = getMatrix(arr, i);
				determinant += sign * arr[i][0] * calculateDeterminant(newArray);
				sign = -sign;
			}
		}

		return determinant;
	}

	void fillRandom()
	{
		random_device rd;
		mt19937 mersenne(rd());
		uniform_real_distribution<double> urd(-10.0, 10.0);

		for (size_t i = 0; i < capacity; ++i)
		{
			*(array + i) = round(urd(mersenne) * 10) / 10;
		}

		matrixDeterminant = calculateDeterminant((*this));
	}

	void print()
	{
		for (size_t i = 0; i < capacity;)
		{
			cout << setw(5) << *(array + i++);
		}
	}

	class Iterator
	{
		double* current;

	public:
		Iterator(double* pointer) : current(pointer) {}

		Iterator operator ++()
		{
			++current;
			return* this;
		}

		double operator *()
		{
			return*current;
		}

		double operator[](size_t iterator)
		{
			return* (current + iterator);
		}

		bool operator !=(const Iterator& i)
		{
			return current != i.current;
		}
	};

	Iterator operator[](size_t i)
	{
		return Iterator(array + i * SIZE);
	}

	Iterator begin()
	{
		return Iterator(array);
	}

	Iterator end()
	{
		return Iterator(array + capacity);
	}

	~Matrix()
	{
		delete[] array;
	}
};

void task_2()
{
	for (size_t i = 1; i < 8; ++i)
	{
		cout << "Matrix " << i << 'x' << i << ':' << endl;
		Matrix m(i);
		m.fillRandom();
		m.print();
		cout << "Define matrix: " << setprecision(10) << m.determinant() << "\n\n";
	}
}

//=========================================================================================

void task_3()
{
	Matrix m(4);
	m.fillRandom();

	for (const double& i : m)
	{
		cout << setw(5) << i;
	}

	cout << endl;
}

int main()
{

	task_1();
	//task_2();
	//task_3();

	return 0;
}
