#include <string>
#include <vector>
#include <unistd.h>


void execute(char ** args);

int main(){
    char * args [] = {"ls", NULL};
    execute(args);
}

void execute(char ** args){
    execvp(args[0], args);
}
