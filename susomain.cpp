#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct notification
{
    std::string message;
    std::string date;
    std::string time;

    notification(std::string msg, std::string dt, std::string tm) : message(msg), date(dt), time(tm) {}
    notification() {}

    std::string getMessage() const
    {
        return message;
    }

    std::string getDate() const
    {
        return date;
    }

    std::string getTime() const
    {
        return time;
    }
};

class NotiBuilder
{
    notification *notif;

public:
    NotiBuilder() : notif(new notification()) {}

    NotiBuilder &setMessage(std::string msg)
    {
        notif->message = msg;
        return *this;
    }

    NotiBuilder &setDate(std::string dt)
    {
        notif->date = dt;
        return *this;
    }

    NotiBuilder &setTime(std::string tm)
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
    std::queue<notification> queue;
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

    std::vector<notification> display()
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
        std::cout << "Orc attacks with power " << attackPower << "!" << std::endl;
    }

    void takeDamage(int damage) override
    {
        health -= damage;
        std::cout << "Orc takes " << damage << " damage. Health is now " << health << "." << std::endl;
    }
};

// Clase derivada Goblin
class Goblin : public Enemy
{
public:
    Goblin(int lvl) : Enemy(lvl) {}

    void attack() override
    {
        std::cout << "Goblin attacks with power " << attackPower << "!" << std::endl;
    }

    void takeDamage(int damage) override
    {
        health -= damage;
        std::cout << "Goblin takes " << damage << " damage. Health is now " << health << "." << std::endl;
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

// Clase Map para manejar la navegación
class Map
{
private:
    std::vector<std::vector<int>> grid;

public:
    Map(int width, int height) : grid(width, std::vector<int>(height, 0)) {}

    void displayMap()
    {
        for (const auto &row : grid)
        {
            for (int cell : row)
            {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    bool isWalkable(int x, int y)
    {
        return grid[x][y] == 0;
    }

    std::vector<std::pair<int, int>> findPath(int startX, int startY, int endX, int endY)
    {
        // Implementar algoritmo de búsqueda de caminos, como A*
        return {}; // Retornar el camino encontrado
    }
};

// Clase Armor para gestionar las armaduras del personaje
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

public:
    void equipArmor(Armor *newArmor)
    {
        armor = newArmor;
        std::cout << "Armor equipped with defense " << armor->getDefense() << "." << std::endl;
    }

    int getDefense()
    {
        return armor ? armor->getDefense() : 0;
    }
};

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
        std::cout << "Game is running!" << std::endl;
    }
};

int main()
{

    // Crear notificaciones
    NotiBuilder notis;
    QueueNotificator notificator(3);

    notificator.push(notis.setMessage("Hola").setDate("2021-09-01").setTime("10:00").build());
    notificator.push(notis.setMessage("Hola2").setDate("2021-09-01").setTime("10:01").build());
    notificator.push(notis.setMessage("Hola3").setDate("2021-09-01").setTime("10:02").build());

    std::cout << "1:" << std::endl;
    std::vector<notification> temp = notificator.display();
    std::for_each(temp.begin(), temp.end(), [](notification &n)
                  { std::cout << n.getMessage() << " " << n.getDate() << " " << n.getTime() << std::endl; });

    notificator.push(notis.setMessage("Hola4").setDate("2021-09-01").setTime("10:03").build());

    std::cout << "2:" << std::endl;
    temp = notificator.display();
    std::for_each(temp.begin(), temp.end(), [](notification &n)
                  { std::cout << n.getMessage() << " " << n.getDate() << " " << n.getTime() << std::endl; });

    /*
    // Crear cola de prioridad para los enemigos
    std::priority_queue<Enemy *, std::vector<Enemy *>, CompareEnemy> enemyQueue;

    // Crear y agregar enemigos a la cola
    enemyQueue.push(new Orc(3));
    enemyQueue.push(new Goblin(1));
    enemyQueue.push(new Orc(2));
    enemyQueue.push(new Goblin(4));

    // Enfrentar enemigos de menor a mayor nivel
    while (!enemyQueue.empty())
    {
        Enemy *enemy = enemyQueue.top();
        enemyQueue.pop();

        enemy->attack();
        enemy->takeDamage(20);

        delete enemy;
    }

    // Crear mapa y mostrarlo
    Map map(5, 5);
    map.displayMap();

    // Crear armadura y personaje
    Armor leatherArmor(10);
    Character hero;
    hero.equipArmor(&leatherArmor);
    std::cout << "Hero's defense: " << hero.getDefense() << std::endl;

    // Iniciar el juego
    GameManager &gameManager = GameManager::getInstance();
    gameManager.run();
    */
    return 0;
}
