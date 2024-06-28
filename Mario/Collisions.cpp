#include "Collisions.h"

CollisionResult HandleCollision(
    const sf::FloatRect& objectRect/*положение и размеры объекта для которого считаем коллизию*/,
    const sf::Vector2f& objectVelocity /*скорость и направление движения объекта*/,
    const Level& level /*карта с тайлами*/,
    EOrientaion orientation /*ориентация коллизии. Горизонтальная или вертикальная*/,
    const sf::Vector2f& tileSize /*размер тайла*/)
{
    // Находим индексы тайлов в которых сейчас находится наш объект для которого мы считаем коллизию

    //Тайлы по X
    const int xLeftTile = objectRect.left / tileSize.x;
    int xRightTile = (objectRect.left + objectRect.width - 1) / tileSize.x; // -1 для того чтобы убрать погрешность при делении и обрабатывать только не тайлы на которых реально стоит персонаж
    
    //Тайлы по Y
    const int yTopTile = objectRect.top / tileSize.y;
    int yBottomTile = (objectRect.top + objectRect.height - 1) / tileSize.y;

    CollisionResult result;
    result.newPosition = objectRect.getPosition();
    
    for(int i = yTopTile; i <= yBottomTile; ++i)
    {
        for(int j = xLeftTile; j <= xRightTile; ++j)
        {
            // Тайл с которым сейчас обрабатываем коллизию
            const Tile& tile = *level.tiles[i][j];
            const sf::Vector2f tilePosition = sf::Vector2f(j * tileSize.x, i * tileSize.y);
            
            if(tile.collisionType == ETileCollisionType::Collision)
            {
                result.bIsCollided = true;
                // Если коллизия горизонтальная, то смотрим на движение по оси X    
                if(orientation == EOrientaion::Horizontal)
                {
                    // Если объект двигается влево, то сдвигаем его вправо
                    if(objectVelocity.x < 0)
                    {
                        // Берём позицию тайла с коллизией и сдвигаем персонажа на правый тайл относительно тайла с коллизией
                        // Для этого мы берем координату тайла с коолизией и прибавляем размер этого тайла чтобы перескочить на правый тайл
                        result.newPosition = sf::Vector2f(tilePosition.x + tileSize.x, objectRect.top);
                    }
                    else
                    {
                        result.newPosition = sf::Vector2f(tilePosition.x - objectRect.width, objectRect.top);
                    }
                }
                else
                {
                    if(objectVelocity.y < 0)
                    {
                        result.newPosition = sf::Vector2f(objectRect.left, tilePosition.y - objectRect.height);
                    }
                    else
                    {
                        result.newPosition = sf::Vector2f(objectRect.left, tilePosition.y + tileSize.y);
                    }
                }

                return result;
            }
        }
    }
    //Получаем позицию объекта из структуры Rect
    return result;
}