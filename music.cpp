#include "headers/music.h"

#include <iostream>

void SFX::free()
{
    Mix_FreeMusic(music);
    music = NULL;

    Mix_FreeChunk(chunk);
    chunk = NULL;
}

void SFX::loadMusic(std::string path)
{
    music = Mix_LoadMUS(path.c_str());
    if( music == NULL )
    {
        printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void SFX::loadChunk(std::string path)
{
//    std::cout << path << std::endl;
    chunk = Mix_LoadWAV(path.c_str());
    if( chunk == NULL )
    {
        printf( "Failed to load chunk sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void SFX::playMusic()
{
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( music, -1 );
    }
}

void SFX::playChunk()
{
    Mix_PlayChannel( -1, chunk, 0 );
}

void SFX::stopMusic()
{
    Mix_HaltMusic();
}

Mix_Chunk* SFX::getChunk()
{
    Mix_Chunk* ch = chunk;
    return ch;
}
