#include <stdio.h>
int paper[128][128], w, b;
void color(int x, int y, int n){
    int cnt = 0;
    for (int i = x; i < x+n; i++)
        for (int j = y; j < y+n; j++)
            paper[i][j] && cnt++;
    if (cnt == n*n)	b++;
    else if (!cnt) w++;
    else {
        color(x, y, n/2);
        color(x, y+n/2, n/2);
        color(x+n/2, y, n/2);
        color(x+n/2, y+n/2, n/2);
    }	
}
int main(){
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N*N; i++)
        scanf("%d", &paper[i/N][i%N]);
    color(0, 0, N);
    printf("%d\n%d", w, b);
}