#include <sys/wait.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "cmd.hpp"

std::string prompt = "ksh $ ";

std::vector<std::string> tokenize(std::string s);
void run(std::string input);
std::string get_input();
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
    std::vector<std::string> tokens = tokenize(input);
    
    cmd my_cmd(tokens);
    my_cmd.run();
}


std::vector<std::string> tokenize(std::string s) {
    s += " ";
    std::vector<std::string> res;
    std::string curr = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            if (curr.length() > 0) {
                res.push_back(curr);
            }
            curr = "";
        }else {
            curr += s[i];
        }
    }
    return res;
}
