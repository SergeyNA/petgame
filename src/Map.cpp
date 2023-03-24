char sector_index_v[16] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
char sector_index_h[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
enum class own {NONE, PLAYER, HUMANITY, PIRATES, ALIENS1, ALIENS2, REBELS};
enum class fleetDestination {STAND, LEFTWARD, RIGHTWARD, UPWARD, DOWNWARD};

std::string getOwnerRecord(own owner)
{
    std::string answ;
    switch(owner)
    {
    case own::NONE:
        answ = "None";
        break;
    case own::PLAYER:
        answ = "You";
        break;
    case own::HUMANITY:
        answ = "The Coalition";
        break;
    case own::PIRATES:
        answ = "Pirates";
        break;
    case own::ALIENS1:
        answ = "Xelors";
        break;
    case own::ALIENS2:
        answ = "Snake Empire";
        break;
    case own::REBELS:
        answ = "Rebels";
        break;
    default:
        answ = "Undefined";
    }
    return answ;
}

class Sector
{
    int h;
    int v;
    int difficult;
    int wealth;
    bool shadow;
    bool anomaly;
    own owner;
    std::string owner_name;
    std::vector<Planet> planets;

public:
    int investigate_count;
    bool planet_counter;
    bool show_defense;

    //Sector() {planets.reserve(4);}

    void init(int x, int y, int reach, int abundant)
    {
        v = x;
        h = y;
        shadow = true;
        planet_counter = false;
        show_defense = false;
        difficult = reach;
        wealth = abundant;
        investigate_count = 0;
        owner = own::NONE;
        owner_name = "None";
        anomaly = false;

        if(wealth != 0)
        {
            int pl_count = rand() %  (wealth + 1) + wealth;
            for(int i = 0; i < pl_count; i++)
                planets.push_back(Planet());
        }
    }

    void resetPlanets()
    {
        planets.clear();
    }

    void addPlanet(terrain surface, proportions size_of_planet, int people, int people_max, bool hidden_flag = true)
    {
        planets.push_back(Planet(size_of_planet, surface, people, people_max, hidden_flag));
        if(!hidden_flag)
            investigate_count++;
    }

    void setOwner(own holder, std::string holder_name, bool hide_icon = false)
    {
        shadow = hide_icon;
        owner = holder;
        owner_name = holder_name;
        if(shadow)
            investigate_count = 0;
        else
            investigate_count = 1;
    }

    void setVisible()
    {
        shadow = false;
        show_defense = true;
        planet_counter = true;
        for(std::vector<Planet>::iterator it = planets.begin(); it != planets.end(); it++)
        {
            it->setHidden(false);
        }
    }

    void full_init(int x, int y, bool hidden, bool show_planet, bool show_power, own holder, std::string holder_name, int reach, int abundant, bool isAnomaly)
    {
        v = x;
        h = y;
        shadow = hidden;
        planet_counter = show_planet;
        owner = holder;
        owner_name = holder_name;
        difficult = reach;
        wealth = abundant;
        anomaly = isAnomaly;
        show_defense = show_power;
        if(planet_counter)
            investigate_count = 1;
        else
            investigate_count = 0;

        if(wealth != 0)
        {
            int pl_count = rand() %  (wealth + 1) + wealth;
            for(int i = 0; i < pl_count; i++)
                planets.push_back(Planet());
        }
    }

    std::pair<int, int> getPos()
    {
        return std::make_pair(v, h);
    }

    void addAnomaly()
    {
        anomaly = true;
    }
    bool isAnomaly()
    {
        return anomaly;
    }

    bool isInvestigate()
    {
        if(shadow || !planet_counter)
            return true;
        for(std::vector<Planet>::iterator it = planets.begin(); it != planets.end(); it++)
        {
            if(it->isHidden())
                return true;
        }
        return false;
    }
    void doInvestigate()
    {
        for(std::vector<Planet>::iterator it = planets.begin(); it != planets.end(); it++)
        {
            if(it->isHidden())
                it->discover();
        }
    }

    int getExploredPC()
    {
        int answ = 0;
        for(std::vector<Planet>::iterator it = planets.begin(); it != planets.end(); it++)
        {
            if(it->isHidden())
                answ++;
        }
        return planets.size() - answ;
    }
    std::string get_sector_planet_info()
    {
        std::string answ = toString(getExploredPC());
        answ.push_back('/');
        if(planet_counter)
            answ += toString(planets.size());
        else
            answ.push_back('?');
        return answ;
    }

    std::string getStarCoordinate()
    {
        std::string answ;
        answ.push_back(sector_index_v[v]);
        answ.push_back(sector_index_h[h]);
        return answ;
    }

    void newTurn()
    {
        if(owner == own::PLAYER)
        {
            for(unsigned int i = 0; i < planets.size(); i++)
            {
                planets[i].newTurn();
                people += planets[i].getPopulation();
            }
        }
        else
        {
            for(unsigned int i = 0; i < planets.size(); i++)
            {
                planets[i].newTurn();
            }
        }
    }

    bool isShadow()
    {
        return shadow;
    }

    std::string getOwner()
    {
        return owner_name;
    }

    own getOwnerIndex()
    {
        return owner;
    }

    void print_planets()
    {
        std::cout<<"Quadrant "<<getStarCoordinate()<<"   wealth = "<<wealth<<std::endl;
        for(Planet iter : planets)
            std::cout<<iter.getTerrainType()<<" "<<iter.getPlanetSize()<<" "<<iter.max_population<<std::endl;
    }

    int getPower()
    {
        int answ = 0;
        for(std::vector<Planet>::iterator it = planets.begin(); it != planets.end(); it++)
        {
            answ += 100 * it->getPopulation();
        }
        for(int index = 0; index < static_cast<int>(fleets.size()); index++)
        {
            if(v == fleets[index].getX() && h == fleets[index].getY())
                answ += fleets[index].getPower();
        }
        return answ;
    }
    int getDif()
    {
        return difficult;
    }
    int getRich()
    {
        return wealth;
    }

    void setShadow(bool new_state)
    {
        shadow = new_state;
    }

    bool isHere(int x, int y)
    {
        if(x > 40 * h + 20 && x < 40 * (h + 1) + 20 && y > 122 + 40 * v && y < 122 + 40 * (v + 1))
            return true;
        return false;
    }

    void render_icon(WrapTexture* link)
    {
        link->render(20 + v * 40, 122 + h * 40);
    }
};

class Map
{
private:
    //map
    WrapTexture star_sector;
    std::pair<int, int> focus;
    Sector sectors[16][10];

    //icons
    WrapTexture map_icon_unknow;
    WrapTexture map_icon_humans;
    WrapTexture map_icon_player;
    WrapTexture map_icon_pirate;
    WrapTexture map_icon_rebels;
    WrapTexture map_icon_aliens1;
    WrapTexture map_icon_aliens2;
    WrapTexture fleet_icon_player;
    WrapTexture fleet_icon_player2;

    //quadrant descr
    WrapTexture quadrant_coordinates;
    WrapTexture power_value;
    WrapTexture owner_name;
    WrapTexture properties;

    WrapTexture arrow;
    WrapTexture selected_arrow;

    bool paint_arrow = false;
    fleetDestination fleetDir = fleetDestination::STAND;

    Sector& getSector(int x, int y)
    {
        return sectors[(x - 20) / 40][(y - 122) / 40];
    }
    void draw_color_sector_edge(std::pair<int, int> coord)
    {
        SDL_RenderDrawLine( renderer, 20 + coord.first * 40, 122 + coord.second * 40, 20 + coord.first * 40, 122 + coord.second * 40 + 39 );
        SDL_RenderDrawLine( renderer, 20 + coord.first * 40 + 39, 122 + coord.second * 40 + 1, 20 + coord.first * 40 + 39, 122 + coord.second * 40 + 40 - 1 );
        SDL_RenderDrawLine( renderer, 20 + coord.first * 40, 122 + coord.second * 40, 20 + coord.first * 40 + 39, 122 + coord.second * 40 );
        SDL_RenderDrawLine( renderer, 20 + coord.first * 40, 121 + coord.second * 40 + 40, 20 + coord.first * 40 + 39, 121 + coord.second * 40 + 40 );

        SDL_RenderDrawLine( renderer, 20 + coord.first * 40 - 1, 122 + coord.second * 40 - 1, 20 + coord.first * 40 - 1, 122 + coord.second * 40 + 40 );
        SDL_RenderDrawLine( renderer, 20 + coord.first * 40 + 40, 122 + coord.second * 40 - 1, 20 + coord.first * 40 + 40, 122 + coord.second * 40 + 40 - 1 );
        SDL_RenderDrawLine( renderer, 20 + coord.first * 40 - 1, 122 + coord.second * 40 - 1, 20 + coord.first * 40 + 40, 122 + coord.second * 40 - 1 );
        SDL_RenderDrawLine( renderer, 20 + coord.first * 40 - 1, 121 + coord.second * 40 + 40 + 1, 20 + coord.first * 40 + 40, 121 + coord.second * 40 + 40 + 1 );
    }
    void render_icon(Sector* link)
    {
        if(link->isShadow())
            link->render_icon(&map_icon_unknow);
        else
        {
            switch(link->getOwnerIndex())
            {
                case own::PLAYER:
                    link->render_icon(&map_icon_player);
                    break;
                case own::HUMANITY:
                    link->render_icon(&map_icon_humans);
                    break;
                case own::PIRATES:
                    link->render_icon(&map_icon_pirate);
                    break;
                case own::REBELS:
                    link->render_icon(&map_icon_rebels);
                    break;
                case own::ALIENS1:
                    link->render_icon(&map_icon_aliens1);
                    break;
                case own::ALIENS2:
                    link->render_icon(&map_icon_aliens2);
                    break;
                default:
                    break;
            }
        }
    }

public:
    WrapTexture quadrant_title;
    WrapTexture power_title;
    WrapTexture owner_title;
    WrapTexture properties_title;
    WrapTexture planets_title;
    WrapTexture objects_titile;

    bool init()
    {
        if(!star_sector.loadFromFile("22.jpg"))
            return false;
        if(!arrow.loadFromFile("arrow_up.png", true))
            return false;
        if(!selected_arrow.loadFromFile("selected_arrow_up.png", true))
            return false;
        if(!map_icon_humans.loadFromFile("map_humanity2.png", true))
            return false;
        if(!map_icon_unknow.loadFromFile("map_icon_q.png", true))
            return false;
        if(!map_icon_player.loadFromFile("map_player_emblem.png", true))
            return false;
        if(!map_icon_rebels.loadFromFile("rebels_icon.png", true))
            return false;
        if(!map_icon_aliens2.loadFromFile("snake_icon.png", true))
            return false;
        if(!map_icon_aliens1.loadFromFile("aliens_icon.png", true))
            return false;
        if(!map_icon_pirate.loadFromFile("empire_emblem_pirates_2.png", true))
            return false;
        if(!fleet_icon_player.loadFromFile("fleet_icon1.png", true))
            return false;
        if(!fleet_icon_player2.loadFromFile("fleet_icon2.png", true))
            return false;
        star_sector.setRenderPos(20, 122);
        focus.first = -1;
        focus.second = -1;

        for(int i = 0; i < 16; i++)
            for(int j = 0; j < 10; j++)
            {
                sectors[i][j].init(i, j, rand() % 4, rand() % 5);
                /*sectors[i][j].print_planets();
                std::cout<<std::endl;*/
            }

        for(int i = 0; i < 16; i++)
            for(int j = 0; j < 10; j++)
            {
                if(rand() % 4 == 0)
                    sectors[i][j].setOwner(own::PIRATES, getOwnerRecord(own::PIRATES));
            }

        for(int i = 10; i < 15; i++)
            for(int j = 4; j < i - 5; j++)
            {
                if(rand() % 5 == 0)
                    sectors[i][j].setOwner(own::REBELS, getOwnerRecord(own::REBELS));
                else
                    sectors[i][j].setOwner(own::HUMANITY, getOwnerRecord(own::HUMANITY));
            }

        int player_home_x = rand() % 16;
        int player_home_y = rand() % 10;
        mapPosition.first = player_home_x;
        mapPosition.second = player_home_y;
        if(player_home_x - 1 >= 0)
            sectors[player_home_x - 1][player_home_y].setOwner(own::PLAYER, getOwnerRecord(own::PLAYER));
        if(player_home_x + 1 < 16)
            sectors[player_home_x + 1][player_home_y].setOwner(own::PLAYER, getOwnerRecord(own::PLAYER));
        if(player_home_y - 1 >= 0)
            sectors[player_home_x][player_home_y - 1].setOwner(own::PLAYER, getOwnerRecord(own::PLAYER));
        if(player_home_y + 1 < 10)
            sectors[player_home_x][player_home_y + 1].setOwner(own::PLAYER, getOwnerRecord(own::PLAYER));

        int snake_invasion = rand() % 2;
        if(snake_invasion == 0)
        {
            int invasion_deep = rand() % 3 + 1;
            int invasion_center = rand() % 16;
            int invasion_spread = 0;
            while(invasion_deep-- > 0)
            {
                for(int snake_index = invasion_center - invasion_spread; snake_index <= invasion_center + invasion_spread; snake_index++)
                {
                    if(snake_index >= 0 && snake_index < 16)
                        sectors[snake_index][invasion_deep].setOwner(own::ALIENS2, getOwnerRecord(own::ALIENS2));
                }
                invasion_spread++;
            }
        }

        int xenos_invasion = rand() % 2;
        if(xenos_invasion == 0)
        {
            int invasion_deep = rand() % 3 + 1;
            int invasion_center = rand() % 10;
            int invasion_spread = 0;
            while(invasion_deep-- > 0)
            {
                for(int xenos_index = invasion_center - invasion_spread; xenos_index <= invasion_center + invasion_spread; xenos_index++)
                {
                    if(xenos_index >= 0 && xenos_index < 10)
                        sectors[invasion_deep][xenos_index].setOwner(own::ALIENS1, getOwnerRecord(own::ALIENS1));
                }
                invasion_spread++;
            }
        }

        sectors[player_home_x][player_home_y].setOwner(own::PLAYER, getOwnerRecord(own::PLAYER));
        sectors[player_home_x][player_home_y].planet_counter = true;
        sectors[player_home_x][player_home_y].setVisible();
        sectors[player_home_x][player_home_y].resetPlanets();
        sectors[player_home_x][player_home_y].addPlanet(terrain::terran, proportions::normal, 100, 125, false);
        sectors[player_home_x][player_home_y].addPlanet(terrain::oceanic, proportions::large, 150, 250, false);

        quadrant_title.loadFromRenderedText("Quadrant:", YELLOW, 2);
        quadrant_title.setRenderPos(SCREEN_WIDTH - 290, 120);
        owner_title.loadFromRenderedText("Owner:", YELLOW, 0);
        owner_title.setRenderPos(SCREEN_WIDTH - 275, 170);
        power_title.loadFromRenderedText("Defense:", YELLOW, 0);
        power_title.setRenderPos(SCREEN_WIDTH - 275, 190);
        properties_title.loadFromRenderedText("Properties:", YELLOW, 0);
        properties_title.setRenderPos(SCREEN_WIDTH - 275, 210);
        planets_title.loadFromRenderedText("Colonies:", YELLOW, 0);
        planets_title.setRenderPos(SCREEN_WIDTH - 275, 230);
        objects_titile.loadFromRenderedText("Anomalies:", YELLOW, 0);
        objects_titile.setRenderPos(SCREEN_WIDTH - 275, 250);

        return true;
    }
    bool isClickOnStarsectorsMap(int x, int y)
    {
        if(x > 20 && x < 20 + 640 && y > 122 && y < 122 + 400)
            return true;
        return false;
    }
    void handleClick(int x, int y)
    {
        if(isClickOnStarsectorsMap(x, y))
        {
            if(paint_arrow)
            {
                logMessage = "Your starfleet is moving from sector " + sectors[focus.first][focus.second].getStarCoordinate() + " to ";
                std::vector<Fleet>::iterator it;
                for(it = fleets.begin(); it != fleets.end(); it++)
                {
                    if(it->isHere(focus.first, focus.second)) {break;}
                }
                switch(fleetDir)
                {
                case fleetDestination::DOWNWARD:
                    it->moveFleet(focus.first, focus.second+1, 1);
                    logMessage += sectors[focus.first][focus.second+1].getStarCoordinate();
                    break;
                case fleetDestination::UPWARD:
                    it->moveFleet(focus.first, focus.second-1, 1);
                    logMessage += sectors[focus.first][focus.second-1].getStarCoordinate();
                    break;
                case fleetDestination::LEFTWARD:
                    it->moveFleet(focus.first-1, focus.second, 1);
                    logMessage += sectors[focus.first-1][focus.second].getStarCoordinate();
                    break;
                case fleetDestination::RIGHTWARD:
                    it->moveFleet(focus.first+1, focus.second, 1);
                    logMessage += sectors[focus.first+1][focus.second].getStarCoordinate();
                    break;
                case fleetDestination::STAND:
                    break;
                }
                if(fleetDir != fleetDestination::STAND)
                {
                    mapPosition.first = it->getX();
                    mapPosition.second = it->getY();
                    action_handler(MOVING_FLEET);
                }
            }


            if(focus != getSector(x, y).getPos())
                focus = getSector(x, y).getPos();
            else
                this->delFocus();

            paint_arrow = false;
            for(std::vector<Fleet>::iterator it = fleets.begin(); it != fleets.end(); it++)
            {
                if(it->isHere(focus.first, focus.second))
                {
                    if(it->canMoved())
                    {
                        paint_arrow = true;
                        break;
                    }
                }
            }
        }
    }
    Sector& getSector(std::pair<int, int> coordinates)
    {
        return sectors[coordinates.first][coordinates.second];
    }
    bool isInvestigatable(int x, int y)
    {
        if(isClickOnStarsectorsMap(x, y))
        {
            bool can_continue = false;
            Sector temp_sector = getSector(x, y);
            std::pair<int, int> sector_pos = temp_sector.getPos();

            if(sectors[sector_pos.first][sector_pos.second].getOwnerIndex() == own::PLAYER)
                can_continue = true;
            if(sector_pos.first > 0)
                if(sectors[sector_pos.first - 1][sector_pos.second].getOwnerIndex() == own::PLAYER)
                    can_continue = true;
            if(sector_pos.first < 15)
                if(sectors[sector_pos.first + 1][sector_pos.second].getOwnerIndex() == own::PLAYER)
                    can_continue = true;
            if(sector_pos.second > 0)
                if(sectors[sector_pos.first][sector_pos.second - 1].getOwnerIndex() == own::PLAYER)
                    can_continue = true;
            if(sector_pos.second < 9)
                if(sectors[sector_pos.first][sector_pos.second + 1].getOwnerIndex() == own::PLAYER)
                    can_continue = true;

            if(can_continue)
                if(temp_sector.isInvestigate())
                    return true;
        }
        return false;
    }
    bool makeInvestigate()
    {
        if(action_points > 0)
        {
            int difficult = sectors[focus.first][focus.second].getDif();
            if(difficult < 2)
                difficult = 2;
            sectors[focus.first][focus.second].investigate_count++;
            if(rand() % difficult == 0)
                sectors[focus.first][focus.second].planet_counter = true;
            if(rand() % difficult == 0)
                sectors[focus.first][focus.second].setShadow(false);
            if(technologies[39].research_progress > 0)
                sectors[focus.first][focus.second].show_defense = true;
            sectors[focus.first][focus.second].doInvestigate();
        }
        logMessage = "Exploring sector " + sectors[focus.first][focus.second].getStarCoordinate();
        if(!sectors[focus.first][focus.second].isInvestigate())
            return true;
        return false;
    }
    void delFocus()
    {
        focus.first = -1;
        focus.second = -1;
    }
    void newTurn()
    {
        for(int i = 0; i < 16; i++)
            for(int j = 0; j < 10; j++)
                sectors[i][j].newTurn();
    }
    void drawFleetMoveVariant(int drawArrowX, int drawArrowY, double angle)
    {
        SDL_GetMouseState( &mouseX, &mouseY );
        if(mouseX > drawArrowX && mouseX < drawArrowX + 40 && mouseY > drawArrowY && mouseY < drawArrowY + 40)
        {
            if(mouseX < 20 + focus.first * 40 || mouseX > 20 + (focus.first + 1) * 40 || mouseY < 122 + focus.second * 40 || mouseY > 122 + (focus.second + 1) * 40)
            {
                selected_arrow.render2(drawArrowX, drawArrowY, nullptr, angle);
                if(mouseX < 20 + focus.first * 40) fleetDir = fleetDestination::LEFTWARD;
                else if(mouseX > 20 + (focus.first + 1) * 40) fleetDir = fleetDestination::RIGHTWARD;
                else if(mouseY < 122 + focus.second * 40) fleetDir = fleetDestination::UPWARD;
                else if(mouseY > 122 + (focus.second + 1) * 40) fleetDir = fleetDestination::DOWNWARD;
            }
            else
                arrow.render2(drawArrowX, drawArrowY, nullptr, angle);
        }
        else
            arrow.render2(drawArrowX, drawArrowY, nullptr, angle);
    }
    void render()
    {
        star_sector.render();

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 100 );
        for(int i = 0; i <= 16; i++)
        {
            SDL_RenderDrawLine( renderer, 20 + i * 40, 122, 20 + i * 40, 122 + 400 );
            SDL_RenderDrawLine( renderer, 19 + i * 40, 122, 19 + i * 40, 122 + 400 );
        }
        for(int i = 0; i <= 10; i++)
        {
            SDL_RenderDrawLine( renderer, 20, 122 + 40 * i, 20 + 640, 122 + 40 * i);
            SDL_RenderDrawLine( renderer, 20, 121 + 40 * i, 20 + 640, 121 + 40 * i);
        }

        //draw sector owner icons on the map
        for(int i = 0; i < 16; i++)
            for(int j = 0; j < 10; j++)
                render_icon(&sectors[i][j]);

        //draw fleet icons on the map
        SDL_SetRenderDrawColor( renderer, 200, 200, 0, 255 );
        for(std::vector<Fleet>::iterator it = fleets.begin(); it != fleets.end(); it++)
        {
            //draw_color_sector_edge(std::make_pair(it->getX(), it->getY())); //draw bold sector edges by RenderDrawColor
            //if(!sectors[it->getX()][it->getY()].isShadow()) {fleet_icon_player.render(20 + it->getX() * 40, 122 + it->getY() * 40, 0.4);}
            if(it->canMoved())
                fleet_icon_player.render(20 + it->getX() * 40, 122 + it->getY() * 40, 0.4);
            else
                fleet_icon_player2.render(20 + it->getX() * 40, 122 + it->getY() * 40);
        }

        //additional draw for selected sector
        if(focus.first != -1)
        {
            SDL_SetRenderDrawColor( renderer, 200, 200, 0, 255 );
            draw_color_sector_edge(focus);

            if(paint_arrow)
            {
                fleetDir = fleetDestination::STAND;
                if(focus.second > 0)
                {
                    /*if(sectors[focus.first][focus.second - 1].getOwnerIndex() != own::PLAYER)
                    {
                        SDL_SetRenderDrawColor( renderer, 150, 0, 0, 255 );
                        draw_color_sector_edge(std::make_pair(focus.first, focus.second - 1));
                    }*/
                    //arrow.render(20 + focus.first * 40, 122 + focus.second * 40 - 30);
                    drawFleetMoveVariant(20 + focus.first * 40, 122 + focus.second * 40 - 30, 0);
                }
                if(focus.first < 15)
                {
                    //arrow.render2(20 + focus.first * 40 + 30, 122 + focus.second * 40, nullptr, 90);
                    drawFleetMoveVariant(20 + focus.first * 40 + 30, 122 + focus.second * 40, 90);
                }
                if(focus.second < 9)
                {
                    //arrow.render2(20 + focus.first * 40, 122 + focus.second * 40 + 30, nullptr, 180);
                    drawFleetMoveVariant(20 + focus.first * 40, 122 + focus.second * 40 + 30, 180);
                }
                if(focus.first > 0)
                {
                    //arrow.render2(20 + focus.first * 40 - 30, 122 + focus.second * 40, nullptr, 270);
                    drawFleetMoveVariant(20 + focus.first * 40 - 30, 122 + focus.second * 40, 270);
                }
            }
        }

        power_title.render();
        owner_title.render();
        properties_title.render();
        planets_title.render();
        objects_titile.render();

        SDL_GetMouseState( &mouseX, &mouseY );
        if(isClickOnStarsectorsMap(mouseX, mouseY) || focus.first != -1)
        {
            Sector current_sector;
            if(isClickOnStarsectorsMap(mouseX, mouseY))
                current_sector = getSector(mouseX, mouseY);
            else
                current_sector = sectors[focus.first][focus.second];
            quadrant_title.render();

            if(current_sector.isShadow())
                owner_name.loadFromRenderedText("???", GRAY, 0, false);
            else
                owner_name.loadFromRenderedText(current_sector.getOwner(), WHITE, 0, false);
            if(current_sector.investigate_count == 0)
                properties.loadFromRenderedText("?/?", WHITE, 0, false);
            else
                properties.loadFromRenderedText(toString(current_sector.getDif()) + "/" + toString(current_sector.getRich()), WHITE, 0, false);
            properties.render(SCREEN_WIDTH - 140, 210);
            quadrant_coordinates.loadFromRenderedText(current_sector.getStarCoordinate(), WHITE, 2, false);

            if(current_sector.show_defense || current_sector.getOwnerIndex() == own::PLAYER)
                power_value.loadFromRenderedText(toString(current_sector.getPower()), WHITE, 0, false);
            else
                power_value.loadFromRenderedText("???", WHITE, 0, false);

            quadrant_coordinates.render(SCREEN_WIDTH - 65, 120);
            power_value.render(SCREEN_WIDTH - 170, 190);
            owner_name.render(SCREEN_WIDTH - 200, 170);
            properties.loadFromRenderedText(current_sector.get_sector_planet_info(), WHITE, 0, false);
            properties.render(SCREEN_WIDTH - 160, 230);
            if(current_sector.isShadow())
                properties.loadFromRenderedText("???", WHITE, 0, false);
            else if(current_sector.isAnomaly())
                properties.loadFromRenderedText("Yes", WHITE, 0, false);
            else
                properties.loadFromRenderedText("No", WHITE, 0, false);
            properties.render(SCREEN_WIDTH - 150, 250);
        }
    }
} field;
