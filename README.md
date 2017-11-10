/* Program has some bugs */

Creation - To build all things necessary just type "make". Other valid options are "make clean" and "make build", but "make" will do both. 

Shell - So my shell works fine as far as I can tell. Just do "./shell" to run. Second argument can be specified as an integer
 for number of decimal places of precision for the output percentage of Monte Carlo Sim. Default is 6 per Dr. Bell's Piazza post saying 5-6. 
For 3 decimal places enter "100", for 6 enter "100000" 


Note: When ran as standalone (terminal), my monte carlo sim supports all required signals except sigusr1 and sigusr2, which is the inverse of running it from my shell.
Also The first seg fault will show on screen but all after that are just dots. If it's too annoying please comment out line 80 of mc.c
Monte Carlo Sim - 1. When ran from terminal (not my shell), must have SECOND AND THIRD arguments. 
                  Arg1 - "./MonteCarlo" - default (no arg2 or arg3) is 6 decimal places and 1000000 evaluations
                  Arg2 - Value passed to alarm() for use as a timer. This should be an integer value for number of seconds. MUST be specified.
                         If you don't want timer, set large value.
                  Arg3 - ABSOLUTELY VITAL for standalone execution, and must specify arg2 if you do arg3. Can be anything, a number, character, smiley face :)

                  2. When ran from my shell, DO NOT use a third argument.
                  Arg1 - "./MonteCarlo" - default (no arg2 or arg3) is 6 decimal places and 1000000 evaluations
                  Arg2 - OPTIONAL value passed to alarm() for use as a timer. This should be an integer value for number of seconds.
                  Arg3 - DO NOT USE THIS



