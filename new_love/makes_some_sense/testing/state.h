#ifndef STATE_H
#define STATE_H

class State
{
    public:
        State(const std::vector<Objects*> &objects);
        virtual ~State() noexcept;
        virtual int simulate(sf::Clock&) = 0;

        virtual sf::Sprite get_background() const;

        virtual std::vector<Texturated_Objects*> get_texturated_objects() const;
    
    private:
        virtual void reset();
        sf::Sprite background;
        std::vector<Objects*> objects;
        std::vector<Objects*> texturated_objects; 
}

#endif