#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void print_arr(int arr[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
}
void print_scan_arr_len_request()
{
    printf("Please enter a non negative integer (n):");
}
void print_scan_int_request()
{
    printf("Please enter a non negative integer (k):");
}

void print_scan_arr_request()
{
    printf("Please enter n integer values with the special characteristic:\n");
}
void arr_sort(int *arr, int length, int k)
{
    int count1=0, count2=k, helper=0;
    while(count1<length)
    {
        while( arr[count1] <= arr[count1 + count2] )
        {
            if( count2<1 || count1+count2 >= length )
                break;
            count2--;
        }
        if( arr[count1] > arr[count1 + count2] && count2 > 0 && count1+count2<length)
        {
            helper = arr[count1];
            arr[count1] = arr[count1 + count2];
            arr[count1 + count2] = helper;
        }
        count1++;
        if(count1 - count2 >=0)
        {
            if(arr[count1] < arr[count1 - count2])
        {
            count1--;
        }
        }
     count2=k;
    }
}
int main()
{
int k=0, length=0;
print_scan_int_request();
while( scanf("%d", &k)==1 )
    {
        if( k < 0 )
        {
            print_scan_int_request();
            continue;
        }
        if( k >= 0 )
            break;
    }
print_scan_arr_len_request();
while( scanf("%d", &length)!=0 )
    {
        if( length < 0 )
        {
            print_scan_arr_len_request();
            continue;
        }
        if( length >= 0 )
           {
            print_scan_arr_request();
            break;
           }
    }
int *arr=(int*)malloc(sizeof(int) * length);
if(arr==NULL){return 0;}
if( length==0 ) {return 0;}
for(int i=0; i<length; i++)
{
    int temp;
    if(!scanf( "%d" , &temp )) {return 0;}
    arr[i] = temp ;
}
arr_sort(arr, length, k);
print_arr(arr, length);

free(arr);

return 0;
}
