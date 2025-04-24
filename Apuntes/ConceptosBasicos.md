
# 🧠 Fundamentos Profundos de Programación en C++ para Estructura de Datos

Este documento tiene como objetivo profundizar en los conceptos esenciales de C++ necesarios para abordar correctamente estructuras de datos. Se hace hincapié en las buenas prácticas, uso eficiente de memoria y principios de diseño limpios.

---

## 📌 Tipos de Datos en C++

### Tipos Primitivos

```cpp
int numero = 10;          // Entero con signo
unsigned int positivo = 20; // Entero sin signo (0 en adelante)
float decimal = 3.14f;    // Decimal de 32 bits
double grande = 3.141592; // Decimal de 64 bits
char letra = 'A';         // Caracter ASCII
bool activo = true;       // Booleano (true/false)
```

- **`short` y `long`** ajustan el tamaño de los enteros según necesidades de memoria.
- **`const`** previene cambios posteriores al valor.

```cpp
const double PI = 3.14159;
```

### Buenas prácticas

- Evitar usar `using namespace std;` en archivos `.h`.
- Usar `auto` para inferencia cuando no se pierde claridad.
- Preferir `nullptr` a `NULL` o `0` para punteros.

---

## 🎯 Punteros y Direcciones de Memoria

Los punteros son fundamentales en estructuras dinámicas (listas, árboles, etc). Permiten manipular directamente la memoria.

```cpp
int valor = 42;
int* puntero = &valor;   // Guarda la dirección de `valor`
std::cout << puntero;    // Imprime dirección
std::cout << *puntero;   // Imprime valor
```

### Operadores importantes

- `&` obtiene la dirección de una variable.
- `*` accede al valor contenido en esa dirección.

### Modificación desde el puntero

```cpp
*puntero = 100;  // Cambia `valor` a 100
```

---

## 🧠 Memoria Dinámica

La memoria dinámica permite reservar espacio en tiempo de ejecución con `new` y liberarlo con `delete`.

```cpp
int* p = new int(5);   // Reserva y asigna
delete p;              // Libera la memoria
```

Para arrays:
```cpp
int* arreglo = new int[10];
delete[] arreglo;
```

### Problemas comunes

- **Memory leak:** Olvidar `delete`
- **Dangling pointer:** Acceder a memoria ya liberada
- **Double free:** Llamar `delete` dos veces

> ✅ Recomendación: Usar `std::unique_ptr` o `std::shared_ptr` cuando sea posible.

---

## 🧩 Organización con Clases - .h y .cpp

### Separación por archivo

- `.h` define estructura y firma de métodos
- `.cpp` implementa métodos

```cpp
// Archivo: Nodo.h
#pragma once
class Nodo {
public:
    Nodo(int val);
    int getValor() const;
private:
    int valor;
};
```

```cpp
// Archivo: Nodo.cpp
#include "Nodo.h"

Nodo::Nodo(int val) : valor(val) {}

int Nodo::getValor() const {
    return valor;
}
```

---

## 🔁 Paso por Referencia y Valor

```cpp
void modificarPorValor(int x) {
    x = 100;
}

void modificarPorReferencia(int& x) {
    x = 100;
}
```

- Paso por **valor** copia el argumento.
- Paso por **referencia** modifica directamente el original.

> 🔥 Siempre que sea posible, pasar grandes estructuras como referencia (`const T&`) para evitar copias innecesarias.

---

## ✅ Recomendaciones Generales

- Comentar el propósito de clases y métodos.
- Inicializar todas las variables.
- Dividir estructuras complejas en módulos.
- Escribir código que se entienda sin comentarios extra.
- Usar `const` para métodos que no modifican el estado interno de un objeto.

---


