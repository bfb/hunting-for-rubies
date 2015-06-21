class Enemy {
    public:
      Enemy(TileMap *tp, int px, int py, int w, int h, int t){
        x = px; y = py;
        width = w; height = h;
        texture = t;
        tileMap = tp;

        Tile tile = tileMap->getNearest(getX(), getY());
        tileY = tile.getY();
        tileX = tile.getX();
      }

      // current anchor x and y for colision

      // get a real X position
      int getX(){ return (width/2) + x; }

      // get a real Y position
      int getY(){ return height-5 + y; }

      int getTexture() { return texture; }

      int getTileX() {
        return tileX;
      }

      int getTileY() {
        return tileY;
      }

      void setTileX(int tx) {
        tileX = tx;
        x = tx;
      }

      void setTileY(int ty) {
        tileY = ty;
        y = ty;
      }

      void setDirection(int d) {
        direction = d;
      }

      /* DIRECTIONS:
          - 0 = north
          - 1 = east
          - 2 = south
          - 3 = west
          - 4 = ne
          - 5 = se
          - 6 = sw
          - 7 = nw
      */
      void move() {

        // find current tile
        Tile tile = tileMap->getNearest(getX(), getY());

        // // check if tiles is a boundary
        // if(tileMap->getBoundaryTexture() == tile.getTexture()) {
        //   // calculate direction
        //   int nextDirection = rand() % 7;
        //   while(direction == nextDirection) {
        //     nextDirection = rand() % 7;
        //   }

        //   // if(direction == 0) {

        //   //   direction =
        //   // }

        //   direction = nextDirection;
        // }




        switch(direction) {
          case 0:
              y -= 10;
              break;
            case 1:
              x += 10;
              break;
            case 2:
              y+= 10;
              break;
            case 3:
              x -= 10;
              break;
            case 4:
              x += 10;
              y -= 5;
              break;
            case 5:
              x += 10;
              y += 5;
              break;
            case 6:
              x -= 10;
              y += 5;
              break;
            case 7:
              x -= 10;
              y -= 5;
              break;
        }

        // update current tile
        tile = tileMap->getNearest(getX(), getY());
        tileY = tile.getY();
        tileX = tile.getX();

      }

      void render() {
          // glColor3d (0.5, 0.5, 0.7);
        glBindTexture( GL_TEXTURE_2D, texture);
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

    private:
      int x, y, width, height, texture, tileX, tileY, direction;
      TileMap *tileMap;
};
