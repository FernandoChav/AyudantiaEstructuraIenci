# 🛷 Heap Binario (MinHeap / MaxHeap)

---
Un Heap Binario es un árbol binario completo que cumple una propiedad de orden específica:
* En un MinHeap, cada nodo es menor o igual que sus hijos.
* En un MaxHeap, cada nodo es mayor o igual que sus hijos.
El Heap no es un árbol binario de búsqueda. No permite recorridos ordenados, pero sí permite obtener el valor mínimo o máximo en tiempo constante (O(1)), e insertar y eliminar en tiempo logarítmico (O(log n)).

Se utiliza en estructuras como colas de prioridad y algoritmos como Heapsort o Dijkstra.
## 📐 Propiedades

---
* Es un árbol binario completo: todos los niveles están llenos excepto el último, que se llena de izquierda a derecha.
* Generalmente se implementa como un arreglo/vector, donde para un índice i:
* Hijo izquierdo: 2i + 1
* Hijo derecho: 2i + 2
* Padre: (i - 1) / 2
## ⚙️ Operaciones típicas

---
Inserción
Se inserta al final del vector y se sube (sift-up) si es menor (en min-heap) o mayor (en max-heap) que su padre.

Extracción del mínimo o máximo
Se extrae la raíz, se reemplaza por el último elemento, y se baja (sift-down) reordenando el heap.

## 💻 Implementación en C++ — MinHeap Genérico


```cpp
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class MinHeap {
    vector<T> heap;

    void subir(int i) {
        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void bajar(int i) {
        int n = heap.size();
        while (2 * i + 1 < n) {
            int hijoMenor = 2 * i + 1;
            if (hijoMenor + 1 < n && heap[hijoMenor + 1] < heap[hijoMenor])
                hijoMenor++;
            if (heap[i] <= heap[hijoMenor]) break;
            swap(heap[i], heap[hijoMenor]);
            i = hijoMenor;
        }
    }

public:
    void insertar(T val) {
        heap.push_back(val);
        subir(heap.size() - 1);
    }

    T extraerMin() {
        if (heap.empty()) throw runtime_error("Heap vacío");
        T min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        bajar(0);
        return min;
    }

    bool vacio() const { return heap.empty(); }

    void mostrar() const {
        for (T val : heap)
            cout << val << " ";
        cout << "\n";
    }
};
```
# 🏔️ Heap Binario Máximo (MaxHeap)

---
Un MaxHeap es un árbol binario completo donde el valor de cada nodo es mayor o igual que el de sus hijos. Su propósito principal es mantener en la raíz el elemento máximo, y es muy útil para algoritmos como Heapsort descendente o para implementar colas de prioridad máximas.
Se utiliza en estructuras como colas de prioridad y algoritmos como Heapsort o Dijkstra.
to, y se baja (sift-down) reordenando el heap.

## 💻 Implementación Genérica en C++


```cpp
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class MaxHeap {
    vector<T> heap;

    void subir(int i) {
        while (i > 0 && heap[i] > heap[(i - 1) / 2]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void bajar(int i) {
        int n = heap.size();
        while (2 * i + 1 < n) {
            int hijoMayor = 2 * i + 1;
            if (hijoMayor + 1 < n && heap[hijoMayor + 1] > heap[hijoMayor])
                hijoMayor++;
            if (heap[i] >= heap[hijoMayor]) break;
            swap(heap[i], heap[hijoMayor]);
            i = hijoMayor;
        }
    }

public:
    void insertar(T val) {
        heap.push_back(val);
        subir(heap.size() - 1);
    }

    T extraerMax() {
        if (heap.empty()) throw runtime_error("Heap vacío");
        T max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        bajar(0);
        return max;
    }

    bool vacio() const { return heap.empty(); }

    void mostrar() const {
        for (T val : heap)
            cout << val << " ";
        cout << "\n";
    }
};
```

