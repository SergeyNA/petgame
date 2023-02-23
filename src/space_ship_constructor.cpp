const int ship_load_list_height = SCREEN_HEIGHT - SCREEN_HEIGHT / 4 - 80;
const int ship_load_list_width = 252;
const int ship_load_list_members = (ship_load_list_height - 10 - 15 ) / 20;

struct space_ship_constructor
{
    Uint8 *ship_hull = nullptr;
    WrapTexture ship_texture;
    int x_offset = 100;
    int y_offset = 100;
    int x_offset_old;
    int y_offset_old;

    std::vector<std::string> ship_names = {"Human_1"};

    int ship_save_index = 9;
    // 51 main (uncomment, dim); 14 (add hull name); 16 (name index); 64 game logic (add params); 45, 46, 47 (dim); create *.png

    double scale[11] = {0.1, 0.2, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 8.0};
    int cellSize[11] = {1, 2, 5, 10, 15, 20, 25, 30, 40, 50, 80};
    int ci = 5;

    int dimX;
    int dimY;

    bool ship_move = false;
    int moveStartX;
    int moveStartY;

    bool visible_grid = true;

    Button open_ship_list;
    bool ship_list_animation = false;
    bool ship_list_opened = false;
    SDL_Rect ship_list_viewport;
    Scroller ship_list_scroller;

    //Ship stats:
    WrapTexture ship_name;
    WrapTexture ship_title;
    WrapTexture ship_cost_text;
    WrapTexture ship_cost_title;
    int ship_cost_res;
    int ship_cost_staff;
    int ship_cost_actions;
    WrapTexture ship_power_text;
    WrapTexture ship_power_title;
    int ship_power;

    Button build_spaceship;

    bool init()
    {
        if(!ship_cost_title.loadFromRenderedText("Ship cost: ", WHITE, 3))
            return false;
        ship_cost_title.setRenderPos(SCREEN_WIDTH * 3 / 4 - 20 + 5, 90 + 60);
        if(!ship_power_title.loadFromRenderedText("Ship power: ", WHITE, 3))
            return false;

        open_ship_list.setImage("Open_ships_list.png", true);
        open_ship_list.setPos(SCREEN_WIDTH * 3 / 4 - ship_load_list_width, SCREEN_HEIGHT - 70);
        build_spaceship.setImage("build.png", true);
        build_spaceship.setPos(SCREEN_WIDTH / 2 - ship_load_list_width, SCREEN_HEIGHT - 70);

        ship_list_viewport.x = SCREEN_WIDTH * 3 / 4 - ship_load_list_width;
        ship_list_viewport.y = SCREEN_HEIGHT - 70;
        ship_list_viewport.h = ship_load_list_height;
        ship_list_viewport.w = ship_load_list_width;

        return true;
    }

    void load_ship( unsigned int name_index = 0, bool grid_creation_mode = false)
    {
        if(ship_hull != nullptr)
            delete[] ship_hull;

        if(grid_creation_mode)
        {
            ship_hull = new Uint8[25 * 54]();
            dimX = 25;
            dimY = 54;
            ship_name.loadFromRenderedText("New hull creation mode", WHITE, 3);
            ship_cost_res = 0;
            ship_cost_staff = 0;
            ship_power = 0;
            ship_cost_actions = 0;
        }
        else
        {
            std::ifstream ships_data;
            ships_data.open("data/ships_data.txt");
            if(!ships_data.is_open())
                std::cout << "Coudn't load hull data: \"ships_data.txt\" not open" << std::endl;

            std::string s = "bla bla";
            int temp;

            ship_name.loadFromRenderedText("New spaceship", WHITE, 3);

            while(ships_data.good())
            {
                ships_data >> s;
                ships_data >> dimX >> dimY >> ship_cost_res >> ship_cost_actions;
                ship_power = dimX * dimY;
                ship_cost_staff = name_index + 1;

                if(s == ship_names[name_index])
                {
                    ship_hull = new Uint8[dimX * dimY]();
                    std::getline(ships_data, s);
                    for(int j = 0; j < dimY; j++)
                        for(int i = 0; i < dimX; i++)
                        {
                            ships_data >> temp;
                            ship_hull[i + dimX * j] = temp;
                        }
                    break;
                }
                else
                {
                    std::getline(ships_data, s);
                    for(int j = 0; j < dimY; j++)
                        for(int i = 0; i < dimX; i++)
                            ships_data >> temp;
                    std::getline(ships_data, s);
                }
            }

            ships_data.close();
        }

        ship_title.loadFromRenderedText("Hull type: " + ship_names[name_index], WHITE, 3);
        ship_texture.loadFromFile("ships/" + ship_names[name_index] + ".png", true);
    }

    void clear_()
    {
        if(ship_hull != nullptr)
            delete[] ship_hull;
        ship_hull = nullptr;
        open_ship_list.offButton();
        build_spaceship.offButton();
    }

    void render()
    {
        ship_texture.render(x_offset, y_offset, scale[ci]);

        if(visible_grid)
        {
            for(int i = 0; i < dimX; i++)
            {
                for(int j = 0; j < dimY; j++)
                {
                    SDL_Rect fillRect = { x_offset + i * cellSize[ci], y_offset + j * cellSize[ci], cellSize[ci], cellSize[ci] };
                    switch(ship_hull[j * dimX + i])
                    {
                        case 1:
                        SDL_SetRenderDrawColor( renderer, 0, 150, 0, 150 );
                        SDL_RenderFillRect( renderer, &fillRect );
                        break;
                        case 2:
                        SDL_SetRenderDrawColor( renderer, 150, 0, 0, 150 );
                        SDL_RenderFillRect( renderer, &fillRect );
                        break;
                        case 3:
                        SDL_SetRenderDrawColor( renderer, 0, 0, 150, 150 );
                        SDL_RenderFillRect( renderer, &fillRect );
                        break;
                        case 4:
                        SDL_SetRenderDrawColor( renderer, 150, 150, 0, 150 );
                        SDL_RenderFillRect( renderer, &fillRect );
                    }
                }
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 50 );
                SDL_RenderDrawLine( renderer, x_offset + i * cellSize[ci], y_offset,
                    x_offset + i * cellSize[ci], y_offset + cellSize[ci] * dimY );
            }
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 50 );
            for(int i = 0; i < dimY + 1; i++)
                SDL_RenderDrawLine( renderer, x_offset, y_offset + i * cellSize[ci],
                    x_offset + cellSize[ci] * dimX, y_offset + i * cellSize[ci]);
            SDL_RenderDrawLine( renderer, x_offset + dimX * cellSize[ci], y_offset,
                    x_offset + dimX * cellSize[ci], y_offset + cellSize[ci] * dimY );
        }

        if(ship_list_opened || ship_list_animation)
        {
            if(ship_list_animation)
            {
                if(ship_list_opened)
                {
                    ship_list_viewport.y -= 10;
                    if(ship_list_viewport.y <= SCREEN_HEIGHT - 70 - ship_load_list_height + 6)
                    {
                        ship_list_animation = false;
                        ship_list_viewport.y = SCREEN_HEIGHT - 70 - ship_load_list_height + 6;
                        if( ship_names.size() > static_cast<unsigned int>(ship_load_list_members))
                            ship_list_scroller.on();
                    }
                }
                else
                {
                    ship_list_viewport.y += 10;
                    if(ship_list_viewport.y >= SCREEN_HEIGHT - 70)
                    {
                        ship_list_animation = false;
                        ship_list_viewport.y = SCREEN_HEIGHT - 70;
                    }
                }
            }

            SDL_RenderSetViewport( renderer, &ship_list_viewport );
            SDL_Rect fillRect = { 0, 0, ship_load_list_width, ship_load_list_height };
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 150 );
            SDL_RenderFillRect( renderer, &fillRect );

            WrapTexture hull_name;
            int elem_count = 0;
            int frst_output_index = static_cast<int>((ship_names.size() - ship_load_list_members) * ship_list_scroller.getVal());
            for(unsigned int i = frst_output_index; i < ship_names.size(); i++)
            {
                hull_name.loadFromRenderedText(ship_names[i], WHITE, 3, false);
                hull_name.render(10, 8 + 20 * elem_count++);
                if(elem_count == ship_load_list_members)
                    break;
            }

            if(!ship_list_animation && construction_mode == LOADING_SHIP)
            {
                int x, y;
                SDL_GetMouseState( &x, &y );
                if( !(x > SCREEN_WIDTH * 3 / 4 - 20 ||  x < SCREEN_WIDTH * 3 / 4 - ship_load_list_width ||
                      y < SCREEN_HEIGHT - ship_load_list_height - 70 + 6) )
                {
                    y -= SCREEN_HEIGHT - ship_load_list_height - 70 + 12;
                    if(y < 20 * static_cast<int>(ship_names.size()) )
                    {
                        fillRect.h = 20;
                        fillRect.w = ship_load_list_width - 22;
                        fillRect.x = 4;
                        fillRect.y = y - y % 20 + 5;
                        SDL_SetRenderDrawColor( renderer, 0, 0, 220, 100 );
                        SDL_RenderFillRect( renderer, &fillRect );
                    }
                }
            }

            SDL_RenderSetViewport( renderer, nullptr );
        }

        if(construction_mode == OVERVIEW_MODE)
        {
            SDL_Rect ship_info_background = { SCREEN_WIDTH * 3 / 4 - 20, 90, SCREEN_WIDTH / 4 + 10, SCREEN_HEIGHT - 200 };
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 150 );
            SDL_RenderFillRect( renderer, &ship_info_background );

            SDL_RenderSetViewport( renderer, &ship_info_background );

            ship_name.render(5, 10);
            ship_title.render(5, 30);
            //ship_cost_title.render(5, 60);
            ship_cost_text.loadFromRenderedText(toString(ship_cost_res) + "/" + toString(ship_cost_staff) + "/" + toString(ship_cost_actions), WHITE, 3, false);
            ship_cost_text.render(110, 60);
            ship_power_title.render(5, 80);
            ship_power_text.loadFromRenderedText(toString(ship_power), WHITE, 3, false);
            ship_power_text.render(120, 80);

            SDL_RenderSetViewport( renderer, nullptr );
            ship_cost_title.render(); //it's have got "set render pos" at init with abs viewport, because of tip exist...

            build_spaceship.render(); //button
        }

        ship_list_scroller.render();
        open_ship_list.render(); // this is the button
    }

    void handleClick(int x, int y)
    {
        if(open_ship_list.detectEvent(x, y) && construction_mode != LOG_OPEN) //open ship load list
        {
            ship_list_opened ^= true;
            ship_list_animation = true;
            if(ship_list_opened)
            {
                open_ship_list.setImage("Close_ships_list.png", true);
                construction_mode = LOADING_SHIP;
            }
            else
            {
                open_ship_list.setImage("Open_ships_list.png", true);
                construction_mode = OVERVIEW_MODE;
                ship_list_scroller.off();
            }
        }

        else if(build_spaceship.detectEvent(x, y) && construction_mode == OVERVIEW_MODE)
        {
            if(action_points >= 0 && resourses >= ship_cost_res && people >= ship_cost_staff)
                action_handler(BUILD_SHIP);
        }

        else if(construction_mode == CREATE_HULL_MODE) //change square color
        {
            if(x >= x_offset && x <= x_offset + dimX * cellSize[ci])
                if(y >= y_offset && y <= y_offset + dimY * cellSize[ci])
                {
                    ship_hull[ static_cast<int>( (x - x_offset) / cellSize[ci]) +
                        static_cast<int>( (y - y_offset) / cellSize[ci]) * dimX]++;
                    if(ship_hull[ static_cast<int>( (x - x_offset) / cellSize[ci]) +
                            static_cast<int>( (y - y_offset) / cellSize[ci]) * dimX] > 4)
                        ship_hull[ static_cast<int>( (x - x_offset) / cellSize[ci]) +
                            static_cast<int>( (y - y_offset) / cellSize[ci]) * dimX] = 0;
                }
        }

        else if(construction_mode == LOADING_SHIP) //load new hull
        {
            if(x > SCREEN_WIDTH * 3 / 4 - ship_load_list_width + 4 && x < SCREEN_WIDTH * 3 / 4 - 22)
            {
                y -= SCREEN_HEIGHT - ship_load_list_height - 70 + 12;
                if(y > 0 && y < ship_load_list_height - 28)
                {
                    int index = (ship_names.size() - ship_load_list_members) * ship_list_scroller.getVal() + (int) (y / 20);
                    if( index >= 0 && index < static_cast<int>(ship_names.size()) )
                        load_ship(index);
                }
            }
        }

        ship_list_scroller.clickHandler(x, y);
    }

    void handleWheel(int dir, int x, int y)
    {
        if(construction_mode == OVERVIEW_MODE)
        {
            if(dir > 0)
            {
                ci++;
                if(ci > 10)
                    ci = 10;
                else
                {
                    x_offset = x + static_cast<int>( (x_offset - x) * scale[ci] / scale[ci - 1]);
                    y_offset = y + static_cast<int>( (y_offset - y) * scale[ci] / scale[ci - 1]);
                }
            }
            else
            {
                ci--;
                if(ci < 0)
                    ci = 0;
                else
                {
                    x_offset = x + static_cast<int>( (x_offset - x) * scale[ci] / scale[ci + 1]);
                    y_offset = y + static_cast<int>( (y_offset - y) * scale[ci] / scale[ci + 1]);
                }
            }
        }
        else if(construction_mode == LOADING_SHIP && ship_list_scroller.isActive())
        {
            if( !(x > SCREEN_WIDTH * 3 / 4 ||  x < SCREEN_WIDTH * 3 / 4 - ship_load_list_width || y < SCREEN_HEIGHT - ship_load_list_height - 70 + 6) )
            {
                ship_list_scroller.setPosition( -0.05 * dir, true );
            }
        }
    }

    void save_ship(int xDim, int yDim)
    {
        std::ofstream ships_data;
        ships_data.open("ships_data.txt", std::ios::app);

        int cell_count = 0;
        for(int j = 0; j < yDim; j++)
            for(int i = 0; i < xDim; i++)
                if(ship_hull[i + j * dimX])
                    cell_count++;

        ships_data << ship_names[ship_save_index] << std::endl << xDim << " " << yDim << " " << cell_count << " 1" << std::endl;

        for(int j = 0; j < yDim; j++)
        {
            for(int i = 0; i < xDim; i++)
                ships_data << static_cast<int>(ship_hull[i + j * dimX]) << " ";
            ships_data << std::endl;
        }

        ships_data.close();
    }

    void moving_ship(int x, int y)
    {
        if(construction_mode != LOG_OPEN)
        {
            x_offset = x_offset_old - (moveStartX - x);
            y_offset = y_offset_old - (moveStartY - y);
        }
    }

    ~space_ship_constructor()
    {
        if(ship_hull != nullptr)
            delete[] ship_hull;
    }

} ship;
