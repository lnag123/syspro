#include <sys/types.h> 

int main() 
{
   int pid, child, status;
   printf("[%d] Parental process START\n", getpid( ));
   pid = fork();
   if (pid == 0) {
      printf("[%d] Child process START\n", getpid( ));
      exit(1);
   }
   child = wait(&status); // 자식 프로세스가 끝나기를 기다린다.
   printf("[%d] Child process %d end \n", getpid(), child);
   printf("\tEnd Code %d\n", status>>8);
}

