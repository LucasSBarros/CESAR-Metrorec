# Metrorec

The code provided is a simulation of a subway station called "METROREC". The program simulates the interaction between passengers and wagons at a station, where passengers wait for the wagon and board when it arrives.

The main code is contained in the main() function. It starts a subway station using the estacao_init() function and generates a random number of passengers. It then creates a thread for each passenger using the pthread_create() function. Each passenger thread calls the passenger_thread() function, where the passenger waits for the car using the estacao_espera_pelo_vagao() function and increments an atomic counter called counter to track the number of passengers who are ready to board.

In parallel, there is another thread called vagao_thread() that represents a subway car. This thread is created in a loop while there are passengers waiting at the station. The vagao_thread() function fills the wagon by calling estacao_preencher_vagao(), passing the number of free seats in the wagon. Inside estacao_preencher_vagao(), the function waits until the number of free seats equals zero using pthread_cond_wait().

Once the car is full or there are no more passengers waiting at the station, the car thread exits the loop and executes the rest of the code. Passengers are then boarded one at a time using the estacao_embarque() function inside a loop. Each time a passenger boards, the atomic counter is decremented. If at any time the value of the atomic counter counter is greater than the number of passengers remaining in the station, this indicates an error.

After all passengers have boarded, the program prints a message indicating that the station was successfully completed.

In addition to the main code, there is also the definition of the station structure and various auxiliary functions related to the metro station. These roles are responsible for starting the station, filling the car, making passengers wait for the car, and boarding available seats.

In summary, the code simulates the interaction between passengers and cars at a subway station, ensuring that passengers wait for the car and correctly board the available seats.
