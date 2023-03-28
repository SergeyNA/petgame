enum class terrain {terran, sand, frost, vulcanic, oceanic, mountane, plain, gaseous, jungle, utopia};
enum class proportions {asteroid, dwarf, small, normal, large, huge, giant};
static const int terrain_max_pop = 100;

class Planet
{
public:
    int population;
    int max_population;
    terrain landscape;
    proportions radius;
    double colonization_diff;
    double discover_diff;
    int rich;

    bool hidden;

    bool isHidden()
    {
        return hidden;
    }
    void setHidden(bool new_val)
    {
        hidden = new_val;
    }
    void discover()
    {
        double probability = rand() % 100;
        probability /= 100;
        if(probability < discover_diff)
            hidden = false;
    }
    int getPopulation()
    {
        return population;
    }
    void newTurn()
    {
        population = population * colonization_diff + 1;
        if(population > max_population)
            population = max_population;
    }
    std::string getTerrainType()
    {
        std::string answ = "None";
        switch(landscape)
        {
        case terrain::terran:
            answ = "Terran";
            break;
        case terrain::sand:
            answ = "Sand";
            break;
        case terrain::frost:
            answ = "Iceworld";
            break;
        case terrain::vulcanic:
            answ = "Vulcanic";
            break;
        case terrain::oceanic:
            answ = "Oceanic";
            break;
        case terrain::mountane:
            answ = "Mountane";
            break;
        case terrain::plain:
            answ = "Plain";
            break;
        case terrain::gaseous:
            answ = "Gaseous giant";
            break;
        case terrain::jungle:
            answ = "Jungle";
            break;
        case terrain::utopia:
            answ = "Utopia";
            break;
        }
        return answ;
    }
    std::string getPlanetSize()
    {
        std::string answ = "Undefined";
        switch(radius)
        {
        case proportions::asteroid:
            answ = "Asteroid";
            break;
        case proportions::dwarf:
            answ = "Dwarf-planet";
            break;
        case proportions::small:
            answ = "Small";
            break;
        case proportions::normal:
            answ = "Normal";
            break;
        case proportions::large:
            answ = "Large";
            break;
        case proportions::huge:
            answ = "Huge";
            break;
        case proportions::giant:
            answ = "Giant";
            break;
        }
        return answ;
    }

    void init(proportions size_of_planet, terrain surface, int people = 1, int people_max = 1)
    {
        population = people;
        max_population = people_max;
        landscape = surface;
        radius = size_of_planet;
        hidden = true;
        discover_diff = 0.5;
        rich = 1;

        if(max_population == 1)
        {
            switch(landscape)
            {
            case terrain::terran:
                max_population = terrain_max_pop;
                break;
            case terrain::sand:
                max_population = terrain_max_pop * 0.7;
                break;
            case terrain::frost:
                max_population = terrain_max_pop * 0.6;
                break;
            case terrain::vulcanic:
                max_population = terrain_max_pop * 0.5;
                break;
            case terrain::oceanic:
                max_population = terrain_max_pop;
                break;
            case terrain::mountane:
                max_population = terrain_max_pop * 0.9;
                break;
            case terrain::plain:
                max_population = terrain_max_pop;
                break;
            case terrain::gaseous:
                max_population = terrain_max_pop * 0.4;
                break;
            case terrain::jungle:
                max_population = terrain_max_pop;
                break;
            case terrain::utopia:
                max_population = terrain_max_pop * 2;
                break;
            }
            switch(radius)
            {
            case proportions::asteroid:
                max_population /= 10;
                break;
            case proportions::dwarf:
                max_population /= 2;
                break;
            case proportions::small:
                max_population *= 0.75;
                break;
            case proportions::normal:
                break;
            case proportions::large:
                max_population *= 1.201;
                break;
            case proportions::huge:
                max_population *= 1.5;
                break;
            case proportions::giant:
                max_population *= 2;
                break;
            }
        }
        switch(landscape)
        {
        case terrain::terran:
            colonization_diff = 1.1;
            rich += (rand() % 5 - 2) * 0.1;
            break;
        case terrain::sand:
            colonization_diff = 1.05;
            rich -= (rand() % 4 + 1) * 0.1;
            break;
        case terrain::frost:
            colonization_diff = 1.05;
            discover_diff *= 0.8;
            rich += (rand() % 3 - 1) * 0.1;
            break;
        case terrain::vulcanic:
            colonization_diff = 1.025;
            discover_diff *= 2;
            rich += (rand() % 3 + 1) * 0.1;
            break;
        case terrain::oceanic:
            colonization_diff = 1.025;
            discover_diff *= 1.2;
            rich += (rand() % 3 - 1) * 0.1;
            break;
        case terrain::mountane:
            colonization_diff = 1.05;
            rich += (rand() % 3) * 0.1;
            break;
        case terrain::plain:
            colonization_diff = 1.09;
            rich += (rand() % 3 - 1) * 0.1;
            break;
        case terrain::gaseous:
            colonization_diff = 1.01;
            rich += (rand() % 5 - 2) * 0.1;
            break;
        case terrain::jungle:
            colonization_diff = 1.03;
            rich += (rand() % 3 - 2) * 0.1;
            break;
        case terrain::utopia:
            colonization_diff = 1.2;
            discover_diff /= 2;
            rich += (rand() % 4 - 4) * 0.1;
            break;
        }
        switch(radius)
        {
        case proportions::asteroid:
            discover_diff /= 4;
            break;
        case proportions::dwarf:
            discover_diff /= 3;
            break;
        case proportions::small:
            discover_diff /= 2;
            break;
        case proportions::normal:
            break;
        case proportions::large:
            discover_diff *= 1.2;
            break;
        case proportions::huge:
            discover_diff *= 1.5;
            break;
        case proportions::giant:
            discover_diff *= 2;
            break;
        }
        if(discover_diff > 1)
            discover_diff = 1.0;
        else if(discover_diff < 0.1)
            discover_diff = 0.1;
    }

    void gen()
    {
        terrain pl_type;
        proportions pl_size = proportions::normal;
        switch(rand() % 34)
        {
        case 0:
            pl_type = terrain::utopia;
            break;
        case 1:
        case 2:
            pl_type = terrain::terran;
            break;
        case 3:
        case 4:
            pl_type = terrain::oceanic;
            break;
        case 5:
        case 6:
            pl_type = terrain::jungle;
            break;
        case 7:
        case 8:
        case 9:
            pl_type = terrain::plain;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            pl_type = terrain::mountane;
            break;
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            pl_type = terrain::sand;
            break;
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
            pl_type = terrain::vulcanic;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
            pl_type = terrain::frost;
            break;
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
            pl_type = terrain::gaseous;
            break;
        default:
            pl_type = terrain::utopia;
        }
        switch(pl_type)
        {
        case terrain::utopia:
            switch(rand() % 3)
            {
            case 0:
                pl_size = proportions::small;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            }
            break;
        case terrain::terran:
            switch(rand() % 5)
            {
            case 0:
                pl_size = proportions::small;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::dwarf;
                break;
            case 4:
                pl_size = proportions::huge;
                break;
            }
            break;
        case terrain::oceanic:
            switch(rand() % 4)
            {
            case 0:
                pl_size = proportions::huge;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::giant;
                break;
            }
            break;
        case terrain::jungle:
            switch(rand() % 5)
            {
            case 0:
                pl_size = proportions::small;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::giant;
                break;
            case 4:
                pl_size = proportions::huge;
                break;
            }
            break;
        case terrain::plain:
            switch(rand() % 6)
            {
            case 0:
                pl_size = proportions::small;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::dwarf;
                break;
            case 4:
                pl_size = proportions::huge;
                break;
            case 5:
                pl_size = proportions::asteroid;
                break;
            }
            break;
        case terrain::sand:
            switch(rand() % 6)
            {
            case 0:
                pl_size = proportions::small;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::dwarf;
                break;
            case 4:
                pl_size = proportions::huge;
                break;
            case 5:
                pl_size = proportions::asteroid;
                break;
            }
            break;
        case terrain::vulcanic:
            switch(rand() % 5)
            {
            case 0:
                pl_size = proportions::huge;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::giant;
                break;
            case 4:
                pl_size = proportions::small;
                break;
            }
            break;
        case terrain::frost:
            switch(rand() % 5)
            {
            case 0:
                pl_size = proportions::dwarf;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::asteroid;
                break;
            case 4:
                pl_size = proportions::small;
                break;
            }
            break;
        case terrain::mountane:
            switch(rand() % 7)
            {
            case 0:
                pl_size = proportions::small;
                break;
            case 1:
                pl_size = proportions::normal;
                break;
            case 2:
                pl_size = proportions::large;
                break;
            case 3:
                pl_size = proportions::dwarf;
                break;
            case 4:
                pl_size = proportions::huge;
                break;
            case 5:
                pl_size = proportions::asteroid;
                break;
            case 6:
                pl_size = proportions::giant;
                break;
            }
        case terrain::gaseous:
            switch(rand() % 2)
            {
            case 0:
                pl_size = proportions::huge;
                break;
            case 1:
                pl_size = proportions::giant;
                break;
            }
            break;
        }
        init(pl_size, pl_type);
    }

    Planet() {gen();}
    Planet(proportions size_of_planet, terrain surface, int people, int people_max, bool new_hidden = true)
    {
        init(size_of_planet, surface, people, people_max);
        setHidden(new_hidden);
    }

};
