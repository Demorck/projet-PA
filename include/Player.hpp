# ifndef PLAYER_HPP
#define PLAYER_HPP
#include <Entity.hpp>

class Player : public Entity
{   
    public:
        Player(int hp, float speed, float x, float y, int width, int height);
        ~Player();
        void render(SDL_Renderer* renderer);
        void update(double time);
        
        void handleEvents();
    
    private:
        bool moveLeft;
        bool moveRight; 
        bool moveDown;
        bool moveUp;
};

#endif