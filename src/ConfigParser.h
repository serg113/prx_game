#pragma once

#include <SFML/Graphics.hpp>


enum class TileColor { NoColor, Red, Green, Blue, Violet };
enum class BackgroundType { Type1, Type2, FieldChecked };

void initConfig();

size_t getBgTileSize();
size_t getPawnSize();
size_t getRowCount();
size_t getColumnCount();
size_t getStartPosX();
size_t getStartPosY();


sf::Texture getBackgroundTexture(BackgroundType bgType);


