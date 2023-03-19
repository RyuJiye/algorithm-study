#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
	long long x;
	long long y;
};
struct Cut {
	Point s;
	Point e;
	long long w;
};

long long ccw(Point p1, Point p2, Point p3) {
	if ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y) > 0) return 1;
	if ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y) < 0) return -1;
	else return 0;
	//그냥 리턴 바로 하면 오버플로우남
}

bool isCross(Cut c1, Cut c2) {
	if (ccw(c1.s, c1.e, c2.s) * ccw(c1.s, c1.e, c2.e) < 0
		&& ccw(c2.s, c2.e, c1.s) * ccw(c2.s, c2.e, c1.e) < 0)
		return true;
	else
		return false;
}

bool wlCmp(Cut c1, Cut c2) {//가중치 오름차순
	return c1.w < c2.w;	
}

int main() {
	int n;
	cin >> n;
	Cut* cut = new Cut[n];
	for (int i = 0; i < n; i++) cin >> cut[i].s.x >> cut[i].s.y >> cut[i].e.x >> cut[i].e.y >> cut[i].w;
	//입력 받기 끝
	//서로 교차하면 가중치 작은 거부터 먼저
	sort(cut, cut + n, wlCmp);
	long long ans = 0;
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int j = i + 1; j < n; j++)
		{
			if (isCross(cut[i], cut[j])) count++;
		}
		ans += cut[i].w * (count + 1);
	}
	cout << ans;
}