#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int arr[10] = {0};
    int A, B, C = 0;
    cin >> A;

    while (A>0) //A의 각 자릿수에 있는 수를 카운트
    {
        arr[A%10]++;
        A/=10;
    }

    B = (arr[6] + arr[9] + 1)/2; //6과 9는 같은 숫자 취급
    arr[6] = 0;
    arr[9] = B;


    for(int i = 0; i <10; i++) //가장 많이 카운트된 횟수 출력
    {
        if (arr[i] > C) 
            C = arr[i];
    }

    cout << C; 

    return 0;
}