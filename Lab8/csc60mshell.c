/* Author(s): Please put your student name(s) & section here.
 *
 * This is a csc60mshell.c
 * This program serves as a skeleton for starting for lab 8.
 * Student is required to use this program to build a mini shell
 * using the specification as documented in direction.
 * Date: Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 80
#define MAXARGS 20
#define MAX_PATH_LENGTH 50
#define MAXPATH 256

/* function prototypes */
void process_input(int argc, char **argv);
int parseline(char *cmdline, char **argv);
void handle_redir(int count, char *argv[]);

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
int main(void)
{
    char cmdline[MAXLINE];
    char *argv[MAXARGS];
    int argc;
    int status;
    char path[MAXPATH];
    pid_t pid;

    /* Loop forever to wait and process commands */
    while (1) {
	/* Print your shell name: csc60mshell (m for mini shell) */
	printf("csc60mshell > ");
	fgets(cmdline, MAXLINE, stdin);

	/* Call parseline to build argc/argv: their limits declared above */
	argc = parseline(cmdline, argv);
	/* If user hits enter key without a command, continue to loop again at the beginning */
	/*  Hint: if argc is zero, no command declared */
	/*  Hint: look up for the keyword "continue" in C */
	if(argc ==0)
		continue;
	/* Handle build-in command: exit, pwd, or cd  */
	if(strcmp("pwd", argv[0]) == 0 )
	{
		printf("%s\n", getenv("PWD"));
		continue;
	}
	else if(strcmp("exit", argv[0]) == 0)
	{
		exit(0);
	}
	else if (*argv[0] == '<' || *argv[0] == '>')
	{
		fprintf(stderr, "No Command Line.");
		continue;
	}
	else if(strcmp("cd", argv[0]) == 0)
	{
		char *dir;
		if(argv[1] == NULL)
		{
			dir = getenv("HOME");
			chdir(dir);
		}
		else
		{
			dir = argv[1];
			chdir(dir);
		}
		getcwd(path, MAXPATH);
		setenv("PWD", path, 1);
		continue;
	}
	/* Else, fork off a process */
	else
	{
		pid = fork();
        	switch(pid)
		{
	    	case -1:
			perror("Shell Program fork error");
	        	exit(1);
	    	case 0:
		/* I am child process. I will execute the command, call: execvp */
			process_input(argc, argv);
			break;
	    	default:
		/* I am parent process */
			if (wait(&status) == -1)
		    		perror("Shell Program error");
			else
		    		printf("Child returned status: %d\n",status);
			break;
		} /* end of the switch */
	}/*end of else*/	
    } /* end of the while */
} /* end of main */
/* ----------------------------------------------------------------- */
/*                  parseline                                        */
/* ----------------------------------------------------------------- */
/* parse input line into argc/argv format */

int parseline(char *cmdline, char **argv)
{
    int count = 0;
    char *separator = " \n\t";
 
    argv[count] = strtok(cmdline, separator);
    while ((argv[count] != NULL) && (count+1 < MAXARGS)) {
	argv[++count] = strtok((char *) 0, separator);
    }		
    return count;
}
/* ----------------------------------------------------------------- */
/*                  process_input                                    */
/* ----------------------------------------------------------------- */
void process_input(int argc, char **argv) {
    /* Step 1: Call handle_redir to deal with operators:            */
    /* < , or  >, or both                                           */
	handle_redir(argc,argv);
    /* Step 2: perform system call execvp to execute command        */
    /* Hint: Please be sure to review execvp.c sample program       */
    /* if (........ == -1) {                                        */
    /*  perror("Shell Program");                                    */
    /*  _exit(-1);                                                  */
   
	if(execvp(*argv, argv) == -1);
	{
		perror("Shell Program");
		_exit(-1);
	}
		
}
/* ----------------------------------------------------------------- */
void handle_redir(int count, char *argv[])
{
/* Put your code here.  See pseudo-code in assignment directions     */
	int fide;
	int i = 0;
	int Inp = 0;
	int Out = 0;
	int Car = 0;

	for(i; i < count; i++)
	{
		if(argv[i][0] == '<')
		{
			if(Inp == 1)
				fprintf(stderr,"Cannot have two < in a statement \n");
			if(Out == 1)
				fprintf(stderr,"Cannot have both < and > in a statement\n");
			if(argv[i+1] == NULL | argv[i-1] == NULL)
				fprintf(stderr, "Must have imput file after < \n");
			if((fide = open (argv[i+1], O_RDONLY)) < 0)
				fprintf(stderr, "Already opened\n");
			if(dup2(fide, 0), 0 < 0)
				fprintf(stderr, "Failed to imput File\n");
			close(fide);
			argv[i] = NULL;
			Inp = 1;
		}
		else if(argv[i][0] == '>')
                {
                        if(Out == 1)
                                fprintf(stderr, "Cannot have two > in a statement\n");
			if(Inp == 1)
				fprintf(stderr, "Cannot have both > and < in a statement\n");
                        if(argv[i+1] == NULL | argv[i-1] == NULL);
                                fprintf(stderr, "Must have output file after >\n");
                        if((fide = open (argv[i+1], O_TRUNC | O_WRONLY | O_CREAT, 0766)) < 0)
                                fprintf(stderr, "Already opened\n");
                        if(dup2(fide, 1) < 0)
                                fprintf (stderr, "Failed to output File\n");
                        close(fide);
                        argv[i] = NULL;
                        Out = 1;
                }
		else if(strcmp(">>", argv[i]) == 0 )
                {
                       	if(Car == 1)
				fprintf(stderr, "Cannot have two >> in a statement\n");
			if(argv[i+1] == NULL)
                                fprintf(stderr, "Must have output file after >>\n");
                        if((fide = open (argv[i+1], 1),O_APPEND | O_WRONLY | O_CREAT, 0766) < 0)
                                fprintf(stderr, "Already Appended\n");
                        if(dup2(fide, 1) < 0)
                                fprintf (stderr, "Failed to append File\n");
                        close(fide);
                        argv[i] = NULL;
			Car = 1;
                }
		
	}
	
}
/* ----------------------------------------------------------------- */
