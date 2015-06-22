class DiamondView : public View {
    public:
     DiamondView(int r, int c, int ix, int iy) : View(r, c, ix, iy)

      void build(int *m) {
        std::vector<Tile> map;
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
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
};
