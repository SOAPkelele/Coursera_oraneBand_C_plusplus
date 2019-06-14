#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// ���������� �����
// * ����� Matrix
// * �������� ����� ��� ������ Matrix �� ������ istream
// * �������� ������ ������ Matrix � ����� ostream
// * �������� �������� �� ��������� ���� �������� ������ Matrix
// * �������� �������� ���� �������� ������ Matrix


class Matrix {
public:
	Matrix() {
		num_rows = 0;
		num_cols = 0;
	}

	Matrix(int rows, int cols) {
		num_rows = rows;
		num_cols = cols;
	}

	int At(int row, int col) {
		return matrix;
	}

	void Reset(int rows, int cols) {
		num_rows = rows;
		num_cols = cols;
	}

	int GetNumRows() const{
		return num_rows;
	}

	int GetNumColumns() const {
		return num_cols;
	}

private:
	int num_rows;
	int num_cols;
	vector <vector<int>> matrix;
};


int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;
	system("pause");
	return 0;
}