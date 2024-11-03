#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " program_to_run\n";
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Error: fork failed." << std::endl;
        exit(1);
    }

    if (pid > 0) {
        exit(0);
    }

    if (pid == 1){
        if (setsid() < 0) { 
        std::cerr << "Error: setsid failed." << std::endl;
        exit(1);
    }
    int dev_null = open("/dev/null", O_RDWR);
    if (dev_null < 0) {
        std::cerr << "Error: open file failed." << std::endl;
        exit(1);
    }
    //int out = open("out.txt", O_WRONLY | O_CREAT);
    //int err = open("err.txt", O_WRONLY | O_CREAT);
    dup2(dev_null, STDIN_FILENO);
    dup2(dev_null, STDOUT_FILENO);
    dup2(dev_null, STDERR_FILENO);

    execv(argv[1], &argv[1]);

    close(dev_null);
    }
    
    return 0;
}