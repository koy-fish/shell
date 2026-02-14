#include <string>
#include <vector>
#include <unistd.h>


void execute(char ** args);
std::vector<std::string> parse(std::string s);
char ** make_args(std::vector<std::string> sep);
void run(std::string input);
int main(){
    run("ls -l");
    return 0;
}

void run(std::string input){
    std::vector<std::string> separated = parse(input);
    char ** args = make_args(separated);
    execute(args);
}


char ** make_args(std::vector<std::string> sep){
    char ** args = new char* [sep.size() + 1];

    for(int i = 0;i < sep.size();i++){
        args[i] = new char [sep[i].length() + 1];
        strcpy(args[i], sep[i].c_str());
        args[i][sep[i].length()] = '\0';
    }
    args[sep.size()] = NULL;
    return args;
}


std::vector<std::string> parse(std::string s){
    s += " ";
    std::vector<std::string> res;
    std::string curr = "";
    for(int i = 0; i < s.length(); i++){
        if(s[i] == ' '){
            if(curr.length() >0){
                res.push_back(curr);
            }
            curr = "";
        }else{
            curr += s[i];
        }
    }
    return res;
}

void execute(char ** args){
    execvp(args[0], args);
}
