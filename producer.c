
void* producer(void *ptr)
{
  int i,k;
       pthread_mutex_lock(&the_mutex);

         for(k=0;k<items;k++)
        {
            printf("producer %d produced %d item \n", ptr,k);
             if(buffer == (buffersize-1))
            {
              printf("Buffer Is Full \n");
              pthread_cond_wait(&condp,&the_mutex);
               pthread_mutex_lock(&the_mutex);
               pthread_cond_signal(&condc);
               pthread_mutex_unlock(&the_mutex);


            }
            buffer++;

                 pthread_cond_signal(&condc);
               pthread_mutex_unlock(&the_mutex);
        }

   }
