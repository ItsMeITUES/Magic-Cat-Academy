#ifndef __MUSIC
#define __MUSIC

#include <SDL_mixer.h>
#include <string>

class SFX
{
    private:
        Mix_Music* music = NULL;
        Mix_Chunk* chunk = NULL;

    public:
        void free();

        void loadMusic(std::string path);
        void loadChunk(std::string path);

        void playMusic();
        void playChunk();

        void stopMusic();

        Mix_Chunk* getChunk();
};

#endif // __MUSIC
