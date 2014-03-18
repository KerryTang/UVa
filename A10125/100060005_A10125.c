#include <stdio.h>
#include <stdlib.h>
#define PROBLEM_SIZE 1000

/* X = a + b */
typedef struct{
	long long int a, b, sum;
}AB;

int long_comparator(const void *a, const void *b);
int B_Search(const long long int array[], const int size, const long long int n);
int valid(const long long int n1, const long long int n2, const long long int n3, const long long int n4);

int main(const int argc, const char *argv[]){
	int  i, j, t_flag, S_len, X_len;
	long long int S[PROBLEM_SIZE] = {0}, c;
	/*Stack memory isn't large enoughto open 1e6 array memory. Need to use heap instead. */
	AB *X = (AB *)malloc(PROBLEM_SIZE*PROBLEM_SIZE*sizeof(AB));

	#ifndef ONLINE_JUDGE
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
	#endif

	while(scanf("%d", &S_len) && (S_len != 0)){

		for( i = 0; i < S_len; i++)
			scanf("%lld",&S[i]);

		qsort(S, S_len, sizeof(long long int), long_comparator);

		/* check S */
		#ifdef DEBUG
		printf("%d\n", S_len);
		for(i = 0; i < S_len; i++)
			printf("%lld ", S[i]);
		printf("\n");
		#endif
		/* calculate X = a + b */
		X_len = 0;
		for( i = 0; i < S_len-1; i++){
			for( j = i+1; j < S_len; j++){

				X[X_len++] = (AB) { .a = S[i], .b = S[j], .sum = S[i]+S[j]};

				#ifdef DEBUG
				printf("X[%d]=(%lld, %lld, %lld)\n", X_len-1, X[X_len-1].a, X[X_len-1].b, X[X_len-1].sum);
				#endif
			}
		}

		t_flag = 0;
		/*Try to find (c, d) combination from d = maximum of S*/
		for(i = S_len-1; i >= 0; i--){
			for( j = 0; j < X_len; j++){
				c = S[i] - X[j].sum;
				if(B_Search(S, S_len, c)){
					if(valid(X[j].a, X[j].b, c, S[i])){
						t_flag = 1;
						break;
					}
				}
			}
			if(t_flag)
				break;
		}
		if(t_flag)
			printf("%lld\n", S[i]);
		else
			printf("no solution\n");

	}

	free(X);
	return 0;
}

int long_comparator(const void *a, const void *b){
	long long int i1, i2;
	i1 = *(long long int *)a;
	i2 = *(long long int *)b;

	if(i1 > i2)
		return 1;
	else if(i1 == i2)
		return 0;
	else
		return -1;
}

int B_Search(const long long int array[], const int size, const long long int n){
	int U, L, X;
	
	U = size - 1;
	L = 0;

	while(U >= L){
		X = (U + L)>>1;
		
		if(n < array[X])
			U = X - 1;
		else if(n == array[X])
			return 1;
		else
			L = X + 1;
	}

	return 0;
}

int valid(const long long int n1, const long long int n2, const long long int n3, const long long int n4){
	/* a has been set to be different from b during construct X array. */
	if((n1 == n3) || (n1 == n4) || (n2 == n3) || (n2 == n4) || (n3 == n4))
		return 0;
	else
		return 1;
}
