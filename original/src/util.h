#ifndef UTIL_H
#define UTIL_H
typedef struct
{
  GLdouble x;
  GLdouble y;
  GLdouble z;
} vector_t;

void *smalloc(size_t s);
inline void vset(vector_t *v, GLdouble x, GLdouble y, GLdouble z);
inline void vaddto(vector_t *vd, vector_t *vs);
inline void vaddscaled(vector_t *vd, GLdouble s, vector_t *vs);
inline void vsubfrom(vector_t *vd, vector_t *vs);
inline GLdouble vdot(vector_t *v1, vector_t *v2);
inline vector_t vcross(vector_t *v1, vector_t *v2);
inline vector_t vscale(GLdouble s, vector_t *v);
inline vector_t vsub(vector_t *v1, vector_t *v2);
inline GLdouble vnorm(vector_t *v);
inline GLdouble vdist(vector_t *v1, vector_t *v2);
#endif
