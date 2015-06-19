class Character {
    public:
      Character(int px, int py, int w, int h){
        x = px; y = py;
        width = w; height = h;
      }

      // get a real X position
      int getX(){ return (width/2) + x; }

      // get a real Y position
      int getY(){ return height-5 + y; }

      void move(unsigned char direction) {
        switch(direction) {
          case 'N':
            y -= 10;
            break;
          case 'S':
            y += 10;
            break;
          case 'W':
            x -= 10;
            break;
          case 'E':
            x += 10;
            break;
        }
      }

      void render() {
          // glColor3d (0.5, 0.5, 0.7);
          glBegin(GL_POLYGON);
              glTexCoord2d(0, 0);
              glVertex3f (x + 0, y + 0, 0.0);
              glTexCoord2d(1, 0);
              glVertex3f (x + width, y + 0, 0.0);
              glTexCoord2d(1, 1);
              glVertex3f (x + width, y + height, 0.0);
              glTexCoord2d(0, 1);
              glVertex3f (x + 0, y + height, 0.0);
          glEnd();
      }

    private:
      int x, y, width, height;
};
