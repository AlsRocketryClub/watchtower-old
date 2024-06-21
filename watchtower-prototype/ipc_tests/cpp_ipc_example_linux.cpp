// IPC example with internal pipe in linux 

#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <string>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        std::cerr << "Pipe failed" << std::endl;
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close the read end of the pipe
        std::string message = "Hello from child process!";
        write(pipefd[1], message.c_str(), message.size());
        close(pipefd[1]);
    } else {
        // Parent process
        close(pipefd[1]); // Close the write end of the pipe 
        char buffer[100];
        read(pipefd[0], buffer, 100);
        std::cout << "Received message: " << buffer << std::endl;
        close(pipefd[0]);
    }

    return 0;
}