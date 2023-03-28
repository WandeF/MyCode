/*
    auther: @WandeF
    字符串ASCII加减操作，方便目前阶段逆向的flag获取
    目的是一个小程序
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 100

void asciiCircle(char *plaintext, int n, int len); //传入字符串数组地址，直接对参数进行修改 ;n：步数，len：字符串长度
int main(){
    int n;    
    int len;

    char plaintext[MAXLEN];

    printf("plseae input your step:");

    scanf("%d",&n);

    printf("please input your string:");
    getchar();

    fgets(plaintext,MAXLEN,stdin);   //fgets(str,strmaxlen,stdin)  stdin:标准输入流，键盘输入,fgets()相比于gets()规定了最大输入长度，防止了栈溢出

    len = strlen(plaintext)-1; //fgets()读取的字符串多了一个'\n' ,因此需要长度-1

    asciiCircle(plaintext,n,len);

    printf("your ciphertext is:%s",plaintext);

    system("pause");
}

void asciiCircle(char *plaintext, int n, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
      plaintext[i] = plaintext[i] + n;
    }
}