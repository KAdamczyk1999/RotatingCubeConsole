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

    f(op, rand() / (RAND_MAX / (3.0f)) + 2.0f);
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
    float pointCoordsFront[12] = {-.5f, -.5f, .5f, -.5f, .5f, .5f, .5f, .5f, .5f, .5f, -.5f, .5f};
    Vector pointsFront[4];
    Shape rectFront;
    createRect(&rectFront, pointsFront, pointCoordsFront);

    float pointCoordsBack[12] = {-.5f, -.5f, -.5f, -.5f, .5f, -.5f, .5f, .5f, -.5f, .5f, -.5f, -.5f};
    Vector pointsBack[4];
    Shape rectBack;
    createRect(&rectBack, pointsBack, pointCoordsBack);

    Matrix xOp;
    Matrix yOp;
    Matrix zOp;

    _setUpOperator(&xOp, generateXRotationOperator);
    _setUpOperator(&yOp, generateYRotationOperator);
    _setUpOperator(&zOp, generateZRotationOperator);

    for (;;) {
        _delay(100);
        fillGridWithBaseValues();
        drawRectOnGrid(rectFront);
        drawRectOnGrid(rectBack);
        connectRects(rectFront, rectBack);
        flattenGrid();

        printGrid();

        for (int i = 0; i < rectFront.verticesCount; i++) {
            applyOperatorOn3dPoint(xOp, &(rectFront.vertices[i]));
            applyOperatorOn3dPoint(yOp, &(rectFront.vertices[i]));
            applyOperatorOn3dPoint(zOp, &(rectFront.vertices[i]));

            applyOperatorOn3dPoint(xOp, &(rectBack.vertices[i]));
            applyOperatorOn3dPoint(yOp, &(rectBack.vertices[i]));
            applyOperatorOn3dPoint(zOp, &(rectBack.vertices[i]));
        }
    }

    _freeOperators(&xOp, &yOp, &zOp);

    return 0;
}