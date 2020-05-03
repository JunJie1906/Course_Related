#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{

	pid_t childpid;
	int retval;
	int status;
	childpid = fork();
	if(childpid == 0)
	{
		printf("CHILD: This is CHILD process!!\n");
		printf("CHILD: PID = %d\n",getpid());
		printf("CHILD: parent's PID = %d\n",getppid());
		printf("CHILD: fork return is : %d\n",childpid);
		printf("CHILD: sleep for 1 second\n");
		sleep(1);
		printf("CHILD: Enter an exit value(0,255):");
		scanf("%d",&retval);
		printf("CHILD: Goodbye!!\n");
		exit(retval);
	}
	if(childpid>0)
	{
		printf("PARENT: This is parent process\n");
		printf("PARENT: Here's my PID : %d\n",getpid());
		printf("PARENT: The value of my child's PID is : %d\n",childpid);
		printf("PARENT: I will wait for my child to exit, and store its status\n");
		wait(&status);
		printf("PARENT: Child's exit code is %d\n",WEXITSTATUS(status));
		printf("PARENT: Goodbye!!\n");
		exit(0);
	}
	if(childpid<0)
	{
		perror("fork");
		exit(0);
	}

}
