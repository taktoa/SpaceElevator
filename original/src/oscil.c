#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

#define NUMPOINTS 100
#define TIMESTEP ((double) 0.5)
#define BREAKPOINT 50

#define WIDTH 600
#define HEIGHT 600

typedef struct
{
    vector_t pos, v, f; // position, velocity, force
    GLdouble m; // mass
    GLdouble k; // spring rigidity
    GLdouble frict; // friction coefficient
    GLdouble initlen; // initial length of segment
    GLdouble tension; // tension
    GLdouble crosssect; // cross section
} point_t;


GLdouble c_Re, c_Ge, c_Slim, c_Vang,
    c_Ecnt, c_Dcnt, c_Clen, c_Fs,
    c_Mpay, c_Fr_cnt, c_Vele, c_Rgeo;

int numpoints;
point_t *points;
GLdouble curtime;
GLdouble maxforce, curforce;

void initConstants() {                              // --- Set constants
    c_Re = 6.36e6;                                  // Earth radius (m)
    c_Ge = 3.986e14;                                // Earth gravity (Me * G) (m^3 / s^2)
    c_Slim = 130e9;                                 // Cable max tensile strength (Pa)
    c_Vang = 7.3e-5;                                // Earth rotation (radians/s)
    c_Ecnt = 1e12;                                  // Young's modulus of cable (Pa)
    c_Dcnt = 1300;                                  // Density of cable (kg/m^3)
    c_Clen = 91e6;                                  // Cable length (m)
    c_Fs = 2;                                       // Factor of safety (DL)
    c_Mpay = 1.2e3;                                 // Payload mass (kg)
    c_Fr_cnt = 10;                                  // Friction coefficient of cable (DL)
    c_Vele = 55;                                    // Elevator target speed (m/s)
    c_Rgeo = pow(c_Ge / c_Vang / c_Vang, 1./3.);    // Geosynchronous orbit height (m)
}

void init()                                         // --- Initialization routine
{
    double tension = c_Mpay;
    double fcoef = 0;
    double mt = 0;

    curtime = 0;                                    // Set current time to 0
    numpoints = NUMPOINTS;                          // Set variable to macro
    points = smalloc((numpoints + 1) * sizeof(point_t)); // Allocate points (FIXME)

    for(int i = 0; i < numpoints; i++) {            // Loop over points
        vset(&points[i].pos, c_Clen * i / NUMPOINTS + c_Re, 0, 0);
        vset(&points[i].v, 0, 0, 0);

        points[i].crosssect = c_Fs * tension / c_Slim;
        points[i].k = c_Ecnt / (c_Clen / NUMPOINTS) * points[i].crosssect;
        points[i].initlen = (c_Clen / NUMPOINTS - tension / points[i].k);
        points[i].frict = c_Fr_cnt;
        mt += points[i].m = points[i].initlen * points[i].crosssect * c_Dcnt;

        fcoef = c_Ge / (points[i].pos.x * points[i].pos.x) - points[i].pos.x * c_Vang * c_Vang;
        tension += fcoef * points[i].m;
    }

    points[numpoints - 1].m = -tension / fcoef * 1; // FIXME

    if(0) {
        for(int i = 0; i < numpoints; i++) {
           printf("Item number: %d\n", i + 1);
           printf("Position: %f, %f, %f\n", points[i].pos.x, points[i].pos.y, points[i].pos.z);
           printf("Velocity: %f, %f, %f\n", points[i].v.x, points[i].v.y, points[i].v.z);
           printf("Force: %f, %f, %f\n", points[i].f.x, points[i].f.y, points[i].f.z);
           printf("Mass: %f\n", points[i].m);
           printf("Spring Constant: %f\n", points[i].k);
           printf("Friction Coefficient: %f\n", points[i].frict);
           printf("Initial Length: %f\n", points[i].initlen);
           printf("Cross Sectional Area: %f\n", points[i].crosssect);
        }
    } else if(1) {
        for(int i = 0; i < numpoints; i++) {
           //printf("[%d, ", i + 1);
           printf("[(%e, %e, %e), ", points[i].pos.x, points[i].pos.y, points[i].pos.z);
           printf("(%e, %e, %e), ", points[i].v.x, points[i].v.y, points[i].v.z);
           printf("(%e, %e, %e), ", points[i].f.x, points[i].f.y, points[i].f.z);
           printf("%e, ", points[i].m);
           printf("%e, ", points[i].k);
           printf("%e, ", points[i].frict);
           printf("%e, ", points[i].initlen);
           printf("%e]\n", points[i].crosssect);
        }
    }
}

inline void pointdynamics(point_t *curpt)           // Calculate point movement
{
    GLdouble r = vnorm(&curpt->pos);
    vector_t grav;
    vector_t rotf;
    vector_t coriolis;

    if(r > c_Re) {                                  // Points outside Earth
        grav = vscale(-c_Ge * curpt->m / pow(r,3), &curpt->pos);
        vaddto(&curpt->f, &grav);
    } else {                                        // Take care of points that
        vector_t scaled;                            // are inside Earth
        curpt->pos = vscale(c_Re / vnorm(&curpt->pos), &curpt->pos);
        scaled = vscale(-vdot(&curpt->pos, &curpt->v) / c_Re / c_Re, &curpt->pos);
        vaddto(&curpt->v, &scaled);
        curpt->v = vscale(0, &curpt->v);
    }

    rotf = vscale(c_Vang * c_Vang * curpt->m, &curpt->pos);
    rotf.z = 0;
    vset(&coriolis, 2 * curpt->v.y * curpt->m * c_Vang, -2 * curpt->v.x * curpt->m * c_Vang, 0);
    vaddto(&curpt->f, &rotf);
    vaddto(&curpt->f, &coriolis);
    vaddscaled(&curpt->v, TIMESTEP / curpt->m, &curpt->f);
    vaddscaled(&curpt->pos, TIMESTEP, &curpt->v);
    if(curtime <= 0) { curpt->v = vscale(.99, &curpt->v); }
}

void simul()
{
    for(int i = 0; i < numpoints; i++) { vset(&points[i].f, 0, 0, 0); }

    for(int i = 0; i < numpoints - 1; i++) {
        vector_t vdiff;
        GLdouble axialv, frict, elast;

        vector_t diff = vsub(&points[i+1].pos, &points[i].pos);
        GLdouble l = vnorm(&diff);
        vector_t f;

        elast = points[i].k * (1 - points[i].initlen / l);
        if(elast < 0) { elast = 0; }
        points[i].tension = elast * l;

        vdiff = vsub(&points[i+1].v, &points[i].v);
        axialv = vdot(&vdiff, &diff) / l;
        frict = axialv / l * points[i].frict;

        f = vscale(elast + frict, &diff);
        vaddto(&points[i].f, &f);
        vsubfrom(&points[i+1].f, &f);
    }

    for(int i = 0; i < numpoints; i++) {
        double loading = points[i].tension / points[i].crosssect / c_Slim;
        if(loading > 1 && curtime > 0) {
            points[i].k = 0;
            points[i].frict = 0;
        }
    }

    for(int i = 0; i < numpoints; i++) { pointdynamics(&points[i]); }

    {
        points[0].pos.x = c_Re * cos(0 / 180.0 * M_PI);
        points[0].pos.y = 0;
        points[0].pos.z = c_Re * sin(0 / 180.0 * M_PI);
        vset(&points[0].v, 0, 0, 0);
        if(curtime > 1) {
            points[BREAKPOINT].k = 0;
            points[BREAKPOINT].frict = 0;
        }
    }

    curtime += TIMESTEP;
}

void mainloop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glutWireSphere(c_Re,20,10);
    glutWireSphere(c_Rgeo,20,10);

    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < numpoints; i++) {
        if(i > 0 && points[i - 1].k == 0) {
            glEnd();
            glBegin(GL_LINE_STRIP);
        }
        glVertex3d(points[i].pos.x, points[i].pos.y, points[i].pos.z);
    }
    glEnd();

    glutSwapBuffers();

    for(int i = 0; i < 600; i++) { simul(); }
}

int main(int argc, char **argv)
{
    initConstants();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);

    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Elevator");
    glutDisplayFunc(mainloop);
    glutIdleFunc(mainloop);

    glMatrixMode(GL_MODELVIEW);
    glScaled(1/90e6,1/90e6,1/90e6);

    init();
    glutMainLoop();
    return 0;
}
