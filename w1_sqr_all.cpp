#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;



template <typename F, typename S> pair<F, S> operator*(pair<F, S> p1, const pair<F, S> p2);
template <typename T> vector<T> Sqr(const vector <T>& v);
template <typename F, typename S> map<F, S> Sqr(const map<F, S>& m);
template <typename T> T Sqr(T x);

template <typename T>
vector<T> Sqr(const vector <T>& v) {
	vector<T> v_tmp = v;
	for (auto& i : v_tmp) {
		i = Sqr(i);
	}

	return v_tmp;
}


template <typename F, typename S>
pair<F, S> operator*(pair<F, S> p1, pair<F, S> p2) {
	return { p1.first * p2.first, p1.second * p2.second };
}

template <typename F, typename S>
map<F, S> Sqr(const map<F, S>& m) {
	map<F, S> m_tmp;
	for (auto& i : m) {
		m_tmp[i.first] = Sqr(i.second);
	}

	return m_tmp;
}

template <typename T>
T Sqr(T x) {
	return x * x;
}