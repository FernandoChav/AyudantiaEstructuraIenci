
# 📊 Análisis Detallado de Complejidad Algorítmica: Paso a Paso

Este documento enseña cómo **analizar la complejidad de un algoritmo en C++ de forma exacta**, identificando:
1. La **línea exacta** con la operación clave.
2. La **cantidad de repeticiones** de esa línea.
3. La **expresión formal** como sumatoria.
4. El resultado final en **notación Big O**.

---

## 🧩 Ejemplo 1: Bucle Simple

```cpp
for (int i = 0; i < n; i++) {          // (1)
    cout << i << endl;                // (2) ← operación activa
}
```

- Línea activa: **(2)** `cout << i`
- Se ejecuta **una vez por iteración del for**
- El for se repite `n` veces
- Expresión:
  ```
  T(n) = 1 + 1 + 1 + ... + 1   ← n veces
       = ∑_{i=0}^{n-1} 1 = n
  ```
- **Complejidad final: O(n)**

---

## 🧩 Ejemplo 2: Bucle Anidado Cuadrático

```cpp
for (int i = 0; i < n; i++) {              // (1)
    for (int j = 0; j < n; j++) {          // (2)
        cout << i << "," << j << endl;     // (3) ← operación activa
    }
}
```

- Línea activa: **(3)**
- Bucle exterior se ejecuta `n` veces
- Bucle interior también `n` veces por cada ciclo exterior
- Expresión:
  ```
  T(n) = ∑_{i=0}^{n-1} ∑_{j=0}^{n-1} 1 = n * n = n²
  ```
- **Complejidad final: O(n²)**

---

## 🧩 Ejemplo 3: Bucle Triangular

```cpp
for (int i = 0; i < n; i++) {              // (1)
    for (int j = 0; j < i; j++) {          // (2)
        cout << "*";                      // (3) ← operación activa
    }
}
```

- Línea activa: **(3)**
- Iteraciones:
    - i = 0 → 0 veces
    - i = 1 → 1 vez
    - i = 2 → 2 veces
      ...
    - i = n-1 → n-1 veces
- Expresión:
  ```
  T(n) = ∑_{i=0}^{n-1} i = n(n-1)/2
  ```
- **Complejidad final: O(n²)**

---

## 🧩 Ejemplo 4: Búsqueda Binaria

```cpp
int buscar(int arr[], int x, int izq, int der) {
    while (izq <= der) {                      // (1)
        int medio = (izq + der) / 2;          // (2)
        if (arr[medio] == x) return medio;    // (3)
        else if (arr[medio] < x)              // (4)
            izq = medio + 1;                  // (5)
        else der = medio - 1;                 // (6)
    }
    return -1;                                // (7)
}
```

- Línea activa principal: **comparación de (3)**
- Cada iteración **divide el espacio de búsqueda a la mitad**
- Expresión:
  ```
  T(n) = log₂(n)
  ```
- **Complejidad final: O(log n)**

---

## 🧩 Ejemplo 5: Recursión Exponencial

```cpp
int f(int n) {
    if (n <= 1) return 1;
    return f(n-1) + f(n-1);  // ← operación activa (2 llamadas)
}
```

- Árbol de llamadas se duplica en cada nivel
- Nivel 0: 1 llamada
- Nivel 1: 2 llamadas
- Nivel 2: 4 llamadas
- ...
- Nivel k: 2^k llamadas → hasta que `n = 0`

- Expresión:
  ```
  T(n) = 2^n
  ```
- **Complejidad final: O(2^n)**

---

## 📌 Conclusiones y Consejos

- **Identifica la operación activa** (la que se repite dentro de bucles o recursión).
- **Cuenta cuántas veces se repite**, usando sumatorias cuando sea necesario.
- **Ignora constantes**, y usa el término dominante para Big O.
- Practica con `for`, `while`, `if`, `recursión` y mezcla de estos.

Esta técnica te permitirá analizar cualquier algoritmo que enfrentes, tanto en la universidad como en entrevistas técnicas o programación competitiva.
