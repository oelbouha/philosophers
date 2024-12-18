Philosophers
I never thought philosophy would be so deadly.

Introduction
Philosophy, derived from the Greek word philosophia (love of wisdom), explores fundamental questions about existence, knowledge, values, reason, and language.<br>
In this project, you'll bring philosophy to life by simulating the infamous Dining Philosophers Problem—a classic synchronization exercise used to demonstrate the challenges of managing shared resources in concurrent programming.<br>

Description
This project introduces you to threading and process management, where philosophers alternate between eating, thinking, and sleeping.<br>
They compete for forks, which are shared resources.<br>
You will need to use threading, mutexes, and semaphores to solve synchronization challenges, avoiding deadlocks, starvation, and race conditions.<br>

Key points of the simulation:<br>

Philosophers eat, sleep, or think.<br>
Philosophers need two forks to eat.<br>
A philosopher dies if they don't eat within a given time_to_die.<br>
The simulation stops when a philosopher dies or when a predefined condition is met (e.g., all philosophers have eaten enough times).<br>
Mandatory Features
Thread-based Implementation<br>

Each philosopher is represented by a thread.<br>
Mutexes are used to manage fork access and ensure proper synchronization.<br>
Input Parameters<br>
Your program should take the following arguments:<br>

number_of_philosophers – Number of philosophers (and forks).<br>
time_to_die – Maximum time (in milliseconds) a philosopher can go without eating before dying.<br>
time_to_eat – Time (in milliseconds) it takes for a philosopher to eat.<br>
time_to_sleep – Time (in milliseconds) a philosopher spends sleeping.<br>
[number_of_times_each_philosopher_must_eat] (optional) – Simulation stops when all philosophers have eaten at least this many times.<br>
State Logs<br>

Every philosopher action must be logged with a timestamp in milliseconds:<br>
csharp
Copy code
[timestamp_in_ms] X has taken a fork  
[timestamp_in_ms] X is eating  
[timestamp_in_ms] X is sleeping  
[timestamp_in_ms] X is thinking  
[timestamp_in_ms] X died  
Ensure logs are printed without overlapping or mixing.<br>
No Global Variables<br>

Your program must not rely on global variables to store state.<br>
Bonus Features
Process-based Implementation<br>

Each philosopher is represented as a separate process.<br>
Forks are managed with semaphores rather than mutexes.<br>
Single Fork Pool<br>

All forks are placed in a shared pool represented by a semaphore.<br>
Parent Process<br>

The main process monitors child processes (philosophers) and handles cleanup.<br>
Requirements
Programming Language: C<br>
External Functions Allowed:<br>
Mandatory: memset, printf, malloc, free, write, usleep, gettimeofday, pthread_* functions.<br>
Bonus: Additional functions like fork, kill, waitpid, sem_*.<br>
Memory Management: No memory leaks. All dynamically allocated memory must be freed.<br>
Makefile:<br>
Must include the rules: NAME, all, clean, fclean, re.<br>
Separate targets for mandatory and bonus parts.<br>
Compilation and Usage
Mandatory Part
Compilation<br>
go
make
```<br>  

Running the Program
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**
./philo 5 800 200 200
<br>
This simulates 5 philosophers with the following parameters:<br>  
- `time_to_die = 800ms`<br>  
- `time_to_eat = 200ms`<br>  
- `time_to_sleep = 200ms`<br>  
Bonus Part
Compilation<br>
go
make bonus
```<br>  

Running the Program

./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**<br>  
./philo_bonus 5 800 200 200 5
<br>
This stops the simulation when all philosophers eat at least 5 times.<br>  
Project Rules
Ensure no deadlocks or data races.<br>
Display state messages clearly and in the correct order.<br>
A philosopher's death should be logged within 10ms of their actual death.<br>
Implementation Notes
Deadlock Prevention<br>

Implement a solution where philosophers don’t hold onto one fork indefinitely, e.g., using an odd/even pickup rule or prioritizing certain philosophers.<br>
Synchronization<br>

Use mutexes for thread-based synchronization (mandatory).<br>
Use semaphores for process-based synchronization (bonus).<br>
Time Management<br>

Use gettimeofday for accurate timestamp logging.<br>
Avoid busy waiting—use usleep to simulate delays.<br>
Testing<br>

Test with varying parameters to ensure all edge cases are handled (e.g., 1 philosopher, long time_to_die, etc.).<br>
Resources
Concepts:<br>

Dining Philosophers Problem - Wikipedia<br>
Thread Synchronization - GeeksforGeeks<br>
Code Examples:<br>

POSIX Threads Programming<br>
Semaphores in C<br>
Debugging Tools:<br>

Valgrind for memory leak checks.<br>
Use custom test cases to debug race conditions and ensure thread safety.<br>
Conclusion
The Philosophers project is an engaging way to learn threading, synchronization, and process management in C.<br>
By solving the challenges of the dining philosophers problem, you will develop a deeper understanding of concurrency, resource sharing, and deadlock prevention, laying the groundwork for more complex system-level programming.<br>

Happy coding! 🧠✨<br>
