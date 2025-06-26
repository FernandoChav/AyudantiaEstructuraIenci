# 🌳 Árbol B (B-Tree)

---
El Árbol B es un árbol de búsqueda generalizado balanceado y multicamino (es decir, cada nodo puede tener más de dos hijos). A diferencia del ABB o AVL, que están optimizados para memoria RAM, el Árbol B está diseñado para minimizar accesos a disco, haciendo que cada operación toque la menor cantidad posible de bloques.
## 📘 Definición general

---
* Un Árbol B de orden t (o grado mínimo t ≥ 2) cumple:
* Cada nodo puede tener como máximo 2t - 1 claves y 2t hijos.
* Cada nodo (excepto la raíz) debe tener al menos t - 1 claves.
* Las claves dentro de un nodo están ordenadas.
* Es siempre balanceado: todas las hojas están en el mismo nivel.
* Las operaciones de búsqueda, inserción y eliminación tienen complejidad O(log n).
## 🧠 Estructura del nodo

---

## Recorridos (conceptualmente)

---
Preorden: Nodo → Izquierdo → DerechoInorden: Izquierdo → Nodo → DerechoPostorden: Izquierdo → Derecho → NodoPor niveles (BFS): Visita nivel por nivel usando una cola (queue)

---
## 🧠 Nodo especial
```cpp
template<typename T>
struct NodoB {
    bool hoja;
    vector<T> claves;
    vector<NodoB<T>*> hijos;

    NodoB(bool esHoja) : hoja(esHoja) {}
};

```
---
## ⚙️ Búsqueda en Árbol B


---

```cpp
template<typename T>
bool buscarEnB(NodoB<T>* nodo, T k) {
    int i = 0;
    while (i < nodo->claves.size() && k > nodo->claves[i])
        i++;

    if (i < nodo->claves.size() && k == nodo->claves[i])
        return true;

    if (nodo->hoja)
        return false;

    return buscarEnB(nodo->hijos[i], k);
}
```
## ➕ Inserción (resumen conceptual)
1. Si el nodo raíz está lleno (tiene 2t - 1 claves), se divide en dos y se promueve la clave central.
2. El árbol crece de forma controlada y balanceada dividiendo nodos a medida que se llenan.
3. La inserción se hace de arriba hacia abajo, dividiendo nodos en el camino si es necesario.
## 📦 División de un nodo hijo lleno

---
```cpp
template<typename T>
void dividirHijo(NodoB<T>* padre, int i, int t) {
    NodoB<T>* y = padre->hijos[i];
    NodoB<T>* z = new NodoB<T>(y->hoja);

    // Mover las últimas t - 1 claves de y a z
    for (int j = 0; j < t - 1; j++)
        z->claves.push_back(y->claves[j + t]);

    // Si no es hoja, mover los hijos también
    if (!y->hoja) {
        for (int j = 0; j < t; j++)
            z->hijos.push_back(y->hijos[j + t]);
    }

    // Reducir el tamaño de y
    y->claves.resize(t - 1);
    if (!y->hoja)
        y->hijos.resize(t);

    // Insertar z como nuevo hijo del padre
    padre->hijos.insert(padre->hijos.begin() + i + 1, z);
    padre->claves.insert(padre->claves.begin() + i, y->claves[t - 1]);
}
```
## 🧩 Inserción en un nodo no lleno

```cpp
template<typename T>
void insertarNoLleno(NodoB<T>* nodo, T k, int t) {
    int i = nodo->claves.size() - 1;

    if (nodo->hoja) {
        nodo->claves.push_back(k); // espacio adicional
        while (i >= 0 && k < nodo->claves[i]) {
            nodo->claves[i + 1] = nodo->claves[i];
            i--;
        }
        nodo->claves[i + 1] = k;
    } else {
        while (i >= 0 && k < nodo->claves[i])
            i--;
        i++;
        if (nodo->hijos[i]->claves.size() == 2 * t - 1) {
            dividirHijo(nodo, i, t);
            if (k > nodo->claves[i]) i++;
        }
        insertarNoLleno(nodo->hijos[i], k, t);
    }
}
```
## 🌱 Insertar en el árbol
```cpp
template<typename T>
NodoB<T>* insertarB(NodoB<T>* raiz, T k, int t) {
    if (!raiz) {
        raiz = new NodoB<T>(true);
        raiz->claves.push_back(k);
        return raiz;
    }

    if (raiz->claves.size() == 2 * t - 1) {
        NodoB<T>* nuevaRaiz = new NodoB<T>(false);
        nuevaRaiz->hijos.push_back(raiz);
        dividirHijo(nuevaRaiz, 0, t);
        insertarNoLleno(nuevaRaiz, k, t);
        return nuevaRaiz;
    } else {
        insertarNoLleno(raiz, k, t);
        return raiz;
    }
}
```
## 🗑️ Eliminación en Árbol B

Eliminar una clave en un Árbol B requiere mantener todas sus propiedades:
1. Eliminar como en un árbol de búsqueda, pero considerando que los nodos tienen múltiples claves e hijos.
2. Si al eliminar una clave un nodo queda con menos de t - 1 claves, se reequilibra mediante:

   * Redistribución (tomar del hermano).
   * Fusión (merge) con un hermano y una clave del padre.
   
3. Puede implicar reducir la altura del árbol si la raíz queda sin claves y solo tiene un hijo.

## 🧠 Casos principales al eliminar k de nodo x

* Caso 1: k está en un nodo hoja → eliminar directamente.

* Caso 2: k está en un nodo interno:

    * Si el hijo anterior (y) tiene al menos t claves → reemplazar con el predecesor de k y eliminarlo recursivamente.
    
    * Si el siguiente hijo (z) tiene al menos t claves → reemplazar con el sucesor y eliminarlo.
    
    * Si ambos tienen t - 1 claves → fusionarlos e ir recursivamente.

* Caso 3: k no está en el nodo → navegar al hijo adecuado:

    * Si ese hijo tiene solo t - 1 claves → asegúrate de que tenga al menos t antes de descender, usando redistribución o fusión.

## 🔧 Implementación C++ (resumen funcional)
Dada su extensión, aquí te muestro la estructura clave para implementar la eliminación:
```cpp
template<typename T>
void eliminarDeNodo(NodoB<T>* nodo, T k, int t);

// Función auxiliar: fusión de dos hijos
template<typename T>
void fusionar(NodoB<T>* padre, int idx, int t) {
    NodoB<T>* y = padre->hijos[idx];
    NodoB<T>* z = padre->hijos[idx + 1];

    // Insertar clave del padre entre y y z
    y->claves.push_back(padre->claves[idx]);

    // Mover claves e hijos de z a y
    y->claves.insert(y->claves.end(), z->claves.begin(), z->claves.end());
    if (!z->hoja)
        y->hijos.insert(y->hijos.end(), z->hijos.begin(), z->hijos.end());

    // Borrar clave e hijo de padre
    padre->claves.erase(padre->claves.begin() + idx);
    padre->hijos.erase(padre->hijos.begin() + idx + 1);

    delete z;
}

// Eliminar clave k de un nodo (incluye casos internos y hojas)
template<typename T>
void eliminarDeNodo(NodoB<T>* nodo, T k, int t) {
    int idx = 0;
    while (idx < nodo->claves.size() && nodo->claves[idx] < k)
        idx++;

    if (idx < nodo->claves.size() && nodo->claves[idx] == k) {
        if (nodo->hoja) {
            // Caso 1: eliminar directamente
            nodo->claves.erase(nodo->claves.begin() + idx);
        } else {
            NodoB<T>* pred = nodo->hijos[idx];
            NodoB<T>* succ = nodo->hijos[idx + 1];

            if (pred->claves.size() >= t) {
                T predecesor = pred->claves.back();
                nodo->claves[idx] = predecesor;
                eliminarDeNodo(pred, predecesor, t);
            } else if (succ->claves.size() >= t) {
                T sucesor = succ->claves.front();
                nodo->claves[idx] = sucesor;
                eliminarDeNodo(succ, sucesor, t);
            } else {
                fusionar(nodo, idx, t);
                eliminarDeNodo(pred, k, t);
            }
        }
    } else {
        // Clave no encontrada en nodo actual
        if (nodo->hoja) return; // No existe

        bool enUltimo = (idx == nodo->claves.size());
        NodoB<T>* hijo = nodo->hijos[idx];

        if (hijo->claves.size() == t - 1) {
            NodoB<T>* hermanoIzq = (idx > 0) ? nodo->hijos[idx - 1] : nullptr;
            NodoB<T>* hermanoDer = (idx < nodo->hijos.size() - 1) ? nodo->hijos[idx + 1] : nullptr;

            // Préstamo del hermano izquierdo
            if (hermanoIzq && hermanoIzq->claves.size() >= t) {
                hijo->claves.insert(hijo->claves.begin(), nodo->claves[idx - 1]);
                nodo->claves[idx - 1] = hermanoIzq->claves.back();
                hermanoIzq->claves.pop_back();
                if (!hermanoIzq->hoja) {
                    hijo->hijos.insert(hijo->hijos.begin(), hermanoIzq->hijos.back());
                    hermanoIzq->hijos.pop_back();
                }
            }
            // Préstamo del hermano derecho
            else if (hermanoDer && hermanoDer->claves.size() >= t) {
                hijo->claves.push_back(nodo->claves[idx]);
                nodo->claves[idx] = hermanoDer->claves.front();
                hermanoDer->claves.erase(hermanoDer->claves.begin());
                if (!hermanoDer->hoja) {
                    hijo->hijos.push_back(hermanoDer->hijos.front());
                    hermanoDer->hijos.erase(hermanoDer->hijos.begin());
                }
            }
            // Fusión
            else {
                if (hermanoIzq)
                    fusionar(nodo, idx - 1, t), hijo = nodo->hijos[idx - 1];
                else if (hermanoDer)
                    fusionar(nodo, idx, t);
            }
        }

        if (enUltimo && idx > nodo->claves.size())
            eliminarDeNodo(nodo->hijos[idx - 1], k, t);
        else
            eliminarDeNodo(nodo->hijos[idx], k, t);
    }
}

```