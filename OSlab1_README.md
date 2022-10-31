# OSlab1 -- Dylan Sarell -- 10/31/22

  For my First operating Systems Lab, this was inherrantly difficult. I have put numerous hours into this Assignment throughout the past week and there was so much new code that I have not seen before. To be honest I am still not sure if I have the Program fully working, but I got it to output something. In this assigment the Job was to create a program invloving the Producer Consumer Problem. It was to create two separate processes, a producer and a consumer, connecting them with shared memory. You were also to use semaphores to syncronize both processes so that way the producer or consumer don't enter their critical sections at the same time. The producer's job is to input data in a buffer (Via shared memory), and the consumer's job is to output the numbers, remove them from memory.
  
  In my program, the Producer will generate 2 random numbers (between 0 and 99), and store them into the buffer inside a shared memory structure. Below is my shared memory sturcture where it has 2 semaphores notEmpty (checks for buffer is not empty) and notFull (checks if buffer is not full). Cnt is the number of integers currently in the buffer. The buffer or "Table" is where the data is being stored. BUF_SIZE = 2 for there are only 2 integers in the table at one time.

  // Shared memory object
struct shmbuf {
    sem_t  notEmpty, notFull;           // semaphores 
    size_t cnt;             // Number of bytes used in buffer
    int buffer[BUF_SIZE];   // Table. The data being stored.
};

  
  
![shared h - dsarell1  SSH_ wasp cs kent edu  - Visual Studio Code 10_31_2022 12_44_24 PM](https://user-images.githubusercontent.com/116117025/199062436-5c1e1d27-9183-496c-8285-502a1fa803ef.png)
