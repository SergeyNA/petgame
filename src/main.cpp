#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <vector>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "resources_controller.h"

#include "SDL_func.cpp"
/*#include "Tips.cpp"
#include "Research_tree.cpp"
#include "Scroller.cpp"
#include "Fleet.cpp"
#include "space_ship_constructor.cpp"
#include "Planet.cpp"
#include "map.cpp"
#include "Interface.cpp"
#include "Logger.cpp"
#include "game_logic.cpp"*/

bool game_res_init()
{
    if(!loadFont("courier", 20, 0))
        return false;
    if(!loadFont("block", 20, 1))
        return false;
    if(!loadFont("block", 40, 2))
        return false;
    if(!loadFont("courier", 16, 3))
        return false;

    resourses = 5000;
    science_points = 100000;
    people = 100;
    action_limits = 5;
    action_points = 5;

    /*if(!ship.init())
        return false;

    if(!MENU.init())
        return false;

    LOG.add_message("Game start! Your's turn...", WHITE, 0);
    if(!LOG.log_scroller.setImage("Scroller-icon.png", true))
        return false;
    LOG.log_scroller.setPos( SCREEN_WIDTH * 3 / 4 - 15, SCREEN_HEIGHT / 2 - 10 );

    close_branch.loadFromFile("research_trig_close.png", true);
    open_branch.loadFromFile("research_trig_open.png", true);

    fleets.push_back(Fleet(9, 3));

    technologies[0].init("ROOT", 0, 0, 0, new int[1]{0});
    technologies[0].setChildren(new int[5]{1, 2, 3, 4, 5}, 5);
    technologies[0].opened = true;

    for(int i = 0; i < static_cast<int> ((SCREEN_HEIGHT - 80) / 25); i++)
        tree_render_pos[i] = std::make_pair( i, -20);

    technologies[1].init("Hulls", 1, 1, 10, new int[10]{100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000});
    technologies[2].init("Weapons", 2, 1, 10, new int[10]{100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000});
    technologies[3].init("Engines", 3, 1, 10, new int[10]{100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000});
    technologies[4].init("Theoretics", 4, 1, 10, new int[10]{100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000});
    technologies[5].init("Supply", 5, 1, 10, new int[10]{100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000});

    technologies[6].init("Frigate", 6, 2, 5, new int[5]{1000, 1500, 2000, 5000, 25000});
    technologies[7].init("Destroyer", 7, 2, 5, new int[5]{2500, 5000, 10000, 20000, 50000});
    technologies[8].init("Shunting Engine", 8, 2, 1, new int[1]{1000});
    technologies[9].init("Subspace Communication", 9, 2, 1, new int[1]{1000});
    technologies[10].init("Inertial Dampers", 10, 2, 1, new int[1]{1000});
    technologies[11].init("Anti-Matter", 11, 2, 1, new int[1]{1000});
    technologies[12].init("Electromagnetic Manipulations", 12, 2, 1, new int[1]{1000});
    technologies[17].init("Cruiser", 17, 2, 5, new int[5]{5000, 5000, 10000, 15000, 25000});
    technologies[18].init("BattleCruiser", 18, 2, 5, new int[5]{10000, 5000, 10000, 15000, 25000});
    technologies[19].init("BattleShip", 19, 2, 5, new int[5]{25000, 10000, 25000, 5000, 100000});
    technologies[20].init("CapitalShip", 20, 2, 5, new int[5]{50000, 25000, 40000, 80000, 150000});
    technologies[21].init("MotherShip", 21, 2, 5, new int[5]{75000, 25000, 50000, 100000, 200000});
    technologies[22].init("Titan", 22, 2, 5, new int[5]{100000, 100000, 125000, 150000, 250000});
    technologies[25].init("Energy", 25, 2, 5, new int[5]{1000, 1500, 2500, 5000, 10000});
    technologies[26].init("Shield", 26, 2, 5, new int[5]{2500, 1500, 5000, 10000, 25000});
    technologies[31].init("Supply Bay", 31, 2, 1, new int[1]{100});
    technologies[32].init("Repair Drone", 32, 2, 1, new int[1]{1000});
    technologies[37].init("Fast Supply Lines", 37, 2, 10, new int[10]{250, 500, 1500, 2500, 5000, 10000, 25000, 50000, 100000, 200000});
    technologies[38].init("Long-term Planning", 38, 2, 1, new int[1]{1000});
    technologies[39].init("Military Scout", 39, 2, 1, new int[1]{2500});

    technologies[1].setChildren(new int[8]{6, 7, 17, 18, 19, 20, 21, 22}, 8);
    technologies[3].setChildren(new int[1]{8}, 1);
    technologies[4].setChildren(new int[6]{25, 9, 10, 11, 12, 38}, 6);
    technologies[5].setChildren(new int[5]{26, 31, 32, 37, 39}, 5);

    technologies[13].init("Sublight Acceleration", 13, 3, 1, new int[1]{5000});
    technologies[14].init("Antimatter Shell", 14, 3, 1, new int[1]{5000});
    technologies[15].init("Antimatter Energy", 15, 3, 1, new int[1]{5000});
    technologies[16].init("Antimatter Emission", 16, 3, 1, new int[1]{5000});
    technologies[23].init("Fighter", 23, 3, 3, new int[3]{500, 1000, 5000});
    technologies[24].init("Bomber", 24, 3, 1, new int[1]{5000});
    technologies[27].init("Fighter Shields", 27, 3, 1, new int[1]{1500});
    technologies[28].init("Heavy Shield", 28, 3, 1, new int[1]{5000});
    technologies[29].init("SuperHeavy Shield", 29, 3, 1, new int[1]{10000});
    technologies[30].init("Colossal Shield", 30, 3, 1, new int[1]{25000});
    technologies[33].init("Large Supply Bay", 33, 3, 1, new int[1]{500});
    technologies[34].init("Extended Supply Bay", 34, 3, 1, new int[1]{1000});
    technologies[35].init("Ordnance Fabricator", 35, 3, 1, new int[1]{1000});

    technologies[8].setChildren(new int[1]{13}, 1);
    technologies[11].setChildren(new int[3]{14, 15, 16}, 3);
    technologies[6].setChildren(new int[2]{23, 24}, 2);
    technologies[31].setChildren(new int[3]{33, 34, 35}, 3);

    technologies[36].init("Large Ordnance Fabricator", 36, 4, 1, new int[1]{2500});

    technologies[35].setChildren(new int[1]{36}, 1);

    //technologies[0].print();

    technologies[26].setRequirements(new std::pair<int, int>[1]{std::make_pair(25, 3)}, 1);
    technologies[38].setRequirements(new std::pair<int, int>[2]{std::make_pair(37, 1), std::make_pair(9, 1)}, 2);*/

    return true;
}

int main(int argc, char* argv[])
{
    if(!SDL_initialaize())
        return 1;

    if(!game_res_init())
        return 2;

    SDL_Event e;

    while(true)
    {
        SDL_RenderClear(renderer);

        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
                goto endgame;

            else if( e.type == SDL_KEYDOWN )
            {
                switch(e.key.keysym.sym) {
                case SDLK_q:
                    goto endgame;
                /*case SDLK_m:
                    LOG.add_message("Some event " + toString(LOG.getMessageCount()), static_cast<font_colors>(rand()%5), 0);
                    break;
                case SDLK_r:
                    if(MENU.isShipyard())
                    {
                        ship.x_offset = 0;
                        ship.y_offset = 80;
                        ship.ci = 3;
                    }
                    break;*/
                //===========case SDLK_s:
                //    if(MENU.isShipyard())
                //    {
                //        ship.save_ship(25, 54);
                //    }
                //===========    break;
                /*case SDLK_e:
                    if( MENU.isShipyard() )
                    {
                        MENU.closeShipyard();
                        ship.clear_();
                    }
                    else if(MENU.isMap())
                        MENU.handleClick(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150);
                    break;
                case SDLK_v:
                    if( MENU.isShipyard() )
                        ship.visible_grid ^= true;
                    break;*/
                case SDLK_f:
                    if(FULLSCREEN)
                    {
                        SDL_SetWindowFullscreen(window , 0);
                    }
                    else
                    {
                        SDL_SetWindowFullscreen(window , SDL_WINDOW_FULLSCREEN);
                    }
                    FULLSCREEN ^= true;
                    break;
                /*case SDLK_SPACE:
                    if(MENU.isMainMenu())
                        action_handler(GAME_NEW_TURN);
                    break;
                case SDLK_a:
                    if(MENU.isMainMenu())
                        action_handler(GAME_ATTACK);
                    break;
                case SDLK_KP_PLUS:
                    MENU.top_scroller.setPosition(0.1, true);
                    MENU.updTopMenu();
                    break;
                case SDLK_KP_MINUS:
                    MENU.top_scroller.setPosition(-0.099, true);
                    MENU.updTopMenu();
                    break;*/
                default:
                    printf("Physical %s key acting as %s key\n",
                        SDL_GetScancodeName(e.key.keysym.scancode),
                            SDL_GetKeyName(e.key.keysym.sym));
                }
            }

            /*else if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x, y;
                SDL_GetMouseState( &x, &y );

                if(MENU.isShipyard())
                {
                    if(e.button.button == SDL_BUTTON_RIGHT)
                    {
                        SDL_GetMouseState( &ship.moveStartX, &ship.moveStartY );
                        ship.x_offset_old = ship.x_offset;
                        ship.y_offset_old = ship.y_offset;
                        ship.ship_move = true;
                    }
                    else
                    {
                        if(!log_tab.detectEvent(x, y))
                            ship.handleClick(x, y);
                    }
                }
                MENU.handleClick(x, y);
                LOG.handleClick(x, y);
            }*/

            /*else if( e.type == SDL_MOUSEWHEEL )
            {
                int x, y;
                SDL_GetMouseState( &x, &y );
                int dir = e.wheel.y;
                //=============std::cout << "y = " << dir << std::endl;

                MENU.handleWheel(dir, x, y);
                LOG.handleWheel(dir, x, y);
                if(MENU.isShipyard() && MENU.isLogDisabled())
                    ship.handleWheel(dir, x, y);
            }

            else if( scroll_move )
            {
                if(MENU.top_scroller.isMoving())
                    MENU.updTopMenu();

                if(e.type == SDL_MOUSEBUTTONUP)
                {
                    scroll_move = false;
                    //==========MENU.scroller2.setMoveFalse();
                    MENU.tree_scroller.setMoveFalse();
                    MENU.top_scroller.setMoveFalse();
                    ship.ship_list_scroller.setMoveFalse();
                }
                if(e.type == SDL_MOUSEMOTION)
                {
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    MENU.top_scroller.clickHandler2(x, y);
                    MENU.tree_scroller.clickHandler2(x, y);
                    ship.ship_list_scroller.clickHandler2(x, y);
                    //=============MENU.scroller2.clickHandler2(x, y);
                }
            }

            else if( MENU.isShipyard() )
            {
                if(e.type == SDL_MOUSEBUTTONUP)
                {
                    ship.ship_move = false;
                }
                if(ship.ship_move)
                {
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    ship.moving_ship(x, y);
                }
            }*/
        }

        //MENU.render();
        //LOG.render();
        //MENU.render_cursor();
        //==============SDL_SetRenderDrawColor( renderer, 0, 150, 0, 255 ); //background color

        SDL_RenderPresent(renderer);
    }

endgame:

    Close_SDL();

    return 0;
}
