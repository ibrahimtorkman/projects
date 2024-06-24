#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROTATE_LEFT 1
#define ROTATE_RIGHT 0
#define OP_ROTATE_LEFT 'L'
#define OP_ROTATE_RIGHT 'R'
#define OP_AVERAGE 'V'
#define OP_NEGATE 'N'
#define MAX_VALUE 255

void PrintRowMessage()		{	printf("Enter the number of rows in your image matrix:\n");	}
void PrintColumnMessage()	{	printf("Enter the number of columns in your image matrix:\n");	}
void PrintEnterMatrix()		{	printf("Enter your matrix:\n");	}
void PrintImageMessage()	{	printf("Your original image is:\n");	}
void PrintPrompt()			{	printf("What you would like to do with your photo (L,R,V,N)?\n"); }
void PrintLeftRotation()	{	printf("The image after left rotation:\n");	}
void PrintRightRotation()	{	printf("The image after right rotation:\n");	}
void PrintAveraging()		{	printf("The image after averaging:\n");	}
void PrintNegating()		{	printf("The image after negating:\n");	}

void print_image(int* image, int n, int m)
{
    int i,j;
    for(j=0;j < n; j++)
    {
    for (i =0; i < m; i++)
        {
            if (i != m-1)
                printf("%d\t", *( (image+j*m) + i));//image[j][i]
            else
                printf("%d", *( (image+j*m) + i));

        }
    printf("\n");
    }
}
void negative(int* image, int n, int m, int* target)
{
    for(int i=0; i<(n*m); i++)
    {
        *(target+i)=MAX_VALUE-*(image+i);
    }
}
void average(int* image, int n, int m, int* target)
{
    for(int i=0; i<(n*m); i++)
    {
        //top left
        if(i==0)
        {
            *(target+i)=( *(image+i) + *(image+i+1) + *(image+i+m) + *(image+i+m+1) )/4;
            continue;
        }
        //top right
        if(i==m-1)
        {
            *(target+i)=( *(image+i) + *(image+i-1) + *(image+i+m) + *(image+i+m-1) )/4;
            continue;
        }
        //bottom left
        if(i==(n*m)-m)
        {
            *(target+i)=( *(image+i) + *(image+i+1) + *(image+i-m) +*(image+i-m+1) )/4;
            continue;
        }
        //bottom right
        if(i==(n*m)-1)
        {
            *(target+i)=( *(image+i) + *(image+i-1) + *(image+i-m) + *(image+i-m-1) )/4;
            continue;
        }
        //top row
        if(i<m)
        {
            *(target+i)=( *(image+i) + *(image+i+1) + *(image+i-1) + *(image+i+m) + *(image+i+m+1)
                         + *(image+i+m-1) )/6;
                         continue;
        }
        //left col
        if(i%m==0)
        {
            *(target+i)=( *(image+i) + *(image+i+1) + *(image+i-m) + *(image+i-m+1) + *(image+i+m)
                         + *(image+i+m+1) )/6;
                         continue;
        }
        //right col
        if(i%m== m-1)
        {
            *(target+i)=( *(image+i) + *(image+i-1) + *(image+i-m) + *(image+i-m-1) + *(image+i+m)
                         + *(image+i+m-1) )/6;
                         continue;
        }
        //bottom row
        if( (i<n*m) && (i>((n*m)-m)) )
        {
            *(target+i)=( *(image+i) + *(image+i+1) + *(image+i-1) + *(image+i-m) + *(image+i-m+1)
                         + *(image+i-m-1) )/6;
                         continue;
        }
        //middle
        *(target+i)=( *(image+i) + *(image+i+1) + *(image+i-1) + *(image+i-m) + *(image+i-m+1)
                     + *(image+i-m-1) + *(image+i+m) + *(image+i+m+1) + *(image+i+m-1) )/9;
    }
}
void rotate(int* image, int n, int m, int* target, int d)
{
if(d==ROTATE_RIGHT)
{
    int index_image=n*m-m, index_target=0;
    for(int i=0;i<m;i++)
    {
        index_image=n*m-m+i;
        for(int j=index_image; j>=0; j-=m)
        {
        *(target+index_target)=*(image+j);
        index_target++;
        }
    }
}
if(d==ROTATE_LEFT)
{
    int index_image=m-1, index_target=0;
    for(int i=m-1;i>=0;i--)
    {
        index_image=i;
        for(int j=index_image; j<=n*m; j+=m)
        {
        *(target+index_target)=*(image+j);
        index_target++;
        }
    }
}
}
void print(int* image, int n, int m)
{
    int i,j;
    for(j=0;j < n; j++)
    {
    for (i =0; i < m; i++)
        {
            if (i != m-1)
                printf("%d\t", *( (image+j*m) + i));
            else
                printf("%d", *( (image+j*m) + i));

        }
    printf("\n");
    }
}


int main()
{
int *image, row=0, col=0, *target;
char prompt;
PrintRowMessage();
PrintColumnMessage();
if( !(scanf("%d", &row)) || !(scanf("%d", &col)) ) return 0;
image=(int*)malloc(sizeof(int)*(row*col));
target=(int*)malloc(sizeof(int)*(row*col));
if( (image==NULL) || (target==NULL) )return 0;
PrintEnterMatrix();
for(int i=0; i<(row*col); i++)
{
    scanf("%d", image+i);
}
PrintImageMessage();
print_image(image, row, col);
PrintPrompt();
scanf(" %c", &prompt);
    if(prompt==OP_NEGATE)
    {
        PrintNegating();
        negative(image, row, col, target);
        print(target, row, col);
    }
    if(prompt==OP_AVERAGE)
    {
        PrintAveraging();
        average(image, row, col, target);
        print(target, row, col);
    }
    if(prompt==OP_ROTATE_RIGHT)
    {
        PrintRightRotation();
        rotate(image, row, col, target, ROTATE_RIGHT);
        print(target, col, row);
    }
    if(prompt==OP_ROTATE_LEFT)
    {
        PrintLeftRotation();
        rotate(image, row, col, target, ROTATE_LEFT);
        print(target, col, row);
    }
free(image);
free(target);
  return 0;
}
