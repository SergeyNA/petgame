bool SDL_initialaize()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
       std::cout << SDL_GetError() << std::endl;
       return false;
    }
    if (IMG_Init(IMG_INIT_JPG) < 0)
    {
       std::cout << IMG_GetError() << std::endl;
       return false;
    }
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    window = SDL_CreateWindow("Canvas", SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
       std::cout << SDL_GetError() << std::endl;
       return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
       std::cout << SDL_GetError() << std::endl;
       return false;
    }
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    if( SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND ) < 0)
    {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Close_SDL()
{
    TTF_CloseFont(gFont[0]);
    TTF_CloseFont(gFont[1]);
    TTF_CloseFont(gFont[2]);
    TTF_CloseFont(gFont[3]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

inline std::string toString(int num)
{
    string_buffer.str( "" );
    string_buffer << num;
    return string_buffer.str();
}

bool loadFont(std::string font_name, int f_size, int index)
{
    if(gFont[index] != nullptr)
        TTF_CloseFont(gFont[index]);
    gFont[index] = TTF_OpenFont( ("fonts/" + font_name + ".ttf").c_str(), f_size );
    if( gFont[index] == nullptr )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    return true;
}

void setFontTransparent(Uint8 val)
{
    textColor.a = val;
}

void setFontColor(font_colors c)
{
    switch(c) {
    case RED:
        textColor.r = 250;  textColor.g = 0;     textColor.b = 0;
        break;
    case GREEN:
        textColor.r = 0;    textColor.g = 250;   textColor.b = 0;
        break;
    case BLUE:
        textColor.r = 0;    textColor.g = 0;     textColor.b = 250;
        break;
    case YELLOW:
        textColor.r = 250;  textColor.g = 250;   textColor.b = 0;
        break;
    case GRAY:
        textColor.r = 170;  textColor.g = 170;   textColor.b = 170;
        break;
    case BLACK:
        textColor.r = 0;    textColor.g = 0;     textColor.b = 0;
        break;
    case WHITE:
    default:
        textColor.r = 255;  textColor.g = 255;   textColor.b = 255;
    }
}

class WrapTexture
{
	public:
		WrapTexture();
		WrapTexture(std::string path, bool transparent, int x, int y);
		~WrapTexture();
		bool loadFromFile( std::string path, bool mode);
		bool loadFromRenderedText( std::string textureText, font_colors color, int font, bool q, int max_width );
		void free();
		void render(int x, int y, float scale = 1.0);
		void render2( int x, int y,
              SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
		void render(double scale = 1.0);
		void setRenderPos( int x, int y );
		int getW();
		int getH();
		int getrX();
		int getrY();
		void setBlendMode( SDL_BlendMode blending );
        void setAlpha( Uint8 alpha );
        bool exist();

	private:
		SDL_Texture* texture;
		int width;
		int height;
		int rX;
		int rY;
};

WrapTexture::WrapTexture()
{
	texture = nullptr;
	width = 0;
	height = 0;
	rX = 0;
	rY = 0;
}

WrapTexture::WrapTexture(std::string name, bool transparent = false, int posX = 0, int posY = 0)
{
    SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load( ("img/" + name).c_str() );
	if( loadedSurface == nullptr )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", name.c_str(), IMG_GetError() );
	}
	else
	{
        if(transparent)
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == nullptr )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", name.c_str(), SDL_GetError() );
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface( loadedSurface );
	}

	texture = newTexture;
    rX = posX;
    rY = posY;
}

WrapTexture::~WrapTexture()
{
	free();
}

bool WrapTexture::exist()
{
    return texture != nullptr;
}

bool WrapTexture::loadFromFile( std::string path, bool transparent = false )
{
	free();

	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load( ("img/" + path).c_str() );
	if( loadedSurface == nullptr )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
	    if(transparent)
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == nullptr )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	texture = newTexture;
	return texture != nullptr;
}

bool WrapTexture::loadFromRenderedText( std::string textureText, font_colors color, int font, bool qual = true, int wrap_length = 0 )
{
    free();

    setFontColor(color);
    SDL_Surface* textSurface = nullptr;

    if(wrap_length == 0)
        if(qual)
            textSurface = TTF_RenderText_Blended( gFont[font], textureText.c_str(), textColor );
        else
            textSurface = TTF_RenderText_Solid( gFont[font], textureText.c_str(), textColor );
    else
        textSurface = TTF_RenderText_Blended_Wrapped( gFont[font], textureText.c_str(), textColor, wrap_length );

    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }

    return texture != nullptr;
}

void WrapTexture::free()
{
	if( texture != nullptr )
	{
		SDL_DestroyTexture( texture );
		texture = nullptr;
		width = 0;
		height = 0;
		rX = 0;
		rY = 0;
	}
}

void WrapTexture::render(double scale)
{
    SDL_Rect renderQuad = { rX, rY, static_cast<int> (width * scale), static_cast<int> (height * scale) };
	SDL_RenderCopy( renderer, texture, nullptr, &renderQuad );
}

void WrapTexture::render( int x, int y, float scale)
{
	SDL_Rect renderQuad = { x, y, static_cast<int> (width * scale), static_cast<int> (height * scale) };
	SDL_RenderCopy( renderer, texture, nullptr, &renderQuad );
}

void WrapTexture::render2( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, width, height };

	if( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

void WrapTexture::setRenderPos( int x, int y )
{
    rX = x;
    rY = y;
}

int WrapTexture::getW()
{
	return width;
}

int WrapTexture::getH()
{
	return height;
}

int WrapTexture::getrX()
{
	return rX;
}

int WrapTexture::getrY()
{
	return rY;
}

void WrapTexture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( texture, blending );
}

void WrapTexture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

SDL_Texture* LoadImage(std::string file, SDL_Renderer *renderer)
{
    SDL_Surface *loadedImage = nullptr;
    SDL_Texture *texture = nullptr;
    //loadedImage = SDL_LoadBMP(file.c_str());
    loadedImage = IMG_Load(file.c_str());
    if (loadedImage != nullptr)
    {
       texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
       if(texture == nullptr)
       {
           printf( "Unable to create texture from %s! SDL Error: %s\n", file.c_str(), SDL_GetError() );
       }
       SDL_FreeSurface(loadedImage);
    }
    else
       std::cout << "Unable to create texture from " << file << " SDL Error: " << IMG_GetError() << std::endl;
    return texture;
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *renderer)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, nullptr, nullptr, &pos.w, &pos.h);
    SDL_RenderCopy(renderer, tex, nullptr, &pos);
}

SDL_Texture* loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont[0], textureText.c_str(), textColor );
    SDL_Texture *texture = nullptr;
    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        SDL_FreeSurface( textSurface );
    }

    return texture;
}

class Button
{
private:

    int posX = 0;
    int posY = 0;
    int dimW;
    int dimH;
    WrapTexture buttonImage;
    bool isActive = false;

public:

    void render()
    {
        if(isActive)
            buttonImage.render();
    }

    void setPos(int x, int y)
    {
        posX = x;
        posY = y;
        buttonImage.setRenderPos(x, y);
    }

    bool detectEvent(int x, int y)
    {
        if(isActive)
            return (!(x > posX + dimW || x < posX || y > posY + dimH || y < posY));
        return false;
    }

    bool isOn()
    {
        return isActive;
    }

    void onButton()
    {
        isActive = true;
    }

    void offButton()
    {
        isActive = false;
    }

    bool setImage(std::string path, bool transparent)
    {
        buttonImage.free();
        isActive = true;
        if(!buttonImage.loadFromFile(path, transparent))
            return false;
        buttonImage.setRenderPos(posX, posY);
        dimW = buttonImage.getW();
        dimH = buttonImage.getH();
        return true;
    }

    WrapTexture* getTexture()
    {
        return &buttonImage;
    }
};
