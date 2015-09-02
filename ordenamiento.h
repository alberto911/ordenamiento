#include <algorithm>
#include <list>
#include <vector>
#include <cmath>
#include "treeNode.h"

using namespace std;

class Ordenamiento {
public:
	static void bubbleSort(int a[], int n);
	static void cocktailSort(int a[], int n);
	static void insertionSort(int a[], int n);
	static void bucketSort(int a[], int n, int k);
	static void countingSort(int a[], int n, int k);
	static void vectorCountingSort(int a[], int n, int k); // Utilizando vectores, para N = 1000000
	static void mergeSort(int a[], int begin, int end, int n);
	static void merge(int a[], int begin, int middle, int end, int n);
	static void binaryTreeSort(int a[], int n);
	static void radixSort(int a[], int n);
	static void shellSort(int a[], int n);
	static void selectionSort(int a[], int n);
	static void heapSort(int a[], int n);
	static void quickSort(int a[], int lo, int hi);
private:
	static void insert(TreeNode*& node, int number);
	static void inOrder(TreeNode* node, vector<int>& a);
	static void countingSort(int a[], int n, int k, int exp); // Para radix sort
	static void heapify(int a[], int n);
	static void siftDown(int a[], int start, int end);
	static int partition(int a[], int lo, int hi);
};

void Ordenamiento::bubbleSort(int a[], int n) {
	bool swapped = true;
	int j = 0;

	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < n - j; ++i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
	}
}

void Ordenamiento::cocktailSort(int a[], int n) {
	bool swapped = true;

	while (swapped) {
		swapped = false;
		
		for (int i = 0; i < n - 1; ++i) {
			if (a[i] > a[i + 1]) {
				std::swap(a[i], a[i + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			break;
		swapped = false;

		for (int i = n - 1; i > 0; --i) {
			if (a[i - 1] > a[i]) {
				swap(a[i], a[i - 1]);
				swapped = true;
			}
		}
	}
}

void Ordenamiento::insertionSort(int a[], int n) {
	for (int i = 1; i < n; ++i) {
		for (int j = i; j > 0 && a[j - 1] > a[j]; --j)
			swap(a[j], a[j - 1]);
	}
}

void Ordenamiento::bucketSort(int a[], int n, int k) {
	list<int> buckets[k];
	
	for (int i = 0; i < n; ++i)
		buckets[(a[i] * k) / n].push_back(a[i]);

	int pos = 0;

	for (int i = 0; i < k; ++i) {
		buckets[i].sort();
		while(!buckets[i].empty()) {
			a[pos++] = buckets[i].front();
			buckets[i].pop_front();
		}
	}
}

void Ordenamiento::countingSort(int a[], int n, int k) {	
	int count[k];
	int aux[n];
		
	for (int i = 0; i < k; ++i)
		count[i] = 0;
	
	for (int i = 0; i < n; ++i) {
		aux[i] = a[i];		
		++count[aux[i]];
	}

	int total = 0;
	for (int i = 0; i < k; ++i) {
		int oldCount = count[i];	
		count[i] = total;
		total += oldCount;
	}

	for (int i = 0; i < n; ++i)
		a[count[aux[i]]++] = aux[i];
}

void Ordenamiento::vectorCountingSort(int a[], int n, int k) {
	vector<int> count (k, 0);
	vector<int> aux (a, a+n);

	vector<int>::iterator it;

	for (it=aux.begin(); it<aux.end(); it++)
		++count[*it];

	int total = 0;
	for (it=count.begin(); it<count.end(); it++) {
		int oldCount = *it;
		*it = total;
		total += oldCount;
	}

	for (it=aux.begin(); it<aux.end(); it++)
		a[count[*it]++] = *it;
}

void Ordenamiento::countingSort(int a[], int n, int k, int exp) {
	int count[k];
	int aux[n];
		
	for (int i = 0; i < k; ++i)
		count[i] = 0;
	
	for (int i = 0; i < n; ++i) {
		aux[i] = a[i];		
		++count[(aux[i]/exp) % 10];
	}

	int total = 0;
	for (int i = 0; i < k; ++i) {
		int oldCount = count[i];	
		count[i] = total;
		total += oldCount;
	}

	for (int i = 0; i < n; ++i)
		a[count[(aux[i]/exp) % 10]++] = aux[i];
}

void Ordenamiento::mergeSort(int a[], int begin, int end, int n) {
	if (end - begin < 2)
		return;

	int middle = (begin + end) / 2;
	mergeSort(a, begin, middle, n);
	mergeSort(a, middle, end, n);
	merge(a, begin, middle, end, n);
}

void Ordenamiento::merge(int a[], int begin, int middle, int end, int n) {
	int i = begin, j = middle;
	int aux[n];

	for (int k = begin; k < end; ++k) {
		if (i < middle && (j >= end || a[i] <= a[j]))
			aux[k] = a[i++];
		else
			aux[k] = a[j++];
	}

	for (int k = begin; k < end; ++k)
		a[k] = aux[k];
}

void Ordenamiento::binaryTreeSort(int a[], int n) {
	TreeNode* root = nullptr;
	for (int i = 0; i < n; ++i)
		insert(root, a[i]);

	vector<int> aux;
	inOrder(root, aux);

	TreeNode::destroy(root);

	for (int i = 0; i < aux.size(); ++i)
		a[i] = aux[i]; 
}

void Ordenamiento::insert(TreeNode*& node, int number) {
	if (!node)
		node = new TreeNode(number);
	else if (number < node->number)
		insert(node->left, number);
	else
		insert(node->right, number);
}

void Ordenamiento::inOrder(TreeNode* node, vector<int>& a) {
	if (node) {
		inOrder(node->left, a);
		a.push_back(node->number);
		inOrder(node->right, a);
	}
}

void Ordenamiento::radixSort(int a[], int n) {
	for(int exp = 1; (n-1)/exp > 1; exp *= 10)
		countingSort(a, n, 10, exp);
}

void Ordenamiento::shellSort(int a[], int n) {
	int gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1};
	
	for (int i = 0; i < 8; ++i) {
		int gap = gaps[i];
		for (int j = gap; j < n; ++j) {
			int temp = a[j], k;
			for (k = j; k >= gap && a[k - gap] > temp; k -= gap)
				a[k] = a[k - gap];
			a[k] = temp;
		}
	} 
}

void Ordenamiento::selectionSort(int a[], int n) {
	for (int i = 0; i < n-1; ++i) {
		int min = i;
		for (int j = i+1; j < n; ++j) {
			if (a[j] < a[min])
				min = j;
		}
		
		if (min != i)
			swap(a[i], a[min]);
	}
}

void Ordenamiento::heapSort(int a[], int n) {
	heapify(a, n);
	int end = n - 1;
	while (end > 0) {
		swap(a[end--], a[0]);
		siftDown(a, 0, end);
	}
}

void Ordenamiento::heapify(int a[], int n) {
	int start = floor((n-2) / 2);
	while (start >= 0) {
		siftDown(a, start, n-1);
		--start;
	}
}

void Ordenamiento::siftDown(int a[], int start, int end) {
	int root = start;
	while (root * 2 + 1 <= end) {
		int child = root * 2 + 1;
		int sw = root;
		if (a[sw] < a[child])
			sw = child;
		if (child+1 <= end && a[sw] < a[child+1])
			sw = child + 1;
		if (sw == root)
			return;
		else {
			swap(a[root], a[sw]);
			root = sw;
		}
	}
}

void Ordenamiento::quickSort(int a[], int lo, int hi) {
	if (lo < hi) {
		int p = partition(a, lo, hi);
		quickSort(a, lo, p);
		quickSort(a, p+1, hi);
	}
}

int Ordenamiento::partition(int a[], int lo, int hi) {
	int pivot = a[lo];
	int i = lo - 1;
	int j = hi + 1;

	while (true) {
		do {
			--j;
		} while (a[j] > pivot);

		do {
			++i;
		} while (a[i] < pivot);
		
		if (i < j)
			swap(a[i], a[j]);
		else
			return j;
	}
}
