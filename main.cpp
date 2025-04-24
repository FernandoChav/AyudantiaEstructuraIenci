template <typename T>
class Lista {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T valor) : dato(valor), siguiente(nullptr) {}
    };

    Nodo* cabeza;

public:
    Lista() : cabeza(nullptr) {}

    void insertar(T valor) {
        Nodo<T> nuevo = new Nodo(valor);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    void imprimir() {
        Nodo* actual = cabeza; // 1
        while (actual != nullptr) {  // T
            std::cout << actual->dato << " -> "; // c
            actual = actual->siguiente; // 1
        }
        std::cout << "NULL" << std::endl;
    }
    bool buscar(int valor) {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->dato == valor) return true;
            actual = actual->siguiente;
        }
        return false;
    }
};


