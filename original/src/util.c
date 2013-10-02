#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *smalloc(size_t s)
{
    void *p = malloc(s);
    if(p) { return p; }
    fprintf(stderr, "Can't malloc.\n");
    exit(1);
}

typedef struct
{
  GLdouble x;
  GLdouble y;
  GLdouble z;
} vector_t;

inline void vset(vector_t *v, GLdouble x, GLdouble y, GLdouble z)
{
  v->x = x;
  v->y = y;
  v->z = z;
}

inline void vaddto(vector_t *vd, vector_t *vs)
{
  vd->x += vs->x;
  vd->y += vs->y;
  vd->z += vs->z;
}

inline void vaddscaled(vector_t *vd, GLdouble s, vector_t *vs)
{
  vd->x += s * vs->x;
  vd->y += s * vs->y;
  vd->z += s * vs->z;
}

inline void vsubfrom(vector_t *vd, vector_t *vs)
{
  vd->x -= vs->x;
  vd->y -= vs->y;
  vd->z -= vs->z;
}

inline GLdouble vdot(vector_t *v1, vector_t *v2)
{
  return 
    v1->x * v2->x +
    v1->y * v2->y +
    v1->z * v2->z;
}   

inline vector_t vcross(vector_t *v1, vector_t *v2)
{
  vector_t vo;

  vo.x = v1->y * v2->z - v1->z * v2->y;
  vo.y = v1->z * v2->x - v1->x * v2->z;
  vo.z = v1->x * v2->y - v1->y * v2->x;

  return vo;
}
  
inline vector_t vscale(GLdouble s, vector_t *v)
{
  vector_t vd;
  vd.x = s*v->x;
  vd.y = s*v->y;
  vd.z = s*v->z;
  return vd;
}

inline vector_t vsub(vector_t *v1, vector_t *v2)
{
  vector_t v;
  v.x = v1->x - v2->x;
  v.y = v1->y - v2->y;
  v.z = v1->z - v2->z;
  return v;
}

inline GLdouble vnorm(vector_t *v)
{
  return sqrt(vdot(v, v));
}

inline GLdouble vdist(vector_t *v1, vector_t *v2)
{
  vector_t d = vsub(v1, v2);
  
  return vnorm(&d);
}
