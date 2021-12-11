// 09-排序3 Insertion or Heap Sort (25 point(s))
// According to Wikipedia:

// Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort 
// removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until
//  no input elements remain.

// Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest 
// element and moving that to the sorted region. it involves the use of a heap data structure rather than a linear-time search to find the maximum.

// Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can 
// you tell which sorting method we are using?

// Input Specification:
// Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). Then in the next line, N integers 
// are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target 
// sequence is always ascending. All the numbers in a line are separated by a space.

// Output Specification:
// For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result. 
// Then run this method for one more iteration and output in the second line the resulting sequence. It is guaranteed that the answer is unique 
// for each test case. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

// Sample Input 1:
// 10
// 3 1 2 8 7 5 9 4 6 0
// 1 2 3 7 8 5 9 4 6 0
// 结尾无空行
// Sample Output 1:
// Insertion Sort
// 1 2 3 5 7 8 9 4 6 0
// 结尾无空行
// Sample Input 2:
// 10
// 3 1 2 8 7 5 9 4 6 0
// 6 4 5 1 0 3 2 7 8 9
// Sample Output 2:
// Heap Sort
// 5 4 3 1 0 2 6 7 8 9

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int n, t;
	bool isInsert = true;
	scanf("%d", &n);
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	for (int i = 0; i < n; ++i)
		scanf("%d", &b[i]);
	for (t = 1; t < n; ++t)
		if (b[t] < b[t-1]) break;
	for(int i = t; i < n; ++i)
		if (a[i] != b[i]) {
			isInsert = false;
			break;
		}
	if (isInsert) {
		printf("Insertion Sort\n");
		sort(b.begin(), b.begin() + t + 1);
	}
	else {
		printf("Heap Sort\n");
		for (t = n - 1; t >= 0; --t)
			if (b[t] < b[0]) break;
		swap(b[t], b[0]);
		int i = 0, j = i * 2 + 1;
        while (j <= t-1) {
            if (j + 1 <= t-1 && b[j] < b[j + 1]) j = j + 1;
            if (b[i] > b[j]) break;
            swap(b[i], b[j]);
            i = j; j = i * 2 + 1;
        }
	}
	for (int i = 0; i < n; ++i)
		printf("%d%s", b[i], i == n - 1 ? "\n" : " ");

	return 0;
}
