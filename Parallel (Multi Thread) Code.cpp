#include <iostream>
#include <pthread.h>
#include <cmath>
#include <mutex>

using namespace std;

double pi = 0.0;
mutex mx; 

struct ThreadArgs //Construction Thread
{
    int start;
    int end;a
};

void *calculate_pi(void *args) //Calculation pi function
{
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    double sum = 0.0;

    for (int i = threadArgs->start; i < threadArgs->end; ++i) 
    {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
        sum += term;
    }


    {
        lock_guard<mutex> lock(mx);
        pi += sum;
    }

    pthread_exit(nullptr); 
}

int main() 
{
    int num_threads = 4;      
    int num_values = 1000000; 

    cout << "number of threads: " << num_threads << "\n";
    cout << "number of values: " << num_values << "\n";

    pthread_t threads[num_threads];
    pthread_attr_t attrs[num_threads];
    ThreadArgs args[num_threads];

    int values_per_thread = num_values / num_threads;

    for (int t = 0; t < num_threads; ++t) 
{
    args[t].start = t * values_per_thread;
    
    if (t == num_threads - 1)
    {
        args[t].end = num_values;
    } else 
    {
        args[t].end = args[t].start + values_per_thread;
    }

    pthread_attr_init(&attrs[t]);
    pthread_create(&threads[t], &attrs[t], calculate_pi, &args[t]);
}

    for (int t = 0; t < num_threads; ++t)
    {
        pthread_join(threads[t], nullptr);
    }

    pi *= 4;
    cout << "value of pi: " << pi << "\n";

    return 0;
}
