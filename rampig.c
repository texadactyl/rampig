#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>
#include<unistd.h>


#define MAX_LOGBUF_SIZE 1024

static char *mem_ptr = NULL;
static size_t mb = 0L;


/***
	Report bad news, cleanup, and exit to O/S
***/
void byebye(int arg_exit_code) {
	if(mem_ptr != NULL) {
	    printf("rampig: Deallocating %ld MB of RAM\n", mb);
	    free(mem_ptr);
	}
	printf("rampig: Bye bye.\n");
	exit(arg_exit_code);
}


/***
	Report bad news, cleanup, and exit to O/S
***/
void oops(const char *arg_fmt, ...) {

	va_list va_array;
	char format[MAX_LOGBUF_SIZE];

	sprintf(format, "\n*** rampig: Oops, %s\n", arg_fmt);
	va_start(va_array, arg_fmt);
	vfprintf(stdout, format, va_array);
	va_end(va_array);

	byebye(86);
}


/***
    Signal Catcher
***/
void sig_handler(int arg_signo) {
    printf("\nrampig: Caught signal %d.\n", arg_signo);
    byebye(0);
}

/***
    Set up signal catcher for the given signal
***/
void sig_setup_catcher(int arg_signo) {
    if (signal(arg_signo, sig_handler) == SIG_ERR)
        oops("Could not set up to catch %d.", arg_signo);
}

/***
    Is a string all digits?
***/
int valid_number(char *arg_string) {
   for(int ndx = 0; ndx < strlen(arg_string); ndx++)
   {
      //ASCII value of 0 = 48, 9 = 57. So if value is outside of numeric range then fail
      //Checking for negative sign "-" could be added: ASCII value 45.
      if (arg_string[ndx] < 48 || arg_string[ndx] > 57)
         return -1;  // failure, arg_string does not hold a number in string form
   }

   return 0; // success, arg_string holds a number in string form
}


/***
	Main Program Entry Point
***/
int main(int argc, char **argv) {
    char str_mb[20];
    int pid;
    size_t amt;
    
    // Collect the requested number of MB to allocate
    if( --argc != 1)
        oops("Exactly one argument must be specified: the number of megabytes to allocate.");
    strcpy(str_mb, *++argv);
    if(valid_number(str_mb))
       oops("The argument must be numeric: the number of megabytes to allocate.");

    // Announce
    pid = getpid();
    printf("rampig: Hello, my process ID = %d.\n", pid);

    // Allocate the requested space
    mb = atoi(str_mb);
    amt = (size_t) mb * 1000000;
    printf("rampig: Allocating %ld MB of RAM\n", mb);
    mem_ptr = (char*)malloc(amt);
    if(mem_ptr == NULL)
        oops("Insufficient RAM for the requested allocation.");
    memset(mem_ptr, 0xff, amt);
    printf("rampig: Allocated & intialised %ld bytes.\n", amt);

    // Set up signal catcher
    sig_setup_catcher(SIGABRT); // kill -6
    sig_setup_catcher(SIGHUP); // kill -1
    sig_setup_catcher(SIGINT); // Ctrl-C, kill -2
    sig_setup_catcher(SIGQUIT); // kill -3
    sig_setup_catcher(SIGTERM); // kill -15
    
    // Loop
    while(1)
        sleep(3);
}
