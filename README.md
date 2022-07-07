# philosophers

Simulation of the dining philosophers problem.
This project is part of the 42 cursus. Please see the subject PDF for details.

The aim of this C project is to get familiar with multithreading, mutex, and deadlock.

Usage : 

Compile the project with 'make'.

Launch the executable like this :
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_cycles]

[number_of_cycles] is optional.
All times are expressed in ms.

For an even number of philo : [time_to_die] needs to be at least 2 times [time_to_eat] in order for the philos to not die.
For an odd number of philo it's 3 times.
If [time_to_eat] + [time_to_sleep] exceeds [time_to_die], the philos will die too.

Enjoy this little simulation ! The results can be visualized here : https://nafuka11.github.io/philosophers-visualizer
Thank you Naho Fukada for the vizualizer ! --> https://github.com/nafuka11
