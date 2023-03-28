/*
    author: @WandeF
    模拟凯撒加密，实现自定义步数
    以后有空了，写一个des加密
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 100

void caesarCipher(char *plaintext, int n, int len); //传入字符串数组地址，直接对参数进行修改 ;n：步数，len：字符串长度

int main(){
    int n;
    int len;
    char plaintext[MAXLEN];

    printf("please input your step: ");
    scanf("%d", &n);

    printf("please input your string: ");
    getchar();
    fgets(plaintext, MAXLEN, stdin); //fgets(str,strmaxlen,stdin)  stdin:标准输入流，键盘输入,fgets()相比于gets()规定了最大输入长度，防止了栈溢出

    len = strlen(plaintext) - 1; //fgets()读取的字符串多了一个'\n' ,因此需要长度-1

    caesarCipher(plaintext, n, len); 

    printf("your ciphertext is: %s\n", plaintext);
    
    system("pause");  
    
    return 0;
}

void caesarCipher(char *plaintext, int n, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        if('a' <= plaintext[i] && plaintext[i] <= 'z')
        {
            plaintext[i] = (((plaintext[i] - 'a' + n) % 26 + 26) % 26 + 'a');
        }
        else if ('A' <= plaintext[i] && plaintext[i] <= 'Z')
        {
            plaintext[i] = (((plaintext[i] - 'A' + n) % 26 + 26) % 26 + 'A');
        }
        // else 保留原字符
    }
}
