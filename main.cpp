#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

// Clase Armadura
class Armadura {
public:
    string tipo;
    int nivel_proteccion;

    Armadura(string tipo, int nivel_proteccion) : tipo(tipo), nivel_proteccion(nivel_proteccion) {}
};

// Clase Nodo para el Grafo del Mapa
class Nodo {
public:
    string nombre;
    list<Nodo*> adyacentes;

    Nodo(string nombre) : nombre(nombre) {}
};

// Clase Mapa utilizando Singleton
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

    // Método de búsqueda para encontrar la ruta más cercana usando BFS
    list<string> encontrarRuta(string inicio, string destino) {
        list<string> ruta;
        if (nodos.find(inicio) == nodos.end() || nodos.find(destino) == nodos.end()) {
            return ruta;  // Ruta vacía si los nodos no existen
        }

        unordered_map<string, string> predecesor;
        set<string> visitado;
        queue<string> q;
        q.push(inicio);
        visitado.insert(inicio);

        while (!q.empty()) {
            string actual = q.front();
            q.pop();

            if (actual == destino) {
                break;
            }

            for (Nodo* vecino : nodos[actual]->adyacentes) {
                if (visitado.find(vecino->nombre) == visitado.end()) {
                    visitado.insert(vecino->nombre);
                    predecesor[vecino->nombre] = actual;
                    q.push(vecino->nombre);
                }
            }
        }

        // Construir la ruta desde el destino al inicio
        for (string at = destino; at != ""; at = predecesor[at]) {
            ruta.push_front(at);
        }

        return ruta;
    }
};

// Inicializar instancia de Singleton
Mapa* Mapa::instancia = nullptr;

// Clase Enemigo
class Enemigo {
public:
    string nombre;
    int nivel;

    Enemigo(string nombre, int nivel) : nombre(nombre), nivel(nivel) {}

    bool operator<(const Enemigo& e) const {
        return nivel > e.nivel;  // Para ordenar en la priority_queue de menor a mayor nivel
    }
};

// Clase Personaje
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

// Clase Juego
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
        // Lógica para guardar la partida (simulada)
        cout << "Partida guardada." << endl;
    }

    void alertarVictoria() {
        // Lógica para alertar a los jugadores en línea (simulada)
        cout << "Has derrotado a un enemigo. ¡Victoria!" << endl;
    }

    void navegarMapa(string destino) {
        Mapa* mapa = Mapa::obtenerInstancia();
        list<string> ruta = mapa->encontrarRuta("Aldea", destino);  // Suponiendo que el jugador inicia en "Aldea"
        cout << "Ruta a " << destino << ":" << endl;
        for (const string& lugar : ruta) {
            cout << lugar << " ";
        }
        cout << endl;
    }

    Personaje& obtenerJugador() {
        return jugador;
    }

    void iniciar() {
        // Lógica para iniciar el juego (simulada)
        cout << "Juego iniciado." << endl;
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
    mapa->agregarNodo("Montaña");
    mapa->conectarNodos("Aldea", "Bosque");
    mapa->conectarNodos("Bosque", "Montaña");

    // Iniciar el juego
    miJuego.iniciar();

    // Navegar el mapa
    miJuego.navegarMapa("Montaña");

    // Guardar partida
    miJuego.guardarPartida();

    // Alertar victoria
    miJuego.alertarVictoria();

    return 0;
}
