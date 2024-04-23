#ifndef __ANI
#define __ANI

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

    public:
        //Initializes variables
//        LTexture();

        //Deallocates memory
//        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path , SDL_Renderer* gRenderer)
        {
            bool success = 1;
            mTexture = IMG_LoadTexture(gRenderer, path.c_str());
            if(mTexture == NULL)
            {
                success = 0;
                std::cout << "Cannot load sprite sheet! SDL_img Error: " << IMG_GetError();
                return success;
            }
            return success;
        }

        //Deallocates texture
        void free();



        //Gets image dimensions
        int getWidth();
        int getHeight();

    //Renders texture at given point
    void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        //Set clip rendering dimensions
        if( clip != NULL )
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    }
};

struct Animation
{
    std::string path;
    int frameCount, spritePerRow;

    int frameIndex;

    SDL_Rect frameSize;
    std::vector<SDL_Rect> clips;
    LTexture sheetTexture;
};

void loadAnimation(Animation& ani, SDL_Renderer* gRenderer);
void playAnimation(Animation& ani, SDL_Renderer* gRenderer);

#endif // __ANI
