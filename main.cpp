#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int t;
    long long x, y;
    cin >> t;
    while(t > 0){
        cin >> x >> y;
        long long ans = 0, a = 0;
        while(a*a <= y - x) a++;
        a--;
        ans = 2 * a - 1;
        long long remain  = y - x - a*a;
        ans += (long long)ceil((double)remain / (double)a);
        cout << ans << "\n";
        t--;
    }
}
