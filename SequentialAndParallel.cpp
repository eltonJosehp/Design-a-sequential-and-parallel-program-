#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <omp.h>

using namespace std;

// Definimos los palos y valores de las cartas
enum Palo { CORAZONES, TREBOLES, PICAS, DIAMANTES, COMODIN };
const vector<string> nombres_palos = {"Corazones", "Tréboles", "Picas", "Diamantes", "Comodín"};

struct Carta {
    int valor; // 1 al 13 para las cartas normales, 14 para comodín
    Palo palo;
    
    bool operator<(const Carta &otra) const {
        if (palo == otra.palo) return valor < otra.valor;
        return palo < otra.palo;
    }
};

vector<Carta> generar_cartas(int cantidad) {
    vector<Carta> mazo;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_valor(1, 14);
    uniform_int_distribution<int> dist_palo(0, 4);
    
    for (int i = 0; i < cantidad; ++i) {
        mazo.push_back({dist_valor(gen), static_cast<Palo>(dist_palo(gen))});
    }
    return mazo;
}

void ordenar_secuencial(vector<Carta> &mazo) {
    sort(mazo.begin(), mazo.end());
}

void ordenar_paralelo(vector<Carta> &mazo) {
    #pragma omp parallel
    {
        #pragma omp single nowait
        sort(mazo.begin(), mazo.end());
    }
}

int main() {
    const int NUM_CARTAS = 4000000;
    vector<Carta> mazo = generar_cartas(NUM_CARTAS);
    vector<Carta> mazo_copia = mazo;

    // Ordenamiento secuencial
    auto inicio = chrono::high_resolution_clock::now();
    ordenar_secuencial(mazo);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempo_secuencial = fin - inicio;
    cout << "Tiempo secuencial: " << tiempo_secuencial.count() << " segundos\n";

    // Ordenamiento paralelo
    inicio = chrono::high_resolution_clock::now();
    ordenar_paralelo(mazo_copia);
    fin = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempo_paralelo = fin - inicio;
    cout << "Tiempo paralelo: " << tiempo_paralelo.count() << " segundos\n";
    
    return 0;
}
