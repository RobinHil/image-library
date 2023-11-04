#include<iostream>
#include<fstream>
#include<cmath>

#include"Image.hpp"

int main()
{
    // Tests de la classe GrayImage
    
    {
        GrayImage *img = new GrayImage(150, 300);
        img->clear(255);

        img->fillRectangle(1, 2, 50, 72, 0);
        img->fillRectangle(59, 81, 84, 61, 217);
        img->fillRectangle(37, 200, 84, 57, 195);

        img->rectangle(67, 3, 36, 64, 80);
        img->rectangle(6, 92, 53, 37, 152);
        img->rectangle(79, 179, 59, 119, 29);

        std::ofstream osGrayImage("data/img/GrayImage/01-carres.pgm", std::ios::binary);
        img->writePGM(osGrayImage);

        delete img;
    }

    // std::ifstream isGrayImageChat("data/GrayImage/chat.pgm", std::ios::binary);
    // GrayImage *grayImageChat = GrayImage::readPGM(isGrayImageChat);
    // std::ofstream osGrayImageChat("data/img/tp1_chat.pgm", std::ios::binary);
    // grayImageChat->writePGM(osGrayImageChat);
    // delete grayImageChat;

    // std::ifstream isGrayImageChatPetit("data/GrayImage/chat_petit.pgm", std::ios::binary);
    // GrayImage *grayImageChatPetit = GrayImage::readPGM(isGrayImageChatPetit);

    // GrayImage *grayImageChatSimple = grayImageChatPetit->simpleScale(823, 400);
    // std::ofstream osGrayImageChatSimple("data/img/tp1_simple.pgm", std::ios::binary);
    // grayImageChatSimple->writePGM(osGrayImageChatSimple);
    // delete grayImageChatSimple;

    // GrayImage *grayImageChatBilineaire = grayImageChatPetit->bilinearScale(823, 400);
    // std::ofstream osGrayImageChatBilineaire("data/img/tp1_bilineaire.pgm", std::ios::binary);
    // grayImageChatBilineaire->writePGM(osGrayImageChatBilineaire);
    // delete grayImageChatBilineaire;

    // delete grayImageChatPetit;
    
    // std::ifstream isGrayImageChatTGA("data/GrayImage/chat.tga", std::ios::binary);
    // GrayImage *grayImageChatTGA = GrayImage::readTGA(isGrayImageChatTGA);
    // std::ofstream osGrayImageChatTGA("data/img/tp1_chat.tga", std::ios::binary);
    // grayImageChatTGA->writeTGA(osGrayImageChatTGA);
    // std::ofstream osGrayImageChatPGM("data/img/tp1_chat.pgm", std::ios::binary);
    // grayImageChatTGA->writePGM(osGrayImageChatPGM);
    // delete grayImageChatTGA;

    // std::ifstream isGrayImageChatPGM("data/GrayImage/chat.pgm", std::ios::binary);
    // GrayImage *grayImageChatPGM = GrayImage::readPGM(isGrayImageChatPGM);
    // std::ofstream osGrayImageChatTGA2("data/img/tp1_chat2.tga", std::ios::binary);
    // grayImageChatPGM->writeTGA(osGrayImageChatTGA2);
    // std::ofstream osGrayImageChatPGM2("data/img/tp1_chat2.pgm", std::ios::binary);
    // grayImageChatPGM->writePGM(osGrayImageChatPGM2);
    // delete grayImageChatPGM;




    // // Tests de la classe ColorImage

    // ColorImage *colorImage = new ColorImage(320, 240);
    // colorImage->clear(Color(124, 123, 184));
    // colorImage->fillRectangle(50, 17, 94, 72, Color(252, 3, 3));
    // colorImage->fillRectangle(150, 100, 167, 118, Color(39, 196, 76));
    // colorImage->rectangle(128, 3, 176, 196, Color(232, 214, 12));
    // colorImage->rectangle(27, 75, 190, 150);
    // std::ofstream osColorImage("data/img/tp2_carres.ppm", std::ios::binary);
    // colorImage->writePPM(osColorImage);
    // delete colorImage;

    // std::ifstream isColorImageChat("data/ColorImage/chat.ppm", std::ios::binary);
    // ColorImage *colorImageChat = ColorImage::readPPM(isColorImageChat);
    // std::ofstream osColorImageChat("data/img/tp2_chat.ppm", std::ios::binary);
    // colorImageChat->writePPM(osColorImageChat);
    // delete colorImageChat;

    // std::ifstream isColorImageChatPetit("data/ColorImage/chat_petit.ppm", std::ios::binary);
    // ColorImage *colorImageChatPetit = ColorImage::readPPM(isColorImageChatPetit);

    // ColorImage *colorImageChatSimple = colorImageChatPetit->simpleScale(823, 400);
    // std::ofstream osColorImageChatSimple("data/img/tp2_simple.ppm", std::ios::binary);
    // colorImageChatSimple->writePPM(osColorImageChatSimple);
    // delete colorImageChatSimple;

    // ColorImage *colorImageChatBilineaire = colorImageChatPetit->bilinearScale(823, 400);
    // std::ofstream osColorImageChatBilineaire("data/img/tp2_bilineaire.ppm", std::ios::binary);
    // colorImageChatBilineaire->writePPM(osColorImageChatBilineaire);
    // delete colorImageChatBilineaire;

    // delete colorImageChatPetit;

    // std::ifstream isColorImageChatTGA("data/ColorImage/chat.tga", std::ios::binary);
    // ColorImage *colorImageChatTGA = ColorImage::readTGA(isColorImageChatTGA);
    // std::ofstream osColorImageChatTGA("data/img/tp2_chat.tga", std::ios::binary);
    // colorImageChatTGA->writeTGA(osColorImageChatTGA);
    // std::ofstream osColorImageChatTGARLE("data/img/tp2_chat_rle.tga", std::ios::binary);
    // colorImageChatTGA->writeTGA(osColorImageChatTGARLE, false);

    // std::ifstream isPaletteBL_TGA("data/ColorImage/palette_bl.tga", std::ios::binary);
    // ColorImage *colorImagePaletteBL_TGA = ColorImage::readTGA(isPaletteBL_TGA);
    // std::ofstream osPaletteBL_TGA("data/img/bl.tga", std::ios::binary);
    // colorImagePaletteBL_TGA->writeTGA(osPaletteBL_TGA);
    // delete colorImagePaletteBL_TGA;
    
    // std::ifstream isPaletteTL_TGA("data/ColorImage/palette_tl.tga", std::ios::binary);
    // ColorImage *colorImagePaletteTL_TGA = ColorImage::readTGA(isPaletteTL_TGA);
    // std::ofstream osPaletteTL_TGA("data/img/tl.tga", std::ios::binary);
    // colorImagePaletteTL_TGA->writeTGA(osPaletteTL_TGA);
    // delete colorImagePaletteTL_TGA;

    // std::ofstream osColorImageChatPPM("data/img/tp2_chat.ppm", std::ios::binary);
    // colorImageChatTGA->writePPM(osColorImageChatPPM);
    // delete colorImageChatTGA;

    // std::ifstream isColorImageChatPPM("data/ColorImage/chat.ppm", std::ios::binary);
    // ColorImage *colorImageChatPPM = ColorImage::readPPM(isColorImageChatPPM);
    // std::ofstream osColorImageChatTGA2("data/img/tp2_chat2.tga", std::ios::binary);
    // colorImageChatPPM->writeTGA(osColorImageChatTGA2);
    // std::ofstream osColorImageChatPPM2("data/img/tp2_chat2.ppm", std::ios::binary);
    // colorImageChatPPM->writePPM(osColorImageChatPPM2);
    // delete colorImageChatPPM;

    // std::ifstream isChat("data/ColorImage/chat.tga", std::ios::binary);
    // ColorImage *chat = ColorImage::readTGA(isChat);

    // std::ofstream osChatRLE("data/img/chatRLE.tga", std::ios::binary);
    // chat->writeTGA(osChatRLE);

    // std::ofstream osChatNoRLE("data/img/chatNoRLE.tga", std::ios::binary);
    // chat->writeTGA(osChatNoRLE, false);

    // delete chat;
    
    {
        ColorImage *img = new ColorImage(400, 400);
        img->clear(Color(255, 0, 0));

        for (int x=0; x<img->getWidth(); x+=10)
            img->line(0, 0, x, 400, Color(0, 255, 0));
        for (int y=0; y<img->getHeight(); y+=10)
            img->line(0, 0, 400, y, Color(0, 255, 0));

        std::ofstream osImgTGA("data/img/ColorImage/test_line.tga");
        img->writeTGA(osImgTGA);

        delete img;
    }

    {
        int size = 500;

        ColorImage *img = new ColorImage(size, size);
        img->clear(Color(0, 0, 0));

        for (double angle = 0.0; angle <= 360.0; angle += 5.0) {
            double radian = angle * M_PI / 180.0;
            int x = (size/2) + 200 * cos(radian);
            int y = (size/2) + 200 * sin(radian);
            img->line(size/2, size/2, x, y, Color(0, 0, 255));
            img->pixel(x, y) = Color(255, 255, 255);
        }

        std::ofstream osImgTGA("data/img/ColorImage/test_line++.tga");
        img->writeTGA(osImgTGA);

        delete img;
    }

    return EXIT_SUCCESS;
}