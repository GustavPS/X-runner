#ifndef STATE_H
#define STATE_H

class State
{
    public:
        State(const std::vector<Objects*> &objects);
        virtual ~State() noexcept;
        virtual int simulate() = 0;

        //virtual std::vector<sf::RectangleShape> get_visible_objects() = 0;
    
    private:
        virtual void reset();
        std::vector<Objects*> objects;
}

#endif