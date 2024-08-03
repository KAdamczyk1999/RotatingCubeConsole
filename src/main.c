#include <stdlib.h>
#include <time.h>

#include "drawer.h"

void _delay(int milli_seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

int main() {
    float pointCoords[12] = {.5f, .5f, .0f, .5f, -.5f, .0f, -.5f, .5f, .0f, -.5f, -.5f, .0f};
    Vector points[4];
    Shape rect;
    createRect(&rect, points, pointCoords);

    Matrix zOp;
    float rows[3][3];
    zOp.values = (float**)malloc(3 * sizeof(float*));
    for (int i = 0; i < 3; i++) zOp.values[i] = rows[i];
    zOp.columnCount = 3;
    zOp.rowCount = 3;

    generateZRotationOperator(&zOp, 2.0f);

    for (;;) {
        _delay(100);
        system("cls");
        printGrid();
        fillGridWithBaseValues();
        for (int i = 0; i < rect.verticesCount; i++) {
            placePointOnGrid(rect.vertices[i]);
            applyOperatorOn3dPoint(zOp, &(rect.vertices[i]));
        }
    }

    free(zOp.values);
    return 0;
}