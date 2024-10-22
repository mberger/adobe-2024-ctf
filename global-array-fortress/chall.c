./#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For gid_t and setregid on macOS

//gcc -m32 -fno-stack-protector chall.c -o chall

int array[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

void win(void)
{
    system("/bin/sh");
}

void init()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    gid_t gid = getegid();
    setregid(gid, gid);  // Use setregid instead of setresgid on macOS
}

int main()
{
    init();
    int index;
    int value;
    int *address;
    printf("Enter the index to write at: ");
    scanf("%d", &index);
    if(index > 7)
    {
        printf("Invalid index!");
        return 0;
    }
    else
    {
        printf("Current array: \n");
        for(int i = 0; i < 8; i++)
            printf("%d ", array[i]);
        puts("");
        printf("Enter the value to write: ");
        scanf("%d", &value);
        address = &array[index];
        *address = value;
        puts("");
    }
    return 0;
}
