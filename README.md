# Design-a-sequential-and-parallel-program-
Trabajo de programacion paralela en la que se crea 1 programa secuencial y 1 en paralelo sobre la ordenacion de cartas

# Sequential sorting code in python
Overview
This program generates a deck of 4 million cards with suits and values (hearts, clubs, spades, diamonds, and two jokers), and sorts the cards in ascending order. The sorting is based on the suit first (hearts, clubs, spades, diamonds, joker), followed by the card value (numbers 2-10, Jack, Queen, King, Ace).

Two versions are provided:

Sequential version – Sorts the cards using a single-threaded approach.
Parallel version – Sorts the cards using multiple processes to take advantage of parallel computation.
The following code is for the sequential sorting version.

import random

# Define the suits and values
palos = ['corazones', 'tréboles', 'picas', 'diamantes', 'comodín']
valores = [str(i) for i in range(2, 11)] + ['J', 'Q', 'K', 'A']

# Function to generate a deck of cards
def generar_cartas(n):
    cartas = []
    for _ in range(n):
        palo = random.choice(palos)
        if palo == 'comodín':
            carta = ('comodín', 0)  # Jokers are represented with a value of 0
        else:
            valor = random.choice(valores)
            carta = (palo, valor)
        cartas.append(carta)
    return cartas

# Comparison function to sort the cards
def comparar(carta):
    orden_palos = {'corazones': 0, 'tréboles': 1, 'picas': 2, 'diamantes': 3, 'comodín': 4}
    orden_valores = {str(i): i for i in range(2, 11)}
    orden_valores.update({'J': 11, 'Q': 12, 'K': 13, 'A': 14})

    palo, valor = carta
    if palo == 'comodín':  # Jokers always have a fixed value
        return (orden_palos[palo], 0)  # Value 0 is for jokers
    return (orden_palos[palo], orden_valores[str(valor)])  # Normalize value to string for number cards

# Generate 4 million cards
cartas = generar_cartas(4000000)

# Sort the cards
cartas_ordenadas = sorted(cartas, key=comparar)

# Display the first 10 sorted cards
print(cartas_ordenadas[:10])

# Execution time 15 seconds

This program provides a simple and effective way to generate and sort a deck of cards in Python. You can modify the number of cards or adjust the sorting criteria as needed for other types of card games or simulations.

## Parallel Sorting in Python
Overview
This Python program generates a deck of 4 million cards with suits and values (hearts, clubs, spades, diamonds, and jokers), and sorts the cards in ascending order using a parallel approach. The sorting first compares the suit, and then compares the value of the cards within the same suit. The program leverages the Python multiprocessing module to perform parallel sorting with multiple processes for increased efficiency.

The code has two main components:

# Card Generation:
Generates a deck of cards with random suits and values.
# Parallel Sorting:
Sorts the deck of cards using parallel processing.
The final result is a sorted deck with jokers placed at the end.

import random
import multiprocessing

# Define the suits and values
palos = ['corazones', 'tréboles', 'picas', 'diamantes', 'comodín']
valores = [str(i) for i in range(2, 11)] + ['J', 'Q', 'K', 'A']

# Function to generate a deck of cards
def generar_cartas(n):
    cartas = []
    for _ in range(n):
        palo = random.choice(palos)
        if palo == 'comodín':
            carta = ('comodín', 0)  # Jokers are represented with a value of 0
        else:
            valor = random.choice(valores)
            carta = (palo, valor)
        cartas.append(carta)
    return cartas

# Comparison function to sort the cards
def comparar(carta):
    orden_palos = {'corazones': 0, 'tréboles': 1, 'picas': 2, 'diamantes': 3, 'comodín': 4}
    orden_valores = {str(i): i for i in range(2, 11)}
    orden_valores.update({'J': 11, 'Q': 12, 'K': 13, 'A': 14})

    palo, valor = carta
    if palo == 'comodín':  # Jokers always have a fixed value
        return (orden_palos[palo], 0)  # Value 0 is for jokers
    return (orden_palos[palo], orden_valores[str(valor)])  # Normalize value to string for number cards

# Function to divide and sort the cards in parallel
def ordenar_parcial(cartas):
    return sorted(cartas, key=comparar)

def ordenar_en_paralelo(cartas, num_procesos):
    # Divide the cards into chunks for parallel processing
    chunk_size = len(cartas) // num_procesos
    chunks = [cartas[i:i + chunk_size] for i in range(0, len(cartas), chunk_size)]

    # Create a pool of processes
    with multiprocessing.Pool(processes=num_procesos) as pool:
        resultados = pool.map(ordenar_parcial, chunks)

    # Combine the results and sort them
    cartas_ordenadas = [carta for sublist in resultados for carta in sublist]
    return sorted(cartas_ordenadas, key=comparar)

# Generate 4 million cards
cartas = generar_cartas(4000000)

# Sort the cards in parallel with 4 processes
cartas_ordenadas = ordenar_en_paralelo(cartas, 4)

# Display the first 10 sorted cards
print(cartas_ordenadas[:10])
# Conclusion
The execution time of this parallel program is 31 seconds compared to the sequential program which was 15 seconds.
Although parallel programs can offer significant performance improvements, the overhead associated with creating and managing processes, splitting data, and performing multiple sorts can make parallelization slower than the sequential solution. In this case, the overhead of parallelization, inefficient workload distribution, and the final sort operation after parallelization could explain why the parallel program takes longer than the sequential one.


