# process-scheduler-SRTF
### A C-Program implementing the Shortest Remaining Time First algorithm to schedule processes

This algorithm required a user input of process ID, Arrival time, burst time and time quantum. The core of the algorithm works in the following manner: 
- Another structure is created to hold the initial burst times. This is periodically decremented as the given process executed in the CPU.
- A loop is created to transverse through the indi-vidual processes which are stored as structures, and a process is selected for CPU execution only if it  
  - Is not terminated
  - has arrival time less than the current length of CPU executed (for processes yet to get CPU time for the first time)
  - Its remaining time for execution is the least among all candidate processes (in the ready queue) .

It is also the case that there exists very few context switches because after all the processes have entered the CPU for the first time, the algorithm executes in the same manner as the SJF algorithm which switches very sparingly

## Acknowledgements
