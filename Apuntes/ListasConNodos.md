
# 📘 Listas Enlazadas en C++ Usando Clases Genéricas

Este documento explica en profundidad la implementación de **listas enlazadas** en C++, estructuradas por clases genéricas (`template <typename T>`). Se abordan cuatro tipos: simple, doble, circular simple y circular doble, siguiendo un enfoque pedagógico paso a paso.

---

## 🔹 Parte 1: ¿Qué es una Lista Enlazada?

Una **lista enlazada** es una estructura dinámica compuesta por nodos. Cada nodo almacena datos y enlaces (punteros) a otros nodos.

### Tipos de listas:

| Tipo                       | Enlaces                               | Recorrido |
|---------------------------|----------------------------------------|-----------|
| Lista Simple              | Un puntero al siguiente nodo           | Hacia adelante |
| Lista Doble               | Punteros al anterior y siguiente       | Adelante y atrás |
| Lista Circular Simple     | El último apunta al primero            | Cíclico |
| Lista Circular Doble      | Ambos enlaces y ciclo cerrado          | Completo en ambos sentidos |

---

## 🔸 Parte 2: Lista Enlazada Simple

### Clase Nodo

```cpp
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;

    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};
```

### Clase ListaSimple

```cpp
template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;

public:
    ListaSimple() : cabeza(nullptr) {}

    void insertarInicio(T valor);
    void mostrar() const;
    ~ListaSimple();
};
```

### Implementación de métodos

```cpp
template <typename T>
void ListaSimple<T>::insertarInicio(T valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void ListaSimple<T>::mostrar() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato << " -> ";
        actual = actual->siguiente;
    }
    std::cout << "nullptr" << std::endl;
}

template <typename T>
ListaSimple<T>::~ListaSimple() {
    while (cabeza != nullptr) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
```

---

## 🔸 Parte 3: Lista Doblemente Enlazada

### Clase NodoDoble

```cpp
template <typename T>
class NodoDoble {
public:
    T dato;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;

    NodoDoble(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};
```

### Clase ListaDoble

```cpp
template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;

public:
    ListaDoble() : cabeza(nullptr) {}

    void insertarInicio(T valor);
    void mostrar() const;
    ~ListaDoble();
};
```

### Implementación de métodos

```cpp
template <typename T>
void ListaDoble<T>::insertarInicio(T valor) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
    nuevo->siguiente = cabeza;
    if (cabeza != nullptr)
        cabeza->anterior = nuevo;
    cabeza = nuevo;
}

template <typename T>
void ListaDoble<T>::mostrar() const {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato << " <-> ";
        actual = actual->siguiente;
    }
    std::cout << "nullptr" << std::endl;
}

template <typename T>
ListaDoble<T>::~ListaDoble() {
    while (cabeza != nullptr) {
        NodoDoble<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
```

---

## 🔸 Parte 4: Lista Circular Simple

### Clase ListaCircularSimple

```cpp
template <typename T>
class ListaCircularSimple {
private:
    Nodo<T>* ultimo;

public:
    ListaCircularSimple() : ultimo(nullptr) {}

    void insertarInicio(T valor);
    void mostrar() const;
    ~ListaCircularSimple();
};
```

### Implementación de métodos

```cpp
template <typename T>
void ListaCircularSimple<T>::insertarInicio(T valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    if (!ultimo) {
        nuevo->siguiente = nuevo;
        ultimo = nuevo;
    } else {
        nuevo->siguiente = ultimo->siguiente;
        ultimo->siguiente = nuevo;
    }
}

template <typename T>
void ListaCircularSimple<T>::mostrar() const {
    if (!ultimo) return;
    Nodo<T>* actual = ultimo->siguiente;
    do {
        std::cout << actual->dato << " -> ";
        actual = actual->siguiente;
    } while (actual != ultimo->siguiente);
    std::cout << "(circular)" << std::endl;
}

template <typename T>
ListaCircularSimple<T>::~ListaCircularSimple() {
    if (!ultimo) return;
    Nodo<T>* inicio = ultimo->siguiente;
    Nodo<T>* actual = inicio;
    do {
        Nodo<T>* temp = actual;
        actual = actual->siguiente;
        delete temp;
    } while (actual != inicio);
}
```

---

## 🔸 Parte 5: Lista Circular Doblemente Enlazada

### Clase ListaCircularDoble

```cpp
template <typename T>
class ListaCircularDoble {
private:
    NodoDoble<T>* cabeza;

public:
    ListaCircularDoble() : cabeza(nullptr) {}

    void insertarInicio(T valor);
    void mostrar() const;
    ~ListaCircularDoble();
};
```

### Implementación de métodos

```cpp
template <typename T>
void ListaCircularDoble<T>::insertarInicio(T valor) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
    if (!cabeza) {
        nuevo->siguiente = nuevo->anterior = nuevo;
        cabeza = nuevo;
    } else {
        NodoDoble<T>* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        cabeza->anterior = nuevo;
        ultimo->siguiente = nuevo;
        cabeza = nuevo;
    }
}

template <typename T>
void ListaCircularDoble<T>::mostrar() const {
    if (!cabeza) return;
    NodoDoble<T>* actual = cabeza;
    do {
        std::cout << actual->dato << " <-> ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << "(circular)" << std::endl;
}

template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    if (!cabeza) return;
    NodoDoble<T>* actual = cabeza->siguiente;
    while (actual != cabeza) {
        NodoDoble<T>* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    delete cabeza;
}
```

---


