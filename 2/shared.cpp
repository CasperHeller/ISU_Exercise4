#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void *incrementer_func(void* ID); //Prototyper
void *reader_func(void* ID);

unsigned int shared = 0; //Opretter global variabel

int main()
{
  pthread_t incrementer; //Opretter objekter til threads
  pthread_t reader;
  
  char inc[]="Incrementer"; //ID's til de 2 threads
  char read[]="Reader";
  
  cout << "Creating thread: " << inc << endl; 
  if(pthread_create(&incrementer, NULL, incrementer_func, (void*)(inc)) != 0) //Opretter incrementer thread
    {
      cout << "Could not create thread: " << inc << endl;
      cout << "Termination.." << endl;
      return 1;
    }
    
  cout << "Creating thread: " << read << endl; 
  if(pthread_create(&reader, NULL, reader_func, (void*)(read)) != 0) //Opretter reader thread
    {
      cout << "Could not create thread: " << read << endl;
      cout << "Termination.." << endl;
      return 1;
    }
  
  pthread_join(incrementer, NULL); //Venter på de 2 threads dør
  pthread_join(reader, NULL);
  
  return 0;
}

void *incrementer_func(void* ID) //incrementer shared
{
  cout << "Starting: " << (char*)ID << endl;
  
  for(int i=0; i<10; i++)
  {
    shared++;
    sleep(1);
  }

  cout << "Terminating thread: " << (char*)ID << endl;
  pthread_exit(NULL);
  
  return 0;
}

void *reader_func(void* ID) //Udskriver værdien af shared
{
  cout << "Starting: " << (char*)ID << endl;
  
  for(int i=0; i<10; i++)
  {
    cout << "The value of shared: " << shared << endl;
    sleep(1);
  }

  cout << "Terminating thread: " << (char*)ID << endl;
  pthread_exit(NULL);
  
  return 0;
}