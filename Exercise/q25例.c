// 09-排序2 Insert or Merge (25 point(s))
// According to Wikipedia:

// Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort 
// removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no 
// input elements remain.

// Merge sort works as follows: Divide the unsorted list into N sublists, each containing 1 element (a list of 1 element is considered sorted).
//  Then repeatedly merge two adjacent sublists to produce new sorted sublists until there is only 1 sublist remaining.

// Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you 
// tell which sorting method we are using?

// Input Specification:
// Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). Then in the next line, N integers 
// are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target 
// sequence is always ascending. All the numbers in a line are separated by a space.

// Output Specification:
// For each test case, print in the first line either "Insertion Sort" or "Merge Sort" to indicate the method used to obtain the partial result. 
// Then run this method for one more iteration and output in the second line the resuling sequence. It is guaranteed that the answer is unique 
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
// 3 1 2 8 7 5 9 4 0 6
// 1 3 2 8 5 7 4 9 0 6
// 结尾无空行
// Sample Output 2:
// Merge Sort
// 1 2 3 8 4 5 7 9 0 6
// 结尾无空行

#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
int N, CopyA[105], B[105], IsInsertion = 0;
int IsIdentical(int arr[]) {    //判别改变后的数组是否与B数组相同
	for(int i = 0; i < N; i++)
		if( arr[i] != B[i] )
			return 0;
	return 1;
}
void Insertion_Sort(int A[]){
	int Tmp, P, i, flag = 0;
	for( P = 1; P < N; P++){
		Tmp = A[P];
		for( i = P; i > 0 && A[i - 1] > Tmp; i--)	//i--别写成i++; 因为是从后往前比较（错误原因）
			A[i] = A[i - 1];
		A[i] = Tmp;
		//如果相同，说明是插入排序，再做一个迭代就退出
		if( IsIdentical(A) ) {
			printf("Insertion Sort\n");
			IsInsertion = 1;	//如果不是，就转去判别是否是归并
			flag = 1;
			continue;
		}
		if(flag) break;		//再做一次迭代就退出
	}
}
void Merge1( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd ) {
	//将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
	int LeftEnd, NumElements, Tmp;
	int i;
	LeftEnd = R - 1;	//左边终点位置
	Tmp = L;	//有序序列的起始位置
	NumElements = RightEnd - L + 1;		//元素总个数
	while( L <= LeftEnd && R <= RightEnd ) {
		if( A[L] <= A[R] )
			TmpA[Tmp++] = A[L++];	//将左边元素复制到TmpA
		else
			TmpA[Tmp++] = A[R++];	//将右边元素复制到TmpA
	}
	while( L <= LeftEnd )
		TmpA[Tmp++] = A[L++];	//直接复制左边剩下的
	while( R <= RightEnd )
		TmpA[Tmp++] = A[R++];	//直接复制右边剩下的
	for( i = 0; i < NumElements; i++, RightEnd-- )
		A[RightEnd] = TmpA[RightEnd];	//将有序的TmpA复制回A
}
void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length ) {
	//两两归并相邻有序子列
	int i, j;
	for( i = 0; i <= N - 2 * length; i += 2 * length )
		Merge1( A, TmpA, i, i + length, i + 2 * length - 1 );
	if( i + length < N )	//归并最后2个子列
		Merge1( A, TmpA, i, i + length, N - 1 );
	else  //最后只剩1个子列
		for( j = i; j < N; j++ )
			TmpA[j] = A[j];
}
void Merge_Sort_Loop( ElementType A[], int N ) {
	int length, flag = 0;
	ElementType *TmpA;
	length = 1;		//初始化子序列长度
	TmpA = (ElementType *)malloc(N * sizeof(ElementType));
	if ( TmpA != NULL ) {
		while( length < N ) {
			Merge_pass( A, TmpA, N, length );
			//判别是否相同，与插入排序类似
			if( IsIdentical(CopyA) ) {
				printf("Merge Sort\n");
				flag = 1;
				length *= 2;	//要加入这句话，否则会无限循环
				continue;
			}
			length *= 2;
			if(flag) break;
		}
		free( TmpA );
	}
	else printf("空间不足");
}
int main(){
	int A[105];
	scanf("%d", &N);
	//read
	for(int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		CopyA[i] = A[i];
	}
	for(int i = 0; i < N; i++)
		scanf("%d", &B[i]);
	//judge
	Insertion_Sort(A);
	if(IsInsertion) {
		printf("%d", A[0]);
		for(int i = 1; i < N; i++)
			printf(" %d", A[i]);
	}
	else {
		Merge_Sort_Loop(CopyA, N);
		printf("%d", CopyA[0]);
		for(int i = 1; i < N; i++)
			printf(" %d",CopyA[i]);
	}
	system("pause");
	return 0;
}