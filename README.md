# PersonalProject4

This C++ program is a multi-threaded application that simulates a reader-writer problem using POSIX threads (pthreads) and semaphores. The program creates multiple reader threads and writer threads based on the command line arguments. Each thread performs reading or writing operations on a shared string variable.

The program begins by including the necessary header files for pthreads, I/O operations, synchronization mechanisms (semaphores), and other system-related functionality.

Next, the program defines global variables and initializes the required synchronization objects. It uses two semaphores: mutex1 for mutual exclusion when updating the readcount variable and wrt for mutual exclusion between writers and to determine the first or last reader entering the critical section. The readcount variable keeps track of the number of active readers. The shared_string variable holds the string that will be read and written by the threads.

The program defines two functions: writer and reader, which are executed by the writer threads and reader threads, respectively.

The writer function repeatedly executes a loop until the shared_string is empty or has a length of 1,000,000. Within each iteration, the writer thread acquires the wrt semaphore using sem_wait to ensure exclusive access to the shared string. It then prints a message indicating that it is writing and modifies the shared_string by removing the last character using shared_string.pop_back(). After that, it releases the wrt semaphore using sem_post to allow other threads to access the shared string. The writer thread then sleeps for 1 second before starting the next iteration. Finally, the thread exits.

The reader function also executes a loop until the shared_string is empty or has a length of 1,000,000. In each iteration, the reader thread first acquires the mutex1 semaphore using sem_wait to protect the readcount variable. It increments the readcount and prints a message indicating the increment. If the readcount becomes 1 (meaning it was zero before), the reader thread acquires the wrt semaphore to ensure exclusive access for the first reader entering the critical section. The reader then releases the mutex1 semaphore. After that, the reader prints the contents of the shared_string using printf. The thread then reacquires the mutex1 semaphore, decrements the readcount, and prints a message indicating the decrement. If the readcount becomes 0, the reader releases the wrt semaphore to signal the writer. The reader thread releases the mutex1 semaphore and sleeps for 1 second before starting the next iteration.

In the main function, the program starts by checking the command line arguments. It expects two arguments: the number of reader threads and the number of writer threads. If the number of arguments is incorrect or any argument is negative, an error message is printed, and the program terminates.

Next, the program initializes the semaphores (mutex1 and wrt) using sem_init. It then creates arrays of pthreads for reader threads and writer threads. It also defines variables for thread identifiers (pthread_t), a loop variable (t), and a return code (rc).

The program enters a loop to create reader threads using pthread_create. For each thread, it passes the reader function as the thread routine and the loop variable t as the argument. If an error occurs during thread creation, an error message is printed, and the program exits with an error code.

After creating the reader threads, the program enters another loop to create writer threads using pthread_create. The process is similar to creating reader threads.

Once all threads are created, the program waits for the reader threads to finish using pthread_join in a loop. Then it waits for the writer threads to finish in a similar manner.

Finally, the program cleans up the semaphores using sem_destroy and exits the main function.

Overall, the program creates multiple reader and writer threads that concurrently read from and write to a shared string while ensuring mutual exclusion and synchronization using semaphores and a mutex.
