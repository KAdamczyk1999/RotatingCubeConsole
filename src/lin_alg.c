#include "lin_alg.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

float _degsToRads(float angleDegs) { return (angleDegs * PI) / 180.0f; }

void _mat_mul(Matrix matrix1, Matrix matrix2, Matrix* output) {
    assert(matrix1.columnCount == matrix2.rowCount && "Wrong matrix dimensions");
    for (int i = 0; i < matrix1.rowCount; i++) {
        for (int j = 0; j < matrix2.columnCount; j++) {
            for (int k = 0; k < matrix1.columnCount; k++) {
                output->values[i][j] += matrix1.values[i][k] * matrix2.values[k][j];
            }
        }
    }
}

void _vectorToMatrix(Matrix* matrix, Vector vector) {
    for (int i = 0; i < vector.size; i++) matrix->values[i] = &(vector.values[i]);
    matrix->rowCount = vector.size;
    matrix->columnCount = 1;
}

void applyOperatorOn3dPoint(Matrix op, Vector* point) {
    float temporaryValues[3] = {0.0f, 0.0f, 0.0f};
    Vector temporaryPoint;
    temporaryPoint.size = point->size;
    temporaryPoint.values = temporaryValues;
    Matrix temporaryMatrix;
    temporaryMatrix.values = (float**)malloc(point->size * sizeof(float*));
    _vectorToMatrix(&temporaryMatrix, temporaryPoint);
    Matrix pointMatrix;
    pointMatrix.values = (float**)malloc(point->size * sizeof(float*));
    _vectorToMatrix(&pointMatrix, *point);
    _mat_mul(op, pointMatrix, &temporaryMatrix);
    free(temporaryMatrix.values);
    free(pointMatrix.values);
    for (int i = 0; i < point->size; i++) point->values[i] = temporaryValues[i];
}

void generateXRotationOperator(Matrix* matrix, float angle) {
    float angleRad = _degsToRads(angle);
    matrix->values[0][0] = 1;
    matrix->values[0][1] = 0;
    matrix->values[0][2] = 0;
    matrix->values[1][0] = 0;
    matrix->values[1][1] = cos(angleRad);
    matrix->values[1][2] = -sin(angleRad);
    matrix->values[2][0] = 0;
    matrix->values[2][1] = sin(angleRad);
    matrix->values[2][2] = cos(angleRad);
}

void generateYRotationOperator(Matrix* matrix, float angle) {
    float angleRad = _degsToRads(angle);
    matrix->values[0][0] = cos(angleRad);
    matrix->values[0][1] = 0;
    matrix->values[0][2] = sin(angleRad);
    matrix->values[1][0] = 0;
    matrix->values[1][1] = 1;
    matrix->values[1][2] = 0;
    matrix->values[2][0] = -sin(angleRad);
    matrix->values[2][1] = 0;
    matrix->values[2][2] = cos(angleRad);
}

void generateZRotationOperator(Matrix* matrix, float angle) {
    float angleRad = _degsToRads(angle);
    matrix->values[0][0] = cos(angleRad);
    matrix->values[0][1] = -sin(angleRad);
    matrix->values[0][2] = 0;
    matrix->values[1][0] = sin(angleRad);
    matrix->values[1][1] = cos(angleRad);
    matrix->values[1][2] = 0;
    matrix->values[2][0] = 0;
    matrix->values[2][1] = 0;
    matrix->values[2][2] = 1;
}