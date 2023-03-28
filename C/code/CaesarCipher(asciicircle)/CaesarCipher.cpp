/*
    auther: @WandeF
    模拟凯撒加密，实现自定义步数
    以后有空了，写一个des加密
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 100

void caesarCipher(char *plaintext, int n, int len); //传入字符串数组地址，直接对参数进行修改 ;n：步数，len：字符串长度
int main(){
    int add;  //加步数，左移  left steps
    int sub;  //减步数，右移  right steps
    int n;
    int len;

    char plaintext[MAXLEN];

    printf("plseae input your step:\n");

    printf("your add steps:");

    scanf("%d",&add);

    printf("your sub steps:");

    scanf("%d",&sub);

    n=add-sub;

    printf("please input your string:");
    getchar();

    fgets(plaintext,MAXLEN,stdin); //fgets(str,strmaxlen,stdin)  stdin:标准输入流，键盘输入,fgets()相比于gets()规定了最大输入长度，防止了栈溢出

    len = strlen(plaintext)-1; //fgets()读取的字符串多了一个'\n' ,因此需要长度-1

    caesarCipher(plaintext,n,len); 

    printf("your ciphertext is:%s",plaintext);
    
    system("pause");

}

void caesarCipher(char *plaintext, int n, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        if('a'<=plaintext[i]&&plaintext[i]<='z')
        {
            plaintext[i]= ((plaintext[i]-97 + n)%26 + 26)%26 + 97;   //虽然看起来十分复杂，两次模的目的是为了防止出现余为负值的情况
        } else if ('A'<=plaintext[i]&&plaintext[i]<='Z')
        {
            plaintext[i]= ((plaintext[i]-65 + n)%26 + 26)%26 + 65;
        } else 
        {
            plaintext[i] = plaintext[i];         //标点符号不做处理，符合人类阅读习惯
        }    
    }
}