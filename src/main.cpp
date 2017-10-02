#include <iostream>
#include <SFML/Graphics.hpp>

#include "System/GameWorld.hpp"
#include "System/GameRender.hpp"

#define WIN_WIDTH 1600
#define WIN_HEIGHT 900

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Zombie V", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    GameRender::initialize(WIN_WIDTH, WIN_HEIGHT);
    GameWorld world;
    world.initEventHandler(window);

    world.addEntity(WorldEntityPtr(new Hunter(1000, 1000)));

    sf::Mouse::setPosition(sf::Vector2i(WIN_WIDTH/2+100, WIN_HEIGHT/2));

    int waveCount = 1;

    /*world.addEntity(new Turret(1000, 1000));
    world.addEntity(new Turret(1100, 1000));
    world.addEntity(new Turret(1100, 1100));
    world.addEntity(new Turret(1000, 1100));*/
    world.addEntity(WorldEntityPtr(new Turret(1050, 1050)));

    for (int i(100); i--;)
    {
        WorldEntityPtr newZombie(new Zombie(rand()%2000, rand()%2000));
        newZombie->setTarget(&hunter);
        world.addEntity(newZombie);
    }
    waveCount++;

    for (int i(0); i<10; ++i)
    {
        Light light;
        light.position = Vec2(rand()%2000, rand()%2000);
        light.color    = sf::Color(rand()%255, rand()%255,rand()%255);
        light.radius   = 150+rand()%150;
        GameRender::getLightEngine().addDurableLight(light);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) window.close();
				default:
                    break;
			}
        }

        world.update();

        Vec2 p = hunter.getCoord();
        sf::Vector2f playerPosition(p.x, p.y);
        GameRender::setFocus(playerPosition);

        GameRender::clear();

        world.render();
        GameRender::display(&window);

        window.display();
    }

    return 0;
}
