# OSlab1 -- Dylan Sarell -- 10/31/22

  For my First operating Systems Lab, it was inherrantly difficult. I have put numerous hours into this Assignment throughout the past week and there was so much new code that I have not seen before. To be honest I am still not sure if I have the Program fully working, but I got it to output something. In this assigment the Job was to create a program invloving the Producer Consumer Problem. It was to create two separate processes, a producer and a consumer, connecting them with shared memory. You were also to use semaphores to syncronize both processes so that way the producer or consumer don't enter their critical sections at the same time. The producer's job is to input data in a buffer (Via shared memory), and the consumer's job is to output the numbers, remove them from memory.
  
  Below is my shared memory sturcture where it has 2 semaphores notEmpty (checks for buffer is not empty) and notFull (checks if buffer is not full). Cnt is the number of integers currently in the buffer. The buffer or "Table" is where the data is being stored. BUF_SIZE = 2 for there are only 2 integers in the table at one time.

![shared h - dsarell1  SSH_ wasp cs kent edu  - Visual Studio Code 10_31_2022 12_46_58 PM](https://user-images.githubusercontent.com/116117025/199062920-e0614c5e-47dd-4d86-9618-cc444955ba3b.png)

  In my program, the Producer will generate 2 random numbers (between 0 and 99), and store them into the buffer inside a shared memory structure. First the program opens the shared memory with shm_open() and then maps a structure to the structure within shared memory using mmap(). I initalize the semaphores notEmpty and notFull to 0 and 2, respectifully. Before the crit section I make sure that the structure is not full, using sem_wait(). I then make a for loop where it will generate the 2 random numbers and using memcpy(), the program copies the numbers into the integer array called buffer in the shared memory. After the for loop I signal the consumer process that the buffer is notEmpty using sem_post().

  In my Program, the Consumer will output the 2 randomly generated numbers by the producer, waiting 2 seconds before each output. First the program proceeds to do the same thing by opening the same shared memory object and mapping another structure to that structure in shared memory. Before the critical section I check to see if the buffer is notEmpty using sem_wait(). I then use a for loop to output the numbers in shared memory. After the for loop I signal that the buffer is notFull using sem_post().
  
  
