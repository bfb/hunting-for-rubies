class Image {
    public:
      Image(int w, int h){
        width = w; height = h;
        pixels = new int[w*h];
      }

      void setPixel(int rgb, int x, int y){
        pixels[x+y*width] = rgb;
      }

      int getPixel(int x, int y){
        return pixels[x+y*width];
      }

      int getWidth(){ return width; }

      int getHeight(){ return height; }

      int* getPixels(){ return pixels; }

      void setPixels(int* p){
        pixels = p;
      }

      void plot(int startX, int startY, Image image) {

        for(int x = 0; x < image.getWidth(); x++){
          for(int y = 0; y < image.getHeight(); y++){
            int argb = image.getPixel(x, image.getHeight()-1-y);

            int a = (argb >> 24) & 0xff;
            int r = (argb >> 16) & 0xff;
            int g = (argb >> 8)  & 0xff;
            int b =  argb        & 0xff;

            if(r == 255 && b == 255 && g == 0) {
              // mix colors
            } else {
              setPixel(image.getPixel(x, image.getHeight()-1-y), startX + x, startY + y);
            }


          }
        }






        // // working
        // for(int x = 0; x < image.getHeight(); x++){
        //   for(int y = 0; y < image.getWidth(); y++){
        //     // int pixel = image.getPixel(x, y);
        //     // if(pixel )
        //     setPixel(image.getPixel(image.getHeight() - 1 - x, image.getWidth() - 1 - y), startX + y, startY + x);
        //   }
        // }




        // // okk
        // for(int x = 0; x < image.getHeight(); x++){
        //   for(int y = 0; y < image.getWidth(); y++){
        //     // int pixel = image.getPixel(x, y);
        //     // if(pixel )
        //     setPixel(image.getPixel(image.getHeight() - 1 - x, image.getWidth() - 1 - y), startX + y, startY + x);
        //   }
        // }

        // for(int x = 0; x < image.getHeight(); x++){
        //   for(int y = 0; y < image.getWidth(); y++){
        //     // int pixel = image.getPixel(x, y);
        //     // if(pixel )
        //     setPixel(image.getPixel(image.getHeight() - 1 - x, image.getWidth() - 1 - y), startX + y, startY + x);
        //   }
        // }




      }

    private:
      int *pixels; // alternativamente char *pixels – 1 byte por canal
                    // neste caso, pixels = new char[w*h*3];
      int width, height;
};
