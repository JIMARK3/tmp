// 快速排序函数，用于对给定的整数数组进行排序
void fast_sort(int a[], int n)
{
    // 如果数组长度小于等于 1，直接返回，因为不需要排序
    if (n <= 1 )
    {
        return;
    }

    // 选择中间元素作为基准值
    int mid = a[n / 2];

    // 初始化左边索引为 0
    int count_left = 0;

    // 初始化右边索引为数组长度减 1
    int count_right = n - 1;

    // 初始化一个寄存器变量用于交换元素
    int reg = -1;

    // 当左边索引小于右边索引时，循环执行以下操作
    while (count_left < count_right)
    {

        // 如果左边元素小于等于基准值，左边索引加 1
        if (a[count_left] <= mid)
        {
            count_left++;
        }
        else
        {   
            // 否则，将右边的元素赋值给寄存器变量
            reg = a[count_right];

            // 将左边的元素赋值给右边的元素
            a[count_right] = a[count_left];

            // 将寄存器变量中的值（右边的元素）赋值给左边的元素
            a[count_left] = reg;

            // 右边索引减 1，缩小范围
            count_right--;
        }
        
    }
    // 判断左边索引是否等于数组长度减 1，或者右边索引是否等于 0
    if (count_left == n - 1 || count_right == 0)
    {
        // 如果满足条件，直接返回，因为已经排好序了
        return;
    }

    // 递归地对左边的子数组进行快速排序
    fast_sort(a, count_left + 1);

    // 递归地对右边的子数组进行快速排序
    fast_sort(a + count_left, n - count_left - 1);

}
