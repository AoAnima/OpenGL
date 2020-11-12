/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"


/// ����� GameLevel �������� ��� ������� ������� ����, 
/// � ����� ���������� ��� �������� � �������� ����� ���������� � �� ����������
class GameLevel
{
public:
    // ��������� ������
    std::vector<GameObject> Bricks;
    // �����������
    GameLevel() { }
    // �������� ������ �� �����
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // ��������� ������
    void Draw(SpriteRenderer& renderer);
    // ��������, ������� �� ������� (��� ����������� ������� ������ ���� ����������)
    bool IsCompleted();
private:
    // ������������� ������ ������� �� tileData
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif
