#include <stdio.h>
int main(){
    char name[5];
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Hello, %s!\n", name);
    return 0;

}
// the last character in a array has to be a null
