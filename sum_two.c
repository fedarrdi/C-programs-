#include <stdio.h>

int vis_table[10000], index_table[10000];

void sum_two(const int *nums, int nums_c, int target, int *out_arr)
{
    for (int i = 0; i < nums_c; i++)
    {
        vis_table[nums[i]] = 1;
        index_table[nums[i]] = i;

        int curr_num = target - nums[i];
        if(vis_table[curr_num])
        {
            *out_arr = i;
            out_arr++;
            *out_arr = index_table[curr_num];
            return;
        }
    }
}

int main()
{
    int nums[7] = {1, 2, 3, 4, 5, 6, 7}, nums_c = 7, target = 6 + 7, ans[2];
    sum_two(nums, nums_c, target, ans);
    printf("%d, %d", ans[0], ans[1]);
    return 0;
}
