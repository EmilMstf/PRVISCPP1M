#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " program_to_run\n";
        return 1;
    }
    int out = open("out.txt", O_WRONLY | O_CREAT);
    int err = open("err.txt", O_WRONLY | O_CREAT);

    dup2(out, STDOUT_FILENO);
    dup2(err, STDERR_FILENO);

    execv(argv[1], &argv[1]);

    close(out);
    close(err);

    return 0;
}