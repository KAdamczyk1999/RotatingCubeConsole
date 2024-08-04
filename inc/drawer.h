#pragma once

#include "lin_alg.h"
#include "shapes.h"

#define GRID_WIDTH 100
#define GRID_HEIGHT 32

void fillGridWithBaseValues();
void printGrid();
void createRect(Shape* rect, Vector* points, float* pointCoords);
void drawRectOnGrid(Shape rect);
void connectRects(Shape rect1, Shape rect2);