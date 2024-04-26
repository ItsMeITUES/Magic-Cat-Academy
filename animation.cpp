#include "headers/animation.h"

int LTexture::getWidth()
{
    int x = mWidth;
    return x;
}

int LTexture::getHeight()
{
    int x = mHeight;
    return x;
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    bool success = 1;
    mTexture = IMG_LoadTexture(gRenderer, path.c_str());
    if(mTexture == NULL)
    {
        success = 0;
        std::cout << "Cannot load sprite sheet! SDL_img Error: " << IMG_GetError() << std::endl;
        return success;
    }
    return success;
}

void LTexture::render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double scaler)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
//        if( clip != NULL )
//        {
        renderQuad.w = scaler * clip->w;
        renderQuad.h = scaler * clip->h;

        renderQuad.x -= renderQuad.w / 2;
        renderQuad.y -= renderQuad.h / 2;

//            std::cout << renderQuad.x << " " << renderQuad.y << " " << renderQuad.w << " " << renderQuad.h << std::endl;
//            std::cout << mTexture << std::endl;
//        }

    //Render to screen
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
//        std::cout << "a";
}

void LTexture::free()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer)
{
    bool success = 1;

    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if(textSurface == NULL)
    {
        success = 0;
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return 0;
    }

    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if( mTexture == NULL )
    {
        success = 0;
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        return success;
    }

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);

    return (mTexture != NULL);
}

bool LTexture::loadFont(std::string path, int fontSize)
{
    bool success = 1;
    font = TTF_OpenFont(path.c_str(), fontSize);
    if( font == NULL )
    {
        std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        success = 0;
    }
    return success;
}

void LTexture::renderText(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = mWidth;
    rect.h = mHeight;
    SDL_RenderCopyEx(gRenderer, mTexture, NULL, &rect, angle, center, flip);
}

void loadAnimation(Animation& ani, SDL_Renderer* gRenderer)
{
    std::string path = ani.path;
    if(!ani.sheetTexture.loadFromFile(path, gRenderer))
    {
        return;
    }

    for(int i = 0; i < ani.frameCount; i++)
    {
        SDL_Rect framePos;
        framePos.x = (i % ani.spritePerRow) * ani.frameSize.w;
        framePos.y = (i / ani.spritePerRow) * ani.frameSize.h;
        framePos.w = ani.frameSize.w;
        framePos.h = ani.frameSize.h;

//        std::cout << framePos.x << " " << framePos.y << std::endl;

        ani.clips.push_back(framePos);
    }
}

void playAnimation(Animation& ani, SDL_Renderer* gRenderer, int x, int y, double scaler)
{
    SDL_Rect* currentFrame = &ani.clips[ani.frameIndex / (60 / ani.framePerSecond)];

//    std::cout << ani.frameIndex / 6 << std::endl;
    ani.sheetTexture.render(x, y, gRenderer, currentFrame, scaler);
    ani.frameIndex++;

    if(ani.frameIndex / (60 / ani.framePerSecond) >= ani.frameCount) ani.frameIndex = 0;
}
