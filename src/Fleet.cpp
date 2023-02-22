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
        posX = x;
        posY = y;
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

int Fleet::move_per_turn = 1;
std::vector<Fleet> fleets;
