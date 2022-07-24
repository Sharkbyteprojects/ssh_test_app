#include "sar.hpp"
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void init(){
    system("clear");
    std::cout << "Welcome to SharkCli\n<c> Sharkbyteprojects\n\nType exit or q to exit" << std::endl;
}

#define s(x) std::string(x)

std::string list_dir(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   
   if (dir == NULL) {
      return "";
   }
   std::string r = "";
   while ((entry = readdir(dir)) != NULL) {
    auto e = s(entry->d_name);
    if(e == s(".dockerenv")) continue;
    r += e + " ";
   }
   r[r.length()-1] = '\n';
   closedir(dir);
   return r;
}

void err(const char* error){
    fprintf(stderr, "\x1b[31m%s\x1b[0m\n", error);
}

void run(const std::string& command, const std::string& p){
    if(command == s("echo")){
        std::cout << p << std::endl;
    }else if(command == s("ls")){
        if(p == s(".")||p==s("/")||p==s("")){
            std::string _l = list_dir(p.c_str()), r="";
            size_t dc=0;
            char rt[2]={0, 0};
            for(size_t x=0;x<_l.length();x++){
                rt[0]=_l[x];
                dc++;
                if(rt[0]==' '){
                    if(dc>10){
                        dc=0;
                        rt[0]='\n';
                    }
                }
                r+=rt;
            }
            std::cout << r;
        }else
            err((s("You have not the required permissions to access \"") + p + "\"").c_str());
    }
    else if(command == s("cd")){
        if(p == s("")){
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                err("Current dir not available");
            }
        }
        else err("You aren't allowed to change the current dir!");
    }
    else if(command == s("help")){
        std::cout << "Commands:\n\t\x1b[92mhelp\x1b[0m, \x1b[92mps\x1b[0m, \x1b[92mcd\x1b[0m, \x1b[92mls\x1b[0m,"
        " \x1b[92mecho\x1b[0m, \x1b[92mexit\x1b[0m, \x1b[92mq\x1b[0m, \x1b[92mclear\x1b[0m\n" << "\n";
    }
    else if(command == s("clear")){
        init();
    }
    else if (command==s("ps")) _ps();
    else if(command != s("")){
        std::cerr << "\x1b[31mCan't find Command \"" << command << "\"\x1b[0m\n";
    }
}
