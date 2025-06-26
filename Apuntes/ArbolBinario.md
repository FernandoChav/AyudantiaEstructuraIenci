# 🌳 Árbol Binario (AB)

---
Un árbol binario es una estructura de datos jerárquica donde cada nodo puede tener como máximo dos hijos: uno izquierdo y uno derecho. Su principal característica es su forma estructural, no impone reglas específicas sobre el contenido de los nodos, lo que lo distingue de estructuras más especializadas como el árbol binario de búsqueda (ABB) o los heaps.

El árbol binario se utiliza como base para múltiples estructuras de datos avanzadas. Es ideal para representar relaciones jerárquicas simples, expresiones matemáticas (como árboles de sintaxis), estructuras de decisión, y para implementar algoritmos de recorrido y evaluación.

## 📐 Propiedades

---
* Un árbol binario de altura h puede tener hasta 2^h - 1 nodos.

* La altura de un árbol con n nodos en el peor caso puede ser n, y en el mejor caso (balanceado), log₂(n + 1).

* Puede clasificarse en:

* Lleno: todos los niveles están completos.

* Completo: todos los niveles están completos, excepto el último que se llena de izquierda a derecha.

* Balanceado: la diferencia de altura entre subárboles izquierdo y derecho es pequeña (generalmente ≤1).

## Operaciones básicas

---
* Recorridos (preorden, inorden, postorden, por niveles)

* Contar nodos

* Calcular altura

* Buscar un valor

* Contar hojas

* Clonar árbol

* Comparar si dos árboles son iguales

## Recorridos (conceptualmente)

---
Preorden: Nodo → Izquierdo → DerechoInorden: Izquierdo → Nodo → DerechoPostorden: Izquierdo → Derecho → NodoPor niveles (BFS): Visita nivel por nivel usando una cola (queue)

---
## 🧠 Nodo especial

---
* Raíz: nodo inicial.

* Interno: nodo con al menos un hijo.

* Hoja: nodo sin hijos.

---

## 💻 Implementación en C++ con tipo genérico T

```cpp
#include <iostream>
using namespace std;

template<typename T>
struct NodoAB {
    T dato;
    NodoAB<T>* izq;
    NodoAB<T>* der;
    NodoAB(T val) : dato(val), izq(nullptr), der(nullptr) {}
};

// Recorridos básicos

template<typename T>
void preorden(NodoAB<T>* nodo) {
    if (!nodo) return;
    cout << nodo->dato << " ";
    preorden(nodo->izq);
    preorden(nodo->der);
}

template<typename T>
void inorden(NodoAB<T>* nodo) {
    if (!nodo) return;
    inorden(nodo->izq);
    cout << nodo->dato << " ";
    inorden(nodo->der);
}

template<typename T>
void postorden(NodoAB<T>* nodo) {
    if (!nodo) return;
    postorden(nodo->izq);
    postorden(nodo->der);
    cout << nodo->dato << " ";
}
```
## 💻 Recorridos Iterativos en C++

---
```cpp
#include <stack>
#include <queue>

// Recorrido Inorden Iterativo
template<typename T>
void inordenIterativo(NodoAB<T>* raiz) {
    stack<NodoAB<T>*> pila;
    NodoAB<T>* actual = raiz;

    while (actual || !pila.empty()) {
        while (actual) {
            pila.push(actual);
            actual = actual->izq;
        }
        actual = pila.top();
        pila.pop();
        cout << actual->dato << " ";
        actual = actual->der;
    }
}

// Recorrido Preorden Iterativo
template<typename T>
void preordenIterativo(NodoAB<T>* raiz) {
    if (!raiz) return;
    stack<NodoAB<T>*> pila;
    pila.push(raiz);

    while (!pila.empty()) {
        NodoAB<T>* actual = pila.top();
        pila.pop();
        cout << actual->dato << " ";

        if (actual->der) pila.push(actual->der);
        if (actual->izq) pila.push(actual->izq);
    }
}

// Recorrido Postorden Iterativo
template<typename T>
void postordenIterativo(NodoAB<T>* raiz) {
    if (!raiz) return;
    stack<NodoAB<T>*> pila1, pila2;
    pila1.push(raiz);

    while (!pila1.empty()) {
        NodoAB<T>* actual = pila1.top();
        pila1.pop();
        pila2.push(actual);

        if (actual->izq) pila1.push(actual->izq);
        if (actual->der) pila1.push(actual->der);
    }

    while (!pila2.empty()) {
        cout << pila2.top()->dato << " ";
        pila2.pop();
    }
}

// Recorrido por Niveles (BFS)
template<typename T>
void porNiveles(NodoAB<T>* raiz) {
    if (!raiz) return;
    queue<NodoAB<T>*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        NodoAB<T>* actual = cola.front();
        cola.pop();
        cout << actual->dato << " ";

        if (actual->izq) cola.push(actual->izq);
        if (actual->der) cola.push(actual->der);
    }
}
```

