#include "includes.h"

using namespace std;

GLuint texture;
GLuint texture2;
GLuint texture3;
GLuint texture4;
GLuint textures[10];

Image *image;

int initialX = 400;
int initialY = 150;

int tileWidth = 60;
int tileHeight = 30;

int highlightX = 0;
int highlightY = 0;

// game status
int gameStatus = 1;

// game components
Character *character;
Enemy *enemy;
Tree *tree;
// PowerUp *powerUp;

TileMap *tileMap;

void loadTexture(GLuint texture, std::string filename){
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

    // glGenTextures( texture, textures );
    glBindTexture( GL_TEXTURE_2D, texture );

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0,
    GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());

    free(image);
}

void keyboard(unsigned char key, int x, int y) {
    cout << x;
    cout << " x ";
    cout << y;
    cout << endl;

    // character->move();


}

void checkCollision() {
    cout << "CHECK COLLISION" << endl;
    cout << character->getTileX() << "==" << enemy->getTileX() << endl;
    if (character->getTileX() == enemy->getTileX() && character->getTileY() == enemy->getTileY()) {
        // GAME OVER
        tileMap->highlightTile(character->getTileX(), character->getTileY());
        gameStatus = 0;
    }
}

void keyboardCommands(int key, int x, int y) {
    // DIRECTIONS:
    // - 0 = north
    // - 1 = east
    // - 3 = south
    // - 4 = west

    switch(key) {
        case GLUT_KEY_UP:
            character->setDirection(0);
            break;
        case GLUT_KEY_DOWN:
            character->setDirection(3);
            break;
        case GLUT_KEY_LEFT:
            character->setDirection(4);
            break;
        case GLUT_KEY_RIGHT:
            character->setDirection(1);
            break;
    }

    character->move();

    checkCollision();

    // getTileByPoints(character->getX(), character->getY());
    // tileMap->updateTileTexture(nearX, nearY, textures[1]);

    // tileMap->highlightNearest(character->getX(), character->getY());
    glutPostRedisplay();
}

void moveCharacter(Character *c, char direction) {
    c->move();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << x;
        cout << " x ";
        cout << y;
        cout << endl;

        // getTileByPoints(x,y);
        // Tile t = tileMap->getNearest(x,y);

        tileMap->highlightNearest(x, y);
        // cout << "NEAREST: " << t.getX() << "x" << t.getY() << endl;
        // tileMap->updateTileTexture(t.getX(), t.getY(), textures[1]);

        glutPostRedisplay();
    }
}

void renderGameOver() {
    int x = 0;
    int y = 10;
    int width = 300;
    int height = 50;

    glBindTexture( GL_TEXTURE_2D, textures[6]);
    glBegin(GL_POLYGON);
        glTexCoord2d(0, 0);
        glVertex3f (x + 0, y + 0, 0.0);
        glTexCoord2d(1, 0);
        glVertex3f (x + width, y + 0, 0.0);
        glTexCoord2d(1, 1);
        glVertex3f (x + width, y + height, 0.0);
        glTexCoord2d(0, 1);
        glVertex3f (x + 0, y + height, 0.0);
    glEnd();
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);

    if(gameStatus == 0) {
        renderGameOver();
    }

    // renders the tile map
    tileMap->render();

    enemy->render();
    // if(character->getX() > tree->getX()
    //     && character->getY() > tree->getY()
    //     || character->getY() > tree->getY()) {

    //     tree->render();
    //     character->render();
    // } else {
        character->render();
        // tree->render();
    // }

    // cout << character->getX() << "x" << character->getY() << " : " << enemy->getX() << "x" << enemy->getY() << endl;
    glFlush ();
}


void animateEnemy(int x) {
    enemy->move();
    checkCollision();
    glutPostRedisplay();

    if(gameStatus == 1) {
        glutTimerFunc(200, animateEnemy, 1);
    }

}


void init (void)
{
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

    glGenTextures(10, textures);

    loadTexture(textures[0], "images/floor.ptm");
    loadTexture(textures[1], "images/texture3.ptm");
    loadTexture(textures[2], "images/char.ptm");
    loadTexture(textures[3], "images/enemy.ptm");
    loadTexture(textures[4], "images/tree.ptm");
    loadTexture(textures[5], "images/collision.ptm");
    loadTexture(textures[6], "images/gameover.ptm");
    loadTexture(textures[7], "images/truck.ptm");
    // loadTexture(textures[8], "images/sphere.ptm");
    // loadTexture(textures[9], "images/powerup.ptm");

    // int map[100];
    // for(int i = 0; i < 100; i++) {
    //     if(i < 10){
    //         map[i] = textures[1];
    //     } else {
    //         map[i] = textures[0];
    //     }

    // }

    // map[2] = textures[1];
    // // map[12] = textures[1];
    // // map[44] = textures[1];

    int map[100] = {textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1],
        textures[1], textures[0], textures[1], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[1],
        textures[1], textures[0], textures[1], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[1],
        textures[1], textures[0], textures[1], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[1],
        textures[1], textures[0], textures[1], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[1],
        textures[1], textures[0], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1],
        textures[1], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[1],
        textures[1], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[1],
        textures[1], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[0], textures[1],
        textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1], textures[1]};

    tileMap = new TileMap(10, 10, tileWidth, tileHeight, initialX, initialY,
                            textures[5], textures[1], map);


    character = new Character(tileMap, initialX, initialY, 30, 60, textures[2]);
    enemy = new Enemy(tileMap, initialX + 50, initialY + 20, 30, 60, textures[3]);
    // enemy = new Enemy(tileMap, initialX + 50, initialY + 20, 100, 80, textures[7]);
    // enemy = new Enemy(tileMap, initialX + 50, initialY + 20, 30, 30, textures[8]);
    enemy->setDirection(3);

    // tree = new Tree(initialX - 20, initialY - 20, 80, 110, textures[4]);
    // powerUp = new PowerUp(tileMap, initialX - 20, initialY - 20, 80, 110, textures[9]);

    // animateEnemy(0);
    glutMainLoop();

    return 0;   /* ISO C requires main to return int. */
}
