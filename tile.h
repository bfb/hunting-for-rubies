class Tile {
    public:
      Tile(int px, int py){
        x = px; y = py;
      }

      Tile(int px, int py, int t){
        x = px; y = py;
        texture = t;
      }

      // anchor x
      int getX(){ return x; }

      // anchor y
      int getY(){ return y; }

      int getTexture() { return texture; }

      void setTexture(int t) {
        texture = t;
      }

    private:
      int x, y, texture;
};
