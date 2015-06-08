#include "includes.h"

using namespace std;

void display(void) {
    int tileWidth = 16;
    int tileHeight = 8;
    glClear (GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < 5; i++) { // height of the map
        for (int j = 0; j < 5; j++) { // width of the map

            if(i % 2 == 0 && j % 2 == 0) {
                glColor3d (0.5, 0.5, 0.7);
            } else if (i % 2 != 0 && j % 2 != 0) {
                glColor3d (0.2, 0.1, 0.4);
            } else if (i % 2 == 0 && j % 2 != 0) {
                glColor3d (0.4, 0.8, 0.2);
            } else {
                glColor3d (0.1, 0.9, 0.9);
            }

            int x = j * tileWidth / 2;
            int y = i * tileHeight;

            int xx = (x - y);
            int yy = ((x + y) / 2);

            cout << "{ x: ";
            cout << xx;
            cout << ", y: ";
            cout << yy;
            cout << " },";
            cout << endl;

            glBegin(GL_POLYGON);
            glVertex3f (xx, yy - tileHeight/2, 0.0);
            glVertex3f (xx - tileWidth/2, yy, 0.0);
            glVertex3f (xx, yy + tileHeight/2, 0.0);
            glVertex3f (xx + tileWidth/2, yy, 0.0);
            glEnd();

        }
    }

    // // first line

    // glColor3d (1, 1, 0.7);

    // glBegin(GL_POLYGON);
    // glVertex3f (tileWidth/2, 0.0, 0.0);
    // glVertex3f (0.0, tileHeight/2, 0.0);
    // glVertex3f (tileWidth/2, tileHeight, 0.0);
    // glVertex3f (tileWidth, tileHeight/2, 0.0);
    // glEnd();


    // glColor3d (0.5, 0.5, 0.7);

    // glBegin(GL_POLYGON);
    // glVertex3f (tileWidth/2 + tileWidth/2, 0.0 + tileHeight/2, 0.0);
    // glVertex3f (0.0 + tileWidth/2, tileHeight/2 + tileHeight/2, 0.0);
    // glVertex3f (tileWidth/2 + tileWidth/2, tileHeight + tileHeight/2, 0.0);
    // glVertex3f (tileWidth + tileWidth/2, tileHeight/2 + tileHeight/2, 0.0);
    // glEnd();

    // glColor3d (0.2, 0.2, 0.7);

    // glBegin(GL_POLYGON);
    // glVertex3f (tileWidth/2 + (tileWidth/2)*2, 0.0 + (tileHeight/2) * 2, 0.0);
    // glVertex3f (0.0 + (tileWidth/2)*2, tileHeight/2 + (tileHeight/2) * 2, 0.0);
    // glVertex3f (tileWidth/2 + (tileWidth/2) * 2, tileHeight + (tileHeight/2) * 2, 0.0);
    // glVertex3f (tileWidth + (tileWidth/2) * 2, tileHeight/2 + (tileHeight/2) * 2, 0.0);
    // glEnd();

    // glBegin(GL_POLYGON);
    // glVertex3f (tileWidth/2 + tileWidth/2, 0.0 + tileHeight/2, 0.0);
    // glVertex3f (0.0, tileHeight/2, 0.0);
    // glVertex3f (tileWidth/2, tileHeight, 0.0);
    // glVertex3f (tileWidth, tileHeight/2, 0.0);
    // glEnd();

    // for( int a = 0; a < 5; a++) {
    //     glColor3d (0.2, 0.2, 0.7);
    //     glBegin(GL_POLYGON);
    //     glVertex3f (tileWidth/2 + (tileWidth/2)*a, 0.0 + (tileHeight/2) * a, 0.0);
    //     glVertex3f (0.0 + (tileWidth/2)*a, tileHeight/2 + (tileHeight/2) * a, 0.0);
    //     glVertex3f (tileWidth/2 + (tileWidth/2) * a, tileHeight + (tileHeight/2) * a, 0.0);
    //     glVertex3f (tileWidth + (tileWidth/2) * a, tileHeight/2 + (tileHeight/2) * a, 0.0);
    //     glEnd();
    // }


    // for( int a = 0; a < 5; a++) {
    //     glColor3d (0.4, 0.3, 0.7);
    //     glBegin(GL_POLYGON);
    //     glVertex3f ((tileWidth/2 + (tileWidth/2)*a) + tileWidth/2, (0.0 + (tileHeight/2) * a) + tileHeight/2, 0.0);
    //     glVertex3f ((0.0 + (tileWidth/2)*a) + tileWidth/2, (tileHeight/2 + (tileHeight/2) * a) + tileHeight/2, 0.0);
    //     glVertex3f ((tileWidth/2 + (tileWidth/2) * a) + tileWidth/2, (tileHeight + (tileHeight/2) * a) + tileHeight/2, 0.0);
    //     glVertex3f ((tileWidth + (tileWidth/2) * a) + tileWidth/2, (tileHeight/2 + (tileHeight/2) * a) + tileHeight/2, 0.0);
    //     glEnd();
    // }




    glFlush ();
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGoal");
    init();
    glutDisplayFunc(display);
    // glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;   /* ISO C requires main to return int. */
}
