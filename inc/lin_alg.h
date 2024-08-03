#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#define PI 3.141592654f

typedef struct {
    float** values;
    int rowCount;
    int columnCount;
} Matrix;

typedef struct {
    float* values;
    int size;
} Vector;

void applyOperatorOn3dPoint(Matrix op, Vector* point);
void generateXRotationOperator(Matrix* matrix, float angle);
void generateYRotationOperator(Matrix* matrix, float angle);
void generateZRotationOperator(Matrix* matrix, float angle);

#ifdef __cplusplus
}
#endif