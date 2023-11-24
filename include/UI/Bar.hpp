#ifndef BAR_HPP
#define BAR_HPP
#include <SDL2/SDL.h>
#include <Constant.hpp>

class Bar
{
    public:
        Bar(int x, int y, int w, int h, SDL_Color color = {255, 255, 255});
        Bar(SDL_Rect rect, SDL_Color color = {255, 255, 255});
        ~Bar();
        void render(SDL_Renderer* renderer);

        void setWidth(int width);
        void setColor(SDL_Color color);

        SDL_Rect getRect();

        void moveBar();
    private:
        SDL_Rect barRect;
        SDL_Color color;

        bool onLeft;
    
};


#endif