// 01-复杂度2 Maximum Subsequence Sum (25 分)
// Given a sequence of K integers { N1, N2, ..., NK}. A continuous subsequence is defined to be { Ni,N i+1, ..., Nj} where 1≤i≤j≤K. The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.
// Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.
// Input Specification:
// Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (≤10000). The second line contains K numbers, separated by a space.
// Output Specification:
// For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.
// Sample Input:
// 10
// -10 1 2 3 4 -5 -23 3 7 -21
// 结尾无空行
// Sample Output:
// 10 1 4

结尾无空行#include <stdio.h>

// int main()
// {
//     int result = 0, thissum = 0;
//     int N, digit[10005];
//     int first =0, begin = 0, last = 0;
//     scanf("%d",&N);
//     scanf("%d",digit);
    
//     result = thissum = digit[0];
//     for(int i=1;i<N;i++)
//     {
//         scanf("%d",digit+i);
//         if(thissum>=0)
//             thissum+=digit[i];
//         else{
//             thissum = digit[i];
//             begin = i;
//         }
//         if(thissum>result)
//         {
//             last = i;
//             first = begin;
            
//             result = thissum;
//         }
//     }
//     if(result < 0)
//     {
//         result = 0;
//         first = 0;
//         last = N-1;
//     }
//     printf("%d %d %d",result,digit[first],digit[last]);
//     return 0 ;
// }

int main()
{
    int maxsum = 0, thissum = 0;
    int N, digit[10005];
    int first = 0, last = 0, tryfirst = 0;
    scanf("%d",&N);
//     scanf("%d",digit);
    

    for(int i=0;i<N;i++)
    {
        scanf("%d",digit+i);
    }
    maxsum= digit[0];
    
    for(int i=0;i<N;i++)
    {
        
        thissum+=digit[i];
        
        if(thissum<0)    
        {
            thissum = 0;
            tryfirst = i+1;
        }
        else if(thissum>maxsum)
        {
            last = i;
            first = tryfirst;
            maxsum = thissum;
        }
    }
    if(maxsum < 0)
    {
        maxsum = 0;
        first = 0;
        last = N-1;
    }
//     for(int i=0;i<N;i++)
//     {
//         printf("%d\n",digit[i]);
//     }
//     printf("%d %d \n",first,last);
    
    printf("%d %d %d",maxsum,digit[first],digit[last]);
    return 0;
}