# Dining_Philosophers
## **[Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem):**
>In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
\
\
>It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present formulation.\
Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.
Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.

## **Subject**
**Dining_Philosophers** is a termainal application implementing a simulation of a philosopher's life.\
Philosopher tries to take the fork on his left and the one on his right, eats spaghetti and after that put down both forks. Then it sleeps, and after that thinks, waiting for his neighbors to put down their forks. After taking both forks again, cycle continues. One of simulation parameters is time_to_die. If the time interval between ецщ meals exceeds this parameter, philosopher dies and simulation stops.

You give the program simulation parameters as program arguments. Those are:\
**number_of_philosophers**\
**time_to_die**\
**time_to_eat**\
**time_to_sleep**\
**(optional) number_of_times_each_philosopher_must_eat**\
## **usage**
Git clone the repository by entering\
```
git clone https://github.com/BuddhaCola/Dining_Philosophers.git
```
cd into it
```
cd Dining_Philosophers
```
This is a Makefile project. Compile it by entering
```
make
```
After that you can lauch program by entering\
./philosophers [params]\
replacing [params] with parameters.\
For example
```
./philosophers 5 410 200 200
```
\
![Screen-Recording-2021-09-23-at-1 55 34-PM](https://user-images.githubusercontent.com/63592194/134495648-ac69f3ad-5cb5-49dc-bd86-c86cabbf827e.gif)
