# Current List 

## Round-Robin (preempt)
#### A C program that simulates process scheduling using the preemptive round robin algorithm

This algorithm requires a user input of process ID, Arrival time, burst time and time quantum. The core of the algorithm works in the following manner: 
- Another structure is created to hold the initial burst times called temp. This is periodically decremented as the given process executed in the CPU, modelling continuous execution in the CPU.
- A loop is created to transverse through the individual processes which are stored as structures, and a process is selected for CPU execution only if it  
   - Is not terminated
   - has arrival time less than the current length of CPU executed (for processes yet to get CPU time for the first time)
   - It precedes the next executed process or succeeds the previous executed process during the first transversal through the loop.
The only exception to the third condition is if any of the three successive processes terminates, in that case, their successor (or predecessor) takes the spot.


## SRTF
#### A C-Program implementing the Shortest Remaining Time First algorithm to schedule processes

This algorithm requires a user input of process ID, Arrival time, burst time and time quantum. The core of the algorithm works in the following manner: 
- Another structure is created to hold the initial burst times. This is periodically decremented as the given process executed in the CPU.
- A loop is created to transverse through the indi-vidual processes which are stored as structures, and a process is selected for CPU execution only if it  
  - Is not terminated
  - has arrival time less than the current length of CPU executed (for processes yet to get CPU time for the first time)
  - Its remaining time for execution is the least among all candidate processes (in the ready queue) .

It is also the case that there exists very few context switches because after all the processes have entered the CPU for the first time, the algorithm executes in the same manner as the SJF algorithm which switches very sparingly

## Acknowledgements
Few posts on google I can't seem to find now
