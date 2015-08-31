#include <iostream>
#include <cstdlib>
#include "ordenamiento.h"

#define N 100

using namespace std;

int main() {
	int a[N];
	for (int i = 0; i < N; ++i)
		a[i] = rand() % N;

	Ordenamiento::quickSort(a, 0, N-1);

	return 0;
}

