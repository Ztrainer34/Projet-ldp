#include "paddle_mouvement.hpp"
#include "object.hpp" // ou include paddle.hpp

void paddleMouvement(ALLEGRO_EVENT event, Paddle &paddle){
//direction droit 1 gauche -1 
    int direction;
    if (event.type == ALLEGRO_EVENT_KEY_DOWN){
        switch (event.keyboard.keycode){
            case ALLEGRO_KEY_A:
                direction = -1;
                update_position(direction);
                break;

            case ALLEGRO_KEY_Q:
                direction = -1;
                update_position(direction);
                break;

            case ALLEGRO_KEY_P:
                direction = 1;
                update_position(direction);
                break;

            case ALLEGRO_KEY_D:
                direction = 1;
                update_position(direction);
                break;
                
        }
    
        
    }
    else if (event.type == ALLEGRO_EVENT_MOUSES_AXES){
        //TODO
    }
}
