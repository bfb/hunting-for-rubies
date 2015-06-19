#include "includes.h"

using namespace std;

GLuint texture;
GLuint texture2;
GLuint texture3;
GLuint texture4;

Image *image;

int initialX = 400;
int initialY = 150;

int tileWidth = 60;
int tileHeight = 30;

int highlightX = 0;
int highlightY = 0;

Character *character;
Character *character2;

GLuint loadImageTexture(std::string filename){

    // ifstream is used for reading files
    ifstream inf(filename);

    // If we couldn't open the output file stream for reading
    if (!inf) {
      // Print an error and exit
      cerr << "File error: " + filename << endl;
      exit(1);
    }

    std::string format;
    std::string width;
    std::string height;
    std::string max;

    inf >> format;
    inf >> width;
    inf >> height;
    inf >> max;

    std::string r;
    std::string g;
    std::string b;
    std::string a;

    // Image *image = new Image(std::stoi(width), std::stoi(height));
    image = new Image(std::stoi(width), std::stoi(height));

    for(int y = 0; y < image->getHeight(); y++) {
        for(int x = 0; x < image->getWidth(); x++) {
          inf >> a;
          inf >> r;
          inf >> g;
          inf >> b;

          int rgb = (std::stoi(a) << 24) | (std::stoi(r) << 16) | (std::stoi(g) << 8) | std::stoi(b);
          // int rgb = (std::stoi(r) << 16) | (std::stoi(g) << 8) | std::stoi(b) | (std::stoi(a) << 24);
          // int rgb = (std::stoi(r) << 24) | (std::stoi(g) << 16) | std::stoi(b) << 8 | (std::stoi(a) << 24);

          image->setPixel(rgb, x, y);
        }
    }

    GLuint texture;

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );


    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0,
GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());

    return texture;
}

GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *) malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
GL_MODULATE ); //set texture environment parameters

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
GL_LINEAR );

    //Here we are setting the parameter to repeat the texture instead of clamping the texture
    //to the edge of our shape.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
GL_REPEAT );

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return texture; //return whether it was successfull
}

// iterate over all tiles check the distance between x and y
// if this distance is major than width or height the click was in an invalid area
void getTileByPoints(int px, int py) {

    int xx;
    int yy;

    int nearX = 0;
    int nearY = 0;

    int currentX;
    int currentY;

    float minDistance = 99999;

    for (int i = 0; i < 10; i++) { // height of the map
        for (int j = 0; j < 10; j++) { // width of the map

            int x = j * tileWidth / 2;
            int y = i * tileHeight;

            xx = (x - y);
            yy = ((x + y) / 2);

            xx = xx + initialX;
            yy = yy + initialY;

            float distance = sqrt(pow((double) (px - xx), 2) + pow((double) (py - yy), 2));

            if(distance < minDistance) {
                minDistance = distance;

                nearX = xx;
                nearY = yy;
            }

        }
    }

    highlightX = nearX;
    highlightY = nearY;
}


void keyboard(unsigned char key, int x, int y) {
    cout << x;
    cout << " x ";
    cout << y;
    cout << endl;

    // character->move();


}

void keyboardCommands(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            character->move('N');
            break;
        case GLUT_KEY_DOWN:
            character->move('S');
            break;
        case GLUT_KEY_LEFT:
            character->move('W');
            break;
        case GLUT_KEY_RIGHT:
            character->move('E');
            break;
    }

    getTileByPoints(character->getX(), character->getY());
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << x;
        cout << " x ";
        cout << y;
        cout << endl;

        getTileByPoints(x,y);
        glutPostRedisplay();
    }

}

void display(void) {


    glClear (GL_COLOR_BUFFER_BIT);

    glBindTexture( GL_TEXTURE_2D, texture2 );

    for (int i = 0; i < 10; i++) { // height of the map
        for (int j = 0; j < 10; j++) { // width of the map

            int x = j * tileWidth / 2;
            int y = i * tileHeight;

            int xx = (x - y);
            int yy = ((x + y) / 2);

            xx = xx + initialX;
            yy = yy + initialY;

            if(xx == highlightX && yy == highlightY) {
                glBindTexture( GL_TEXTURE_2D, texture4 );
            } else {
                glBindTexture( GL_TEXTURE_2D, texture2 );
            }

            // // DEBUG ANCHOR POINTS
            // cout << "{ x: ";
            // cout << xx;
            // cout << ", y: ";
            // cout << yy;
            // cout << " },";
            // cout << endl;

            glBegin(GL_POLYGON);

            // glTexCoord2d(0.0f, 0.0f);
            glTexCoord2d(0, 0);
            glVertex3f (xx, yy - tileHeight/2, 0.0);

            // glTexCoord2d(0.0f, 1.0f);
            glTexCoord2d(0, 1);
            glVertex3f (xx - tileWidth/2, yy, 0.0);

            // glTexCoord2d(1.0f, 1.0f);
            glTexCoord2d(1, 1);
            glVertex3f (xx, yy + tileHeight/2, 0.0);

            // glTexCoord2d(1.0f, 0.0f);
            glTexCoord2d(1, 0);
            glVertex3f (xx + tileWidth/2, yy, 0.0);

            glEnd();

        }
    }

    glBindTexture( GL_TEXTURE_2D, texture );
    character->render();
    character2->render();

    // glDrawPixels(image->getWidth(), image->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getPixels());

    glFlush ();
}


void animateCharacter(int x) {
    character2->move('W');
    glutPostRedisplay();
    glutTimerFunc(200, animateCharacter, 1);
}


void init (void)
{
    // glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearColor( 1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );

    // // transparency
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glOrtho(0.0f, 800, 600, 0.0f, 0.0f, 1.0f);
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
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGoal");
    init();
    glutDisplayFunc(display);
    // glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardCommands);
    glutMouseFunc(mouse);


    texture2 = LoadTexture("images/texture2.raw", 256, 256);
    texture3 = LoadTexture("images/texture3.raw", 256, 256);
    // texture4 = loadImageTexture("texture.ptm");
    texture4 = loadImageTexture("images/texture3.ptm");
    texture = loadImageTexture("images/char.ptm");

    character = new Character(initialX, initialY, 30, 60);
    character2 = new Character(initialX + 50, initialY + 20, 30, 60);
    animateCharacter(0);
    glutMainLoop();

    return 0;   /* ISO C requires main to return int. */
}
