#ifndef __ANI
#define __ANI

#include <SDL_ttf.h>

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

//Texture wrapper class
class LTexture
{
    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;

        TTF_Font* font = NULL;

    public:
//        Initializes variables
//        LTexture();

//        Deallocates memory
//        ~LTexture();

        int getWidth();
        int getHeight();

        //Loads image at specified path
        bool loadFromFile( std::string path , SDL_Renderer* gRenderer);

        //Deallocates texture
        void free();

    //Renders texture at given point
        void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double scaler);

        bool loadFont(std::string path, int fontSize);

        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer);

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        void renderText(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

struct Animation
{
    std::string path;
    int frameCount, spritePerRow = 5;
    int framePerSecond = 12;
    int frameIndex = 0;

    SDL_Rect frameSize;
    std::vector<SDL_Rect> clips;
    LTexture sheetTexture;
};

void loadAnimation(Animation& ani, SDL_Renderer* gRenderer);
void playAnimation(Animation& ani, SDL_Renderer* gRenderer, int x, int y, double scaler = 1);

#endif // __ANI
