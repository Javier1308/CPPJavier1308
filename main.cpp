#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <queue>

using namespace std;

class Armadura {
public:
    string tipo;
    int nivel_proteccion;

    Armadura(string tipo, int nivel_proteccion) : tipo(tipo), nivel_proteccion(nivel_proteccion) {}
};

class Juego {
private:
    Personaje jugador;
    priority_queue<Enemigo> enemigos;  // Usar priority_queue para enfrentar enemigos de menor a mayor nivel

public:
    Juego(string nombreJugador, int nivelJugador) : jugador(nombreJugador, nivelJugador) {}

    void agregarEnemigo(string nombre, int nivel) {
        enemigos.push(Enemigo(nombre, nivel));
    }

    void guardarPartida() {
        // Lógica para guardar la partida
    }

    void alertarVictoria() {
        // Lógica para alertar a los jugadores en línea
    }

    void navegarMapa(string destino) {
        Mapa* mapa = Mapa::obtenerInstancia();
        list<string> ruta = mapa->encontrarRuta("PosicionActual", destino);
        // Imprimir la ruta
    }

    Personaje& obtenerJugador() {
        return jugador;
    }

    void iniciar() {
        // Lógica para iniciar el juego
    }
};

class Mapa {
private:
    map<string, Nodo*> nodos;
    static Mapa* instancia;

    Mapa() {}

public:
    static Mapa* obtenerInstancia() {
        if (instancia == nullptr) {
            instancia = new Mapa();
        }
        return instancia;
    }

    void agregarNodo(string nombre) {
        nodos[nombre] = new Nodo(nombre);
    }

    void conectarNodos(string nombre1, string nombre2) {
        Nodo* nodo1 = nodos[nombre1];
        Nodo* nodo2 = nodos[nombre2];
        nodo1->adyacentes.push_back(nodo2);
        nodo2->adyacentes.push_back(nodo1);
    }

    // Método de búsqueda para encontrar la ruta más cercana
    list<string> encontrarRuta(string inicio, string destino) {
        // Implementar búsqueda en anchura (BFS) o búsqueda en profundidad (DFS)
        list<string> ruta;
        // ...
        return ruta;
    }
};

// Inicializar instancia de Singleton
Mapa* Mapa::instancia = nullptr;


class Nodo {
public:
    string nombre;
    list<Nodo*> adyacentes;

    Nodo(string nombre) : nombre(nombre) {}
};


class Enemigo {
public:
    string nombre;
    int nivel;

    Enemigo(string nombre, int nivel) : nombre(nombre), nivel(nivel) {}
};

class Personaje {
public:
    string nombre;
    int nivel;
    vector<Armadura> armaduras;

    Personaje(string nombre, int nivel) : nombre(nombre), nivel(nivel) {}

    void agregarArmadura(Armadura a) {
        armaduras.push_back(a);
    }

    void eliminarArmadura(string tipo) {
        armaduras.erase(remove_if(armaduras.begin(), armaduras.end(), [&tipo](Armadura& a) {
            return a.tipo == tipo;
        }), armaduras.end());
    }

    void mostrarArmaduras() {
        cout << "Armaduras de " << nombre << ":" << endl;
        for (auto& a : armaduras) {
            cout << " - " << a.tipo << " (Nivel de protección: " << a.nivel_proteccion << ")" << endl;
        }
    }
};

int main() {
    // Crear el juego
    Juego miJuego("Heroe", 1);

    // Agregar armaduras al personaje
    Personaje& jugador = miJuego.obtenerJugador();
    jugador.agregarArmadura(Armadura("Casco", 5));
    jugador.agregarArmadura(Armadura("Pechera", 10));
    jugador.mostrarArmaduras();

    // Agregar enemigos
    miJuego.agregarEnemigo("Goblin", 3);
    miJuego.agregarEnemigo("Orco", 5);

    // Configurar el mapa
    Mapa* mapa = Mapa::obtenerInstancia();
    mapa->agregarNodo("Aldea");
    mapa->agregarNodo("Bosque");
    mapa->conectarNodos("Aldea", "Bosque");

    // Iniciar el juego
    miJuego.iniciar();

    return 0;
}
