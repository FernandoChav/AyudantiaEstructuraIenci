
# 🧠 Matriz Poco Poblada (MPP) con Listas Enlazadas en C++

Una **matriz poco poblada** (MPP) es una matriz en la que la mayoría de los elementos son cero o vacíos. Para evitar desperdiciar memoria almacenando ceros, se puede representar la matriz usando **listas enlazadas** y **nodos especiales**.

---

## 📌 Parte 1: ¿Qué es una MPP y Por Qué Usarla?

En lugar de usar un array bidimensional tradicional, la MPP guarda **solo los valores distintos de cero**, junto con su posición (fila y columna).

### Ventajas:
- Uso eficiente de memoria.
- Recorrido optimizado para matrices grandes con pocos datos.

---

## 🧱 Parte 2: Estructura del Nodo

Cada nodo de la MPP contiene:

- Valor `dato`
- Fila `fila` (int)
- Columna `columna` (int)
- Puntero a la **derecha** (hacia la siguiente celda en la fila)
- Puntero hacia **abajo** (hacia la siguiente celda en la columna)

```cpp
template <typename T>
class NodoMPP {
public:
    int fila, columna;
    T dato;
    NodoMPP<T>* derecha;
    NodoMPP<T>* abajo;

    NodoMPP(int f, int c, T val)
        : fila(f), columna(c), dato(val), derecha(nullptr), abajo(nullptr) {}
};
```

También se utiliza un nodo **cabecera** que organiza las filas y columnas.

---

## 🏗 Parte 3: Implementación Básica en C++

### Clase MPP

```cpp
template <typename T>
class MPP {
private:
    NodoMPP<T>* inicio;  // Nodo cabecera

public:
    MPP();
    void insertar(int fila, int columna, T valor);
    T obtener(int fila, int columna);
    void mostrar();
    ~MPP();
};
```

### Constructor

```cpp
template <typename T>
MPP<T>::MPP() {
    inicio = nullptr;
}
```

### Insertar elemento

```cpp
template <typename T>
void MPP<T>::insertar(int fila, int columna, T valor) {
    if (valor == 0) return; // No se almacenan ceros

    NodoMPP<T>* nuevo = new NodoMPP<T>(fila, columna, valor);

    if (!inicio || fila < inicio->fila || (fila == inicio->fila && columna < inicio->columna)) {
        nuevo->abajo = inicio;
        inicio = nuevo;
        return;
    }

    NodoMPP<T>* actual = inicio;
    NodoMPP<T>* anterior = nullptr;

    while (actual && (actual->fila < fila || (actual->fila == fila && actual->columna < columna))) {
        anterior = actual;
        actual = actual->abajo;
    }

    nuevo->abajo = actual;
    anterior->abajo = nuevo;
}
```

### Obtener valor

```cpp
template <typename T>
T MPP<T>::obtener(int fila, int columna) {
    NodoMPP<T>* actual = inicio;
    while (actual) {
        if (actual->fila == fila && actual->columna == columna) {
            return actual->dato;
        }
        actual = actual->abajo;
    }
    return 0;
}
```

### Mostrar matriz

```cpp
template <typename T>
void MPP<T>::mostrar() {
    NodoMPP<T>* actual = inicio;
    while (actual) {
        std::cout << "Valor en [" << actual->fila << "][" << actual->columna << "]: "
                  << actual->dato << std::endl;
        actual = actual->abajo;
    }
}
```

### Destructor

```cpp
template <typename T>
MPP<T>::~MPP() {
    NodoMPP<T>* actual = inicio;
    while (actual) {
        NodoMPP<T>* temp = actual;
        actual = actual->abajo;
        delete temp;
    }
}
```

---

