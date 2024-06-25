/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DICTIONARY_SIZE 6

void PrintMallocError() 				{ 	printf("Malloc error.\n");}
void PrintWelcomeMessage()				{	printf("What is the length of your word?\n");}
void PrintWordMessage() 				{	printf("Enter your word:\n");}
void PrintCharMessage()					{	printf("Enter your secret char:\n");}
void PrintTransformedWord(char* word)	{	printf("The transformed word is: %s\n", word);}
void transform(char* str, char c, char* str_trns, char* source_strings[], char*
target_strings[])
{
int i=0, j=0;
while(*(str+i))
{
    if(*(str+i)=='a' || *(str+i)=='A' || *(str+i)=='e' || *(str+i)=='E' ||
        *(str+i)=='i' || *(str+i)=='I' || *(str+i)=='o' || *(str+i)=='O' ||
        *(str+i)=='u' || *(str+i)=='U' )
    {
        *(str_trns+j)=*(str+i);
        *(str_trns+j+1)=c;
        *(str_trns+j+2)=*(str+i);
        j+=3;
    }
    else
    {
        *(str_trns+j)=*(str+i);
        j++;
    }
    i++;
}
while(*(str_trns+j))
{
    *(str_trns+j)=0;
    j++;
}
for(int k=0; k<DICTIONARY_SIZE; k++)
{
    if(!(strcmp(str_trns, source_strings[k])))
    {
        strcpy(str_trns, target_strings[k]);
    }
}
}
int main()
{
int length=0;
char *str, c, *str_trns;
char *source_string[DICTIONARY_SIZE]={"hebeabal", "woborld", "mabakebe", "ibit", "bebetteber", "plabacebe"};
char *target_string[DICTIONARY_SIZE]={ "rappao", "olam", "taaso", "oto", "tov", "makom"};
PrintWelcomeMessage();
scanf("%d", &length);
PrintWordMessage();
str=(char*) malloc((length)*sizeof(char));
str_trns=(char*) malloc((3*length)*sizeof(char));
scanf("%s", str);
PrintCharMessage();
scanf(" %c", &c);
transform(str,c , str_trns, source_string, target_string);
PrintTransformedWord(str_trns);
free(str);
free(str_trns);
return 0;
}
