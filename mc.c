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

static unsigned long int numEvals = 0;
static unsigned long int numSegFaults = 0;
sigjmp_buf env;  
static unsigned long int evalLimit = 1000000;
static unsigned long int segFaultLimit = 1000000;
float alarmCounter;
int digits = 0;
int standAlone = 0;
int signalReceived = 0;

int powTen(int val)
{
return (val == 10 || val == 100 || val == 1000 || val == 10000 || val == 100000 || val == 1000000 || val == 10000000 || val == 100000000);

// Code below here works, but it is VERY slow, code above is much faster, yet less flexible
/*while (val > 0 && ((val % 10) == 0))
{ 
  val = val/10;
}
if(val == 1)
{
return 1;
}
else
{
return 0;
}*/
}

void printResults()
{
printf("\nNumber of Evaluations: %d\n", numEvals);
printf("Number of Segmentation Faults: %d\n", numSegFaults);
//if(signalReceived == 1)
//{
if(standAlone == 1)
{ 
digits = 6;
}
printf("Percent Segmentation Faults: %.*lf\n", digits, (((float)numSegFaults/numEvals)*100.0f));
//}

return;
}


void sigalrm_handler(int sig)
{
  write(1, "\nHandling SIGALRM\n", 20);
  printResults();
  exit(0);
}


void sigint_handler(int sig)
{
  write(1, "\nHandling SIGINT\n", 20);
  printResults();
  exit(0);
}

void sigsegv_handler(int sig)
{
  ++numSegFaults;
  ++numEvals;
  if(numSegFaults == 1)
  {
  write(1, "\nHandling SIGSEGV", 20);
  }
  else
  {
   if((numSegFaults % 100) == 0){ printf("."); }
  }

  if(numSegFaults == segFaultLimit || numEvals == evalLimit)
  {
  printResults();
  exit(0);
  }
  siglongjmp(env, 1); 
}

void sigtstp_handler(int sig)
{
  write(1, "\nHandling SIGTSTP\n", 20);
  printResults();
  getchar();
  siglongjmp(env, 1);
}


void sigusr2_handler(int sig)
{
  write(1, "\nHandling SIGUSR2\n", 20);
  signalReceived = 1;
  printResults();
  exit(0);
}


// other function name
int main(int argc, char** argv)
{

  srand(time(NULL));


  if(argc == 2)
  {
  alarmCounter = atof(argv[1]);
  printf("Alarm val is: %d\n", (int)alarmCounter);
  }  

  if(argc == 3)
  {
  standAlone = 1;
  }

  if(signal(SIGALRM, sigalrm_handler) == SIG_ERR)
  { 
  printf("signal error for SIGALRM\n");
  }  

  if(signal(SIGINT, sigint_handler) == SIG_ERR)
  { 
  printf("signal error for SIGINT\n");
  }  

  if(signal(SIGTSTP, sigtstp_handler) == SIG_ERR)
  { 
  printf("signal error for SIGTSTP\n"); 
  }


  if(signal(SIGUSR2, sigusr2_handler) == SIG_ERR)
  { 
  printf("signal error for SIGUSR2\n"); 
  }


  if(signal(SIGSEGV, sigsegv_handler) == SIG_ERR)
  { 
  printf("signal error for SIGSEGV\n"); 
  }
  
  if(alarmCounter > 0)
  {
  alarm(alarmCounter);
  }


  
  for(numEvals = 0; numEvals < evalLimit + 1; ++numEvals)//++numEvals)
  {  
 
  sigsetjmp(env, 1);


  
  if(numEvals > 5 && powTen(numEvals) == 1 && standAlone == 0)
  {
  //printf("Power of Ten\n");
  ++digits;
  kill(getppid(), SIGUSR1);
  }

  int fault, *holder;  
  holder = rand(); 
  fault = *holder; 
  }

 // printResults(); 

  return 0;
}



