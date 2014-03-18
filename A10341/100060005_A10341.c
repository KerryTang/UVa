#include <stdio.h>
#include <math.h>

float tri_equation(float x, int q, int r, int s);
float rmd_euqation(float x, int q, int t, int u);

int main(int argc, char *argv[]){
    int p, q, r, s, t, u;
    float upper_bound, lower_bound, x, result_x, result_u, result_l;
    while(~scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u)){
		upper_bound = 1;
		lower_bound = 0;
        result_u = tri_equation(upper_bound, q, r, s) + rmd_euqation(upper_bound, p, t, u);
        result_l = tri_equation(lower_bound , q, r, s) + rmd_euqation(lower_bound, p, t, u);

        if(result_u*result_l > 0){
            printf("No solution\n");
            continue;
        }

		while(upper_bound - lower_bound > 1e-7){
            x = (upper_bound + lower_bound)/2;
            result_u = tri_equation(upper_bound, q, r, s) + rmd_euqation(upper_bound, p, t, u);
            result_x = tri_equation(x, q, r, s) + rmd_euqation(x, p, t, u);

            if((result_x * result_u < 0) || (result_u >= 0 && result_x > result_u) || (result_u <= 0 && result_u > result_x))
  	          lower_bound = x;
            else
              upper_bound = x;
        }

		printf("%.4f\n", x);
    }
    return 0;

}


float tri_equation(float x, int q, int r, int s){
	return q*sin(x) + r*cos(x) + s*tan(x);
}

float rmd_euqation(float x, int p, int t, int u){
	return p*exp(-x) + t*x*x + u;
}
