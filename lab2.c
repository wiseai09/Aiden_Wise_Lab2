#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

   pid_t pid;
   int status;

	//for loop to create 10 child processes
	for(int i = 0; i < 10; i++) {

		//create child processes
		pid = fork();

		//fork() failure
		if (pid < 0) {
		   perror("Fork() failed");
			return 1;
		}
		//child process
		else if (pid == 0) {
         //print child process
			printf("Child process PID: %d\n", getpid());

         //echo command
			char *args[] = { "echo", "Hello Aiden", NULL };
         
         //execvp() failure
         //exit child process
         if (execvp(args[0], args) == -1) {
            perror("Execvp failed");
            return 1;
         }
         
         

		}
	}
   
   //parent process
	//loops through all child processes
   for (int i = 0; i < 10; i++) {
      //waits for all child processes to complete
		pid_t child_pid = wait(&status);

      //wait() failure
	   if (child_pid < 0) {
         perror("Wait() failed");
         return 1;
      }
            
      //checks if child process exited normally or terminated by signal
      if (WIFEXITED(status)) {
         //child process exited normally
         int exit_status = WEXITSTATUS(status);
         printf("Child process with PID %d exited normally with status %d\n", child_pid, exit_status);
      } 
      else if (WIFSIGNALED(status)) {
         //child process terminated by signal
         int signal_num = WTERMSIG(status);
         printf("Child process with PID %d terminated by signal %d\n", child_pid, signal_num);
      }
   }   
   
   //print parent process
   printf("Parent process PID: %d\n", getpid());
}
