class Element {
    public:

      // current anchor x and y for colision

      // get a real X position
      int getX(){ return (width/2) + x; }

      // get a real Y position
      int getY(){ return height-5 + y; }

      int getTexture() { return texture; }

    private:
      int x, y, width, height, texture;
};
