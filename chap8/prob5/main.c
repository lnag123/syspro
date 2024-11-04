#include <stdio.h>
#include <unistd.h>


int main()
{    
    printf("my processor number : [%d] \n", getpid());
    printf("my parents processor number : [%d] \n", getppid());
}

