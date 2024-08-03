#include "drawer.h"

#include <stdio.h>

char grid[GRID_HEIGHT][GRID_WIDTH + 1];

void fillGridWithBaseValues() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) grid[i][j] = '0';
        grid[i][GRID_WIDTH] = '\0';
    }
}

void printGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        printf("%s\n", grid[i]);
    }
    printf("\n");
}

void placePointOnGrid(Vector point) {
    int pointX = (int)(((point.values[0] + 1.0f) / 2) * GRID_WIDTH);
    int pointY = (int)(((-point.values[1] + 1.0f) / 2) * GRID_HEIGHT);
    grid[pointY][pointX] = '1';
}

void createRect(Shape* rect, Vector* points, float* pointCoords) {
    rect->verticesCount = 4;
    for (int i = 0; i < rect->verticesCount; i++) {
        points[i].values = &(pointCoords[i * 3]);
        points[i].size = 3;
    }
    rect->vertices = points;
}