class Scroller {

private:

    int posXs;
    int posYs;
    int posXe;
    int posYe;
    int length;
    int pos;

    bool dir;
    bool hide;
    bool is_moving;

    WrapTexture icon;
    Uint8 colorR;
    Uint8 colorG;
    Uint8 colorB;

public:

    void init(int x1, int y1, int x2, int y2, std::string pic, Uint8 cR, Uint8 cG, Uint8 cB);
    void render();
    void clickHandler(int x, int y);
    void clickHandler2(int x, int y);
    double getVal();
    void on();
    void off();
    void setMoveFalse();
    void setPosition(double offset, bool direction = false);

    bool isMoving()
    {
        return is_moving;
    }

    bool isActive()
    {
        return !hide;
    }
};

void Scroller::init(int x1, int y1, int x2, int y2, std::string pic, Uint8 cR, Uint8 cG, Uint8 cB)
{
    posXs = x1;
    posYs = y1;
    posXe = x2;
    posYe = y2;

    is_moving = false;
    hide = false;

    if(x2 - x1 > y2 - y1)
    {
        dir = true;
        length = x2 - x1;
    }
    else
    {
        dir = false;
        length = y2 - y1;
    }

    if(dir)
        pos = length / 2 + posXs - 10;
    else
        pos = length / 2 + posYs - 10;

    colorR = cR;
    colorG = cG;
    colorB = cB;

    icon.loadFromFile(pic, true);
    if(dir)
        icon.setRenderPos(posXs + pos, posYs);
    else
        icon.setRenderPos(posXs, posYs + pos);
}

double Scroller::getVal()
{
    if(dir)
        return (static_cast<double> (pos + 10 - posXs)) / length;
    else
        return (static_cast<double> (pos + 10 - posYs)) / length;
}

void Scroller::render()
{
    if(!hide)
    {
        SDL_Rect fillRect = { posXs, posYs, posXe - posXs, posYe - posYs };
        SDL_SetRenderDrawColor( renderer, colorR, colorG, colorB, 255 );
        SDL_RenderFillRect( renderer, &fillRect );
        if(dir)
            icon.render(pos, posYs);
        else
            icon.render(posXs, pos);
    }
}

void Scroller::on()
{
    hide = false;
}

void Scroller::off()
{
    hide = true;
}

void Scroller::clickHandler(int x, int y)
{
    if(!hide) {
        if(dir) {
            if(!(x > posXe || x < posXs || y > posYe || y < posYs))
            {
                pos = x - 10;
                if(pos > posXe - 10)
                    pos = posXe - 10;
                scroll_move = true;
                is_moving = true;
            }
        }
        else
        {
            if(!(x > posXe || x < posXs || y > posYe || y < posYs))
            {
                pos = y - 10;
                if(pos > posYe - 10)
                    pos = posYe - 10;
                scroll_move = true;
                is_moving = true;
            }
        }
    }
}

void Scroller::setPosition(double offset, bool direction) //direction == function mode
{
    if(!direction) // set abs position, where offset = 0 it's begin and offset = 1 it's last edge scroller pos
    {
        if(offset >= 0.0 && offset <= 1.0)
        {
            if(dir)
                pos = length * offset + posXs - 10;
            else
                pos = length * offset + posYs - 10;
        }
    }
    else // move relative pos on some value
    {
        if(offset >= -1.0 && offset <= 1.0)
        {
            if(dir)
            {
                pos += length * offset;
                if(pos > posXe - 10)
                    pos = posXe - 10;
                else if(pos < posXs - 10)
                    pos = posXs - 10;
            }
            else
            {
                pos += length * offset;
                if(pos > posYe - 10)
                    pos = posYe - 10;
                else if(pos < posYs - 10)
                    pos = posYs - 10;
            }
        }
    }
}

void Scroller::setMoveFalse()
{
    is_moving = false;
}

void Scroller::clickHandler2(int x, int y)
{
    if(is_moving)
    {
        if(dir)
        {
            if(x < posXs)
                pos = posXs - 10;
            else if(x > posXe)
                pos = posXe - 10;
            else
                pos = x - 10;
        }
        else
        {
            if(y < posYs)
                pos = posYs - 10;
            else if(y > posYe)
                pos = posYe - 10;
            else
                pos = y - 10;
        }
    }
}
