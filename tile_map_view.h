class TileMapView {
    public:
      TileMapView(int w, int h, int px, int py){
        width = w; height = h;
        x = px; y = py;
      }

      int getCols(){ return cols; }

      int getRows(){ return rows; }

      int getTileId(int x, y) {
        return map[x*y];
      }

      int calcPosition() {

      }



    private:
      int *pixels; // alternativamente char *pixels – 1 byte por canal
                    // neste caso, pixels = new char[w*h*3];
      int width, height, x, y;
};
