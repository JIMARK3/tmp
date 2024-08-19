#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


void fast_sort(int a[], int n)
{
    if (n <= 1 )
    {
        return;
    }

    int mid = a[n / 2];
    int count_left = 0;
    int count_right = n-1;
    int reg = -1;
    while (count_left < count_right)
    {

        if (a[count_left] < mid)
        {
            count_left++;
        }else{
            reg = a[count_right];
            a[count_right] = a[count_left];
            a[count_left] = reg;
            count_right--;
        }
        
    }

    if (count_left==n-1|| count_right==0){
        return;
    }

    
    
    fast_sort(a, count_left+1);
    fast_sort(a + count_left, n - count_left-1);

}


// 测试函数
void test_fast_sort()
{
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    fast_sort(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
        /* code */
    }

    // 断言排序结果是否正确
    // assert(arr[0] == 5);
    // assert(arr[1] == 6);
    // assert(arr[2] == 11);
    // assert(arr[3] == 12);
    // assert(arr[4] == 13);
}

int main()
{
    test_fast_sort();
    return 0;
}
