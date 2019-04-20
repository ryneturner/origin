#pragma once

#include <stdio.h>

//Windows class that handles the game interface
class Windows
{
    const int N = 30, M = 20, size = 16, width = size * N, height = size * M;
    int dir, num = 4;
    float timer = 0, delay = 0.1;
    
public:
    void CreateWindow();
    void Tick();
};
