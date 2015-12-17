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

    sf::RenderTexture preBD;
    preBD.create(1600, 840);
    preBD.clear();
    for(int i=0; i<40; i++)
    {
        for(int j=0; j<21; j++)
        {
            if(map.getPixel(i, j)==sf::Color::Black)
            {
                blocks.push_back(BlockSprite());
                blocks.back().setPosition((i*40)+20, (j*40)+20);
                blocks.back().draw(preBD);
                blockCount++;
            }
        }
    }
    preBD.display();
    backdrop = preBD.getTexture();
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
    deg = 0;
    /*
    rt.clear();
    int count = 0;
    /*
    for(int i=0; i<blockCount; i++)
    {
        Vec2 blockPos = blocks[i].getPosition();
        if(toBeRendered(blockPos))
        {
            blocks[i].draw(rt);
            count++;
        }
    }
    std::cout << "RenderedBlocks: "<< count << std::endl;

    sf::Sprite background;
    background.setTexture(backdrop);
    rt.draw(background);
    for(int i=0; i<n; i++)
    {
        sf::Color c;
        if(i==0) c = sf::Color::Blue;
        else if(i==1) c = sf::Color::Red;
        else if(i==2) c = sf::Color::Green;
        else if(i==3) c = sf::Color::Yellow;
        Vec2 playPos = players[i].getPosition();
        if(toBeRendered(playPos)) {
            players[i].draw(rt, c);
        }

        Vec2 bullPos = bullets[i].getPosition();
        if(toBeRendered(bullPos))
            bullets[i].draw(rt, c);
    }
    float charaPosX = players[index].getPosition().getX();
    float charaPosY = players[index].getPosition().getY();

    rt.display();
    sf::Texture actualTexture = rt.getTexture();
    sf::Sprite actualSprite;
    actualSprite.setTexture(actualTexture);
    actualSprite.setRotation(-deg);
    //std::cout << charaPosX << " " << charaPosY << std::endl;
    actualSprite.setOrigin(charaPosX, charaPosY);
    actualSprite.setPosition(400, 300);
    window.draw(actualSprite);
    */

    float charaPosX = players[index].getPosition().getX();
    float charaPosY = players[index].getPosition().getY();
    Vec2 relative(0, 0);
    relative = Vec2(400-charaPosX, 300-charaPosY);
    /*
    if(deg==90) relative = Vec2(400-charaPosX, 300-charaPosY);
    else if(deg==180) relative = Vec2(charaPosY-300, 400-charaPosX);
    else if(deg==270) relative = Vec2(charaPosX-400, charaPosY-300);
    else relative = Vec2(300-charaPosY, charaPosX-400);
    */
    sf::Sprite background;
    background.setTexture(backdrop);
    /*
    if(deg==90) background.setOrigin(0, 0);
    else if(deg==180) background.setOrigin(0, 840);
    else if(deg==270) background.setOrigin(1600, 840);
    else background.setOrigin(1600, 0);
    */
    background.setRotation(-deg);
    background.setPosition(relative.getX(), relative.getY());
    window.draw(background);

    for(int i=0; i<n; i++)
    {
        sf::Color c;
        if(i==0) c = sf::Color::Blue;
        else if(i==1) c = sf::Color::Red;
        else if(i==2) c = sf::Color::Green;
        else if(i==3) c = sf::Color::Yellow;
        Vec2 playPos = players[i].getPosition();
        if(toBeRendered(playPos)) {
            players[i].draw(window, c, relative, -deg);
        }

        Vec2 bullPos = bullets[i].getPosition();
        if(toBeRendered(bullPos))
            bullets[i].draw(window, c, relative);
    }//std::cout << charaPosX << " " << charaPosY << std::endl;
}
