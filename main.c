#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>

#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

#define buffersize 8    //maximum buffer size
#define items 64        //maximum no of items to produce

pthread_mutex_t the_mutex;
pthread_cond_t	condc, condp;

int p,c;
int buffer = 0;


void* producer(void *ptr)
{
  int i,k;
       pthread_mutex_lock(&the_mutex);  /* protect buffer */

         for(k=0;k<items;k++)
        {
            printf("producer %d produced %d item \n", ptr,k);
             if(buffer == (buffersize-1)) // buffer is full
            {
              printf("Buffer Is Full \n");
              pthread_cond_wait(&condp,&the_mutex);  // producer should wait for sometime

               pthread_mutex_lock(&the_mutex);
               sleep(1);
               pthread_cond_signal(&condc);        // wake up the consumer
               pthread_mutex_unlock(&the_mutex);   //release the buffer


            }
               buffer++;

               pthread_cond_signal(&condc);      //wake up the consumer
               pthread_mutex_unlock(&the_mutex);  //release the buffer
        }

   }





void* consumer(void *ptr)
{
  int i,j;

     pthread_mutex_lock(&the_mutex);      //protect buffer

    for(j=0;j<items;j++)
     {
           printf("consumer %d consumed %d item \n",ptr,j);
           if(buffer<=0)               //buffer is empty to consume
              {
              printf("Buffer Is Empty \n");
              pthread_cond_wait(&condc,&the_mutex); //consumer should wait for sometime

              pthread_mutex_lock(&the_mutex);
              sleep(1);
              pthread_cond_signal(&condp);  // wake up the producer
              pthread_mutex_unlock(&the_mutex); //release the buffer
                }

              buffer--;

              pthread_cond_signal(&condp);   //wake the producer
              pthread_mutex_unlock(&the_mutex); //release the buffer
            }
pthread_exit(0); //exit of thread consumer
     }


void main()
{
    int i;
    pthread_t pro,con;


    pthread_mutex_init(&the_mutex, NULL);
    pthread_cond_init(&condc, NULL);   /* Initialize consumer condition variable */
    pthread_cond_init(&condp, NULL);   /* Initialize producer condition variable */

    printf("Enter no of producers \n");
    scanf("%d", &p );
    printf("Enter no of consumers \n");
    scanf("%d", &c);

    for(i=0;i<p;i++)
    pthread_create(&pro, NULL, producer, (void *)i);
    for(i=0;i<c;i++)
    pthread_create(&con, NULL, consumer, (void *)i);

          for(i=0;i<p;i++)
		  pthread_join(pro,NULL);
		  for(i=0;i<c;i++)
          pthread_join(con,NULL);


          pthread_mutex_destroy(&the_mutex); //free up the mutex
          pthread_cond_destroy(&condc);     //free up the consumer condition variable
          pthread_cond_destroy(&condp);     //free up the producer condition variable

          system("PAUSE");

}


