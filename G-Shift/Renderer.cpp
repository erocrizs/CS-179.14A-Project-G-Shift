#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{
    n = -1;
    index = -1;
    sf::Image map;
    map.loadFromFile("asset/levels/stage1.png");
    blockCount = 0;
    deg = 0;
    for(int i=0; i<40; i++)
    {
        for(int j=0; j<21; j++)
        {
            if(map.getPixel(i, j)==sf::Color::Black)
            {
                blocks.push_back(BlockSprite());
                blocks.back().setPosition((i*40)+20, (j*40)+20);
                blockCount++;
            }
        }
    }
}

void Renderer::setN(int number)
{
    n = number;
}

void Renderer::setIndex(int i)
{
    index = i;
}

void Renderer::setPlayerPosition(int i, float u, float v)
{
    players[i].setPosition(u, v);
}

void Renderer::setBulletPosition(int i, float u, float v)
{
    bullets[i].setPosition(u, v);
}

void Renderer::setDeg(int i, float d)
{
    if(i==index)
        deg = d;
    players[i].setDeg(d);
}

void Renderer::draw(sf::RenderWindow& window)
{

    rt.clear();
    for(int i=0; i<blockCount; i++) // render bricks
    {
        Vec2 blockPos = blocks[i].getPosition();
        if(toBeRendered(blockPos))
        {
            blocks[i].draw(rt);
        }
    }
    for(int i=0; i<n; i++)
    {
        // color depending on the player's index
        sf::Color c;
        if(i==0) c = sf::Color::Blue;
        else if(i==1) c = sf::Color::Red;
        else if(i==2) c = sf::Color::Green;
        else if(i==3) c = sf::Color::Yellow;

        // render players
        Vec2 playPos = players[i].getPosition();
        if(toBeRendered(playPos)) {
            players[i].draw(rt, c);
        }

        // render bullets
        Vec2 bullPos = bullets[i].getPosition();
        if(toBeRendered(bullPos))
            bullets[i].draw(rt, c);
    }
    // getting it to a Sprite object
    rt.display();
    actualTexture = rt.getTexture();
    actualSprite.setTexture(actualTexture);

    float charaPosX = players[index].getPosition().getX();
    float charaPosY = players[index].getPosition().getY();

    actualSprite.setOrigin(charaPosX, charaPosY);   // basically means center the player on the sprite
    actualSprite.setRotation(deg);                  // rotates the entire map by deg (deg is the angle of the player sprite)
    actualSprite.setPosition(400, 300);             // centers character sprite in the center of the window
    window.draw(actualSprite);                      // draw sprite


    /*
        Semi-working version: Uncomment to see what it actually look like if no shifting is done
    */
    /**
    rt.clear();
    for(int i=0; i<blockCount; i++)
    {
        Vec2 blockPos = blocks[i].getPosition();
        if(toBeRendered(blockPos))
        {
            blocks[i].draw(window);
        }
    }
    for(int i=0; i<n; i++)
    {
        sf::Color c;
        if(i==0) c = sf::Color::Blue;
        else if(i==1) c = sf::Color::Red;
        else if(i==2) c = sf::Color::Green;
        else if(i==3) c = sf::Color::Yellow;
        Vec2 playPos = players[i].getPosition();
        if(toBeRendered(playPos)) {
            players[i].draw(window, c);
        }

        Vec2 bullPos = bullets[i].getPosition();
        if(toBeRendered(bullPos))
            bullets[i].draw(window, c);
    }
    **/
}
