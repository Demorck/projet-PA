#ifndef RENDER_HPP
#define RENDER_HPP

#include <SDL2/SDL.h>
#include <iostream>

class Render
{
    public:
        Render(Render const&) = delete;
        void operator=(Render const&) = delete;

        static Render* getInstance()
        {
            static Render* instance = 0;
            if(!instance)instance = new Render();
            return instance;
        }

        SDL_Renderer* getRenderer() const { return renderer; }
        SDL_Window* getWindow() const { return window; }

    private:
        SDL_Renderer* renderer;
        SDL_Window* window;

        Render();
        ~Render();
};

#endif
