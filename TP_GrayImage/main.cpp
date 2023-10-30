#include<iostream>
#include<fstream>

#include"GrayImage.hpp"

int main()
{
    GrayImage *img = new GrayImage(150, 300);
    img->clear(255);
    img->fillRectangle(1, 2, 50, 72, 0);
    img->fillRectangle(59, 81, 84, 61, 217);
    img->fillRectangle(37, 200, 84, 57, 195);
    img->rectangle(67, 3, 36, 64, 80);
    img->rectangle(6, 92, 53, 37, 152);
    img->rectangle(79, 179, 59, 119, 29);
    std::ofstream os("data/test.pgm", std::ios::binary);
    img->writePGM(os);

    std::ifstream isChat("data/chat.pgm", std::ios::binary);
    GrayImage *imgChat = GrayImage::readPGM(isChat);
    std::ofstream osChat("data/test2.pgm", std::ios::binary);
    imgChat->writePGM(osChat);

    std::ifstream isFleurs("data/fleurs.pgm", std::ios::binary);
    GrayImage *imgFleurs = GrayImage::readPGM(isFleurs);
    std::ofstream osFleurs("data/test3.pgm", std::ios::binary);
    imgFleurs->writePGM(osFleurs);

    delete img;
    delete imgChat;
    delete imgFleurs;
    return EXIT_SUCCESS;
}