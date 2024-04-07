#pragma once

// Тип текстуры тайла. Нам это нужно чтобы превратить символы из карты во что-то читаемое
enum class ETileTextureType
{
    Empty = 0,
    Ground = 1
};

// Тип коллизии тайла. Коллизия это препятствие
enum class ETileCollisionType
{
    NoCollision,
    Collision
};