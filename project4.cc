//*************************************************************************
//
//    Jonathan Chavez
//    Z1866268
//    CSCI 480
//
//    I certify that this is my own work and where appropriate an extension 
//    of the starter code provided for the assignment.  
//
//****************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <mutex>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
//mutex1 protects the updating of readcount
sem_t mutex1;
//wrt mutual exclusion among writers, as well as for first or last reader that enters the critical section
sem_t wrt;
//how many readers
int readcount = 0;

string shared_string = "All work and no play makes Jack a dull boy.";

//**************************************************************************
// C++ program that takes in two command line arguments: number of reader threads,
// number of writer threads. My program creates several reader threads and several
// writer threads based on the arguments. Each thread loops for several iterations for writing or reading.
//
// @param void.
//
//***************************************************************************/

//***********
// The writer thread will alternate between writing and sleeping for 1 second. 
// In each iteration, it modifies the current contents of the string by chopping
// the last character of it, until it is an empty string.
//
//****************************/
void *writer(void *param)
{
	// loop until the string is empty
	while(!shared_string.empty() && shared_string.length() < 1000000)
	{
		sem_wait(&wrt);
		printf("Writer is writing ...\n");
		shared_string.pop_back();
		sem_post(&wrt);
		sleep(1);
	}
	pthread_exit(NULL);
}

//***********
// The reader thread also has a loop structure. It prints out the content of the
// shared string. In addition, it also prints out the current readcount value when
// the value increments or decrements. When the readcount is 0, the reader calls sem_post()
// on one semaphore to signal the writer.
//
//****************************/

void *reader(void *param)
{
	  while(!shared_string.empty() && shared_string.length() < 1000000)
	{
		sem_wait(&mutex1);
		readcount++;
		printf("readcount increments to: %d\n", readcount);
		if(readcount == 1)
		{
			 sem_wait(&wrt);
		}

		sem_post(&mutex1);
        	printf("%s\n", shared_string.c_str());
		sem_wait(&mutex1);
		readcount--;
		printf("readcount decrements to: %d\n", readcount);

		if(readcount == 0)
		{
			// When the readcount is 0 the reader calls sem_post()
			sem_post(&wrt);
		}

        	 sem_post(&mutex1);
		 sleep(1);
	}
	pthread_exit(NULL);
}

/*
The main program creates writer and reader threads which is grabbed from command line arguments.
Also does error checks for the command line arguments. Create threads based on input.
Once threads are created the main() function will wait for the threads to finish using 
pthread_join().
*/

int main (int argc, char *argv[])
{
	int number_reader_threads;
	int number_writer_threads;

	// Error checks for the command line arguments
	if (argc != 3)
	{
 		fprintf(stderr,"Not enough input values\n");
		return -1;
	}

	if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0)
	{
		fprintf(stderr,"input must be>= 0\n"); return -1;
	}

	// Get command line arguments
	number_reader_threads =  atoi(argv[1]);
	number_writer_threads =  atoi(argv[2]);
	// Initialization of semaphores
        sem_init(&mutex1, 0, 1);
        sem_init(&wrt, 0, 1);

        pthread_t writer_threads[number_writer_threads];
        pthread_t reader_threads[number_reader_threads];

        long t;
        int rc;

	// Create reader threads
       for(t=0; t < number_reader_threads; t++)
       {
                rc = pthread_create(&reader_threads[t], NULL, reader, (void *)t);
                if (rc)
                {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
                }
       }
	// Create writer threads
       for(t=0; t < number_writer_threads; t++)
       {
		rc = pthread_create(&writer_threads[t], NULL, writer, (void *)t);
		if (rc)
		{
         	printf("ERROR; return code from pthread_create() is %d\n", rc);
        	exit(-1);
      		}
       }

	// Wait for reader threads to finish 
	  for (t=0; t< number_reader_threads; t++)
          pthread_join(reader_threads[t], NULL);
	 // Wait for writer threads to finish 
	for (t=0; t< number_writer_threads; t++)
          pthread_join(writer_threads[t], NULL);
	//Cleanup and exit. 
	sem_destroy(&mutex1);
	sem_destroy(&wrt);
	pthread_exit(NULL);
}
