/*
 * Project 1: YASh (Yet Another Shell)
 * Course: Operating Systems
 * Instructor: Ramesh Yeraballi
 * Student Name: Ali Ziyaan Momin
 * Date: Sept 5, 2017
 */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#define RUNNING 0
#define STOPPED 1
#define DONE 2


typedef struct node{
    int job_no;
    int pid;
    int pid2;
    int state; // running, stopped, done
    bool background;
    bool pid_check;
    char usr_input[2000];
    struct node* next;
} node;


node* head_of_linkedlist = NULL;


/*
    returns the job_no for a new job
 */
int get_job_no(node* head){

    node *cursor = head;
    node *temp;
    temp = cursor;

    while(cursor != NULL){
        temp = cursor;
        cursor = cursor->next;
    }

    return temp->job_no + 1;
}


/*
    create a new node
    initialize the data and next field

    return the newly created node
*/
node* create(int job_no, int pid, int pid2, int state, bool background, char* usr_input, node* next){
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL) {
        fprintf(stderr, "LinkedList: Error creating a new node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->job_no = job_no;
    new_node->pid = pid;
    new_node->pid2 = pid2;
    new_node->state = state;
    new_node->background = background;
    new_node->pid_check = false;
    strcpy(new_node->usr_input, usr_input);
    new_node->next = next;

    return new_node;
}



///*
//    add a new node at the beginning of the list
//*/
//node* prepend(node* head, int job_no, int pid, int state, bool status, char* usr_input){
//    node* new_node = create(job_no, pid, state, status, usr_input, head);
//    head = new_node;
//    return head;
//}


/*
    add a new node at the end of the list
*/
node* append(node* head, int pid, int pid2, int state, bool background, char* usr_input){
    if(head == NULL)
        return create(1, pid, pid2, state, background, usr_input, NULL);
    /* go to the last node */
    node *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    node* new_node =  create(get_job_no(head), pid, pid2, state, background, usr_input, NULL);
    cursor->next = new_node;

    return head;
}


/*
    Search for a specific node with input data

    return the first matched node that stores the input data,
    otherwise return NULL
*/
node* search(node* head, int pid){

    node *cursor = head;
    while(cursor!=NULL) {
        if (cursor->pid == pid) {
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
}


/*
    Search for a last node in the linked list

    return the pointer to the last node in the linked list,
    otherwise return NULL
*/
node* get_last_stopped_node(node* head){
    if(head == NULL){
        return NULL;
    }
    node* cursor = head;
    node* temp = NULL;
    temp = cursor;
    while(cursor != NULL){
        if(cursor->state == STOPPED){
            temp = cursor;
        }
        cursor = cursor->next;
    }
    temp->background = true;
    return temp;
}


/*
    Search for a last node in the linked list

    return the pointer to the last node in the linked list,
    otherwise return NULL
*/
node* get_last_node(node* head){
    if(head == NULL){
        return NULL;
    }
    node* cursor = head;
    while(cursor != NULL){
        if(cursor->next == NULL){
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
}


/*
    remove node from the front of list
*/
node* remove_front(node* head) {
    if(head == NULL){
        return NULL;
    }
    node *front = head;
    head = head->next;
//    front->next = NULL;
//    /* is this the last node in the list */
//    if(front == head){
//        head = NULL;
//    }
    free(front);
    return head;
}


/*
    remove node from the back of the list
*/
node* remove_back(node* head){
    if(head == NULL){
        return NULL;
    }

    node *cursor = head;
    node *back = NULL;
    while(cursor->next != NULL){
        back = cursor;
        cursor = cursor->next;
    }

    if(back != NULL){
        back->next = NULL;
    }

    /* if this is the last node in the list*/
    if(cursor == head) {
        head = NULL;
    }
    free(cursor);

    return head;
}


/*
    remove a node from the list
*/
node* remove_any(node* head,node* nd){
    if(nd == NULL){
        return NULL;
    }
    /* if the node is the first node */
    if(nd == head){
        return remove_front(head);
    }

    /* if the node is the last node */
    if(nd->next == NULL){
        return remove_back(head);
    }

    /* if the node is in the middle */
    node* cursor = head;
    while(cursor != NULL){
        if(cursor->next == nd){
            break;
        }
        cursor = cursor->next;
    }

    if(cursor != NULL){
        node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;

}


/*
    remove all element of the list
*/
void dispose(node *head){
    node *cursor, *tmp;

    if(head != NULL){
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL){
            tmp = cursor->next;
            kill(cursor->pid, SIGKILL);
            free(cursor);
            cursor = tmp;
        }
    }
}







bool containsChar(char *arr, int size, char ch){
    for(int i = 0; i < size; i ++){
        if(arr[i] == ch){
            return true;
        }
    }
    return false;
}


int getArgCount(char* arr){
    int spaces = 0;
    for(int i = 0; arr[i] != '\0'; i ++){
        if(arr[i] == ' '){
            spaces ++;
        }
    }

    int argcount = spaces + 1;

    return argcount;
}


char** argsArray(char* arr){

    int argcount = getArgCount(arr);

    char s[2] = " ";
    char **a;

    a = (char**) calloc((size_t) (argcount + 1), sizeof(char*));

    char *token;
    token = strtok(arr, s);

    for(int i = 0; (i < (argcount)) && (token != NULL); i ++){
        a[i] = strdup(token);
        token = strtok(NULL, s);
    }
    a[argcount] = NULL;

    return a;
}





void WCOMMAND(int status, int pid){
    if(WIFEXITED(status)){ //Ctrl-C
        node* node = search(head_of_linkedlist, pid);
        if(node != NULL){
            if(node->background){
                if(node->state == DONE){
                    //head_of_linkedlist = remove_any(head_of_linkedlist, node);
                } else{
                    node->state = DONE;
                }
            } else{
                head_of_linkedlist = remove_any(head_of_linkedlist, node);
            }
        }
    } else if(WIFSIGNALED(status)){
        node* node = search(head_of_linkedlist, pid);
        if(node != NULL){
            if(node->background && WTERMSIG(status) != 2){
                if(node->state == DONE){
                    //head_of_linkedlist = remove_any(head_of_linkedlist, node);
                } else{
                    node->state = DONE;
                }
            } else{
                head_of_linkedlist = remove_any(head_of_linkedlist, node);
            }
        }
    } else if(WIFSTOPPED(status)){ //Ctrl-Z
        node* node = search(head_of_linkedlist, pid);
        if(node != NULL){
            node->state = STOPPED;
        }
    } else if(WIFCONTINUED(status)){ //bg
        node* node = search(head_of_linkedlist, pid);
        if(node != NULL){
            node->state = RUNNING;
            node->background = true;
        }
    }
}


void print_jobs(){
    node* head = head_of_linkedlist;
    if(head != NULL){
        node* cursor = head;
        while(cursor != NULL){
            int status;
            int pid = waitpid(-cursor->pid, &status, WNOHANG);
//            if(cursor->state == DONE){
//                node* next = cursor->next;
//                head_of_linkedlist = remove_any(head, cursor);
//                cursor = next;
//                continue;
//            }

            if(cursor->pid2 != -2){
                if(pid == cursor->pid || pid == cursor->pid2){
                    if(!(cursor->pid_check)){
                        cursor->pid_check = true;
                        pid = -1;
                    }
                    else{
                        pid = cursor->pid;
                    }
                }
            }

            WCOMMAND(status, pid);
            char *state_string = NULL;
            if(cursor->state == RUNNING){
                state_string = strdup("RUNNING");
            } else if(cursor->state == STOPPED){
                state_string = strdup("STOPPED");
            } else if(cursor->state == DONE){
                state_string = strdup("DONE");
            }

            if(cursor->next == NULL){
                printf("[%d]+\t%s\t\t%s\n", cursor->job_no, state_string, cursor->usr_input);
            } else {
                printf("[%d]-\t%s\t\t%s\n", cursor->job_no, state_string, cursor->usr_input);
            }

            if(state_string != NULL){
                free(state_string);
            }
            cursor = cursor->next;
        }
    }
}


void print_done(){

    node* head = head_of_linkedlist;
    if(head != NULL){

        node* cursor = head;

        while(cursor != NULL){

            int status;
            int pid = waitpid(-cursor->pid, &status, WNOHANG);

            if(cursor->pid2 != -2){
                if(pid == cursor->pid || pid == cursor->pid2){
                    if(!(cursor->pid_check)){
                        cursor->pid_check = true;
                        pid = -1;
                    }
                    else{
                        pid = cursor->pid;
                    }
                }
            }

            WCOMMAND(status, pid);

            if(cursor->state == DONE){

                if(cursor->next == NULL){
                    printf("[%d]+\t%s\t\t%s\n", cursor->job_no, "DONE", cursor->usr_input);
                } else {
                    printf("[%d]-\t%s\t\t%s\n", cursor->job_no, "DONE", cursor->usr_input);
                }

                node* next = cursor->next;
                head_of_linkedlist = remove_any(head, cursor);
                cursor = next;

                continue;
            }
            cursor = cursor->next;
        }
    }
}


int execCommand(char **args, int *checkred, char* usr_input, bool background){

    pid_t c1pid;
    pid_t c2pid = -2;
    int pipefd[2];

    if(checkred[3] != -1){
        if(pipe(pipefd) == -1){
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    int fd0 = -1;
    int fd1 = -1;
    int fd2 = -1;

    if(checkred[0] != -1){
        //fd0 = open(args[checkred[0] + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
        fd0 = fileno(fopen(args[checkred[0] + 1], "w+"));
    }
    if(checkred[1] != -1){
        //fd1 = open(args[checkred[1] + 1], O_RDONLY);
        FILE* fp = fopen(args[checkred[1] + 1], "r+");
        if(fp == NULL){
            fprintf(stderr, "%s\n", strerror(errno));
            return EXIT_FAILURE;
        }
        fd1 = fileno(fp);
    }
    if(checkred[2] != -1){
        //fd2 = open(args[checkred[2] + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
        fd2 = fileno(fopen(args[checkred[2] + 1], "w+"));
    }

    if((c1pid = fork()) == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(c1pid == 0){

        //child1

        if(checkred[3] == -1){
            if(checkred[0] != -1){
                printf("check");
                dup2(fd0, STDOUT_FILENO);
                close(fd0);
                args[checkred[0]] = NULL;
            }
        }
        if(checkred[1] != -1){
            dup2(fd1, STDIN_FILENO);
            close(fd1);
            args[checkred[1]] = NULL;
        }
        if(checkred[2] != -1){
            dup2(fd2, STDERR_FILENO);
            close(fd2);
            args[checkred[2]] = NULL;
        }
        if(checkred[3] != -1){
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            args[checkred[3]] = NULL;
        }

        //execute the child1 process
        if(execvp(args[0], args) < 0){
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    } else{

        //parent

        setpgid(c1pid, c1pid);

        if(checkred[3] != -1){
            if((c2pid = fork()) == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            if(c2pid == 0){

                //child2

                close(pipefd[1]);

                if(checkred[0] != -1){
                    dup2(fd0, STDOUT_FILENO);
                    close(fd0);
                    args[checkred[0]] = NULL;

                }
                if(checkred[2] != -1){
                    dup2(fd2, STDERR_FILENO);
                    close(fd2);
                    args[checkred[2]] = NULL;
                }

                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);

                //execute the child2 process
                if(execvp(args[checkred[3]+1], &args[checkred[3]+1]) < 0){
                    fprintf(stderr, "%s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
            }


            setpgid(c2pid, c1pid);
            close(pipefd[0]);
            close(pipefd[1]);
        }

        int status;
        int pid;

        head_of_linkedlist = append(head_of_linkedlist, c1pid, c2pid, RUNNING, background, usr_input);

        if(checkred[3] != -1){
            if(background == false){
                tcsetpgrp(STDIN_FILENO, c1pid);
                waitpid(-c1pid, &status, WUNTRACED);
                pid = waitpid(-c1pid, &status, WUNTRACED);
                if(pid == c1pid || pid == c2pid){
                    pid = c1pid;
                }
                tcsetpgrp(STDIN_FILENO, getpgid(0));
            } else {
                waitpid(-c1pid, &status, WNOHANG);
                pid = waitpid(-c1pid, &status, WNOHANG);
                if(pid != 0){
                    if(pid == c1pid || pid == c2pid){
                        pid = c1pid;
                    }
                }
            }
        } else{
            if(background == false){
                tcsetpgrp(STDIN_FILENO, c1pid);
                pid = waitpid(-c1pid, &status, WUNTRACED);
                tcsetpgrp(STDIN_FILENO, getpgid(0));
            } else {
                pid = waitpid(-c1pid, &status, WNOHANG);
            }
        }


        WCOMMAND(status, pid);

        print_done();

    }

    if(fd0 != -1){
        if(close(fd0) < 0){
            perror("Error closing open file");
        }
    }
    if(fd1 != -1){
        if(close(fd1) < 0){
            perror("Error closing open file");
        }
    }
    if(fd2 != -1){
        if(close(fd2) < 0){
            perror("Error closing open file");
        }
    }

    return EXIT_SUCCESS;
}


void bg(){
    node* last_node = get_last_stopped_node(head_of_linkedlist);
    if(last_node == NULL){
        printf("bg: no such job\n");
        return;
    }

    node* abs_last_node = get_last_node(head_of_linkedlist);
    if(abs_last_node->state == RUNNING && abs_last_node->background){
        printf("bg: job %d already in background\n", abs_last_node->job_no);
        return;
    }

    kill(-(last_node->pid), SIGCONT);
    last_node->background = true;
    //last_node->state = RUNNING;

    int status;
    int pid;
    pid = waitpid(-last_node->pid, &status, WCONTINUED);
    WCOMMAND(status, last_node->pid);
    if(last_node->state == RUNNING){
        printf("[%d]+\t%s\t\t%s\n", last_node->job_no, "RUNNING", last_node->usr_input);
    }
}


void fg(){
    node* last_node = get_last_node(head_of_linkedlist);
    if(last_node == NULL){
        printf("fg: no such job\n");
        return;
    }

    printf("%s\n", last_node->usr_input);
    tcsetpgrp(STDIN_FILENO, last_node->pid);
    kill(-last_node->pid, SIGCONT);
    last_node->background = false;

    int status;
    int pid;
    pid = waitpid(-last_node->pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgid(0));
    WCOMMAND(status, pid);
}


int cd(char *path){
    char pth[2000];
    strcpy(pth,path);

    char cwd[2000];
    if(path[0] != '/') {
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,pth);
        if(chdir(cwd) == -1){
            printf("cd: The directory '%s' does not exist\n", path);
        }
    }else{
        if(chdir(path) == -1){
            printf("cd: The directory '%s' does not exist\n", path);
        }
    }

    return 0;
}





void sigint(int sig){
}

void sigtstp(int sig){
}


int main(int argc, char **argv){

    char usr_input[2000] = {0};
    char copy_of_usr_input[2000] = {0};

    if(signal(SIGINT, sigint) == SIG_ERR){
        perror("signal(SIGINT) error");
    }
    if(signal(SIGTSTP, sigtstp) == SIG_ERR){
        perror("signal(SIGTSTP) error");
    }
    signal(SIGTTOU, SIG_IGN);

    while(true){
        memset(usr_input, 0, 2000);
        memset(copy_of_usr_input, 0, 2000);

        printf("# ");
        fflush(stdout);
        fflush(stdin);
        //int c = scanf("%[^\n]%*c", usr_input);
        if(fgets(usr_input, 2000, stdin) == NULL){
            break;
        }

        if ((strlen(usr_input) > 0) && (usr_input[strlen(usr_input) - 1] == '\n')){
            if(strlen(usr_input) == 1){
                print_done();
                continue;
            }
            usr_input[strlen(usr_input) - 1] = '\0';
        }

        if(strcmp(usr_input, "jobs") == 0){
            print_done();
            print_jobs();
            continue;
        }


        if(strcmp(usr_input, "bg") == 0){
            print_done();
            bg();
            continue;
        }

        if(strcmp(usr_input, "fg") == 0){
            print_done();
            fg();
            continue;
        }

//        if(c == 0 || c == EOF){
//            if(c == EOF){
//                kill(0, SIGKILL);
//                exit(0);
//            }
//            getchar();
//            print_done();
//            continue;
//        }

        print_done();

        strcpy(copy_of_usr_input, usr_input);

        int argcount = getArgCount(usr_input);

        char **arguments = argsArray(usr_input);

        int checkred[4] = {[0 ... 3]=-1};

        if(containsChar(usr_input, 2000, '>') || containsChar(usr_input, 2000, '<') || containsChar(usr_input, 2000, '|')){

            int row = argcount;

            while(row > 0){
                if(strcmp(arguments[row-1],">") == 0){
                    checkred[0] = row-1;
                } else if(strcmp(arguments[row-1], "<") == 0){
                    checkred[1] = row-1;
                } else if(strcmp(arguments[row-1], "2>") == 0){
                    checkred[2] = row-1;
                } else if(strcmp(arguments[row-1], "|") == 0){
                    checkred[3] = row-1;
                }
                row --;
            }

        }

        bool background = false;

        if(strcmp(arguments[argcount-1], "&") == 0){
            background = true;
            arguments[argcount-1] = NULL;
        }

        if(strcmp(arguments[0], "cd") == 0){
            cd(arguments[1]);
        }else{
            execCommand(arguments, checkred, copy_of_usr_input, background);
        }

        int row = argcount;

        while(row > 0){
            free(arguments[row-1]);
            row --;
        }

        free(arguments);
    }

    dispose(head_of_linkedlist);
    return EXIT_SUCCESS;

}