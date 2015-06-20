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
      }

      void setTileY(int ty) {
        tileY = ty;
      }

      void setDirection(int d) {
        direction = d;
      }

      // DIRECTIONS:
      // - 0 = north
      // - 1 = east
      // - 3 = south
      // - 4 = west
      void move() {
        switch(direction) {
          case 0:
            y -= 10;
            break;
          case 3:
            y += 10;
            break;
          case 1:
            x -= 10;
            break;
          case 4:
            x += 10;
            break;
        }

        // find current tile
        Tile tile = tileMap->getNearest(getX(), getY());
        tileY = tile.getY();
        tileX = tile.getX();

        if(tileMap->getBoundaryTexture() == tile.getTexture()) {
          // calculate direction
          switch(direction) {
            case 0:
              direction = 3;
              break;
            case 1:
              direction = 4;
              break;
            case 3:
              direction = 0;
              break;
            case 4:
              direction = 1;
              break;
          }

        }
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
