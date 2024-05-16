#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char *tab[2] = {"./merde", NULL};
    // int s = malloc(-1);
    execve("./merde", tab, NULL);
    printf("test\n");
    access("errno.c", F_OK);
    // access("merde", F_OK | X_OK);
    printf("[%i]{%s}\n", errno, strerror(errno));
    perror("bonjour");
}