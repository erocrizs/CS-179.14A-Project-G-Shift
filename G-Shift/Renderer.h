#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED
#include "PlayerSprite.h"
#include "BulletSprite.h"
#include "BlockSprite.h"
#include <SFML/Graphics.hpp>

class Renderer {
private:
    int  n;
    int index;
    int blockCount;
    float deg;
    std::vector<BlockSprite> blocks;
    PlayerSprite players[4];
    BulletSprite bullets[4];
    sf::RenderTexture preBD;
    sf::Texture backdrop;
    bool toBeRendered(Vec2 here){
        Vec2 playerPos = players[index].getPosition();
        Vec2 resultant = here-playerPos;
        float dist = resultant.magnitude();
        return dist<640;
    }
public:
    Renderer();
    void setPlayerPosition(int, float, float);
    void setBulletPosition(int, float, float);
    void setN(int);
    void setIndex(int);
    void draw(sf::RenderWindow&);
    void setDeg(int, float);
};
#endif // RENDERER_H_INCLUDED
