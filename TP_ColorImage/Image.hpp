#ifndef IMAGE_HPP
#define IMAGE_HPP

#include<iostream>
#include<cstdint>

extern const char * const identifier;
extern const char * const informations;

class GrayImage
{
    const uint16_t width, height;
    uint8_t *array;

public :
    GrayImage() = delete;
    GrayImage& operator=(const GrayImage&) = delete;
    GrayImage(const uint16_t&, const uint16_t&);
    GrayImage(const GrayImage&);
    ~GrayImage();

    /// @brief Getter permettant d'obtenir la largeur de l'instance courante de GrayImage.
    /// @return Référence constante sur un uint16_t.
    inline const uint16_t& getWidth() const {return width;}

    /// @brief Getter permettant d'obtenir la hauteur de l'instance courante de GrayImage.
    /// @return Référence constante sur un uint16_t.
    inline const uint16_t& getHeight() const {return height;}

    /// @brief Permet d'obtenir / modifier la valeur d'un pixel de l'instance courante de GrayImage à partir de ses coordonnées dans l'image.
    /// @param x Coordonnée x sur l'axe des abcisses du pixel à renvoyer.
    /// @param y Coordonnée y sur l'axe des ordonnées du pixel à renvoyer.
    /// @return Référence sur un uint8_t.
    inline uint8_t& pixel(const uint16_t& x, const uint16_t& y) {return array[y*width+x];}

    /// @brief Permet d'obtenir la valeur d'un pixel de l'instance courante de GrayImage à partir de ses coordonnées dans l'image.
    /// @param x Coordonnée x sur l'axe des abcisses du pixel à renvoyer.
    /// @param y Coordonnée y sur l'axe des ordonnées du pixel à renvoyer.
    /// @return Référence constante sur un uint8_t.
    inline const uint8_t& pixel(const uint16_t& x, const uint16_t& y) const {return array[y*width+x];}

    static GrayImage* readPGM(std::istream&);
    static GrayImage* readTGA(std::istream&);

    void writePGM(std::ostream&) const;
    void writeTGA(std::ostream&) const;

    void clear(const uint8_t& =0);
    
    void rectangle(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const uint8_t& =0);
    void fillRectangle(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const uint8_t& =0);

    GrayImage* simpleScale(const uint16_t&, const uint16_t&) const;
    GrayImage* bilinearScale(const uint16_t&, const uint16_t&) const;
};

class Color
{
public :
    uint8_t r, g, b;

    inline Color (const uint8_t& _r=0, const uint8_t& _g=0, const uint8_t& _b=0)
    : r(_r), g(_g), b(_b){}

    friend Color operator*(const double&, const Color&);
    friend Color operator+(const Color&, const Color&);
};

class ColorImage
{
    uint16_t width, height;
    Color *array;

public:
    ColorImage() = delete;
    ColorImage& operator=(const ColorImage&) = delete;
    ColorImage(const uint16_t&, const uint16_t&);
    ColorImage(const ColorImage&);
    ~ColorImage();

    /// @brief Getter permettant d'obtenir la largeur de l'instance courante de ColorImage.
    /// @return Référence constante sur un uint16_t.
    inline const uint16_t& getWidth() const {return width;}

    /// @brief Getter permettant d'obtenir la hauteur de l'instance courante de ColorImage.
    /// @return Référence constante sur un uint16_t.
    inline const uint16_t& getHeight() const {return height;}

    /// @brief Permet d'obtenir / modifier la valeur d'un pixel de l'instance courante de ColorImage à partir de ses coordonnées dans l'image.
    /// @param x Coordonnée x sur l'axe des abcisses du pixel à renvoyer.
    /// @param y Coordonnée y sur l'axe des ordonnées du pixel à renvoyer.
    /// @return Référence sur un Color.
    inline Color& pixel(const uint16_t& x, const uint16_t& y) {return array[y*width+x];}

    /// @brief Permet d'obtenir la valeur d'un pixel de l'instance courante de ColorImage à partir de ses coordonnées dans l'image.
    /// @param x Coordonnée x sur l'axe des abcisses du pixel à renvoyer.
    /// @param y Coordonnée y sur l'axe des ordonnées du pixel à renvoyer.
    /// @return Référence sur un Color.
    inline const Color& pixel(const uint16_t& x, const uint16_t& y) const {return array[y*width+x];}

    static ColorImage* readPPM(std::istream&);
    static ColorImage* readTGA(std::istream&);
    void writePPM(std::ostream&) const;
    void writeTGA(std::ostream&, const bool& =true) const;

    void clear(const Color& =Color());
    void rectangle(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const Color& =Color());
    void fillRectangle(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const Color& =Color());

    ColorImage* simpleScale(const uint16_t&, const uint16_t&) const;
    ColorImage* bilinearScale(const uint16_t&, const uint16_t&) const;

    void line(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const Color&);
};

#endif