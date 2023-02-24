class Tips
{
private:
    int sW;
    int sH;
    SDL_Texture* text;
    WrapTexture* link;
public:
    ~Tips()
    {
        if(text != nullptr)
            SDL_DestroyTexture( text );
    }
    void init(std::string t, WrapTexture* obj, int width = 300)
    {
        sW = width;
        setFontColor(BLACK);
        SDL_Surface * temp;
        temp = TTF_RenderText_Blended_Wrapped( gFont[3], t.c_str(), textColor, sW );
        sH = temp->h;
        text = SDL_CreateTextureFromSurface( renderer, temp );
        SDL_FreeSurface( temp );
        link = obj;
    }
    void render(int x, int y)
    {
        //std::cout<<link->getrX() + link->getW()<<" "<<link->getrX()<<" "<<link->getrY() + link->getH()<<" "<<link->getrY()<<std::endl;
        if(!(x > link->getrX() + link->getW() || x < link->getrX() || y > link->getrY() + link->getH() || y < link->getrY() ))
        {
            x += 15;
            y = y - sH / 2 + 10 - 10;
            if(x + sW + 5 + 6 > SCREEN_WIDTH)
                x = x - 30 - sW;
            if(y < 5)
                y = 5;
            else if(y + sH + 5 + 10 > SCREEN_HEIGHT)
                y = SCREEN_HEIGHT - sH - 5 - 10;

            SDL_Rect fillRect = { x, y, sW + 10, sH + 10 };
            SDL_SetRenderDrawColor( renderer, 233, 199, 87, 220 );
            SDL_RenderFillRect( renderer, &fillRect );
            fillRect.x += 2;
            fillRect.y += 2;
            fillRect.h -= 4;
            fillRect.w -= 4;
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
            SDL_RenderDrawRect( renderer, &fillRect );
            fillRect.x += 1;
            fillRect.y += 1;
            fillRect.h -= 2;
            fillRect.w -= 2;
            SDL_RenderDrawRect( renderer, &fillRect );
            fillRect.x += 7;
            fillRect.y += 5;
            fillRect.h -= 4;
            fillRect.w -= 4;
            SDL_RenderCopy( renderer, text, nullptr,  &fillRect);
        }
    }
};
