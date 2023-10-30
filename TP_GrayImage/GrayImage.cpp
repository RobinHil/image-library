#include"GrayImage.hpp"

/// @brief Passe une ligne dans un istream (lecture de PGM).
/// @param is 
void skip_line(std::istream& is)
{
    while (is.get()!='\n')
        ;
}

/// @brief Saute les commentaires du PGM (lecture de PGM).
/// @param is 
void skip_comments(std::istream& is)
{
    char c;
    do {
        c=is.get();
        if (c=='#')
            skip_line(is);
    } while (c=='#');
    is.putback(c);
}

/// @brief Constructeur de GrayImage à partir de ses paramètres width et height.
/// @param w 
/// @param h 
GrayImage::GrayImage(uint16_t w, uint16_t h)
    : width(w), height(h), array(nullptr)
{array=new uint8_t[width*height];}

/// @brief Constructeur de copie de GrayImage.
/// @param o 
GrayImage::GrayImage(const GrayImage& o)
    : width(o.width), height(o.height), array(nullptr)
{
    array=new uint8_t[o.width*o.height];
    for (size_t t=0; t<size_t(width*height); t++)
        array[t]=o.array[t];
}

/// @brief Destructeur de GrayImage.
GrayImage::~GrayImage()
{delete [] array;}

/// @brief Lit un PGM.
/// @param is 
/// @return GrayImage*
GrayImage* GrayImage::readPGM(std::istream& is)
{   
    char c=is.get();
    char c2=is.get();
    if (c!='P' || c2!='5')
        throw std::runtime_error("Erreur: le fichier n'est pas au format PGM.");

    skip_line(is);
    skip_comments(is);

    uint16_t w, h;
    is >> w >> h;

    skip_line(is);
    skip_comments(is);

    uint32_t p_value;
    is >> p_value;
    if (p_value>255)
        throw std::runtime_error("Erreur: valeur maximale d'un pixel incorrecte (maximum 255).");
    
    is.get();
    GrayImage *image=new GrayImage(w, h);
    
    is.read((char*)image->array, w*h);

    return image;
}

/// @brief Ecrit un PGM à partir d'un objet GrayImage.
/// @param os 
void GrayImage::writePGM(std::ostream& os) const
{
    os << "P5\n"
       << "#Image sauvegardée par Robin HILAIRE\n"
       << width << " " << height << "\n"
       << "255\n";

    //os.write((const char*)array, width*height);
    for (uint16_t j=0; j<height; ++j)
        for (uint16_t i=0; i<width; ++i)
            os.put(pixel(i,j));
}

/// @brief Efface l'image en mettant tous ses pixels à la valeur 'color'.
/// @param color 
void GrayImage::clear(uint8_t color)
{
    if (color>255)
        throw std::runtime_error("Erreur: valeur maximale d'un pixel incorrecte (maximum 255).");
    for (uint16_t x=0; x<width; x++)
        for (uint16_t y=0; y<height; y++)
            array[y*width+x] = color;
}

/// @brief Dessine un cadre rectangulaire de couleur 'color' dont le coin supérieur gauche est à la coordonée (x,y), de largeur 'w', de hauteur 'h'.
/// @param x 
/// @param y 
/// @param w 
/// @param h 
/// @param color 
void GrayImage::rectangle(uint16_t x, uint16_t y, int16_t w, uint16_t h, uint8_t color)
{
    if (x>width || y>height)
        throw std::runtime_error("Erreur: l'ancrage du rectangle est en dehors de l'image.");
    if (w+x-1>width || h+y-1>height)
        throw std::runtime_error("Erreur: la taille du rectangle le fait sortir de l'image.");
    if (color>255)
        throw std::runtime_error("Erreur: valeur maximale d'un pixel incorrecte (maximum 255).");

    for (uint16_t i=x; i<w+x; i++)
        for (uint16_t j=y; j<h+y; j++)
        {
            if (i==x || j==y || i==w+x-1 || j==h+y-1)
                pixel(i,j) = color;
        }
}

/// @brief Dessine un cadre rectangle plein de couleur 'color' dont le coin supérieur gauche est à la coordonée (x,y), de largeur 'w', de hauteur 'h'.
/// @param x 
/// @param y 
/// @param w 
/// @param h 
/// @param color 
void GrayImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color)
{
    if (x>width || y>height)
        throw std::runtime_error("Erreur: l'ancrage du rectangle est en dehors de l'image.");
    if (w+x-1>width || h+y-1>height)
        throw std::runtime_error("Erreur: la taille du rectangle le fait sortir de l'image.");
    if (color>255)
        throw std::runtime_error("Erreur: valeur maximale d'un pixel incorrecte (maximum 255).");

    for (uint16_t i=x; i<w+x; i++)
        for (uint16_t j=y; j<h+y; j++)
            pixel(i,j) = color;
}

/// @brief Méthode simple pour rééchantillonner une GrayImage.
/// @param w
/// @param h 
/// @return GrayImage*
GrayImage* GrayImage::simpleScale(uint16_t w, uint16_t h) const
{
    GrayImage* ret = new GrayImage(w, h);
    for (uint16_t xPrim=0; xPrim<w; xPrim++)
        for (uint16_t yPrim=0; yPrim<h; yPrim++)
        {
            double x = double(xPrim)/w*width,
                   y = double(yPrim)/h*height;
            uint16_t xi = uint16_t(x),
                     yi = uint16_t(y);
            ret->pixel(xPrim, yPrim) = pixel(xi, yi);
        }
    return ret;
}

/// @brief Méthode bilinéaire pour rééchantillonner une GrayImage.
/// @param w 
/// @param h 
/// @return GrayImage*
GrayImage* GrayImage::bilinearScale(uint16_t w, uint16_t h) const
{
    GrayImage* ret = new GrayImage(w, h);
    for (uint16_t xPrim=0; xPrim<w; xPrim++)
        for (uint16_t yPrim=0; yPrim<h; yPrim++)
        {
            double x = double(xPrim)/w*width,
                   y = double(yPrim)/h*height;
            uint16_t xi = uint16_t(x),
                     yi = uint16_t(y);
            double lambda = x-xi,
                   mu = y-yi;
            uint16_t xip1 = (xi+1<width?xi+1:xi),
                     yip1 = (yi+1<height?yi+1:yi);
            const uint8_t& p1 = pixel(xi, yi),
                           p2 = pixel(xip1, yi),
                           p3 = pixel(xi, yip1),
                           p4 = pixel(xip1, yip1);
            ret->pixel(xPrim, yPrim) = (1-mu)*((1-lambda)*p1+lambda*p2)+mu*((1-lambda)*p3+lambda*p4);
        }
    return ret;
}