class View {
 public:
  View(int r, int c, int ix, int iy) {
    rows = r;
    cols = c;
    initialX = ix;
    initialY = iy;
  }

  void build(int *m) {
    // don't know how to build maps
  }

  int getCols(){ return cols; }
  int getRows(){ return rows; }

 private:
  int rols, cols, initialX, initialY;
};
