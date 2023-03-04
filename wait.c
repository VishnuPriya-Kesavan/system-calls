#include <stdio.h>  // perror()
 #include <stdlib.h> // exit(), EXIT_SUCCESS, EXIT_FAILURE
 #include <unistd.h> // fork()
pid_t wait(int *status); 

void child() {
  printf(" CHILD <%ld> I'm alive! My PID is <%ld> and my parent got PID <%ld>.\n",
         (long) getpid(), (long) getpid(), (long) getppid());
  printf(" CHILD <%ld> Goodbye!\n",
         (long) getpid());
  exit(EXIT_SUCCESS);
}


void parent(pid_t pid) {
   int status;
  
    printf("PARENT <%ld> Spawned a child with PID = %ld.\n",
           (long) getpid(), (long) pid);
  
    wait(&status);
  
    if (WIFEXITED(status)) {
     printf("PARENT <%ld> Child with PID = %ld and exit status = %d terminated.\n",
            (long) getpid(), (long) pid, WEXITSTATUS(status));
   }
 
   printf("PARENT <%ld> Goodbye.\n",
          (long) getpid());
 
   exit(EXIT_SUCCESS);
 }

int main(void) {
  pid_t pid;

  switch (pid = fork()) {
    case -1:
      // On error fork() returns -1.
      perror("fork failed");
      exit(EXIT_FAILURE);
    case 0:
      // On success fork() returns 0 in the child.
      child();
    default:
      // On success fork() returns the pid of the child to the parent.
      parent(pid);
  }
}

