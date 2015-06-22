#include "includes.h"

using namespace std;

GLuint textures[40];

// initial position to start the map
int initialX = 400;
int initialY = 150;

int cols = 10;
int rows = 10;

// tile size
int tileWidth = 60;
int tileHeight = 30;

int scoreX = 40;
int scoreY = 580;

// game status
int gameStatus = 1;

// game components
Character *character;

Tree *tree;
Ruby *ruby;

std::vector<Enemy> enemies;
std::vector<Ruby> gameScore;

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

    Image *image = new Image(std::stoi(width), std::stoi(height));
    // image = new Image(std::stoi(width), std::stoi(height));

    for(int y = 0; y < image->getHeight(); y++) {
        for(int x = 0; x < image->getWidth(); x++) {
          inf >> a;
          inf >> r;
          inf >> g;
          inf >> b;

          int rgb = (std::stoi(a) << 24) | (std::stoi(r) << 16) | (std::stoi(g) << 8) | std::stoi(b);
          // int rgb = (std::stoi(r) << 24) | (std::stoi(g) << 16) | (std::stoi(b) << 8) | (std::stoi(a));



          // int rgb = (std::stoi(r) << 16) | (std::stoi(g) << 8) | std::stoi(b) | (std::stoi(a) << 24);
          // int rgb = (std::stoi(r) << 24) | (std::stoi(g) << 16) | std::stoi(b) << 8 | (std::stoi(a) << 24);

          image->setPixel(rgb, x, y);
        }
    }

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

void checkEnemyCollision() {
    for(int i = 0; i < enemies.size(); i++) {
        Enemy *current = &enemies.at(i);

        if (character->getTileX() == current->getTileX() && character->getTileY() == current->getTileY()) {
            // GAME OVER
            tileMap->highlightTile(character->getTileX(), character->getTileY());
            gameStatus = 0;

            break;
        }
    }
}

void checkRubyCollision() {
    if (character->getTileX() == ruby->getTileX() && character->getTileY() == ruby->getTileY()) {
        // INCREASE SCORE
        // tileMap->highlightTile(character->getTileX(), character->getTileY());

        Ruby *r = new Ruby((gameScore.size() + 1) * (scoreX), scoreY, 30, 30, textures[9]);
        gameScore.push_back(*r);

        // get another position
        ruby->randomPosition();

        glutPostRedisplay();
    }
}

void keyboardCommands(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            character->setDirection(0);
            break;
        case GLUT_KEY_DOWN:
            character->setDirection(2);
            break;
        case GLUT_KEY_LEFT:
            character->setDirection(3);
            break;
        case GLUT_KEY_RIGHT:
            character->setDirection(1);
            break;
        case 'i':
            character->setDirection(4);
            break;
        case 'l':
            character->setDirection(5);
            break;
        case 'k':
            character->setDirection(6);
            break;
        case 'j':
            character->setDirection(7);
            break;
    }

    character->move();

    checkEnemyCollision();
    checkRubyCollision();

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << x;
        cout << " x ";
        cout << y;
        cout << endl;

        tileMap->highlightNearest(x, y);

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

    // render score
    for(int i = 0; i < gameScore.size(); i++) {
        gameScore.at(i).render();
    }

    // renders the tile map
    tileMap->render();

    for(int i = 0; i < enemies.size(); i++) {
        Enemy *current = &enemies.at(i);
        if(character->getX() + 20 > current->getX() ||
           character->getY() > current->getY()){
            current->render();
        }
    }



    ruby->render();

    // if(character->getX() + 20 < tree->getX() ||
    //        character->getY() < tree->getY()){
    //     character->render();
    //     tree->render();
    // } else {
    //     tree->render();
    //     character->render();
    // }

    character->render();

    for(int i = 0; i < enemies.size(); i++) {
        Enemy *current = &enemies.at(i);
        if(character->getX() + 20 < current->getX() ||
           character->getY() < current->getY()){
            current->render();
        }
    }

    // for(int i = 0; i < enemies.size(); i++) {
    //     enemies.at(i).render();
    // }

    tree->render();


    glFlush ();
}

void animateEnemy(int e) {
    Enemy *current = &enemies.at(e);
    current->move();
    checkEnemyCollision();

    glutPostRedisplay();

    if(gameStatus == 1) {
        glutTimerFunc(50, animateEnemy, e);
    }
}

void init (void)
{
    glClearColor( 1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // transparency
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable( GL_TEXTURE_2D );

    glOrtho(0.0f, 800, 600, 0.0f, 0.0f, 1.0f);
}

void loadAllTextures() {
    glGenTextures(40, textures);

    loadTexture(textures[0], "images/grass.ptm");
    loadTexture(textures[1], "images/grass.ptm");
    loadTexture(textures[2], "images/sidewalk_central.ptm");
    loadTexture(textures[3], "images/enemy.ptm");
    loadTexture(textures[4], "images/tree.ptm");
    loadTexture(textures[5], "images/selected.ptm");
    loadTexture(textures[6], "images/gameover.ptm");
    loadTexture(textures[7], "images/grass_with_water.ptm");
    loadTexture(textures[8], "images/sphere.ptm");
    loadTexture(textures[9], "images/ruby.ptm");
    loadTexture(textures[18], "images/sidewalk.ptm");
    loadTexture(textures[19], "images/sidewalk2.ptm");
    loadTexture(textures[20], "images/grass_with_flower.ptm");
    loadTexture(textures[21], "images/grass_with_flower2.ptm");

    // character textures
    loadTexture(textures[10], "images/charN.ptm");
    loadTexture(textures[11], "images/charE.ptm");
    loadTexture(textures[12], "images/charS.ptm");
    loadTexture(textures[13], "images/charW.ptm");
    loadTexture(textures[14], "images/charNE.ptm");
    loadTexture(textures[15], "images/charSE.ptm");
    loadTexture(textures[16], "images/charSW.ptm");
    loadTexture(textures[17], "images/charNW.ptm");
}

void createMap() {

    int map[100] = {textures[1], textures[1], textures[1], textures[1], textures[18], textures[1], textures[1], textures[1], textures[1], textures[1],
                    textures[1], textures[0], textures[21], textures[0], textures[18], textures[0], textures[0], textures[0], textures[0], textures[1],
                    textures[19], textures[19], textures[19], textures[19], textures[2], textures[19], textures[19], textures[19], textures[19], textures[19],
                    textures[1], textures[0], textures[0], textures[0], textures[18], textures[0], textures[0], textures[0], textures[0], textures[1],
                    textures[1], textures[0], textures[0], textures[0], textures[18], textures[0], textures[0], textures[7], textures[0], textures[1],
                    textures[1], textures[20], textures[0], textures[0], textures[18], textures[0], textures[0], textures[0], textures[0], textures[1],
                    textures[1], textures[0], textures[0], textures[0], textures[18], textures[0], textures[0], textures[0], textures[0], textures[1],
                    textures[1], textures[7], textures[0], textures[0], textures[18], textures[0], textures[21], textures[0], textures[0], textures[1],
                    textures[1], textures[0], textures[0], textures[20], textures[18], textures[0], textures[0], textures[0], textures[0], textures[1],
                    textures[1], textures[1], textures[1], textures[1], textures[18], textures[1], textures[1], textures[1], textures[1], textures[1]};

    tileMap = new TileMap(cols, rows, tileWidth, tileHeight, initialX, initialY,
                            textures[5], textures[1], map);

    tree = new Tree(240, 270, 80, 110, textures[4]);
}

void createCharacter() {
    // char textures vector
    std::vector<int> ct;
    ct.push_back(textures[10]);
    ct.push_back(textures[11]);
    ct.push_back(textures[12]);
    ct.push_back(textures[13]);
    ct.push_back(textures[14]);
    ct.push_back(textures[15]);
    ct.push_back(textures[16]);
    ct.push_back(textures[17]);
    ct.push_back(textures[18]);

    character = new Character(tileMap, initialX, initialY, 30, 60, ct);
}

void createRuby() {
    std::vector<Tile> possibleTiles;

    // possible tiles to drop the ruby
    Tile *t;

    t = new Tile(550, 285);
    possibleTiles.push_back(*t);

    t = new Tile(490, 345);
    possibleTiles.push_back(*t);

    t = new Tile(400, 300);
    possibleTiles.push_back(*t);

    t = new Tile(310, 285);
    possibleTiles.push_back(*t);

    t = new Tile(190, 285);
    possibleTiles.push_back(*t);

    t = new Tile(370, 225);
    possibleTiles.push_back(*t);

    t = new Tile(520, 240);
    possibleTiles.push_back(*t);

    t = new Tile(400, 180);
    possibleTiles.push_back(*t);

    t = new Tile(370, 375);
    possibleTiles.push_back(*t);

    t = new Tile(310, 225);
    possibleTiles.push_back(*t);

    ruby = new Ruby(tileMap, 30, 30, textures[9], possibleTiles);
}

void createEnemies() {
    Enemy *enemy = new Enemy(tileMap, 340, 240, 30, 30, textures[8]);
    enemy->setDirection(5);

    Enemy *enemy2 = new Enemy(tileMap, 490, 285, 30, 30, textures[8]);
    enemy2->setDirection(2);

    Enemy *enemy3 = new Enemy(tileMap, 520, 300, 30, 30, textures[8]);
    enemy3->setDirection(1);

    Enemy *enemy4 = new Enemy(tileMap, 250, 285, 30, 30, textures[8]);
    enemy4->setDirection(4);

    enemies.push_back(*enemy);
    enemies.push_back(*enemy2);
    enemies.push_back(*enemy3);
    enemies.push_back(*enemy4);

    animateEnemy(0);
    animateEnemy(1);
    animateEnemy(2);
    animateEnemy(3);
}

void loadGame() {
    createMap();
    createCharacter();
    createRuby();
    createEnemies();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hunting for Rubies");
    init();
    glutDisplayFunc(display);
    // glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardCommands);
    glutMouseFunc(mouse);

    loadAllTextures();
    loadGame();


    // enemy = new Enemy(tileMap, initialX + 50, initialY + 20, 30, 60, textures[3]);
    // enemy = new Enemy(tileMap, 280, 210, 100, 80, textures[7]);



    glutMainLoop();

    return 0;   /* ISO C requires main to return int. */
}


