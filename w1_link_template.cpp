#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

template<typename key, typename value> value& GetRefStrict(const map<key, value>& m, const key& kk);

template<typename key, typename value>
value& GetRefStrict(map<key, value>& m, const key& kk) {
	if (m.count(kk) == 1) return m[kk];
	else throw runtime_error("GG");
}