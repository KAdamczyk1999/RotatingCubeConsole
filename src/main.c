#include <stdlib.h>
#include <time.h>

#include "drawer.h"

void _delay(int milli_seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void _setUpOperator(Matrix* op, void (*f)(Matrix*, float)) {
    op->values = (float**)malloc(3 * sizeof(float*));
    for (int i = 0; i < 3; i++) op->values[i] = (float*)malloc(3 * sizeof(float));
    op->columnCount = 3;
    op->rowCount = 3;

    f(op, 2.0f);
}

void _freeOperators(Matrix* xOp, Matrix* yOp, Matrix* zOp) {
    for (int i = 0; i < 3; i++) {
        free(xOp->values[i]);
        free(yOp->values[i]);
        free(zOp->values[i]);
    }
    free(xOp->values);
    free(yOp->values);
    free(zOp->values);
}

int main() {
    float pointCoords[12] = {-.5f, -.5f, .0f, -.5f, .5f, .0f, .5f, .5f, .0f, .5f, -.5f, .0f};
    Vector points[4];
    Shape rect;
    createRect(&rect, points, pointCoords);

    Matrix xOp;
    Matrix yOp;
    Matrix zOp;

    _setUpOperator(&xOp, generateXRotationOperator);
    _setUpOperator(&yOp, generateYRotationOperator);
    _setUpOperator(&zOp, generateZRotationOperator);

    for (;;) {
        _delay(100);
        fillGridWithBaseValues();
        system("cls");

        drawLineOnGrid(rect.vertices[rect.verticesCount - 1], rect.vertices[0]);
        for (int i = 0; i < rect.verticesCount - 1; i++) {
            drawLineOnGrid(rect.vertices[i], rect.vertices[i + 1]);
        }

        printGrid();
        for (int i = 0; i < rect.verticesCount; i++) {
            applyOperatorOn3dPoint(xOp, &(rect.vertices[i]));
            applyOperatorOn3dPoint(yOp, &(rect.vertices[i]));
            applyOperatorOn3dPoint(zOp, &(rect.vertices[i]));
        }
    }

    _freeOperators(&xOp, &yOp, &zOp);

    return 0;
}