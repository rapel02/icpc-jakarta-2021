#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

const int MAXN = 500010;
int n;
long long A[MAXN];
long long rev_A[MAXN];
long long pos[MAXN];
long long neg[MAXN];

long long max_diff(long long A[], int n){
	memset(pos, 0, sizeof(pos));
	memset(neg, 0, sizeof(neg));
	
	pos[0] = 0;
	pos[n+1] = -1000000000;
	neg[n+1] = 0;
	neg[0] = -1000000000;

	long long sumPos = 0;
	for(int i=1; i<=n; i++){
		sumPos = max(A[i], sumPos + A[i]);
		pos[i] = sumPos;
	}

	long long sumNeg = 0;
	for(int i=n; i>=1; i--){
		sumNeg = min(A[i], sumNeg + A[i]);
		neg[i] = sumNeg;
	}

	long long mx = 0;
	for(int i=1; i<n; i++){
		if(mx < pos[i] - neg[i+1]){
			mx = pos[i] - neg[i+1];
		}
	}

	return mx;
}

int main(){

	while(scanf("%d", &n) != EOF){
		for(int i=0; i<n; i++){
			scanf("%lld", &A[i+1]);
		}
		for(int i=1; i<=n; i++){
			rev_A[i] = A[n-i+1];
		}

		long long res1 = max_diff(A, n);
		long long res2 = max_diff(rev_A, n);

		long long res = max(res1, res2);

		printf("%lld\n", res);
	}

	return 0;
}