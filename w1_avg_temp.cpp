#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector <int> days;
	for (int i = 0; i < N; i++) {
		unsigned int temp;
		cin >> temp;
		days.push_back(temp);
	}

	int64_t sum = 0;
	for (auto i : days) {
		sum += i;
	}

	vector <int>  temps;
	int days_num = 0;
	for (int i = 0; i < days.size(); i++) {
		if (sum /(static_cast<int> (days.size())) < days[i]) {
			days_num++;
			temps.push_back(i);
		}
	}

	cout << days_num << endl;
	for (auto i : temps) {
		cout << i << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}