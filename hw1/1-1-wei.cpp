#include <stdio.h>
#include <stdlib.h>
void merge(long long int left, long long int right, long long int box[100000][2])
{
    long long int i, j, k, temp[100000][2], mid = (left + right) / 2;
    for (k = 0, i = left, j = mid + 1; i <= mid || j <= right; k++) {
        if (i > mid) {
            temp[k][0] = box[j][0];
            temp[k][1] = box[j][1];
            j++;
        }
        else if (j > right) {
            temp[k][0] = box[i][0];
            temp[k][1] = box[i][1];
            i++;
        }
        else if (box[i][0] > box[j][0]) {
            temp[k][0] = box[i][0];
            temp[k][1] = box[i][1];
            i++;
        }
        else if (box[i][0] == box[j][0] && box[i][1] > box[j][1]) {
            temp[k][0] = box[i][0];
            temp[k][1] = box[i][1];
            i++;
        }
        else {
            temp[k][0] = box[j][0];
            temp[k][1] = box[j][1];
            j++;
        }
    }
    for (i = left, k = 0; i <= right; i++, k++) {
        box[i][0] = temp[k][0];
        box[i][1] = temp[k][1];
    }
    return;
}
void mergesort(long long int left, long long int right, long long int box[100000][2])
{
    long long int mid = (left + right) / 2;
    if (left < right) {
        mergesort(left, mid, box);
        mergesort(mid + 1, right, box);
        merge(left, right, box);
    }
    return;
}
long long int countbox(long long int left, long long int right, long long int box[100000][2])
{
    long long int i, j, k, count = 0, temp[100000][2], mid = (left + right) / 2;
    for (k = 0, i = left, j = mid + 1; i <= mid || j <= right; k++) {
        if (i > mid) {
            temp[k][0] = box[j][0];
            temp[k][1] = box[j][1];
            j++;
        }
        else if (j > right) {
            temp[k][0] = box[i][0];
            temp[k][1] = box[i][1];
            i++;
        }
        else if (box[i][1] >= box[j][1]) {
            temp[k][0] = box[i][0];
            temp[k][1] = box[i][1];
            count += right - j + 1;
            i++;
        }
        else {
            temp[k][0] = box[j][0];
            temp[k][1] = box[j][1];
            j++;
        }
    }
    for (i = left, k = 0; i <= right; i++, k++) {
        box[i][0] = temp[k][0];
        box[i][1] = temp[k][1];
    }
    return count;
}
long long int mergebox(long long int left, long long int right, long long int box[100000][2])
{
    long long int count = 0, mid = (left + right) / 2;
    if (left < right) {
        count += mergebox(left, mid, box);
        count += mergebox(mid + 1, right, box);
        count += countbox(left, right, box);
    }
    return count;
}
int main(void)
{
    long long int i, j, k, T, n, test;
    scanf("%lld", &T);
    for (i = 0; i < T; i++) {
        scanf("%lld", &n);
        long long int box[n][2], temp, count = 0, repeat = 1;
        for (j = 0; j < n; j++) {
            scanf("%lld%lld", &box[j][0], &box[j][1]);
            if (box[j][0] < box[j][1]) {
                temp = box[j][0];
                box[j][0] = box[j][1];
                box[j][1] = temp;
            }
        }


        mergesort(0, n - 1, box);


        count += mergebox(0, n - 1, box);
        
        
        for (j = 0; j < n - 1; j++) {
            if (box[j][0] == box[j + 1][0] && box[j][1] == box[j + 1][1])
                repeat++;
            else {
                count += repeat * (repeat - 1) / 2;
                repeat = 1;
            }
        }count += repeat * (repeat - 1) / 2;
        
        printf("%lld\n", count);
    }
}