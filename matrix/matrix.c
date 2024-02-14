#include <stdio.h>

int gaussMethod(int n, int m, int *A)//m - lines, n - cols
{
	int i, j, k, l, r;
	
	i = 0;
	j = 0;
	
	while (i < m && j < n){
		r = 0;
		for (k = i; k < m; ++k){
			if (a[k*n + j] > r){
				l = k;
				r = a[k*n + j];
			}
		}
		if (r == 0){
			for (k = j; k < n; ++k){
				a[k*n + j] = 0;
			}
			++j;
			continue;
		}

		if (l != i){
			for (k = j; k < n; ++k){
				r = a[i*n + k];
				a[i*n + k] = a[l*n + k];
				a[l*n + k] = -r;
			}
		}

		for (k = i + 1; k < m; ++k){
			r = (-a[k*n + j] / a[i*n + j]);
			a[k*n + j] = 0;

			for (l = j + 1; l < n; ++l){
				a[k*n + l] += r * a[i*n + l];
			}
		}
		++i;
		++j;
	}
	return i;
}


