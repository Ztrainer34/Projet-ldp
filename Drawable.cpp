class Drawable {
protected:
    Drawable()                             = default;
    Drawable(const Drawable &)            = default;
    Drawable(Drawable &&)                 = default;
    Drawable &operator=(const Drawable &) = default;
    Drawable &operator=(Drawable &&)      = default;

public:
    virtual void draw() = 0;
    virtual ~Drawable() = default;
};