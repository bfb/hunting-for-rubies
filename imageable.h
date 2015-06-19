#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Imageable {
    public:

      Image loadImage(std::string filename){

          // ifstream is used for reading files
          ifstream inf(filename);

          // If we couldn't open the output file stream for reading
          if (!inf) {
              // Print an error and exit
              cerr << "File error: " + filename << endl;
              exit(1);
          }

          std::string format;
          std::string width;
          std::string height;
          std::string max;

          inf >> format;
          inf >> width;
          inf >> height;
          inf >> max;

          std::string r;
          std::string g;
          std::string b;
          std::string a;

          Image *image = new Image(std::stoi(width), std::stoi(height));

          for(int y = 0; y < image->getHeight(); y++) {
            for(int x = 0; x < image->getWidth(); x++) {
              inf >> a;
              inf >> r;
              inf >> g;
              inf >> b;

              int rgb = (std::stoi(a) << 24) | (std::stoi(r) << 16) | (std::stoi(g) << 8) | std::stoi(b);
              // int rgb = (std::stoi(r) << 16) | (std::stoi(g) << 8) | std::stoi(b);

              image->setPixel(rgb, x, y);
            }
          }

          return *image;
      }

      Image loadPPMImage(std::string filename){

          // ifstream is used for reading files
          ifstream inf(filename);

          // If we couldn't open the output file stream for reading
          if (!inf) {
              // Print an error and exit
              cerr << "File error: " + filename << endl;
              exit(1);
          }

          std::string format;
          std::string width;
          std::string height;
          std::string max;

          inf >> format;
          inf >> width;
          inf >> height;
          inf >> max;

          std::string r;
          std::string g;
          std::string b;
          std::string a;

          Image *image = new Image(std::stoi(width), std::stoi(height));

          for(int x = 0; x < image->getHeight(); x++) {
            for(int y = 0; y < image->getWidth(); y++) {
              inf >> r;
              inf >> g;
              inf >> b;

              int rgb = (std::stoi(r) << 16) | (std::stoi(g) << 8) | std::stoi(b);

              image->setPixel(rgb, x, y);

              // cout << "\n";
              // cout << std::to_string(x);
              // cout << "x";
              // cout << std::to_string(y);
              // cout << " RGB ";
              // cout << std::to_string(rgb);
            }
          }

          return *image;
      }
};
