#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <sys/stat.h>   
#include <ctype.h>     
#include <signal.h>
#include <fcntl.h>
#define MAXL 100
#define MAX 1000

void afficher_cwd()
{
    char cwd[1000];
    getcwd(cwd, sizeof(cwd));
    printf("\nDirectory is: %s", cwd);
}

void parseurEsp(char* buffer, char** parseur)
{
	int i;

	for (i = 0; i < MAXL; i++) {
		parseur[i] = strsep(&buffer, " ");
        if (parseur[i] == NULL)
			break;
		if (strlen(parseur[i]) == 0)
			i--;
	}
}
void execmdS(char** parseur)
{
	pid_t pid = fork();

	if (pid == -1) {
		printf("\nFailed forking child");
		return;
	} else if (pid == 0) {
		if (execvp(parseur[0], parseur) < 0) {
			printf("\nCould not execute command");
		}
		exit(0);
	} else {
		wait(NULL);
		return;
	}
}
void execmdCT(char** parseur, char** parstube)
{
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0) {
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0) {
		printf("\nCould not fork");
		return;
	}

	if (p1 == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parseur[0], parseur) < 0) {
			printf("\nCould not execute command 1");
			exit(0);
		}
	} else {
		p2 = fork();

		if (p2 < 0) {
			printf("\nCould not fork");
			return;
		}
		if (p2 == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parstube[0], parstube) < 0) {
				printf("\nCould not execute command 2");
				exit(0);
			}
		} else {
			wait(NULL);
			wait(NULL);
		}
	}
}

int parseurTube(char* buffer, char** strtube)
{
	int i;
	for (i = 0; i < 2; i++) {
		strtube[i] = strsep(&buffer, "|");
		if (strtube[i] == NULL)
			break;
	}

	if (strtube[1] == NULL)
		return 0; 
	else {
		return 1;
	}
}
void execmdCA(char** parseur, char** parstube)
{
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0) {
		printf("\nAnd operator could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0) {
		printf("\nCould not fork");
		return;
	}
        if (p2 < 0) {
		printf("\nCould not fork");
		return;
	}
	if ((p1 == 0) && (p2 == 0))
		 {close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parseur[0], parseur) < 0) {
			printf("\nCould not execute command 1");
			exit(0);
			
			}
		} else {
			wait(NULL);
			wait(NULL);
		}
	
}
int parseur_and(char* buffer, char** strtube)
{
	int i;
	for (i = 0; i < 2; i++) {
		strtube[i] = strtok(buffer, "&&");
		if (strtube[i] == NULL)
			break;
	}

	if (strtube[1] == NULL)
		return 0; 
	else {
		return 1;
	}
}
void execmdCOr(char** parseur, char** parstube)
{
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0) {
		printf("\nAnd operator could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 == 0) {
		printf("\nCould not fork");
		return;
	}
        if (p2 < 0) {
		printf("\nCould not fork");
		return;
	}
	if ((p1 < 0) && (p2 == 0))
		 {close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parseur[0], parseur) < 0) {
			printf("\nCould not execute command 1");
			exit(0);
			
			}
		} else {
			wait(NULL);
			wait(NULL);
		}
}
int parseur_or(char* buffer, char** strtube)
{
	int i;
	for (i = 0; i < 2; i++) {
		strtube[i] = strtok(buffer, "||");
		if (strtube[i] == NULL)
			break;
	}

	if (strtube[1] == NULL)
		return 0; 
	else {
		return 1;
	}
}
void execmdCOp(char** parseur, char** parstube)
{
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0) {
		printf("\nLink operator could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0) {
		printf("\nCould not fork");
		return;
	    wait(NULL);
	}
	if (p1 == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parseur[0], parseur) < 0) {
			printf("\nCould not execute command 1");
			exit(0);
		}
		p2 = fork();
		if (p2 < 0) {
			printf("\nCould not fork");
			return;
		    wait(NULL);
		}
		if (p2 == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parstube[0], parstube) < 0) {
				printf("\nCould not execute command 2");
				exit(0);
			}
		}
	}
}
int parseur_op(char* buffer, char** strtube)
{
	int i;
	for (i = 0; i < 2; i++) {
		strtube[i] = strsep(&buffer, ";");
		if (strtube[i] == NULL)
			break;
	}

	if (strtube[1] == NULL)
		return 0; 
	else {
		return 1;
	}
}
int Traitecmd(char* buffer, char** parseur, char** parstube)
{

	char* strtube[2];
	int Tube = 0;
    int and = 0;
	int or = 0;
	int op = 0;
	Tube = parseurTube(buffer, strtube);
    and = parseur_and(buffer, strtube);
	or = parseur_or(buffer, strtube);
	op = parseur_op(buffer, strtube);
	if (Tube) {
		parseurEsp(strtube[0], parseur);
		parseurEsp(strtube[1], parstube);
        
	} 
	else if (and) {
		parseurEsp(strtube[0], parseur);
		parseurEsp(strtube[1], parstube);
        
	}
    else if (or) {
		parseurEsp(strtube[0], parseur);
		parseurEsp(strtube[1], parstube);
      
	} 
	else if (op) {
		parseurEsp(strtube[0], parseur);
		parseurEsp(strtube[1], parstube);
        
	} else {

		parseurEsp(buffer, parseur);
	}
         return 1;
}
void redirection(char** parseur)
{   pid_t pid;
    if (!parseur[0]) return;
    pid = fork();
    if (pid < 0) {
    printf("fork a échoué (%s)\n",strerror(errno));
    return;
  }
    if (pid==0) {
    int i;
    
    for (i=0;parseur[i+1];i++);

    if (parseur[i][0]=='>') {
     
      int file = open(&parseur[i][1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (file==-1) { 
	printf("ne peut pas créer le fichier \"%s\" (%s)\n", &parseur[i][1],strerror(errno));
	exit(1);
      }
      close(1);
      dup2(file,1);
      parseur[i] = NULL;
    }
    execvp(parseur[0], parseur);
    printf("impossible d'éxecuter \"%s\" (%s)\n",parseur[0],strerror(errno));
    exit(1);
  }
}

int hist(char* buffer)
{
	char* line;
        
	line = readline("\n% ");
	if (strlen(line) != 0) {
		add_history(line);
		strcpy(buffer, line);
            return 0;
	} else{
            return 1;
}
}

int main(int argc,char *argv[],char *arge[])
{  
    char** parseur;
    char** parstube;
    char** strtube;
    char str[MAX], *parseurArg[MAXL];
    char* parseurArgTube[MAXL];
    int type = 0;
while(1)
{    
    afficher_cwd();
   
    
    char buffer[100];
    if (argc>1)
    {
        printf("mode batch\n");
        FILE *afile=fopen(argv[1],"r");
        if (afile==NULL)
        {
            fprintf(stderr,"%s: %s\n",argv[1],buffer);
            exit(EXIT_FAILURE);
        }
        while (fgets(buffer,150,afile)!=NULL)
        {
            if (buffer[0]!='#')
            {
                exit(0);
            }
        }
        exit(0);
    }
    else    
    {if(hist(str))
    {     
        char prompt = '%';
        printf("%c ", prompt);
        fgets(buffer,150,stdin);
        
        buffer[strlen(buffer)-1]='\0';
        if (strlen(buffer)<0)
        {
            printf("Un nombre inadéquat d’arguments dans l’invite de commande");
	        exit(0);
        }
        if (strcmp("quit",buffer)==0)
        {
            exit(0);
        }	
        }
        if(hist(str))
        continue;	
        type = Traitecmd(str, parseurArg, parseurArgTube);
		if (type == 1)
			execmdS(parseurArg);

		if (type == 2){
        if(strcmp("|", buffer) == 0) {
			execmdCT(parseurArg, parseurArgTube);
		}
        if(strcmp(";", buffer) == 0) {
			execmdCOp(parseur, parstube);
		}
		else if(strcmp("||", buffer) == 0) {
			execmdCOr(parseur, parstube);
		}
		else if(strcmp("&&", buffer) == 0) {
			execmdCA(parseur, parstube);
		}
        else if(strcmp(">", buffer) == 0) {
			redirection(parseur);
		}
        else if (strcmp(parseur[0], "cd") == 0) {
            chdir(parseur[1]);
}
	}
	}
}
	return 0;
}

