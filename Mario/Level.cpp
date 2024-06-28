#include "Level.h"

#include "World.h"

void Tile::draw(sf::RenderWindow& window)
{
    Level& level = world->level;
    sf::Vector2f tileSize = level.tileSize;
    
    sf::Vector2f tileDrawPosition = {tileSize.x * tilePosition.x, tileSize.y * tilePosition.y};
    tileDrawPosition -= world->camera.position;

    sf::Sprite& sprite = level.tileTextureTypeToSprite[textureType];
    sprite.setPosition(tileDrawPosition);
    window.draw(sprite);
}

Level CreateLevel(World& world, const LevelDescriptor& levelDescriptor, sf::Vector2f tileScale, sf::Vector2f tileSize)
{
    Level level;
    level.tileSize = tileSize;
    
    for(int i = 0; i < levelDescriptor.levelSymbols.size(); ++i)
    {
        // Добавляем новый элемент в вектор. Это будет другой пустой вектор. аргумент {} превращается в std::vector<Tile>
        // Почитать об конвертации {} в объект можно тут https://en.cppreference.com/w/cpp/language/list_initialization
        level.tiles.push_back({});
        for(int j = 0; j < levelDescriptor.levelSymbols[i].size(); ++j)
        {
            Tile* tile = new Tile;
            tile->world = &world;
            tile->tilePosition.x  = j;
            tile->tilePosition.y = i;
            
            // В зависимости от символа инициализируем тайл
            if(levelDescriptor.levelSymbols[i][j] == 'B')
            {
                tile->textureType = ETileTextureType::Ground;
                tile->collisionType = ETileCollisionType::Collision;
            }
            else if(levelDescriptor.levelSymbols[i][j] == 'S')
            {
                tile->textureType = ETileTextureType::Empty;
                tile->collisionType = ETileCollisionType::NoCollision;
            }

            world.objects.push_back(tile);
            // Добавляем тайл в карту
            level.tiles[i].push_back(tile);
        }
    }

    //for(std::map<ETileTextureType, sf::IntRect>::const_iterator it = levelDescriptor.tileTextureTypeToTextureRect.begin(); it != levelDescriptor.tileTextureTypeToTextureRect.end(); ++it)
    // перебираем все элементы из контейнера levelDescriptor.tileTextureTypeToTextureRect и создаем на их основе спрайты для отрисовки карты
    for(const auto& tileTextureTypeToRect : levelDescriptor.tileTextureTypeToTextureRect)
    {
        sf::Sprite sprite;
        sprite.setTexture(levelDescriptor.tileSetTexture);
        sprite.setTextureRect(tileTextureTypeToRect.second);
        sprite.setScale(tileScale);
        level.tileTextureTypeToSprite[tileTextureTypeToRect.first] = sprite;
    }

    return level;
}
