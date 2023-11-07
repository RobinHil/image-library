#ifndef IMAGE_HPP
#define IMAGE_HPP

#define CORR_PGMASCII
#define CORR_PPMASCII
#define CORR_BRESENHAM

#include<iostream>
#include<cstdint>

extern const char * const identifier;
extern const char * const informations;

/// @brief Classe permettant de lire / écrire / manipuler des images en niveaux de gris.
class GrayImage
{
    /// @brief Largeur (width) et hauteur (height), en pixels, de l'image.
    const uint16_t width, height;

    /// @brief Tableau dynamique contenant les couleurs de chaque pixel de l'image.
    uint8_t *array;

public :
    /// @brief Il est impossible de construire une instance de GrayImage sans fournir aucun paramètre au constructeur.
    GrayImage() = delete;

    /// @brief Il est impossible d'utiliser l'operator= pour la classe GrayImage.
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
    void writeTGA(std::ostream&, const bool& =true) const;

    void clear(const uint8_t& =0);
    
    void rectangle(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const uint8_t& =0);
    void fillRectangle(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const uint8_t& =0);

    GrayImage* simpleScale(const uint16_t&, const uint16_t&) const;
    GrayImage* bilinearScale(const uint16_t&, const uint16_t&) const;
};

/// @brief Classe permettant de stocker une couleur au format RGB.
class Color
{
public :
    /// @brief Données membres contenant la quantité de chaque couleur (rouge, vert, bleu) dans la couleur RGB.
    uint8_t r, g, b;

    /// @brief Constructeur de la classe Color à partir des valeurs à assigner à ses données membres passées en paramètre.
    /// @param _r Quantité de rouge (red) dans la couleur RGB.
    /// @param _g Quantité de vert (green) dans la couleur RGB.
    /// @param _b Quantité de bleu (blue) dans la couleur RGB.
    inline Color (const uint8_t& _r =0, const uint8_t& _g =0, const uint8_t& _b =0)
    : r(_r), g(_g), b(_b){}

    friend Color operator*(const double&, const Color&);
    friend Color operator+(const Color&, const Color&);
};

/// @brief Classe permettant de lire / écrire / manipuler des images en couleurs.
class ColorImage
{
    /// @brief Largeur (width) et hauteur (height), en pixels, de l'image.
    uint16_t width, height;

    /// @brief Tableau dynamique contenant les couleurs de chaque pixel de l'image.
    Color *array;

public:
    /// @brief Il est impossible de construire une instance de ColorImage sans fournir aucun paramètre au constructeur.
    ColorImage() = delete;

    /// @brief Il est impossible d'utiliser l'operator= pour la classe ColorImage.
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