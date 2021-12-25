#include<iostream>
#include"UFSets.hpp"

using namespace std;
int main() {
	UFSets ufsets(10);
	int n;
	while (true) {
		cin >> n;
		if (n == 1) {
			int d;
			cin >> d;
			cout << ufsets.Find(d) << "\n";
		}
		if (n == 2) {
			int a, b;
			cin >> a >> b;
			cout << ufsets.Union(a, b) << "\n";
		}
	}
}