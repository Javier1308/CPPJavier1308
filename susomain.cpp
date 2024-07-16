#include <iostream>
#include <vector>
#include <queue>

template <typename T>
class BoundedQueue
{
private:
    std::vector<T> queue;
    int maxSize;
    int front;
    int rear;
    int currentSize;

public:
    BoundedQueue(int size) : maxSize(size), front(0), rear(-1), currentSize(0)
    {
        queue.resize(size);
    }

    bool enqueue(const T &item)
    {
        if (isFull())
        {
            std::cout << "Queue is full. Cannot enqueue item: " << item << std::endl;
            return false;
        }
        rear = (rear + 1) % maxSize;
        queue[rear] = item;
        currentSize++;
        return true;
    }

    bool dequeue(T &item)
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty. Cannot dequeue item." << std::endl;
            return false;
        }
        item = queue[front];
        front = (front + 1) % maxSize;
        currentSize--;
        return true;
    }

    bool isFull() const
    {
        return currentSize == maxSize;
    }

    bool isEmpty() const
    {
        return currentSize == 0;
    }

    int size() const
    {
        return currentSize;
    }

    void display() const
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty." << std::endl;
            return;
        }
        std::cout << "Queue contents: ";
        for (int i = 0; i < currentSize; i++)
        {
            std::cout << queue[(front + i) % maxSize] << " ";
        }
        std::cout << std::endl;
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

    return 0;
}
