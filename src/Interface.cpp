#define DEFAULT_BACKGROUND "793.jpg"
#define BACKGROUND_FILTER_1 "p160_9812.jpg"
#define DEFAULT_BACKGROUND_2 "21.jpg" //not used
#define BACKGROUND_FILTER_2 "22.jpg" //used as the map
#define DEFAULT_BACKGROUND_3 "31.jpg"
#define BACKGROUND_FILTER_3 "32.jpg"

//main window right
Button log_tab;
Button new_turn;
Button research;
Button attack;

//main window center
Button explore;
Button shipyard;
Button colonize;

//research
Button change_tree;

//map
Button close_map;
Button explore_sector;

//shipyard
Button back_from_yard_to_main_menu;

class Interface {

private:
    WrapTexture cursor;

    WrapTexture human_count;
    //WrapTexture enemy_str;
    WrapTexture res_counter;
    WrapTexture research_points;
    WrapTexture res_per_round;
    WrapTexture science_per_round;
    WrapTexture actions;

    WrapTexture colonize1;
    WrapTexture colonize2;
    WrapTexture shipyard1;
    WrapTexture shipyard2;
    WrapTexture seek1;
    WrapTexture seek2;

    WrapTexture tech_descr;
    WrapTexture tech_requir;
    WrapTexture tech_unlocks;

    WrapTexture background;
    WrapTexture background_filter;

    bool logger_off;
    bool research_open;
    bool main_menu;
    bool shipyard_open;
    bool map_open;

    bool tree_button_state = true;

    Tips tips[10];

public:

    Scroller top_scroller;
    Scroller tree_scroller;

    bool init()
    {
        if(!cursor.loadFromFile("Cursor.png", true))
            return false;

        if(!background.loadFromFile( DEFAULT_BACKGROUND ))
            return false;
        if(!background_filter.loadFromFile( BACKGROUND_FILTER_1 ))
            return false;
        background_filter.setBlendMode(SDL_BLENDMODE_BLEND);
        background_filter.setAlpha(127);

        if(!log_tab.setImage("button1.png", true))
            return false;
        log_tab.setPos( SCREEN_WIDTH - 225, SCREEN_HEIGHT - 100 );

        if(!new_turn.setImage("new turn.png", true))
            return false;
        new_turn.setPos( SCREEN_WIDTH - 225, SCREEN_HEIGHT - 180 );

        if(!research.setImage("research_button.png", true))
            return false;
        research.setPos( SCREEN_WIDTH - 265, SCREEN_HEIGHT - 275 );

        if(!change_tree.setImage("show_tree.png", true))
            return false;
        change_tree.setPos( SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 + 90 );
        change_tree.offButton();

        if(!close_map.setImage("close_map_button.png", true))
            return false;
        close_map.setPos( SCREEN_WIDTH - 200, SCREEN_HEIGHT - 170 );
        close_map.offButton();

        if(!back_from_yard_to_main_menu.setImage("back_button.png", true))
            return false;
        back_from_yard_to_main_menu.setPos( 20, SCREEN_HEIGHT - 100 );
        back_from_yard_to_main_menu.offButton();

        if(!explore_sector.setImage("explore_sector.png", true))
            return false;
        explore_sector.setPos( SCREEN_WIDTH - 200, SCREEN_HEIGHT - 240 );
        explore_sector.offButton();

        if(!explore.setImage("explore.png", true))
            return false;
        explore.setPos( SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3 );

        if(!shipyard.setImage("shipyard.png", true))
            return false;
        shipyard.setPos( SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3 );

        if(!colonize.setImage("investigate.png", true))
            return false;
        colonize.setPos( SCREEN_WIDTH * 2 / 3 - SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3 - 3 );

        if(!attack.setImage("picture-36.png", true))
            return false;
        attack.setPos( SCREEN_WIDTH - 230, SCREEN_HEIGHT - 375 );

        if(!human_count.loadFromRenderedText("Population: " + toString(people), YELLOW, 0))
            return false;
        human_count.setRenderPos(25, 55);

        //if(!enemy_str.loadFromRenderedText("Enemy strength: " + toString(enemy_fleet_str), RED, 0))
        //    return false;
        //enemy_str.setRenderPos(SCREEN_WIDTH - 240, 50);

        TTF_SetFontStyle(gFont[0], TTF_STYLE_UNDERLINE);
        if(!tech_descr.loadFromRenderedText("Description:", YELLOW, 0))
            return false;
        tech_descr.setRenderPos(25, 35);
        if(!tech_unlocks.loadFromRenderedText("Unlocks:", YELLOW, 0))
            return false;
        if(!tech_requir.loadFromRenderedText("Prerequisites:", YELLOW, 0))
            return false;
        TTF_SetFontStyle(gFont[0], TTF_STYLE_NORMAL);

        if(!actions.loadFromRenderedText("ACTIONS: " + toString(action_points) + "/" + toString(action_limits), WHITE, 2))
            return false;
        actions.setRenderPos(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 170);

        top_scroller.init(SCREEN_WIDTH / 4 + 75, 20, SCREEN_WIDTH * 3 / 4 - 75, 40, "foo.png", 181, 149, 213);
        tree_scroller.init(SCREEN_WIDTH / 3 - 20, 80, SCREEN_WIDTH / 3, SCREEN_HEIGHT, "Scroller-icon.png", 181, 149, 213);
        tree_scroller.setPosition(0);
        ship.ship_list_scroller.init(SCREEN_WIDTH * 3 / 4 - 13, SCREEN_HEIGHT - 70 - ship_load_list_height + 6 + 8, SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT - 70 - ship_load_list_height + 6 + 20 * ship_load_list_members, "vertical_tight_scroller_icon.png", 255, 228, 181);
        ship.ship_list_scroller.off();
        ship.ship_list_scroller.setPosition(0);

        if(!res_per_round.loadFromRenderedText(toString(static_cast<int>(floor(people * top_scroller.getVal() + .5))), GRAY, 0))
            return false;
        res_per_round.setRenderPos(SCREEN_WIDTH / 4 - 40 + 75, 22);
        tips[0].init("The amount of resources receiving at the turn's end", &res_per_round, 280);
        if(!science_per_round.loadFromRenderedText(toString(static_cast<int>(floor(people * (1 - top_scroller.getVal()) + .5))), BLUE, 0))
            return false;
        science_per_round.setRenderPos(SCREEN_WIDTH * 3 / 4 + 25 - 75, 22);
        tips[1].init("The amount of tech points receiving at the turn's end", &science_per_round, 280);
        tips[2].init("1'st: total amount of required resources 2'nd: reduction in your population after build 3'rd: required actions", &ship.ship_cost_title, 235);
        tips[3].init("Not enough resources for construction the scpaceship", ship.build_spaceship.getTexture(), 280);
        tips[4].init("Can't find a crew. Increase the population of your empire", ship.build_spaceship.getTexture(), 300);
        tips[5].init("Please restore actions on any positive value", ship.build_spaceship.getTexture(), 230);
        tips[6].init("Known space objects with possible self-existence", &field.planets_title, 195);
        tips[7].init("The complexity of discovering new space objects and their concentration in this area", &field.properties_title, 300);
        tips[8].init("Strange signals/places or other undefined things", &field.objects_titile, 255);
        tips[9].init("Please restore actions on any positive value", explore_sector.getTexture(), 230);

        if(!research_points.loadFromRenderedText("Tech potential:" + toString(science_points), BLUE, 0))
            return false;
        research_points.setRenderPos(25, 5);
        if(!res_counter.loadFromRenderedText("Resourses:" + toString(resourses), GRAY, 0))
            return false;
        res_counter.setRenderPos(25, 30);

        //TTF_SetFontStyle(gFont[0], TTF_STYLE_BOLD);
        colonize1.loadFromRenderedText("Populate", GREEN, 1);
        colonize1.setRenderPos(SCREEN_WIDTH * 2 / 3 - SCREEN_WIDTH / 7 + 40, SCREEN_HEIGHT / 3 - 20);
        colonize2.loadFromRenderedText("New World", GREEN, 1);
        colonize2.setRenderPos(SCREEN_WIDTH * 2 / 3 - SCREEN_WIDTH / 7 + 30, SCREEN_HEIGHT / 3 + 135);
        shipyard1.loadFromRenderedText("Open", YELLOW, 1);
        shipyard1.setRenderPos(SCREEN_WIDTH / 3 + 40, SCREEN_HEIGHT / 3 - 20);
        shipyard2.loadFromRenderedText("Shipyard", YELLOW, 1);
        shipyard2.setRenderPos(SCREEN_WIDTH / 3 + 20, SCREEN_HEIGHT / 3 + 135);
        seek1.loadFromRenderedText("Find", WHITE, 1);
        seek1.setRenderPos(SCREEN_WIDTH / 8 + 45, SCREEN_HEIGHT / 3 - 20);
        seek2.loadFromRenderedText("New World", WHITE, 1);
        seek2.setRenderPos(SCREEN_WIDTH / 8 + 15, SCREEN_HEIGHT / 3 + 135);
        //TTF_SetFontStyle(gFont[0], TTF_STYLE_NORMAL);

        logger_off = true;
        research_open = false;
        shipyard_open = false;
        main_menu = true;
        map_open = false;

        construction_mode = OVERVIEW_MODE;

        if(SDL_ShowCursor(SDL_DISABLE) < 0)
            return false;

        if(!field.init())
            return false;

        return true;
    }

    bool isLogDisabled()
    {
        return logger_off;
    }

    bool isMap()
    {
        return map_open;
    }

    bool setBackground(std::string name)
    {
        if(!background.loadFromFile( name ))
            return false;
        return true;
    }

    bool setFilterBackground(std::string name, Uint8 alpha)
    {
        if(!background_filter.loadFromFile( name ))
            return false;
        background_filter.setBlendMode(SDL_BLENDMODE_BLEND);
        background_filter.setAlpha(alpha);
        return true;
    }

    void updTopMenu()
    {
        human_count.loadFromRenderedText("Population: " + toString(people), YELLOW, 0);
        human_count.setRenderPos(25, 55);
        res_per_round.loadFromRenderedText(toString(static_cast<int>(floor(people * top_scroller.getVal()) + .5)), GRAY, 0, false);
        res_per_round.setRenderPos(SCREEN_WIDTH / 4 - 40 + 75, 22);
        science_per_round.loadFromRenderedText(toString(static_cast<int>( people -  floor(people * top_scroller.getVal()) + .5) ), BLUE, 0, false);
        science_per_round.setRenderPos(SCREEN_WIDTH * 3 / 4 + 25 - 75, 22);
        research_points.loadFromRenderedText("Tech potential:" + toString(science_points), BLUE, 0);
        research_points.setRenderPos(25, 5);
        res_counter.loadFromRenderedText("Resourses:" + toString(resourses), GRAY, 0);
        res_counter.setRenderPos(25, 30);
    }

    void updActionCounter()
    {
        actions.loadFromRenderedText("ACTIONS: " + toString(action_points) + "/" + toString(action_limits), WHITE, 2);
        if(research_open)
            actions.setRenderPos(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 170);
        else
            actions.setRenderPos(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 170);
    }

    void handleClick(int x, int y)
    {
        if(logger_off)
        {
            if(new_turn.isOn())
                if(new_turn.detectEvent(x, y))
                    action_handler(GAME_NEW_TURN);

            if(attack.isOn())
                if(attack.detectEvent(x, y))
                    action_handler(GAME_ATTACK);

            if(research.isOn())
                if(research.detectEvent(x, y))
                {
                    research_open ^= true;
                    if(research_open)
                    {
                        //GAME_RESEARCH_OPEN
                        main_menu = false;
                        research.setImage("research_close.png", true);
                        setBackground(DEFAULT_BACKGROUND_3);
                        setFilterBackground(BACKGROUND_FILTER_3, 100);

                        new_turn.offButton();
                        attack.offButton();
                        colonize.offButton();
                        shipyard.offButton();
                        explore.offButton();
                        change_tree.onButton();

                        actions.setRenderPos(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 170);
                    }
                    else
                    {
                        //GAME_RESEARCH_CLOSE
                        main_menu = true;
                        research.setImage("research_button.png", true);
                        setBackground(DEFAULT_BACKGROUND);
                        setFilterBackground(BACKGROUND_FILTER_1, 127);
                        new_turn.onButton();
                        attack.onButton();
                        colonize.onButton();
                        shipyard.onButton();
                        explore.onButton();
                        change_tree.offButton();
                        actions.setRenderPos(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 170);
                    }
                }

            if(shipyard.isOn())
                if(shipyard.detectEvent(x, y))
                {
                    shipyard_open = true;
                    main_menu = false;
                    back_from_yard_to_main_menu.onButton();
                    new_turn.offButton();
                    attack.offButton();
                    colonize.offButton();
                    shipyard.offButton();
                    explore.offButton();
                    research.offButton();
                    action_handler(HULL_CREATION);
                }
            if(back_from_yard_to_main_menu.detectEvent(x, y))
            {
                closeShipyard();
                ship.clear_();
            }
            if(explore.isOn())
            {
                if(explore.detectEvent(x, y))
                {
                    main_menu = false;
                    new_turn.offButton();
                    attack.offButton();
                    colonize.offButton();
                    shipyard.offButton();
                    explore.offButton();
                    research.offButton();
                    setBackground("black.png");
                    map_open = true;
                    close_map.onButton();
                }
            }
            else if(map_open)
            {
                if(close_map.detectEvent(x, y))
                {
                    main_menu = true;
                    new_turn.onButton();
                    attack.onButton();
                    colonize.onButton();
                    shipyard.onButton();
                    explore.onButton();
                    research.onButton();
                    setBackground(DEFAULT_BACKGROUND);
                    map_open = false;
                    close_map.offButton();
                    explore_sector.offButton();
                    field.delFocus();
                }
                else if(explore_sector.detectEvent(x, y))
                {
                    action_handler(EXPLORATION);
                }
                else
                {
                    field.handleClick(x, y);
                    if(field.isInvestigatable(x, y))
                        explore_sector.onButton();
                    else
                        explore_sector.offButton();
                }
            }
        }

        if( log_tab.detectEvent(x, y) )
        {
            logger_off ^= true;
            if(logger_off)
            {
                log_tab.setImage("button1.png", true);
                if(ship.ship_list_opened)
                    construction_mode = LOADING_SHIP;
                else
                    construction_mode = OVERVIEW_MODE;
            }
            else
            {
                log_tab.setImage("button2.png", true);
                construction_mode = LOG_OPEN;
            }
        }

        top_scroller.clickHandler(x, y);
        if(top_scroller.isMoving())
            updTopMenu();

        if(research_open)
        {
            if(x <= SCREEN_WIDTH / 3)
            {
                tree_scroller.clickHandler(x, y);

                int max_index = static_cast<int> ((SCREEN_HEIGHT - 80) / 25 + 1);
                for(int index = 0; index < max_index; index++)
                {
                    if(!(x > technologies[tree_render_pos[index].first].lvl * 10 + 11 ||
                         x < technologies[tree_render_pos[index].first].lvl * 10 ||
                         y > tree_render_pos[index].second + 11 || y < tree_render_pos[index].second))
                    {
                        if(technologies[tree_render_pos[index].first].children_count != 0)
                            technologies[tree_render_pos[index].first].opened ^= true;
                        break;
                    }
                    else if(x >= technologies[tree_render_pos[index].first].lvl * 10 + 15 &&
                         x < SCREEN_WIDTH / 3 - 20 &&
                         y <= tree_render_pos[index].second + 21 && y >= tree_render_pos[index].second - 3)
                    {
                        research_index = tree_render_pos[index].first;
                        action_handler(DO_RESEARCH);
                        break;
                    }
                }
            }
            else if(change_tree.detectEvent(x, y))
            {
                tree_button_state ^= true;
                if(tree_button_state)
                {
                    change_tree.setImage("show_tree.png" , true);
                    for(int i = 1; i < TECHNOLOGIES_COUNT; i++)
                        technologies[i].opened = false;
                }
                else
                {
                    change_tree.setImage("hide_tree.png" , true);
                    for(int i = 1; i < TECHNOLOGIES_COUNT; i++)
                        if(technologies[i].children_count != 0)
                            technologies[i].opened = true;
                }
            }
        }
    }

    bool isMainMenu()
    {
        return main_menu;
    }

    bool isShipyard()
    {
        return shipyard_open;
    }

    void closeShipyard()
    {
        shipyard_open = false;
        main_menu = true;
        back_from_yard_to_main_menu.offButton();
        new_turn.onButton();
        attack.onButton();
        colonize.onButton();
        shipyard.onButton();
        explore.onButton();
        research.onButton();
    }

    void handleWheel(int dir, int x, int y)
    {
        if(research_open && logger_off)
        {
            if( !(x > SCREEN_WIDTH / 3 || y < 80) )
            {
                tree_scroller.setPosition( -0.05 * dir, true );
            }
        }
    }

    void render()
    {
        if(!shipyard_open)
            background.render(1.5);
        else
        {
            ship.render();
        }

        if(map_open)
        {
            field.render();
            close_map.render();
            explore_sector.render();
        }

        research.render();
        change_tree.render();
        attack.render();
        new_turn.render();

        explore.render();
        shipyard.render();
        colonize.render();

        back_from_yard_to_main_menu.render();

        if(colonize.isOn())
        {
            colonize1.render();
            colonize2.render();
        }
        if(shipyard.isOn())
        {
            shipyard1.render();
            shipyard2.render();
        }
        if(explore.isOn())
        {
            seek1.render();
            seek2.render();
        }

        if(!logger_off)
        {
            background_filter.render(1.5);
        }

        log_tab.render();

        SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, 80 };
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 175 );
        SDL_RenderFillRect( renderer, &fillRect );

        human_count.render();

        res_counter.render();
        research_points.render();
        res_per_round.render();
        science_per_round.render();
        if(main_menu || research_open)
            actions.render();

        top_scroller.render();

        if(research_open)
        {
            y_offset = 0;
            global_shift = 8;
            tree_render_pos_index = 0;
            node_is_shifted = false;
            double tree_height = technologies[0].getChildrenHeight();
            if(tree_height < SCREEN_HEIGHT - 80)
                research_tree_offset = 1;
            else
                research_tree_offset = (tree_height + 80 - SCREEN_HEIGHT) * tree_scroller.getVal() + 1;
            //std::cout<<tree_height<<" "<<research_tree_offset<<std::endl;

            SDL_RenderSetViewport( renderer, &tree_viewport );
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 0xFF );
            technologies[0].render(true);
            SDL_RenderSetViewport( renderer, nullptr );

            tree_scroller.render();
        }

        SDL_GetMouseState( &mouseX, &mouseY );

        if(research_open && mouseX < SCREEN_WIDTH / 3 - 20)
        {
            for(int i = 1; i < tree_render_pos_index; i++)
            {
                if(!(mouseX > SCREEN_WIDTH / 3 || mouseX < technologies[tree_render_pos[i].first].lvl * 10 + 20 ||
                     mouseY > tree_render_pos[i].second + 25 - 4 || mouseY < tree_render_pos[i].second - 4))
                {
                    fillRect.x = technologies[tree_render_pos[i].first].lvl * 10 + 20;
                    fillRect.y = tree_render_pos[i].second - 4;
                    fillRect.w = SCREEN_WIDTH / 3 - fillRect.x - 20;
                    fillRect.h = 25;

                    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 50 );
                    SDL_RenderFillRect( renderer, &fillRect );

                    fillRect.x = SCREEN_WIDTH / 3 + 10;
                    fillRect.y = 85;
                    fillRect.w = SCREEN_WIDTH / 3;
                    fillRect.h = SCREEN_HEIGHT - 90;
                    SDL_SetRenderDrawColor( renderer, 76, 88, 102, 255 );
                    SDL_RenderFillRect( renderer, &fillRect );

                    SDL_RenderSetViewport( renderer, &fillRect );

                    WrapTexture tech_info;
                    tech_info.loadFromRenderedText(technologies[tree_render_pos[i].first].name, WHITE, 1, false);
                    tech_info.render(5, 5);

                    fillRect.x = SCREEN_WIDTH / 3 - 50;
                    fillRect.y = 0;
                    fillRect.w = 50;
                    fillRect.h = 50;
                    if(technologies[tree_render_pos[i].first].research_progress != 0)
                        if(technologies[tree_render_pos[i].first].research_progress == technologies[tree_render_pos[i].first].max_progress)
                        {
                            SDL_SetRenderDrawColor( renderer, 0, 128, 0, 255 );
                            SDL_RenderFillRect( renderer, &fillRect );
                        }
                        else
                        {
                            SDL_SetRenderDrawColor( renderer, 150, 150, 150, 255 );
                            SDL_RenderFillRect( renderer, &fillRect );
                            tech_info.loadFromRenderedText(toString(technologies[tree_render_pos[i].first].research_progress), YELLOW, 2, false);
                            tech_info.render(SCREEN_WIDTH / 3 - 40, 5);
                        }
                    else
                    {
                        SDL_SetRenderDrawColor( renderer, 200, 0, 0, 255 );
                        SDL_RenderFillRect( renderer, &fillRect );
                    }

                    //output tech description text
                    tech_descr.render();
                    technologies[tree_render_pos[i].first].render_descr();

                    //output tech access list //TODO print new modules/hulls and so on
                    tech_unlocks.render(25, 130);
                    for(int j = 0; j < technologies[tree_render_pos[i].first].children_count; j++)
                    {
                        tech_info.loadFromRenderedText(technologies[tree_render_pos[i].first].get_children_name(j), BLACK, 3, false);
                        tech_info.render(15, 160 + 20 * j);
                    }

                    //output tech needs list
                    if(technologies[tree_render_pos[i].first].research_progress == technologies[tree_render_pos[i].first].max_progress)
                        tech_info.loadFromRenderedText("Maximum research level", GREEN, 3, false);
                    else if(science_points >= technologies[tree_render_pos[i].first].getCost())
                        tech_info.loadFromRenderedText("Upgrade cost: " + toString(technologies[tree_render_pos[i].first].getCost()) + " tech points", WHITE, 3, false);
                    else
                        tech_info.loadFromRenderedText("Upgrade cost: " + toString(technologies[tree_render_pos[i].first].getCost()) + " tech points", RED, 3, false);

                    tech_requir.render(25, 170 + 20 * technologies[tree_render_pos[i].first].children_count);
                    tech_info.render(15, 200 + 20 * technologies[tree_render_pos[i].first].children_count);
                    technologies[tree_render_pos[i].first].printRequirements(190 + 20 * technologies[tree_render_pos[i].first].children_count);

                    SDL_RenderSetViewport( renderer, nullptr );

                    break;
                }
            }
        }

        //if mode == something && tips exist -> render tips if mouse here; tips #0 and #1 actual for any mode
        tips[0].render(mouseX, mouseY);
        tips[1].render(mouseX, mouseY);
        if(shipyard_open && construction_mode == OVERVIEW_MODE)
        {
            tips[2].render(mouseX, mouseY);
            if(resourses <= ship.ship_cost_res)
                tips[3].render(mouseX, mouseY);
            else if(people <= ship.ship_cost_staff)
                tips[4].render(mouseX, mouseY);
            else if(action_points <= 0)
                tips[5].render(mouseX, mouseY);
        }
        if(map_open)
        {
            tips[6].render(mouseX, mouseY);
            tips[7].render(mouseX, mouseY);
            tips[8].render(mouseX, mouseY);
            if(action_points <= 0)
                tips[9].render(mouseX, mouseY);
        }
    }

    void render_cursor()
    {
        SDL_GetMouseState( &mouseX, &mouseY );
        cursor.render(mouseX, mouseY);
    }

} MENU;
