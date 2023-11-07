#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*
 Toutes vos définitions de classes doivent être regroupées dans l'unique
 fichier "Image.h". Son nom n'est pas modifiable sinon vous empêcherez la
 compilation de l'autre executable servant à la correction.
*/
#include "Image.hpp"

int main(int argc,char *argv[])
{
  try
  {
    {
      std::ifstream isImg("data/src/chat.mai", std::ios::binary);
      ColorImage *img = ColorImage::readMaison(isImg);

      std::ofstream osImg("data/tests/chat.ppm");
      img->writePPM(osImg);

      delete img;
    }
    {
      std::ifstream isImg("data/src/colibri.mai", std::ios::binary);
      ColorImage *img = ColorImage::readMaison(isImg);

      std::ofstream osImg("data/tests/colibri.ppm");
      img->writePPM(osImg);

      delete img;
    }
    {
      std::ifstream isImg("data/src/lena.mai", std::ios::binary);
      ColorImage *img = ColorImage::readMaison(isImg);

      std::ofstream osImg("data/tests/lena.ppm");
      img->writePPM(osImg);

      delete img;
    }
  } // Trois types d'exceptions seront attrapés (les chaines C et C++ ainsi que
    // les std::exception et toutes ses dérivées). N'utilisez pas autre chose !
  catch(exception& e)
    { cerr<< "Exception :"<<e.what()<< endl; }
  catch(string& e)
    { cerr<< "Exception string :"<<e<< endl; }
  catch(const char * e)
    { cerr<< "Exception const char* :"<<e<< endl; }
 return 0;
}
