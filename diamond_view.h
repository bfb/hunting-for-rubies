class DiamondView {
    public:
      DiamondView(int r, int c, int ix, int iy) {
        cols = c; rows = r;
        initialX = ix;
        initialY = iy;
      }

      int getCols(){ return cols; }

      int getRows(){ return rows; }

      int getInitialX(){ return initialX; }

      int getInitialY(){ return initialY; }

      std::vector<Tile> build(int *m, int tileWidth, int tileHeight) {
        std::vector<Tile> map;

        for (int i = 0; i < rows; i++) { // height of the map
            for (int j = 0; j < cols; j++) { // width of the map

              int x = j * tileWidth / 2;
              int y = i * tileHeight;

              int xx = (x - y);
              int yy = ((x + y) / 2);

              xx = xx + initialX;
              yy = yy + initialY;

              Tile *tile = new Tile(xx, yy);
              tile->setTexture(m[i+j*cols]);

              map.push_back(*tile);

            }

        }


        return map;
      }

    private:
      // std::vector<Tile> map;
      int cols, rows, initialX, initialY;
};
