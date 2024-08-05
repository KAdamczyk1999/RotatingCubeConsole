#include "drawer.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char grid[GRID_HEIGHT][GRID_WIDTH + 1];
char gridFlat[GRID_HEIGHT * (GRID_WIDTH + 1)];

void fillGridWithBaseValues() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) grid[i][j] = '0';
        grid[i][GRID_WIDTH] = '\n';
    }
}

void flattenGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        memcpy(&(gridFlat[(GRID_WIDTH + 1) * i]), grid[i], sizeof(grid[i]));
    }
}

void printGrid() { puts(gridFlat); }

void _castPointsToDistrictValues(Vector point, float* pointX, float* pointY) {
    *pointX = (((point.values[0] + 1.0f) / 2) * GRID_WIDTH);
    *pointY = (((-point.values[1] + 1.0f) / 2) * GRID_HEIGHT);
}

void _establishLineStartAndStop(float* pointStart, float* pointStop, int point1Coord, int point2Coord) {
    if (point2Coord > point1Coord) {
        *pointStart = (float)point1Coord;
        *pointStop = (float)point2Coord;
    } else {
        *pointStart = (float)point2Coord;
        *pointStop = (float)point1Coord;
    }
}

void _drawLineOnGrid(Vector point1, Vector point2) {
    float point1X, point1Y, point2X, point2Y;
    _castPointsToDistrictValues(point1, &point1X, &point1Y);
    _castPointsToDistrictValues(point2, &point2X, &point2Y);

    float horizontalDistance = point2X - point1X;
    float verticalDistance = point2Y - point1Y;

    int diagonalDistance = sqrt(pow(horizontalDistance, 2) + pow(verticalDistance, 2));

    float xStep = horizontalDistance / diagonalDistance;
    float yStep = verticalDistance / diagonalDistance;

    for (int i = 0; i <= diagonalDistance; i++) {
        grid[(int)point1Y][(int)point1X] = '1';
        point1X += xStep;
        point1Y += yStep;
    }
}

void drawRectOnGrid(Shape rect) {
    _drawLineOnGrid(rect.vertices[rect.verticesCount - 1], rect.vertices[0]);
    for (int i = 0; i < rect.verticesCount - 1; i++) {
        _drawLineOnGrid(rect.vertices[i], rect.vertices[i + 1]);
    }
}

void connectRects(Shape rect1, Shape rect2) {
    for (int i = 0; i < rect1.verticesCount; i++) {
        _drawLineOnGrid(rect1.vertices[i], rect2.vertices[i]);
    }
}

void createRect(Shape* rect, Vector* points, float* pointCoords) {
    rect->verticesCount = 4;
    for (int i = 0; i < rect->verticesCount; i++) {
        points[i].values = &(pointCoords[i * 3]);
        points[i].size = 3;
    }
    rect->vertices = points;
}