# 🌳 Árbol AVL (AVL Tree)

---
Un Árbol AVL es un árbol binario de búsqueda (ABB) que se autobalancea. Fue el primer árbol de este tipo, propuesto por Adelson-Velsky y Landis en 1962. Su idea principal es mantener la diferencia de altura (factor de equilibrio) entre los subárboles de cualquier nodo como máximo 1, es decir:

FE
(
𝑛
𝑜
𝑑
𝑜
)
=
altura(izq)
−
altura(der)
∈
{
−
1
,
0
,
1
}
FE(nodo)=altura(izq)−altura(der)∈{−1,0,1}
Cuando una operación (inserción o eliminación) causa un desequilibrio, el árbol realiza rotaciones para restaurar su balance.
## 📐 Propiedades

---
* Mantiene complejidad O(log n) para búsqueda, inserción y eliminación.
* Siempre balanceado, lo que lo hace más eficiente que un ABB común en el peor caso.
* Es ideal cuando se hacen muchas búsquedas y también inserciones.
## 🔁 Rotaciones
Para corregir desequilibrios se aplican rotaciones:
1. Rotación simple a la derecha (RR)
2. Rotación simple a la izquierda (LL)
3. Rotación doble izquierda-derecha (LR)
4. Rotación doble derecha-izquierda (RL)
---

## 💻 Estructura del nodo AVL

```cpp
template<typename T>
struct NodoAVL {
    T dato;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;

    NodoAVL(T val) : dato(val), izq(nullptr), der(nullptr), altura(1) {}
};
```
## ⚙️ Funciones auxiliares

```cpp
template<typename T>
int altura(NodoAVL<T>* nodo) {
    return nodo ? nodo->altura : 0;
}

template<typename T>
int factorEquilibrio(NodoAVL<T>* nodo) {
    return nodo ? altura(nodo->izq) - altura(nodo->der) : 0;
}

template<typename T>
void actualizarAltura(NodoAVL<T>* nodo) {
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
}
```
## 🔁 Rotaciones
```cpp
template<typename T>
NodoAVL<T>* rotarDerecha(NodoAVL<T>* y) {
    NodoAVL<T>* x = y->izq;
    NodoAVL<T>* T2 = x->der;

    x->der = y;
    y->izq = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

template<typename T>
NodoAVL<T>* rotarIzquierda(NodoAVL<T>* x) {
    NodoAVL<T>* y = x->der;
    NodoAVL<T>* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}
```
## ➕ Inserción AVL
```cpp
template<typename T>
NodoAVL<T>* insertarAVL(NodoAVL<T>* nodo, T valor) {
    if (!nodo) return new NodoAVL<T>(valor);

    if (valor < nodo->dato)
        nodo->izq = insertarAVL(nodo->izq, valor);
    else if (valor > nodo->dato)
        nodo->der = insertarAVL(nodo->der, valor);
    else
        return nodo;  // Duplicados no permitidos

    actualizarAltura(nodo);
    int fe = factorEquilibrio(nodo);

    // Rebalanceo
    if (fe > 1 && valor < nodo->izq->dato)  // Izquierda izquierda
        return rotarDerecha(nodo);
    if (fe < -1 && valor > nodo->der->dato) // Derecha derecha
        return rotarIzquierda(nodo);
    if (fe > 1 && valor > nodo->izq->dato) { // Izquierda derecha
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }
    if (fe < -1 && valor < nodo->der->dato) { // Derecha izquierda
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}
```

## 🔍 Búsqueda
```cpp
template<typename T>
bool buscarAVL(NodoAVL<T>* nodo, T valor) {
    if (!nodo) return false;
    if (valor == nodo->dato) return true;
    return valor < nodo->dato ?
        buscarAVL(nodo->izq, valor) :
        buscarAVL(nodo->der, valor);
}
```

## 🗑️ Eliminación en Árbol AVL

 ### Pasos generales:
1. Buscar el nodo a eliminar (como en un ABB).
2. Eliminarlo considerando los 3 casos clásicos:
   * Nodo hoja
   * Nodo con un solo hijo
   * Nodo con dos hijos (se reemplaza con el sucesor inorden)
3. Recalcular altura y rebalancear subárboles como en la inserción.

## 🔧 Código: Eliminación en AVL

```cpp
template<typename T>
NodoAVL<T>* encontrarMin(NodoAVL<T>* nodo) {
    while (nodo->izq)
        nodo = nodo->izq;
    return nodo;
}

template<typename T>
NodoAVL<T>* eliminarAVL(NodoAVL<T>* nodo, T valor) {
    if (!nodo) return nullptr;

    // 1. Buscar el nodo a eliminar
    if (valor < nodo->dato)
        nodo->izq = eliminarAVL(nodo->izq, valor);
    else if (valor > nodo->dato)
        nodo->der = eliminarAVL(nodo->der, valor);
    else {
        // 2. Eliminar el nodo
        if (!nodo->izq || !nodo->der) {
            NodoAVL<T>* temp = nodo->izq ? nodo->izq : nodo->der;
            delete nodo;
            return temp;
        } else {
            NodoAVL<T>* sucesor = encontrarMin(nodo->der);
            nodo->dato = sucesor->dato;
            nodo->der = eliminarAVL(nodo->der, sucesor->dato);
        }
    }

    // 3. Actualizar altura
    actualizarAltura(nodo);

    // 4. Rebalancear
    int fe = factorEquilibrio(nodo);

    if (fe > 1 && factorEquilibrio(nodo->izq) >= 0) // Izquierda izquierda
        return rotarDerecha(nodo);
    if (fe > 1 && factorEquilibrio(nodo->izq) < 0) { // Izquierda derecha
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }
    if (fe < -1 && factorEquilibrio(nodo->der) <= 0) // Derecha derecha
        return rotarIzquierda(nodo);
    if (fe < -1 && factorEquilibrio(nodo->der) > 0) { // Derecha izquierda
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

```