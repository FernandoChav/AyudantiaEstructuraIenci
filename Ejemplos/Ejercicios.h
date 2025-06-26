//
// Created by Ferna on 25-06-2025.
//

#ifndef EJERCICIOS_H
#define EJERCICIOS_H
#include <iostream>
#include <thread>
#include <chrono>



class Ejercicios {
    void tarea(int id) {
        for (int i = 0; i < 3; ++i) {
            std::cout << "Hilo " << id << " ejecutando iteración " << i << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    int main() {
        std::thread h1(tarea, 1);
        std::thread h2(tarea, 2);

        h1.join();
        h2.join();

        std::cout << "Ambos hilos han terminado.\n";
        return 0;
    }
};



#endif //EJERCICIOS_H
