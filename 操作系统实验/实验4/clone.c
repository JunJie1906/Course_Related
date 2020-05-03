#define _GNU_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<signal.h>
#include<malloc.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>

char *prog_argv[4];
int foo;
int fd;


#define CHILD_STACK (1024*64)

int thread_function(void * argu)
{
	printf("CHILD: child thread begin...\n");
	foo = 2008;
	close(fd);
	execvp(prog_argv[0],prog_argv);
	printf("CHILD: child thread exit, this line won't print out.\n");
	return 0;
}

int main()
{
	char c;
	char * stack;
	pid_t pid;
	foo = 2007;
	fd = open("/etc/passwd",O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		exit(-1);
	}
	printf("PARENT: The variable foo was %d\n",foo);
	if(read(fd,&c,1)<1)
	{
		perror("PARENT: File Read Error!");
		exit(1);
	}
	else
	{
		printf("PARENT: We could read from the file : %c\n",c);
	}
	prog_argv[0] = "/bin/ls";
	prog_argv[1] = "-1";
	prog_argv[2] = "/usr";
	prog_argv[3] = NULL;
	
	stack = (char*)malloc(CHILD_STACK);
	if(stack==0)
	{
		perror("malloc : could not allocate stack");
		exit(2);
	}
	printf("PARENT: Creating child thread\n");
	
	pid = clone(thread_function,(void*)(stack + CHILD_STACK),SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM,NULL);
	if(pid == -1)
	{
		perror("clone");
		exit(3);
		
	}
	
	printf("PARENT: Waiting for the finish of child thread: %d\n",pid);
	pid = waitpid(pid,0,0);
	if(pid == -1)
	{
		perror("wait");
		exit(4);	
	}
	free(stack);
	printf("PARENT: Child thread returned and stack freed\n");\
	printf("PARENT: The variable foo now is : %d\n",foo);
	if(read(fd,&c,1)<1)
	{
		perror("PARENT: File Read Error!");
		exit(5);
	}
	else
	{
		printf("PARENT: We could read from the file: %c\n",c);
	}
	return 0;
}
