class TileMap {
    public:
      TileMap(int c, int r, int tw, int th,
              int ix, int iy, int ht, int bt, int *m){

        cols = c; rows = r;
        tileWidth = tw;
        tileHeight = th;
        initialX = ix;
        initialY = iy;
        highlightTexture = ht;
        boundaryTexture = bt;

        build(m);
      }

      void build(int *m) {
        for (int i = 0; i < rows; i++) { // height of the map
            for (int j = 0; j < cols; j++) { // width of the map

              int x = j * tileWidth / 2;
              int y = i * tileHeight;

              int xx = (x - y);
              int yy = ((x + y) / 2);

              xx = xx + initialX;
              yy = yy + initialY;

              // Tile *tile = new Tile(xx, yy, m[i*j]);
              Tile *tile = new Tile(xx, yy);

              // std::cout << xx << "x" << yy << " = ";
              // std::cout << tile->getX() << "x" << tile->getY() << " Texture: " << tile->getTexture() << "\n";
              map.push_back(*tile);
              // std::cout << i << ":" << j << std::endl;
            }
        }

        for(int i = 0; i < map.size(); i ++) {
          map.at(i).setTexture(m[i]);
        }
      }


      void updateTileTexture(int x, int y, int t) {
        // std::cout << "UPDATE TILE: " << x << "x" << y << " Texture: " << t << std::endl;
        for(int i = 0; i < map.size(); i++) {
          Tile tile = map.at(i);

          // std::cout << "W?? " << tile.getX() << "x" << tile.getY() << std::endl;

          if(tile.getX() == x && tile.getY() == y) {
            // std::cout << "FOUND";
            map.at(i).setTexture(t);

            // std::cout << "TEXT: " << map.at(i).getTexture() << std::endl;
            // map[i] = tile;

            break;
          }


        }
      }

      void setCurrent(int x, int y) {
        currentX = x;
        currentY = y;
      }

      Tile getNearest(int px, int py) {
          // int xx;
          // int yy;

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

              // std::cout << "RENDER: " << tile.getX() << "x" << tile.getY() << " Texture: " << tile.getTexture() << "\n";

              if(tile.getX() == currentX && tile.getY() == currentY) {
                  glBindTexture( GL_TEXTURE_2D, highlightTexture);
              } else {
                  glBindTexture( GL_TEXTURE_2D, tile.getTexture());
              }

              glBegin(GL_POLYGON);

              // glTexCoord2d(0.0f, 0.0f);
              glTexCoord2d(0, 0);
              glVertex3f (tile.getX(), tile.getY() - tileHeight/2, 0.0);

              // glTexCoord2d(0.0f, 1.0f);
              glTexCoord2d(0, 1);
              glVertex3f (tile.getX() - tileWidth/2, tile.getY(), 0.0);

              // glTexCoord2d(1.0f, 1.0f);
              glTexCoord2d(1, 1);
              glVertex3f (tile.getX(), tile.getY() + tileHeight/2, 0.0);

              // glTexCoord2d(1.0f, 0.0f);
              glTexCoord2d(1, 0);
              glVertex3f (tile.getX() + tileWidth/2, tile.getY(), 0.0);

              glEnd();
          }
      }

      int getCols(){ return cols; }

      int getRows(){ return rows; }

      int getBoundaryTexture() { return boundaryTexture; }

      int getTileWidth(){ return tileWidth; }

      int getTileHeight(){ return tileHeight; }

      std::vector<Tile> getMap() { return map; }

      Tile getTile(int x, int y) {
        return map[x*y];
      }

    private:
      std::vector<Tile> map;
      int cols, rows, initialX, initialY, tileWidth, tileHeight, currentX, currentY, highlightTexture, boundaryTexture;
};
