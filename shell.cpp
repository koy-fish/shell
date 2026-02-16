#include <sys/wait.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "cmd_list.hpp"

std::string prompt = "ksh % ";

std::vector<std::vector<std::string> > parse(std::string s);
void run(std::string input);
std::string get_input();
int shell_command(std::vector<std::vector<std::string> > parsed);
int main() {
    while(true){
        std::string input = get_input();
        run(input);
    }
    return 0;
}



std::string get_input(){
    std::cout << prompt;
    std::string res;
    std::getline(std::cin, res);
    return res;
}



void run(std::string input) {
    std::vector<std::vector<std::string> > parsed = parse(input);
    if(shell_command(parsed) == 0){
        cmd_list my_cmd_list(parsed);
        my_cmd_list.run();
    }
}

int shell_command(std::vector<std::vector<std::string> > parsed){
    if(parsed[0][0].compare("exit") == 0){
        std::exit(EXIT_SUCCESS);
        return 1;
    }else if(parsed[0][0].compare("cd") == 0){
        std::cout << parsed[0][1] << std::endl;
        if (chdir(parsed[0][1].c_str()) != 0){
            std::cerr << "[ERROR] cd";
        }
        return 1;
    }
    return 0;
}

std::vector<std::vector<std::string> > parse(std::string s){
    s += " ";
    std::vector<std::vector<std::string> > res;
    std::string curr = "";
    res.push_back(std::vector<std::string>());
    int curr_cmd = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            if (curr.length() > 0) {
                res[curr_cmd].push_back(curr);
            }
            curr = "";
        }else if(s[i] == '|'){
            res.push_back(std::vector<std::string>());
            curr_cmd += 1;
        }else {
            curr += s[i];
        }
    }
    return res;
}
