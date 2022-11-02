# OSlab1 -- Dylan Sarell -- 10/31/22

  For my First operating Systems Lab, it was inherrantly difficult. I have put numerous hours into this Assignment throughout the past week and there was so much new code that I have not seen before. To be honest I am still not sure if I have the Program fully working, but I got it to output something. In this assigment the Job was to create a program invloving the Producer Consumer Problem. It was to create two separate processes, a producer and a consumer, connecting them with shared memory. You were also to use semaphores to syncronize both processes so that way the producer or consumer don't enter their critical sections at the same time; to make sure each process is syncronized. The producer's job is to input data in a buffer (Via shared memory), and the consumer's job is to output the numbers, remove them from memory.
  
  Below is my shared memory sturcture where it has 2 semaphores notEmpty (checks for buffer is not empty) and notFull (checks if buffer is not full). Cnt is the number of integers currently in the buffer. The buffer or "Table" is where the data is being stored. BUF_SIZE = 2 for there are only 2 integers in the table at one time. Both my Producer and Consumer Process Include this header file, "Shared.h".

![shared h - dsarell1  SSH_ wasp cs kent edu  - Visual Studio Code 10_31_2022 12_46_58 PM (2)](https://user-images.githubusercontent.com/116117025/199335099-6ff058be-cdec-413c-aaf2-f6c33af7834b.png)

  In my program, the Producer will generate 2 random numbers (between 0 and 99), and store them into the buffer inside a shared memory structure. First the program opens the shared memory with shm_open() and then maps a structure to the structure within shared memory using mmap(). I initalize the semaphores notEmpty and notFull to 0 and 2, respectifully. Before the crit section I make sure that the structure is not full, using sem_wait(). I then make a for loop where it will generate the 2 random numbers and using memcpy(), the program copies the numbers into the integer array called buffer in the shared memory. After the for loop I signal the consumer process that the buffer is notEmpty using sem_post().

  In my Program, the Consumer will output the 2 randomly generated numbers by the producer, waiting 2 seconds before each output. First the program proceeds to do the same thing by opening the same shared memory object and mapping another structure to that structure in shared memory. Before the critical section I check to see if the buffer is notEmpty using sem_wait(). I then use a for loop to output the numbers in shared memory. After the for loop I signal that the buffer is notFull using sem_post(). Then I use shm_unlink() to unlink the shmpath, and removes the shared memory object name. 
  
  My Program only goes through the process only one time. So it randomly inputs 2 numbers into the buffer and outputs those 2 numbers only one time. I wasn't sure how to run it multiple times if you were supposed to at all. I think a way to implement it would to be to use the cnt variable as a tracker to keep track of how many elements in the buffer and keep updating it after each produce and consume; Also it would not unlink the shared memory object or name. There also might be other aspects i'm missing because I tried that in the program but it doesn't work or run multiple times. So in the end I did not end up adding that piece of code to my final revision of the code. 
  
  In the end of this assignment, I faced many problems. The Assignment overall was very vague and confusing. I did not know what kind of output the program would make; I also did not know many of the other coding elements, like shared memory, and semaphores. This was my first time coding in C rather than C++, so it took me awhile before I could even start the project, setting up my IDE to code in c and to use some of the commands. Overall, I struggled with the assignment but I worked really hard to try to understand the code and got my program to output something that makes sense. I hope this statisfies the criteria mentioned in the Instructions.
  
  Using the following commands allows you to run my Program:
  
  gcc producer.c -pthread -lrt -o producer
  
  gcc consumer.c -pthread -lrt -o consumer
  
  ./producer & ./consumer &
  
  # Here are some Examples of the code:
  
![consumer c - dsarell1  SSH_ wasp cs kent edu  - Visual Studio Code 11_1_2022 4_22_40 PM (2)](https://user-images.githubusercontent.com/116117025/199334889-a66a05e6-75e4-49ee-8ced-1797882ce7f5.png)

![producer c - dsarell1  SSH_ wasp cs kent edu  - Visual Studio Code 11_1_2022 4_25_24 PM (2)](https://user-images.githubusercontent.com/116117025/199334935-70f80032-d36f-4a3b-8b15-d4425f1c91f9.png)

![producer c - dsarell1  SSH_ wasp cs kent edu  - Visual Studio Code 11_1_2022 4_37_03 PM (2)](https://user-images.githubusercontent.com/116117025/199336316-3ad19bc7-4823-440a-ac06-ddc7520ed902.png)

