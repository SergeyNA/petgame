class Fleet
{
    int power;
    int posX;
    int posY;
    int move_count;

public:
    static int move_per_turn;
    void createFleet(int x, int y)
    {
        if(x < 0 || x > 15 || y < 0 || y > 9)
        {
            std::cout << "Unasseptable fleet coordinates: " << x << " " << y << " set to (1; 1)" << std::endl;
            posX = 1;
            posY = 1;
        }
        else
        {
            posX = x;
            posY = y;
        }
        power = 0;
        move_count = move_per_turn;
    }
    Fleet(int x, int y) {createFleet(x, y);}

    bool canMoved()
    {
        return move_count > 0;
    }
    bool isHere(int x, int y)
    {
        return posX == x && posY == y;
    }
    int getX()
    {
        return posX;
    }
    int getY()
    {
        return posY;
    }
    void setDestination(int x, int y)
    {
        posX = x;
        posY = y;
    }
    void moveFleet(int x, int y, int move_points = 1)
    {
        this->setDestination(x, y);
        move_count -= move_points;
    }
    void newTurn()
    {
        move_count = move_per_turn;
    }
    int getPower()
    {
        return power;
    }
    void addShip(int ship_power)
    {
        power += ship_power;
    }
};

int Fleet::move_per_turn = 20;
std::vector<Fleet> fleets;
