#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <queue>


using namespace std;

<<<<<<< Updated upstream
class Armadura {
public:
    string tipo;
    int nivel_proteccion;
=======
struct notification
{
    string message;
    string date;
    string time;
>>>>>>> Stashed changes

    notification(string msg, string dt, string tm) : message(msg), date(dt), time(tm) {}
    notification() {}

    string getMessage() const
    {
        return message;
    }

    string getDate() const
    {
        return date;
    }

    string getTime() const
    {
        return time;
    }
};

class NotiBuilder
{
    notification *notif;

public:
    NotiBuilder() : notif(new notification()) {}

    NotiBuilder &setMessage(string msg)
    {
        notif->message = msg;
        return *this;
    }

    NotiBuilder &setDate(string dt)
    {
        notif->date = dt;
        return *this;
    }

    NotiBuilder &setTime(string tm)
    {
        notif->time = tm;
        return *this;
    }

    notification build()
    {
        notification temp = *notif;
        notif = new notification();
        return temp;
    }
};

class QueueNotificator
{
private:
    queue<notification> queue;
    int maxSize;

public:
    QueueNotificator(int size_max) : maxSize(size_max) {}

    void push(const notification &notif)
    {
        if (isFull())
        {
            queue.pop();
        }
        queue.push(notif);
    }

    bool isFull() const
    {
        return queue.size() == maxSize;
    }

    bool isEmpty() const
    {
        return queue.empty();
    }

    int size() const
    {
        return queue.size();
    }

    vector<notification> display()
    {
        std::queue<notification> temp = queue;
        std::vector<notification> output;
        while (!temp.empty())
        {
            output.push_back(temp.front());
            temp.pop();
        }
        return output;
    }
};

// Clase base para Enemigos
class Enemy
{
protected:
    int health;
    int attackPower;
    int level;

    void calculateAttributes()
    {
        health = 50 + (level * 10);
        attackPower = 5 + (level * 3);
    }

public:
    Enemy(int lvl) : level(lvl)
    {
        calculateAttributes();
    }

    virtual void attack() = 0;
    virtual void takeDamage(int damage) = 0;

    int getLevel() const
    {
        return level;
    }

    virtual ~Enemy() {}
};

// Clase derivada Orc
class Orc : public Enemy
{
public:
    Orc(int lvl) : Enemy(lvl) {}

    void attack() override
    {
        cout << "Orc attacks with power " << attackPower << "!" << endl;
    }

    void takeDamage(int damage) override
    {
        health -= damage;
        cout << "Orc takes " << damage << " damage. Health is now " << health << "." << endl;
    }
};

// Clase derivada Goblin
class Goblin : public Enemy
{
public:
    Goblin(int lvl) : Enemy(lvl) {}

    void attack() override
    {
        cout << "Goblin attacks with power " << attackPower << "!" << endl;
    }

    void takeDamage(int damage) override
    {
        health -= damage;
        cout << "Goblin takes " << damage << " damage. Health is now " << health << "." << endl;
    }
};

// Comparador para la cola de prioridad
struct CompareEnemy
{
    bool operator()(Enemy *const &e1, Enemy *const &e2)
    {
        return e1->getLevel() > e2->getLevel();
    }
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
<<<<<<< Updated upstream
};

class Personaje {
public:
    string nombre;
    int nivel;
    vector<Armadura> armaduras;

    Personaje(string nombre, int nivel) : nombre(nombre), nivel(nivel) {}
=======

    bool operator<(const Enemigo& e) const {
        return nivel > e.nivel;  // Para ordenar en la priority_queue de menor a mayor nivel
    }
};

// Clase Personaje
class Armor
{
private:
    int defense;

public:
    Armor(int def) : defense(def) {}
    int getDefense() { return defense; }
};

// Clase Character que integra el sistema de armaduras
class Character
{
private:
    Armor *armor;
>>>>>>> Stashed changes

public:
    void equipArmor(Armor *newArmor)
    {
        armor = newArmor;
        cout << "Armor equipped with defense " << armor->getDefense() << "." << endl;
    }

    int getDefense()
    {
        return armor ? armor->getDefense() : 0;
    }
};

<<<<<<< Updated upstream
=======
// Clase GameManager usando el patrón Singleton
class GameManager
{
private:
    GameManager() {}

public:
    static GameManager &getInstance()
    {
        static GameManager instance;
        return instance;
    }

    void run()
    {
        cout << "Game is running!" << endl;
    }
};

>>>>>>> Stashed changes
int main() {
    // Crear el juego
    Juego miJuego("Heroe", 1);

<<<<<<< Updated upstream
    // Agregar armaduras al personaje
    Personaje& jugador = miJuego.obtenerJugador();
    jugador.agregarArmadura(Armadura("Casco", 5));
    jugador.agregarArmadura(Armadura("Pechera", 10));
    jugador.mostrarArmaduras();

    // Agregar enemigos
    miJuego.agregarEnemigo("Goblin", 3);
    miJuego.agregarEnemigo("Orco", 5);

    // Configurar el mapa
=======
    NotiBuilder notis;
    QueueNotificator notificator(3);

    notificator.push(notis.setMessage("Hola").setDate("2021-09-01").setTime("10:00").build());
    notificator.push(notis.setMessage("Hola2").setDate("2021-09-01").setTime("10:01").build());
    notificator.push(notis.setMessage("Hola3").setDate("2021-09-01").setTime("10:02").build());

    cout << "1:" << endl;
    vector<notification> temp = notificator.display();
    for_each(temp.begin(), temp.end(), [](notification &n)
                  { cout << n.getMessage() << " " << n.getDate() << " " << n.getTime() << endl; });

    notificator.push(notis.setMessage("Hola4").setDate("2021-09-01").setTime("10:03").build());

    cout << "2:" << endl;
    temp = notificator.display();
    for_each(temp.begin(), temp.end(), [](notification &n)
                  { cout << n.getMessage() << " " << n.getDate() << " " << n.getTime() << endl; });

>>>>>>> Stashed changes
    Mapa* mapa = Mapa::obtenerInstancia();
    mapa->agregarNodo("Aldea");
    mapa->agregarNodo("Bosque");
    mapa->conectarNodos("Aldea", "Bosque");

<<<<<<< Updated upstream
    // Iniciar el juego
    miJuego.iniciar();
=======
    // Imprimir el mapa
    mapa->imprimirMapa();

    // Obtener y mostrar lugares cercanos a la Aldea
    list<string> lugaresCercanos = mapa->obtenerLugaresCercanos("Aldea");
    cout << "Lugares cercanos a Aldea: ";
    for (const string& lugar : lugaresCercanos) {
        cout << lugar << " ";
    }
    cout << endl;

    // Encontrar la ruta desde la Aldea a la Montaña
    list<string> ruta = mapa->encontrarRuta("Aldea", "Montania");
    cout << "Ruta de Aldea a Montania: ";
    for (const string& lugar : ruta) {
        cout << lugar << " ";
    }
    cout << endl;
>>>>>>> Stashed changes

    return 0;
}