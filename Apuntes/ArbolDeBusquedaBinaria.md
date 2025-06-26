# 🌳 Árbol de busqueda Binaria (ABB)

---
Un Árbol Binario de Búsqueda (ABB), también llamado Binary Search Tree (BST), es una estructura jerárquica basada en el árbol binario, pero con una regla de ordenamiento estricta: para cada nodo, los valores menores van al subárbol izquierdo y los mayores al subárbol derecho. Esta propiedad permite búsquedas, inserciones y eliminaciones eficientes en promedio.

El ABB es ampliamente utilizado para representar conjuntos ordenados, diccionarios y sistemas de índices simples.

## 📐 Propiedades

---
* El recorrido inorden de un ABB siempre devuelve los elementos en orden ascendente.
* Si está balanceado, todas las operaciones tienen complejidad O(log n).
* En el peor caso (desequilibrado), la complejidad puede degradarse a O(n), como una lista enlazada.

## 🧠 Nodo especial

---
* Raíz: nodo principal del árbol.
* Internos: nodos con al menos un hijo.
* Hojas: nodos sin hijos.
* Padre y descendientes: se usan para definir la posición relativa de los nodos.

## ⚙️ Operaciones típicas

### Búsqueda
```cpp
template<typename T>
bool buscar(NodoAB<T>* nodo, T valor) {
    if (!nodo) return false;
    if (valor == nodo->dato) return true;
    if (valor < nodo->dato)
        return buscar(nodo->izq, valor);
    else
        return buscar(nodo->der, valor);
}
```
### Inserción
```cpp
template<typename T>
NodoAB<T>* insertar(NodoAB<T>* nodo, T valor) {
    if (!nodo) return new NodoAB<T>(valor);
    if (valor < nodo->dato)
        nodo->izq = insertar(nodo->izq, valor);
    else if (valor > nodo->dato)
        nodo->der = insertar(nodo->der, valor);
    // Si valor ya existe, no insertamos (o puedes permitir duplicados según el caso)
    return nodo;
}
```
###  Eliminación
 ```cpp
template<typename T>
NodoAB<T>* encontrarMin(NodoAB<T>* nodo) {
    while (nodo && nodo->izq) nodo = nodo->izq;
    return nodo;
}

template<typename T>
NodoAB<T>* eliminar(NodoAB<T>* nodo, T valor) {
    if (!nodo) return nullptr;

    if (valor < nodo->dato) {
        nodo->izq = eliminar(nodo->izq, valor);
    } else if (valor > nodo->dato) {
        nodo->der = eliminar(nodo->der, valor);
    } else {
        // Caso 1: sin hijos
        if (!nodo->izq && !nodo->der) {
            delete nodo;
            return nullptr;
        }
        // Caso 2: un solo hijo
        else if (!nodo->izq) {
            NodoAB<T>* temp = nodo->der;
            delete nodo;
            return temp;
        } else if (!nodo->der) {
            NodoAB<T>* temp = nodo->izq;
            delete nodo;
            return temp;
        }
        // Caso 3: dos hijos
        NodoAB<T>* sucesor = encontrarMin(nodo->der);
        nodo->dato = sucesor->dato;
        nodo->der = eliminar(nodo->der, sucesor->dato);
    }

    return nodo;
}
```

