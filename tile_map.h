class TileMap {
    public:
      TileMap(int c, int r){
        cols = c; rows = r;
        map = new int[c*r];
      }

      int getCols(){ return cols; }

      int getRows(){ return rows; }

      int getTileId(int x, y) {
        return map[x*y];
      }

    private:
      int *pixels; // alternativamente char *pixels – 1 byte por canal
                    // neste caso, pixels = new char[w*h*3];
      int cols, rows;
};
