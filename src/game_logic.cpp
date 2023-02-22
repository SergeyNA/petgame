void action_handler(game_event e)
{
    switch(e) {

    case GAME_NEW_TURN:
        LOG.add_message("NEW ROUND", WHITE, 1);

        for(std::vector<Fleet>::iterator it = fleets.begin(); it != fleets.end(); it++)
            it->newTurn();

        people = 0;
        //field.newTurn();

        resourses += static_cast<int>(floor(people * MENU.top_scroller.getVal()) + .5);
        science_points += static_cast<int>(people -  floor(people * MENU.top_scroller.getVal()) + .5);
        MENU.updTopMenu();
        action_points += action_limits;
        if(action_points > action_limits)
            action_points = action_limits;
        MENU.updActionCounter();
        break;

    case GAME_ATTACK:
        /*if(fleet_str_val > enemy_fleet_str)
        {
            LOG.add_message("Victory!", GREEN, 0);
            fleet_str_val -= enemy_fleet_str;
            enemy_fleet_str = 0;
        }
        else
        {
            LOG.add_message("DEFEAT!", RED, 0);
            enemy_fleet_str -= fleet_str_val;
            fleet_str_val = 0;
        }*/
        MENU.updTopMenu();
        break;

    /*case BUILD_SHIP:
        fleets[0].addShip(ship.ship_power);
        resourses -= ship.ship_cost_res;
        people -= ship.ship_cost_staff;
        MENU.updTopMenu();
        action_points -= ship.ship_cost_actions;
        MENU.updActionCounter();
        break;

    case EXPLORATION:
        if(action_points > 0)
        {
            action_points--;
            if(field.doInvestigate())
                explore_sector.offButton();
            MENU.updActionCounter();
            LOG.add_message(logMessage, BLUE, 0);
        }
        break;

    case HULL_CREATION:
        ship.load_ship();
        ship.open_ship_list.onButton();
        ship.build_spaceship.onButton();
        break;

    case DO_RESEARCH:
        if(technologies[research_index].isResearchable())
        {
            LOG.add_message("You spend " + toString(technologies[research_index].getCost()) + " tech on \"" +
                    technologies[research_index].name + "\" lvl: " + toString(technologies[research_index].research_progress), BLUE, 0);
            if(technologies[38].research_progress == 0)
                action_points -= 1;
            technologies[research_index].upgrade();
            openTechnology(research_index);
            MENU.updTopMenu();
            MENU.updActionCounter();
        }
        research_index = -1;
        break;*/

    }
}

/*void openTechnology(int index)
{
    switch(index)
    {
    case 7:
        if(technologies[7].research_progress == 1)
        {
            ship.ship_names.push_back("Human_3");
            ship.ship_names.push_back("Human_4");
        }
        break;
    case 17:
        if(technologies[17].research_progress == 1)
            ship.ship_names.push_back("Human_5");
        break;
    case 18:
        if(technologies[18].research_progress == 1)
            ship.ship_names.push_back("Human_6");
        break;
    case 19:
        if(technologies[19].research_progress == 1)
            ship.ship_names.push_back("Human_7");
        break;
    case 20:
        if(technologies[20].research_progress == 1)
        {
            ship.ship_names.push_back("Human_8");
            ship.ship_names.push_back("Human_9");
            ship.ship_names.push_back("Human_10");
        }
        break;
    case 24:
        if(technologies[24].research_progress == 1)
            ship.ship_names.push_back("Human_2");
        break;
    }
}*/
