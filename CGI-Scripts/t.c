
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *env[] = {"SCRIPT_FILENAME=/home/pewpan/Prog/42SP/42Webserv/CGI-Scripts/k.py", NULL};

    // char *arg[] = {"/home/pewpan/Prog/42SP/42Webserv/CGI-Scripts/execute-python.sh", NULL};
    char *arg[] = {"execute-python.sh", NULL};

    execve("./execute-python.sh", arg, env);
}
