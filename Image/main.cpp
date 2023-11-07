#include<fstream>
#include<cmath>

#include"Image.hpp"

int main()
{
//  // Tests de la classe GrayImage
    
    {
        GrayImage *img = new GrayImage(150, 300);
        img->clear(255);

        img->fillRectangle(1, 2, 50, 72, 0);
        img->fillRectangle(59, 81, 84, 61, 217);
        img->fillRectangle(37, 200, 84, 57, 195);

        img->rectangle(67, 3, 36, 64, 80);
        img->rectangle(6, 92, 53, 37, 152);
        img->rectangle(79, 179, 59, 119, 29);

        std::ofstream osImg("data/tests/GrayImage/01-rectangles.pgm", std::ios::binary);
        img->writePGM(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/GrayImage/chat.pgm", std::ios::binary);
        GrayImage *img = GrayImage::readPGM(isImg);

        std::ofstream osImg("data/tests/GrayImage/02-read_p5_write_p5.pgm", std::ios::binary);
        img->writePGM(osImg);

        delete img;
    }

    {
        std::ifstream isSrc("data/GrayImage/chat_petit.pgm", std::ios::binary);
        GrayImage *src = GrayImage::readPGM(isSrc);

        GrayImage *img = src->simpleScale(823, 400);

        delete src;

        std::ofstream osImg("data/tests/GrayImage/04-simple_scale.pgm", std::ios::binary);
        img->writePGM(osImg);
        
        delete img;
    }

    {    
        std::ifstream isSrc("data/GrayImage/chat_petit.pgm", std::ios::binary);
        GrayImage *src = GrayImage::readPGM(isSrc);

        GrayImage *img = src->bilinearScale(823, 400);

        delete src;

        std::ofstream osImg("data/tests/GrayImage/05-bilinear_scale.pgm", std::ios::binary);
        img->writePGM(osImg);
        
        delete img;
    }

    {
        std::ifstream isImg("data/GrayImage/chat.tga", std::ios::binary);
        GrayImage *img = GrayImage::readTGA(isImg);

        std::ofstream osImg("data/tests/GrayImage/06-read_tga_write_tga.tga", std::ios::binary);
        img->writeTGA(osImg);

        std::ofstream osImgNoRLE("data/tests/GrayImage/06-read_tga_write_tga_norle.tga", std::ios::binary);
        img->writeTGA(osImgNoRLE, false);

        delete img;
    }

    {
        std::ifstream isImg("data/GrayImage/chat.tga", std::ios::binary);
        GrayImage *img = GrayImage::readTGA(isImg);

        std::ofstream osImg("data/tests/GrayImage/07-read_tga_write_pgm.pgm", std::ios::binary);
        img->writePGM(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/GrayImage/chat.pgm", std::ios::binary);
        GrayImage *img = GrayImage::readPGM(isImg);

        std::ofstream osImg("data/tests/GrayImage/08-read_pgm_write_pgm.pgm", std::ios::binary);
        img->writePGM(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/GrayImage/chat.pgm", std::ios::binary);
        GrayImage *img = GrayImage::readPGM(isImg);

        std::ofstream osImg("data/tests/GrayImage/09-read_pgm_write_tga.tga", std::ios::binary);
        img->writeTGA(osImg);

        delete img;
    }

    {
        GrayImage *img = new GrayImage(300, 300);
        img->clear(128);

        std::ofstream osImg("data/tests/GrayImage/10-clear.pgm", std::ios::binary);
        img->writePGM(osImg);

        std::ofstream osImgTGARLE("data/tests/GrayImage/10-clear_rle.tga", std::ios::binary);
        img->writeTGA(osImgTGARLE);

        std::ofstream osImgTGANoRLE("data/tests/GrayImage/10-clear_norle.tga", std::ios::binary);
        img->writeTGA(osImgTGANoRLE, false);

        delete img;
    }

    {
        std::ifstream isImg("data/GrayImage/Rafale30000.pgm", std::ios::binary);
        GrayImage *img = GrayImage::readPGM(isImg);

        std::ofstream osImg("data/tests/GrayImage/11-read_p2_write_p5.pgm", std::ios::binary);
        img->writePGM(osImg);

        delete img;
    }


//  // Tests de la classe ColorImage

    {
        ColorImage *img = new ColorImage(320, 240);

        img->clear(Color(124, 123, 184));

        img->fillRectangle(50, 17, 94, 72, Color(252, 3, 3));
        img->fillRectangle(150, 100, 167, 118, Color(39, 196, 76));

        img->rectangle(128, 3, 176, 196, Color(232, 214, 12));
        img->rectangle(27, 75, 190, 150);

        std::ofstream osImg("data/tests/ColorImage/01-rectangles.ppm", std::ios::binary);
        img->writePPM(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/ColorImage/chat.ppm", std::ios::binary);
        ColorImage *img = ColorImage::readPPM(isImg);

        std::ofstream osImg("data/tests/ColorImage/02-read_p6_write_p6.ppm", std::ios::binary);
        img->writePPM(osImg);

        delete img;
    }

    {
        std::ifstream isSrc("data/ColorImage/chat_petit.ppm", std::ios::binary);
        ColorImage *src = ColorImage::readPPM(isSrc);

        ColorImage *img = src->simpleScale(823, 400);

        delete src;

        std::ofstream osImg("data/tests/ColorImage/03-simple_scale.ppm", std::ios::binary);
        img->writePPM(osImg);

        delete img;
    }

    {
        std::ifstream isSrc("data/ColorImage/chat_petit.ppm", std::ios::binary);
        ColorImage *src = ColorImage::readPPM(isSrc);

        ColorImage *img = src->bilinearScale(823, 400);

        delete src;

        std::ofstream osImg("data/tests/ColorImage/04-bilinear_scale.ppm", std::ios::binary);
        img->writePPM(osImg);

        delete img;

    }

    {
        std::ifstream isImg("data/ColorImage/chat.tga", std::ios::binary);
        ColorImage *img = ColorImage::readTGA(isImg);

        std::ofstream osImg("data/tests/ColorImage/05-read_tga_write_tga_no_rle.tga", std::ios::binary);
        img->writeTGA(osImg, false);

        delete img;
    }

    {
        std::ifstream isImg("data/ColorImage/chat.tga", std::ios::binary);
        ColorImage *img = ColorImage::readTGA(isImg);

        std::ofstream osImg("data/tests/ColorImage/06-read_tga_write_tga_rle.tga", std::ios::binary);
        img->writeTGA(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/ColorImage/palette_bl.tga", std::ios::binary);
        ColorImage *img = ColorImage::readTGA(isImg);

        std::ofstream osImg("data/tests/ColorImage/07-palette_bl.tga", std::ios::binary);
        img->writeTGA(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/ColorImage/palette_tl.tga", std::ios::binary);
        ColorImage *img = ColorImage::readTGA(isImg);

        std::ofstream osImg("data/tests/ColorImage/08-palette_tl.ppm", std::ios::binary);
        img->writePPM(osImg);

        delete img;
    }
    
    {
        ColorImage *img = new ColorImage(400, 400);
        img->clear(Color(255, 0, 0));

        for (int x=0; x<img->getWidth(); x+=10)
            img->line(0, 0, x, 400, Color(0, 255, 0));
        for (int y=0; y<img->getHeight(); y+=10)
            img->line(0, 0, 400, y, Color(0, 255, 0));

        std::ofstream osImg("data/tests/ColorImage/09-test_line.tga");
        img->writeTGA(osImg);

        delete img;
    }

    {
        int s = 500;

        ColorImage *img = new ColorImage(s, s);
        img->clear(Color(0, 0, 0));

        for (double angle = 0.0; angle <= 360.0; angle += 5.0) {
            int x = (s/2)+200*cos(angle*M_PI/180.0);
            int y = (s/2)+200*sin(angle*M_PI/180.0);
            img->line(s/2, s/2, x, y, Color(0, 0, 255));
            img->pixel(x, y) = Color(255, 255, 255);
        }

        std::ofstream osImg("data/tests/ColorImage/10-test_line++.tga");
        img->writeTGA(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/ColorImage/Rafale30000.ppm", std::ios::binary);
        ColorImage *img = ColorImage::readPPM(isImg);

        std::ofstream osImg("data/tests/ColorImage/11-read_p3_write_p6.ppm", std::ios::binary);
        img->writePPM(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/ColorImage/Rafale30000.ppm", std::ios::binary);
        ColorImage *img = ColorImage::readPPM(isImg);

        std::ofstream osImg("data/tests/ColorImage/12-read_p3_write_tga_rle.tga", std::ios::binary);
        img->writeTGA(osImg);

        delete img;
    }

    {
        std::ifstream isImg("data/ColorImage/Rafale30000.ppm", std::ios::binary);
        ColorImage *img = ColorImage::readPPM(isImg);

        std::ofstream osImg("data/tests/ColorImage/13-read_p3_write_tga_norle.tga", std::ios::binary);
        img->writeTGA(osImg, false);

        delete img;
    }

    {
      std::ifstream isImg("data/Maison/chat.mai", std::ios::binary);
      ColorImage *img = ColorImage::readMaison(isImg);

      std::ofstream osImg("data/tests/Maison/chat.ppm");
      img->writePPM(osImg);

      delete img;
    }

    {
      std::ifstream isImg("data/Maison/colibri.mai", std::ios::binary);
      ColorImage *img = ColorImage::readMaison(isImg);

      std::ofstream osImg("data/tests/Maison/colibri.ppm");
      img->writePPM(osImg);

      delete img;
    }

    {
      std::ifstream isImg("data/Maison/lena.mai", std::ios::binary);
      ColorImage *img = ColorImage::readMaison(isImg);

      std::ofstream osImg("data/tests/Maison/lena.ppm");
      img->writePPM(osImg);

      delete img;
    }

    return EXIT_SUCCESS;
}