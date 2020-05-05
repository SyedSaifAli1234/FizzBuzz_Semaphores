#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

sem_t* sem1;
sem_t* sem2;
sem_t* sem3;
sem_t* sem4;
int i, mod;
int count1=0;
int count2=0;
int count3=0;

void* Print_1_100 (void* b){

      sem_wait(sem1);
      for(i = 1; i < 101; i++){
        
        if((i%3) == 0 && (i%5)!=0){ 
          sem_post(sem2);
          sem_wait(sem1);
        }
        else if(i%5 == 0 && (i%3)!=0){ 
          sem_post(sem3);
          sem_wait(sem1);
        }
        else if(i%3 == 0 && i%5 == 0){ 
          sem_post(sem4);
          sem_wait(sem1);
        }
        else{
          printf("%d\n",i);
        }        
      }

      pthread_exit(0);
    
}

void* Print_Fizz (void* b){

    while(count1!=27){
      count1=count1+1;
      sem_wait(sem2);
      printf("Fizz\n");
      sem_post(sem1);
    }
    
    pthread_exit(0);

}

void *Print_Buzz(void* b){

    while(count2!=14){
      count2=count2+1;
      sem_wait(sem3);
      printf("Buzz\n");
      sem_post(sem1);
    }
    pthread_exit(0);

}

void *Print_Fizz_Buzz(void* b){

    while(count3!=6){
      count3=count3+1;
      sem_wait(sem4);
      printf("FizzBuzz\n");
      sem_post(sem1);
    }
    pthread_exit(0);

}

int main(){

  pthread_t t1, t2, t3, t4;

  sem1 = sem_open("sem1",O_CREAT|O_EXCL, 666, 1);//Print Nums
  sem2 = sem_open("sem2",O_CREAT|O_EXCL, 666, 0);//Fizz
  sem3 = sem_open("sem3",O_CREAT|O_EXCL, 666, 0);//Buzz
  sem4 = sem_open("sem4",O_CREAT|O_EXCL, 666, 0);//FizzBuzz

  int result = sem_unlink("sem1");
  if ( result < 0){
    perror("Error in removing semaphore sem_fp\n");
    exit(0);
  }


  result = sem_unlink("sem2");
  if ( result < 0){
    perror("Error in removing semaphore sem_fp\n");
    exit(0);
  }

  result = sem_unlink("sem3");
  if ( result < 0){
    perror("Error in removing semaphore sem_fp\n");
    exit(0);
  }

  result = sem_unlink("sem4");
  if ( result < 0){
    perror("Error in removing semaphore sem_fp\n");
    exit(0);
  }


  pthread_create(&t1, NULL, &Print_1_100, NULL);
  pthread_create(&t2, NULL, &Print_Fizz, NULL);
  pthread_create(&t3, NULL, &Print_Buzz, NULL);
  pthread_create(&t4, NULL, &Print_Fizz_Buzz, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  return 0;

}