/*
Frank Lubek
654316476
flubek/flube2
flube2@uic.edu
*/

#include <limits.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


sigjmp_buf env;  
unsigned int reportNum = 1;
int signalCount = 0;
int precision = 100000; // Per Dr Bell should be 5-6 decimal places
pid_t child;

void sigusr1_handler(int sig)
{
  if(sig == SIGUSR1)
  {
  //write(1, "\nHandling SIGUSR1\n", 20);
  reportNum *= 10;
    if(reportNum > precision)
    {
     kill(child, SIGUSR2); 
    }
  }
}


/*void sigint_handler(int sig)
{
  write(1, "\nHandling SIGINT\n", 20);
  exit(0);
}*/



int main(int argc, char **argv)
{
printf("Frank Lubek\nflube2  654316476\nCS 361 Lab 2\n\n\n");


char *input;
char *token;
size_t size = 0;
char path[1024];
char prog[20];


 /* if(signal(SIGINT, sigint_handler) == SIG_ERR)
  { 
  printf("signal error for SIGINT\n");
  } */ 

if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR)
{ 
printf("signal error for SIGUSR1\n"); 
}



if(argc == 2)
{
precision = atoi(argv[1]);
}

// Get User Input
if(getcwd(path, sizeof(path)) == NULL)
{
  printf(">> ");
}
else
{
  printf("%s\n$ ", path);
}

getline(&input, &size, stdin);



// Process Input
while(1)
{
input[strcspn(input, "\r\n")] = '\0';

if(strcmp(input, "exit") == 0)
break;



char *retArr[30];
int j = 0;
for(j = 0; j < 30; ++j)
{
retArr[j] = malloc(25*sizeof(char));
}

int i = 0;
token = strtok(input, " ");

while(token != NULL)
{
strcpy(retArr[i], token);
++i;
token = strtok(NULL, " ");
}

retArr[i] = NULL; // for execvp()




// Acknowledge User
//printf("You typed: \n");

int args = i;
/*
for(i = 0; i < args; ++i)
{
printf("arg[ %d ] = %s\n", i, retArr[i]);
}
*/
 



////////////////////////////////set and restore errno



// Create child processes

  pid_t pid;
  pid = fork();

  if(pid == 0)
  {
  printf("Child's PID = %d\n\n", getpid());
  child = getpid();
  if(execvp(retArr[0], retArr) == -1)
  {
    perror("\nCommand could not be found\n");
    exit(0);
  }
 
  }
  else if(pid < 0)
  {
    perror("\nFork failed\n");
    exit(-1);
  }

  struct rusage ruse;
  int status;
  wait4(pid, &status, 0, ruse);
  printf("\n");
  if(WIFEXITED(status))
  {  
    printf("Exited properly with status %d\n", WEXITSTATUS(status));
  } 
  printf("Uncaught Signal?: %d\n", WIFSIGNALED(status));
  struct timeval t = ruse.ru_utime;
  printf("Time in ms: %d\n", t.tv_usec*10);
  long numFaults = ruse.ru_majflt;
  printf("Faults: %ld\n", numFaults);
  long numSignals = ruse.ru_nsignals;
  printf("Signals Received: %d\n", numSignals);


  printf("\n");
  if(getcwd(path, sizeof(path)) == NULL)
  {
    printf(">> ");
  }
  else
  {
    printf("%s>\n$ ", path);
  }

  getline(&input, &size, stdin);
} // End of Input Loop








}



