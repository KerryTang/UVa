#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORKYARD_SIZE 50
#define PILE_SIZE 20
#define MAX_SIZE 10000
#define PRINT_MAX 10

int ans_len;
int profit[WORKYARD_SIZE][PILE_SIZE], buy[WORKYARD_SIZE][PILE_SIZE], max_profit[WORKYARD_SIZE], buy_len[WORKYARD_SIZE], ans[MAX_SIZE];

int  int_comparator(const void *a, const void *b);
void Depth_Search(const int n, const int stop, int value);

int main(const int argc, const char *argv[]){

	/* W: #workyards, B:#piles in the workyard */
	int  i, j, tmp, W, B, total_max_profit, cnt;

	#ifndef ONLINE_JUDGE
	FILE *f_in, *f_out;
	f_in  = freopen("data.in", "r", stdin);
	f_out = freopen("data.out", "w", stdout);
	#endif
	cnt = 0;
	while(scanf("%d", &W) && (W != 0)){
		/* Output format requires a new line between cases. */
		if(cnt != 0)
			printf("\n");

		/* The default max profit for each workyard is 0 */
		memset(max_profit, 0, sizeof(max_profit));
		cnt++;

		for( i = 0; i < W; i++){
			scanf("%d", &B);
			for( j = 0; j < B; j++){
				scanf(" %d", &tmp);
				/* Cumulate the profit for buying each goods */
				if(j == 0)
					profit[i][j] = 10 - tmp;
				else
					profit[i][j] = profit[i][j-1] + 10 - tmp;
				
				if(max_profit[i] < profit[i][j])
					max_profit[i] = profit[i][j];
			}
			#ifdef DEBUG
			printf("max_profit[%d]:%3d profit[%d]: ", i, max_profit[i], i);
			for( j = 0; j < B; j++)
				printf("%d ", profit[i][j]);
			printf("\n");
			#endif

			/* calculate how many goods can buy to reach the max profit for each workyard */
			buy_len[i] = 0;
			for( j = 0; j < B; j++){
				if(max_profit[i] == profit[i][j]){
					buy[i][buy_len[i]] = j+1;  /* j+1 stands for #goods to buy */
					buy_len[i]++;
				}
			}

			#ifdef DEBUG
			printf("buy[%d]: ", i);
			for( j = 0; j < buy_len[i]; j++)
				printf("%d ", buy[i][j]);
			printf("\n");
			#endif

		}
		total_max_profit = 0;
		for(i = 0; i < W; i++)
			total_max_profit += max_profit[i];

		ans_len = 0;
		memset(ans, 0, sizeof(ans));
		
		Depth_Search(0, W, 0);	
		qsort(ans, ans_len, sizeof(int), int_comparator);
		
		#ifdef DEBUG
		printf("ans: ");
		for(i = 0; i < ans_len; i++)
			printf("%d ", ans[i]);
		printf("\b\n");
		#endif

		printf("Workyards %d\nMaximum profit is %d.\n", cnt, total_max_profit);
        printf("Number of pruls to buy: ");

        for(i = 0, j = 0; (j < PRINT_MAX-1) && (i < ans_len-1); i++){
            if( (i == 0) || (i != 0 && ans[i] != ans[i-1]) ){
                printf("%d ", ans[i]);
                j++;
            }
        }

        for(; i < ans_len; i++){
            if((i == 0) || ((i != 0) && (ans[i] != ans[i-1])) ){
                printf("%d\n", ans[i]);
                break;
            }
        }
	}


	#ifndef ONLINE_JUDGE
	fclose(f_in);
	fclose(f_out);
	#endif
	
	
	return 0;
}


int int_comparator(const void *a, const void *b){
	int i1, i2;
	i1 = *(int *)a;
	i2 = *(int *)b;

	if(i1 > i2)
		return 1;
	else if(i1 == i2)
		return 0;
	else
		return -1;
}
void Depth_Search(const int n, const int stop, int value){
	int i;
	/* Depth_Search leaf */
	if( n == stop){
		ans[ans_len++] = value;
		return;
	}

	if(max_profit[n] == 0)
		Depth_Search(n+1, stop, value);
	
	for( i = 0; i < buy_len[n]; i++)
		Depth_Search(n+1, stop, value + buy[n][i]);

}
