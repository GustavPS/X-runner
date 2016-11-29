#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include <iostream>

sf::RectangleShape to_rec(tmx::MapObject &obj)
{
  auto frec { obj.GetAABB() };
  sf::RectangleShape rec;
  if (obj.GetName() == "Player") {
    rec.setSize(sf::Vector2f{frec.width,frec.height-34});
  }
  else {
    rec.setSize(sf::Vector2f{frec.width,frec.height});
  }
  rec.setPosition(obj.GetPosition());
  return rec;
}

int main()
{

    /*
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world.CreateBody(groundBodyDef);

    tmx::MapLoader ml("");
    ml.Load("new.tmx");
    b2Body* body { tmx::BodyCreator::Add(ml, world) };
*/

    tmx::MapLoader ml("");
    ml.Load("new.tmx");

    sf::RenderWindow window(sf::VideoMode(1024, 768), "X Runner");

    window.setVerticalSyncEnabled(true);

    tmx::MapObject player {};

    //bool collision;
        for(auto layer {ml.GetLayers().begin()}; layer != ml.GetLayers().end(); ++layer)
        {
           // std::cerr << layer->name << "\n";
            //if(layer->name == "Collision")
            //{
                for(auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
                {
                    if (object->GetName() == "Player") {
                        auto frec { object->GetAABB() };
                        std::cerr << frec.height << " ";
                        player = *object;
                    }
               //     std::cerr << "\t" << object->GetName() << "\n";
                    //collision = object->Contains(point);
                }
            //}
        }
        //std::cerr << "\n\n" << player.GetName() << "\n\n";
        //player->Move(100, 100);

    sf::Clock clock;
    float speed {250};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        int xsteps {};
        int ysteps {};
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            xsteps -= 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            xsteps += 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ysteps -= 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ysteps += 1;

        auto ppos = player.GetPosition();
        sf::Time delta { clock.restart() };
        {

            float distance { speed * (delta.asMilliseconds() / 1000.0f) };
            player.Move(xsteps * distance, ysteps * distance);

            bool collision { false };
            for (auto layer {ml.GetLayers().begin()}; layer != ml.GetLayers().end(); ++layer)
            {
                for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
                {
                    if (object->GetName() == "top" || object->GetName() == "bottom")
                    {
                        if (to_rec(*object).getGlobalBounds().intersects(
                              to_rec(player).getGlobalBounds()))
                        {
                            std::cerr << object->GetName();
                            collision = true;
                            break;
                          }
                  }

                }
                if (collision)
                {
                    break;
                }

            }
          }

            /*if (collision)
            {
                //player.SetPosition(ppos);
            }*/


        window.clear();
        window.draw(ml);
        window.display();

      }

}
