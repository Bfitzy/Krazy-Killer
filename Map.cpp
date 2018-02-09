#include "Map.h"
#include <cassert>

Map::Map()
{
    Load("levels/level2.png");
    assert(IsLoaded());

    GetSprite().setOrigin(480,360);
}
Map::~Map()
{

}
