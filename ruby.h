class Ruby {
    public:
      Ruby(int px, int py, int w, int h, int t){
        x = px; y = py;
        width = w; height = h;
        texture = t;
      }

      Ruby(TileMap *tp, int w, int h, int t, std::vector<Tile> tl){
        width = w; height = h;
        texture = t;
        tileMap = tp;
        tiles = tl;

        // calculateTile();
        randomPosition();
      }

      void calculateTile() {
        Tile tile = tileMap->getNearest(getX(), getY());
        tileY = tile.getY();
        tileX = tile.getX();
      }

      void randomPosition() {
        Tile t = tiles.at(rand() % tiles.size());
        setTileX(t.getX());
        setTileY(t.getY());
      }

      // get a real X position
      int getX(){ return x - (width/2); }

      // get a real Y position
      int getY(){ return y - height; }

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

      void render() {
          glBindTexture( GL_TEXTURE_2D, texture);
          glBegin(GL_POLYGON);
              glTexCoord2d(0, 0);
              glVertex3f (getX() + 0, getY() + 0, 0.0);
              glTexCoord2d(1, 0);
              glVertex3f (getX() + width, getY() + 0, 0.0);
              glTexCoord2d(1, 1);
              glVertex3f (getX() + width, getY() + height, 0.0);
              glTexCoord2d(0, 1);
              glVertex3f (getX() + 0, getY() + height, 0.0);
          glEnd();
      }

    private:
      int x, y, width, height, texture, tileX, tileY, direction;
      std::vector<Tile> tiles;
      TileMap *tileMap;
};
