# Dining_Philosophers
**[Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem):**
>In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
\
\
>It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present formulation.\
Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.
Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.

**Dining_Philosophers** is a termainal application implementing a simulation of a philosopher's life. You give it as arguments simulation parameters.\
Those are\
(1)number_of_philosophers
(2)time_to_die
(3)time_to_eat
(4)time_to_sleep
(5)(optional)number_of_times_each_philosopher_must_eat
