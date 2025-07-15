*#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cmath>

using namespace std;

double calculate_partial_pi(int start, int end) {
    double sum = 0.0;
    for (int i = start; i < end; ++i) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
        sum += term;
    }
    return sum;
}

int main() {
    int num_processes = 4;  
    int num_values = 100000; 
    int values_per_process = num_values / num_processes;

    int pipes[num_processes][2];
    pid_t pids[num_processes];

    for (int p = 0; p < num_processes; ++p) {
        if (pipe(pipes[p]) == -1) {
            cerr << "Pipe creation failed\n";
            return 1;
        }

        pids[p] = fork();
        if (pids[p] < 0) {
            cerr << "Fork failed\n";
            return 1;
        }
        
        if (pids[p] == 0) {
            close(pipes[p][0]);
            int start = p * values_per_process;
            int end = (p == num_processes - 1) ? num_values : start + values_per_process;
            double partial_pi = calculate_partial_pi(start, end);
            write(pipes[p][1], &partial_pi, sizeof(partial_pi));
            close(pipes[p][1]);
            exit(0);
        }
        close(pipes[p][1]);
    }

    double pi = 0.0;
    for (int p = 0; p < num_processes; ++p) {
        waitpid(pids[p], nullptr, 0);
        double partial_result;
        read(pipes[p][0], &partial_result, sizeof(partial_result));
        close(pipes[p][0]);
        pi += partial_result;
    }

    pi *= 4;
    cout << "Value of pi: " << pi << "\n";
    return 0;
}