class TileMap {
    public:
      TileMap(DiamondView *v, int tw, int th, int ht, int bt, int *m){
        tileWidth = tw;
        tileHeight = th;
        highlightTexture = ht;
        boundaryTexture = bt;
        view = v;

        build(m);
      }

      void build(int *m) {
        map = view->build(m, tileWidth, tileHeight);
      }

      void updateTileTexture(int x, int y, int t) {
        for(int i = 0; i < map.size(); i++) {
          Tile tile = map.at(i);

          if(tile.getX() == x && tile.getY() == y) {
            map.at(i).setTexture(t);

            break;
          }


        }
      }

      void setCurrent(int x, int y) {
        currentX = x;
        currentY = y;
      }

      Tile getNearest(int px, int py) {
          int nearX = 0;
          int nearY = 0;

          int currentX;
          int currentY;

          Tile *near;

          float minDistance = 99999;

          for(int i = 0; i < map.size(); i++) {
              Tile tile = map.at(i);
              int xx = tile.getX();
              int yy = tile.getY();

              float distance = sqrt(pow((double) (px - xx), 2) + pow((double) (py - yy), 2));

              if(distance < minDistance) {

                  minDistance = distance;

                  nearX = xx;
                  nearY = yy;

                  near = &map.at(i);
              }
          }

          return *near;
      }

      void highlightNearest(int x, int y) {
          Tile near = getNearest(x, y);

          currentX = near.getX();
          currentY = near.getY();

          std::cout << "HIGHLIGHT: " << currentX << "x" << currentY << std::endl;
      }

      void highlightTile(int x, int y) {
          currentX = x;
          currentY = y;
      }

      Tile getTileByPosition(int x, int y) {
        for(int i = 0; i < map.size(); i++) {
            Tile tile = map.at(i);

            if(tile.getX() == x && tile.getY() == y)
                return map.at(i);
        }
      }

      void render(){
          for(int i = 0; i < map.size(); i++) {
              Tile tile = map.at(i);

              if(tile.getX() == currentX && tile.getY() == currentY) {
                  glBindTexture( GL_TEXTURE_2D, highlightTexture);
              } else {
                  glBindTexture( GL_TEXTURE_2D, tile.getTexture());
              }

              glBegin(GL_POLYGON);

              glTexCoord2d(0, 0);
              glVertex3f (tile.getX(), tile.getY() - tileHeight/2, 0.0);

              glTexCoord2d(0, 1);
              glVertex3f (tile.getX() - tileWidth/2, tile.getY(), 0.0);

              glTexCoord2d(1, 1);
              glVertex3f (tile.getX(), tile.getY() + tileHeight/2, 0.0);

              glTexCoord2d(1, 0);
              glVertex3f (tile.getX() + tileWidth/2, tile.getY(), 0.0);

              glEnd();
          }
      }

      int getCols(){ return view->getCols(); }

      int getRows(){ return view->getRows(); }

      int getBoundaryTexture() { return boundaryTexture; }

      int getTileWidth(){ return tileWidth; }

      int getTileHeight(){ return tileHeight; }

      std::vector<Tile> getMap() { return map; }

      Tile getTile(int x, int y) {
        return map[x*y];
      }

    private:
      std::vector<Tile> map;
      DiamondView *view;
      int cols, rows, initialX, initialY, tileWidth, tileHeight, currentX, currentY, highlightTexture, boundaryTexture;
};
