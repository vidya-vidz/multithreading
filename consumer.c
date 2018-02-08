
void* consumer(void *ptr)
{
  int i,j;

     pthread_mutex_lock(&the_mutex);

    for(j=0;j<items;j++)
     {
           printf("consumer %d consumed %d item \n",ptr,j);
           if(buffer<=0)
              {
              printf("Buffer Is Empty \n");
              pthread_cond_wait(&condc,&the_mutex);

              pthread_mutex_lock(&the_mutex);
              pthread_cond_signal(&condp);
              pthread_mutex_unlock(&the_mutex);
                }

              buffer--;
              pthread_cond_signal(&condp);
              pthread_mutex_unlock(&the_mutex);
            }
pthread_exit(0);
     }
