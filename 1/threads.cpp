#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int NUMBERTH = 2; //Antal threads

void *printThread(void* ID); //Prototype

int main()
{
  pthread_t threads[NUMBERTH]; //Opretter variabler af pthread_t
  
  for(int i=0; i<NUMBERTH; i++) //Threads oprettes vha. pthread_create
  {
    cout << "Creating thread with ID: " << i << endl;
    if(pthread_create(&threads[i], NULL, printThread, (void*)(i)) != 0) //Tjekker om oprettes korrekt
    {
      cout << "Could not create thread with ID: " << i << endl;
      cout << "Termination.." << endl;
      return 1;
    }
  }
  
  for(int i=0; i<NUMBERTH; i++) //Venter på threads dør
  {
    pthread_join(threads[i], NULL);
  }
  
  return 0;
}

void *printThread(void* ID) //Printer threads ID og antal gange
{
  int threadID = (int)(ID);
  for(int i=0; i<10; i++)
  {
    cout << "Hello #" << i << " from thread " << threadID << endl;
    sleep(1);
  }
  
  cout << "Terminating thread " << threadID << endl;
  pthread_exit(NULL);
  
  return 0;
}