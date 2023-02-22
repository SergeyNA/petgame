class Logger
{
private:

    static const int LOG_size = 100;
    static const int LOG_disp = SCREEN_HEIGHT / 2 / 25;
    static const int LOG_ANIMATION_SPEED = 10;
    static const int LOG_height = SCREEN_HEIGHT / 2;
    static const int LOG_width = SCREEN_WIDTH * 3 / 4;

    int log_scroll_button_posY = SCREEN_HEIGHT - 1;
    unsigned int message_count = 0;

    WrapTexture* log_messages;

    bool log_animation;

    SDL_Rect log_viewport;
    int log_pos;

    void print_log(int shift)
    {
        int counter = LOG_disp;
        int index = log_pos - shift;
        while(counter-- > 0)
        {
            if(--index < 0)
                index += LOG_size;
            if(log_messages[index].exist())
            {
                log_messages[index].render(25, LOG_height - 25 * (LOG_disp - counter));
            }
        }
    }

public:

    Button log_scroller;

    Logger()
    {
        log_viewport.x = 0;
        log_viewport.y = SCREEN_HEIGHT;
        log_viewport.w = LOG_width + 2;
        log_viewport.h = LOG_height;
        log_animation = false;
        log_pos = 0;
        log_messages = new WrapTexture[LOG_size]();
    };
    ~Logger()
    {
        delete[] log_messages;
    };

    void handleClick(int x, int y)
    {
        if(!MENU.isLogDisabled() && !(x < LOG_width - 10 || x > LOG_width || y <= SCREEN_HEIGHT - LOG_height) )
        {
            log_scroll_button_posY = y;
            log_scroller.setPos(LOG_width - 15, log_scroll_button_posY - 10 - SCREEN_HEIGHT + LOG_height);
        }

        if( !(x < SCREEN_WIDTH - 270 || y < SCREEN_HEIGHT - 100) )
        {
            log_animation = true;
        }
    }

    void handleWheel(int dir, int x, int y)
    {
        if(!MENU.isLogDisabled())
        {
            if( !(x > SCREEN_WIDTH * 3 / 4 || y < SCREEN_HEIGHT - LOG_height) )
            {
                log_scroll_button_posY -= dir * 3 * LOG_height / LOG_size;
                if(log_scroll_button_posY < SCREEN_HEIGHT - LOG_height)
                    log_scroll_button_posY = SCREEN_HEIGHT - LOG_height;
                else if(log_scroll_button_posY > SCREEN_HEIGHT - 1)
                    log_scroll_button_posY = SCREEN_HEIGHT - 1;
                log_scroller.setPos(LOG_width - 15, log_scroll_button_posY - 10 - SCREEN_HEIGHT + LOG_height);
            }
        }
    }

    void add_message(std::string text, font_colors c, int font_index)
    {
        message_count++;
        log_messages[log_pos].loadFromRenderedText(text, c, font_index);
        if(++log_pos == LOG_size)
            log_pos = 0;
    }

    unsigned int getMessageCount()
    {
        return message_count;
    }

    void render()
    {
        if(log_animation || !MENU.isLogDisabled())
        {
            if(MENU.isLogDisabled())
            {
                log_viewport.y += LOG_ANIMATION_SPEED;
                if(log_viewport.y >= SCREEN_HEIGHT)
                {
                    log_animation = false;
                    log_viewport.y = SCREEN_HEIGHT;
                }
            }
            else
            {
                log_viewport.y -= LOG_ANIMATION_SPEED;
                if(log_viewport.y <= SCREEN_HEIGHT - LOG_height)
                {
                    log_animation = false;
                    log_viewport.y = SCREEN_HEIGHT - LOG_height;
                }
            }

            SDL_RenderSetViewport( renderer, &log_viewport );
            SDL_Rect fillRect = { 0, 0, LOG_width, LOG_height };
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 150 );
            SDL_RenderFillRect( renderer, &fillRect );

            fillRect = { LOG_width - 10, 0, 10, LOG_height };
            SDL_SetRenderDrawColor( renderer, 255, 182, 55, 210 );
            SDL_RenderFillRect( renderer, &fillRect );

            log_scroller.render();

            print_log( static_cast<int> (floor((1 + LOG_size - LOG_disp -
                ((log_scroll_button_posY - SCREEN_HEIGHT + LOG_height) * (LOG_size - LOG_disp + 1)) / LOG_height) - 0.5)) );

            SDL_RenderSetViewport( renderer, nullptr );
        }
    }

} LOG;
