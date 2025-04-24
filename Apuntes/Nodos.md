
# 🌱 Nodos en Estructuras de Datos y Uso de Templates en C++

Este documento profundiza el concepto de nodos en C++ y su uso con **templates**. Está orientado a entregar claridad total sobre cómo implementar estructuras dinámicas reutilizables y seguras.

---

## 📌 ¿Qué es un Nodo?

Un **nodo** es una unidad fundamental que forma parte de una estructura de datos dinámica. Almacena:
- Información (dato útil)
- Uno o más enlaces a otros nodos (punteros)

> Por ejemplo, en una lista enlazada, cada nodo apunta al siguiente nodo.

### Nodo sin templates (entero):

```cpp
struct Nodo {
    int dato;       // Información contenida
    Nodo* siguiente; // Apunta al siguiente nodo en la lista
};
```

- El campo `dato` puede almacenar cualquier valor que definamos (int en este caso).
- `siguiente` es un **puntero** al próximo nodo.

### Visualización:
```
+--------+-------------+
|  42    |   siguiente ---> (otro nodo o nullptr)
+--------+-------------+
```

---

## 🧠 ¿Por qué Templates?

Un nodo genérico permite usar **cualquier tipo de dato** sin reescribir el código.

```cpp
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;
};
```

- `T` representa un tipo genérico.
- Puedes crear `Nodo<int>`, `Nodo<float>`, `Nodo<std::string>`, etc.

### Ejemplo de uso:

```cpp
Nodo<std::string>* nodoTexto = new Nodo<std::string>;
nodoTexto->dato = "Hola mundo";
nodoTexto->siguiente = nullptr;
```

---

## 🧩 Tipos de Nodos Comunes

### 🔹 Nodo Simple

```cpp
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(T val) : dato(val), siguiente(nullptr) {}
};
```

- Solo apunta al nodo siguiente.

### 🔹 Nodo Doble (Lista doblemente enlazada)

```cpp
template <typename T>
struct NodoDoble {
    T dato;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;

    NodoDoble(T val) : dato(val), siguiente(nullptr), anterior(nullptr) {}
};
```

- Permite recorrer en ambos sentidos.

### 🔹 Nodo Circular

El último nodo apunta al primero, formando un ciclo.

```cpp
nodoUltimo->siguiente = nodoPrimero;
```

### 🔹 Nodo de Árbol Binario

```cpp
template <typename T>
struct NodoArbol {
    T dato;
    NodoArbol<T>* izquierdo;
    NodoArbol<T>* derecho;

    NodoArbol(T val) : dato(val), izquierdo(nullptr), derecho(nullptr) {}
};
```

### 🔹 Nodo para Matriz Enlazada (poco poblada)

```cpp
template <typename T>
struct NodoMatriz {
    int fila, columna;
    T valor;
    NodoMatriz<T>* derecha;
    NodoMatriz<T>* abajo;

    NodoMatriz(int f, int c, T val) : fila(f), columna(c), valor(val), derecha(nullptr), abajo(nullptr) {}
};
```

---

## ✅ Buenas Prácticas con Nodos

- Inicializa siempre los punteros a `nullptr`.
- Usa constructores para facilitar la creación de nodos.
- Libera la memoria con `delete` si usas `new`.
- Usa `template <typename T>` solo cuando necesites trabajar con múltiples tipos.
- Usa `const T&` al pasar datos a funciones o constructores, para evitar copias innecesarias.

---

## 🚨 Errores Comunes a Evitar

- No inicializar punteros → puede generar **segmentation fault**
- Olvidar liberar memoria → **memory leak**
- Hacer `delete` sin comprobar si el puntero es `nullptr`

```cpp
if (nodo != nullptr) {
    delete nodo;
}
```

---


