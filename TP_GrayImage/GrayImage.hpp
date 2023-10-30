#ifndef GRAYIMAGE_HXX
#define GRAYIMAGE_HXX

#include<iostream>
#include<cstdint>

class GrayImage
{
    const uint16_t width, height;
    uint8_t *array;

public :
    GrayImage() = delete;
    GrayImage& operator=(const GrayImage&) = delete;
    GrayImage(uint16_t, uint16_t);
    GrayImage(const GrayImage&);
    ~GrayImage();

    inline const uint16_t& getWidth() const{return width;}
    inline const uint16_t& getHeight() const{return height;}
    inline uint8_t& pixel(uint16_t x, uint16_t y){return array[y*width+x];}
    inline const uint8_t& pixel(uint16_t x, uint16_t y) const{return array[y*width+x];}

    void writePGM(std::ostream&) const;
    static GrayImage* readPGM(std::istream&);
    void clear(uint8_t =0);
    void rectangle(uint16_t, uint16_t, int16_t, uint16_t, uint8_t =0);
    void fillRectangle(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t =0);
    GrayImage* simpleScale(uint16_t, uint16_t) const;
    GrayImage* bilinearScale(uint16_t, uint16_t) const;
};

#endif