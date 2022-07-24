#include <csignal>
#include "sar.hpp"

bool wfi=false;
void h1(){
    std::cout << "Shark $> " << std::flush;
}
void signalHandler(int signum) {
   std::cout << "\n\x1b[31mExit with the command q or exit\x1b[0m\n";
   if(wfi) h1();
}

void splitAndRun(const std::string& s){
    std::string command{""}, else_{""};
    char cstr[2]{0x00, 0x00};
    bool buildCommand = true;
    for(size_t sr=0;sr < s.length();sr++){
        cstr[0] = s[sr];
        if(buildCommand){
            if(cstr[0] == ' ') {
                buildCommand=false;
                continue;
            }
            command += cstr;
        }else{
            else_ += cstr;
        }
    }

    run(command, else_);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, signalHandler);    
    init();

    std::string l{""};
    while(1){
        wfi=true;
        h1();
        std::getline(std::cin, l);
        wfi=false;

        if(l == std::string("exit")||l==std::string("q")){
            std::cout << "BYE..." << std::endl;
            break;
        }
        splitAndRun(l);
    }
    return 0;
}
