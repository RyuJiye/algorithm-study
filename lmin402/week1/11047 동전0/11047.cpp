#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int>v;

int main() {
	int n, k,tmp;
	cin >> n >> k; 


	for (int i = 0; i < n; i++) {
		cin >> tmp;
		v.push_back(tmp); 
	}

	int count = 0; //K원을 만드는데 필요한 동전의 개수의 최소값
	for (int i = v.size() - 1; i >= 0; i--) { 
		if (k == 0) break;

		if (k >= v[i]) { 
			count += (k / v[i]); 
			k = k % v[i];
		}
	}

	cout << count << '\n';
}