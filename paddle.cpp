class Paddle{
    Point position;
    Size size;
    int speed;
    const ALLEGRO_COLOR COLOR_GREY = al_map_rgb(200, 200, 200);
    Paddle(float x, float y, int speed, int width, int height) : 
    position{x,y}, speed(speed), size{width,height},COLOR_GREY(COLOR_GREY){}

    public: 
        void update_position();
        void collision();

};
