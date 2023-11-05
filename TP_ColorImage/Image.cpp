#include"Image.hpp"

const char * const identifier = "hilaire_r";
const char * const informations = "";


// Fonctions / templates générales.

/// @brief Ignore une ligne en lecture d'un fichier.
/// @param is Flux d'entrée contenant la ligne à ignorer.
void skip_line(std::istream& is)
{
    while (is.get()!='\n')
        ;
}

/// @brief Ignore les commentaires en lecture d'images PGM et PPM.
/// @param is Flux d'entrée contenant l'image dont on va ignorer les commentaires.
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

/// @brief Permute les octets de la variable passée en paramètre (passage de big- à little-endian).
/// @tparam T Type des données contenus de la liste 'bytes'.
/// @param bytes Tableau dont on va inverser l'ordre des éléments.
template<typename T> void swap_bytes(T& bytes)
{
    uint8_t *b = reinterpret_cast<uint8_t*>(&bytes);
    for (size_t i=0; i<sizeof(T)/2; i++)
    {
        uint8_t tmp = b[i];
        b[i] = b[sizeof(T)-1-i];
        b[sizeof(T)-1-i] = tmp;
    }
    delete b;
}


// Fonctions membres / friends de la classe GrayImage.

/// @brief Constructeur de GrayImage à partir de ses paramètres width et height.
/// @param w Largeur en pixels de l'image GrayImage à créer.
/// @param h Hauteur en pixels de l'image GrayImage à créer.
GrayImage::GrayImage(const uint16_t& w, const uint16_t& h)
    : width(w), height(h), array(nullptr)
{
    array=new uint8_t[width*height];
}

/// @brief Constructeur de copie de GrayImage.
/// @param o GrayImage d'origine dont on va construire la copie.
GrayImage::GrayImage(const GrayImage& o)
    : width(o.width), height(o.height), array(nullptr)
{
    array=new uint8_t[o.width*o.height];
    for (size_t t=0; t<size_t(width*height); t++)
        array[t]=o.array[t];
}

/// @brief Destructeur de GrayImage.
GrayImage::~GrayImage()
{
    delete [] array;
}

/// @brief Lit une image au format PGM.
/// @param is Flux d'entrée contenant l'image à transformer en GrayImage.
/// @return Pointeur sur une GrayImage qui aura été créée à partir de is.
GrayImage* GrayImage::readPGM(std::istream& is)
{   
    char c=is.get();
    char c2=is.get();
    if (c!='P' || c2!='5')
        throw std::runtime_error("Erreur: dans GrayImage::readPGM(std::istream& is) impossible de lire l'image fournie dans is car le fichier n'est pas au format PGM (magic number \'P5\').");

    skip_line(is);
    skip_comments(is);

    uint16_t w, h;
    is >> w >> h;

    skip_line(is);
    skip_comments(is);

    uint32_t p_value;
    is >> p_value;
    if (p_value>255)
        throw std::runtime_error("Erreur: dans GrayImage::readPGM(std::istream& is) impossible de lire l'image fournie dans is car la valeur maximale d'un pixel est supérieure au maximum autorisé (maximum=255).");
    
    is.get();
    GrayImage *image=new GrayImage(w, h);
    
    is.read((char*)image->array, w*h);

    return image;
}

/// @brief Lit une image au format TGA.
/// @param is Flux d'entrée contenant l'image à transformer en GrayImage.
/// @return Pointeur sur une GrayImage qui aura été créée à partir de is.
GrayImage* GrayImage::readTGA(std::istream& is)
{
    char *header = new char[18];
    is.read(header, 18);
    if (*reinterpret_cast<uint16_t*>(&header[2])!=3)
        throw std::runtime_error("Erreur: dans GrayImage::readTGA(std::istream& is) impossible de lire l'image fournie dans is car il ne s'agit pas d'un TGA en niveaux de gris.");
    uint16_t w = *reinterpret_cast<uint16_t*>(&header[12]),
             h = *reinterpret_cast<uint16_t*>(&header[14]);
    is.seekg(*reinterpret_cast<uint16_t*>(&header[0])+18);
    delete [] header;

    GrayImage* image = new GrayImage(w, h);
    is.read((char*)image->array, w*h);

    return image;
}

/// @brief Ecrit une image au format PGM à partir d'un objet GrayImage.
/// @param os Flux sortant contenant le fichier PGM où on va écrire l'instance courante de GrayImage.
void GrayImage::writePGM(std::ostream& os) const
{
    os << "P5\n"
       << "#Image sauvegardée par Robin HILAIRE\n"
       << width << " " << height << "\n"
       << "255\n";

    os.write((const char*)array, width*height);
}

/// @brief Ecrit une image au format TGA à partir d'un objet GrayImage.
/// @param os Flux sortant contenant le fichier TGA où on va écrire l'instance courante de GrayImage.
void GrayImage::writeTGA(std::ostream& os) const
{
    char *header = new char[18]
    {
        0, 0, 3, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 8, 32
    };
    *reinterpret_cast<uint16_t*>(&header[12]) = width;
    *reinterpret_cast<uint16_t*>(&header[14]) = height;
    os.write(header, 18);
    delete [] header;

    os.write((const char*)array, width*height);
}

/// @brief Efface l'image en mettant tous ses pixels à la valeur 'color'.
/// @param color Couleur (en niveaux de gris) qui va remplacer tous les pixels de l'instance courante de GrayImage.
void GrayImage::clear(const uint8_t& color)
{
    for (uint16_t x=0; x<width; x++)
        for (uint16_t y=0; y<height; y++)
            array[y*width+x] = color;
}

/// @brief Dessine un cadre rectangulaire d'un pixel d'épaisseur dans l'instance courante de GrayImage.
/// @param x Coordonnée sur l'axe des abcisses du coin supérieur gauche du cadre.
/// @param y Coordonnée sur l'axe des ordonnées du coin supérieur gauche du cadre.
/// @param w Largeur du cadre en pixels.
/// @param h Hauteur du cadre en pixels.
/// @param color Couleur (en niveaux de gris) du cadre à tracer.
void GrayImage::rectangle(const uint16_t& x, const uint16_t& y, const uint16_t& w, const uint16_t& h, const uint8_t& color)
{
    if (x>width || y>height)
        throw std::runtime_error("Erreur: dans GrayImage::rectangle(...) impossible de dessiner le cadre car son ancrage de coordonnées (x, y) se situe en dehors de l'image.");
    if (w+x-1>width || h+y-1>height)
        throw std::runtime_error("Erreur: dans GrayImage::rectangle(...) impossible de dessiner le cadre car il dépasse / sort de l'image.");

    for (uint16_t i=x; i<w+x; i++)
        for (uint16_t j=y; j<h+y; j++)
            if (i==x || j==y || i==w+x-1 || j==h+y-1)
                pixel(i,j) = color;
}

/// @brief Dessine un rectangle dans l'instance courante de GrayImage.
/// @param x Coordonnée sur l'axe des abcisses du coin supérieur gauche du rectangle.
/// @param y Coordonnée sur l'axe des ordonnées du coin supérieur gauche du rectangle.
/// @param w Largeur du rectangle en pixels.
/// @param h Hauteur du rectangle en pixels.
/// @param color Couleur (en niveaux de gris) du rectangle à tracer.
void GrayImage::fillRectangle(const uint16_t& x, const uint16_t& y, const uint16_t& w, const uint16_t& h, const uint8_t& color)
{
    if (x>width || y>height)
        throw std::runtime_error("Erreur: dans GrayImage::fillRectangle(...) impossible de dessiner le rectangle car son ancrage de coordonnées (x, y) se situe en dehors de l'image.");
    if (w+x-1>width || h+y-1>height)
        throw std::runtime_error("Erreur: dans GrayImage::fillRectangle(...) impossible de dessiner le rectangle car il dépasse / sort de l'image.");

    for (uint16_t i=x; i<w+x; i++)
        for (uint16_t j=y; j<h+y; j++)
            pixel(i,j) = color;
}

/// @brief Méthode simple pour rééchantillonner une GrayImage.
/// @param w La largeur à laquelle sera rééchantillonnée l'instance courante de GrayImage.
/// @param h La hauteur à laquelle sera rééchantillonnée l'instance courante de GrayImage.
/// @return Pointeur sur une GrayImage qui représente l'instance courante de GrayImage rééchantillonnée.
GrayImage* GrayImage::simpleScale(const uint16_t& w, const uint16_t& h) const
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
/// @param w La largeur à laquelle sera rééchantillonnée l'instance courante de GrayImage.
/// @param h La hauteur à laquelle sera rééchantillonnée l'instance courante de GrayImage.
/// @return Pointeur sur une GrayImage qui représente l'instance courante de GrayImage rééchantillonnée.
GrayImage* GrayImage::bilinearScale(const uint16_t& w, const uint16_t& h) const
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


// Fonctions membres / friends de la classe Color.

/// @brief Opérateur de multiplication de la classe Color.
/// @param alpha Valeur décimale par laquelle multiplier une Color en RGB.
/// @param color Color en RGB qui va être multipliée par une valeur décimale.
/// @return Objet Color dont la valeur est 'alpha*color'.
Color operator*(const double& alpha, const Color& color)
{
    return Color(color.r*alpha, color.g*alpha, color.b*alpha);
}

/// @brief Opérateur d'addition de la classe Color.
/// @param c1 Premier objet Color à additionner.
/// @param c2 Second objet Color à additionner.
/// @return Objet Color dont la valeur est 'c1+c2'.
Color operator+(const Color& c1, const Color& c2)
{
    return Color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
}


// Fonctions membres / friends de la classe ColorImage.

/// @brief Constructeur de ColorImage à partir d'une largeur et une hauteur.
/// @param w Largeur de l'image ColorImage à construire.
/// @param h Hauteur de l'image ColorImage à construire.
ColorImage::ColorImage(const uint16_t& w, const uint16_t& h)
    : width(w), height(h), array(nullptr)
{
    array=new Color[width*height];
}

/// @brief Constructeur de copie de ColorImage.
/// @param o ColorImage d'origine dont on va construire la copie.
ColorImage::ColorImage(const ColorImage& o)
    : width(o.width), height(o.height), array(nullptr)
{
    array=new Color[o.width*o.height];
    for (size_t t=0; t<size_t(width*height); t++)
        array[t]=o.array[t];
}

/// @brief Destructeur de ColorImage.
ColorImage::~ColorImage()
{
    delete [] array;
}

/// @brief Lit une image au format PPM.
/// @param is Flux d'entrée contenant l'image à transformer en ColorImage.
/// @return Pointeur sur une ColorImage qui aura été créée à partir de is.
ColorImage* ColorImage::readPPM(std::istream& is)
{
    char c=is.get();
    char c2=is.get();
    if (c!='P' || c2!='6')
        throw std::runtime_error("Erreur: dans ColorImage::readPPM(std::istream& is) impossible de lire l'image fournie dans is car le fichier n'est pas au format PPM (magic number \'P6\').");

    skip_line(is);
    skip_comments(is);

    uint16_t w, h;
    is >> w >> h;

    skip_line(is);
    skip_comments(is);

    uint32_t p_value;
    is >> p_value;
    if (p_value>255)
        throw std::runtime_error("Erreur: dans ColorImage::readPPM(std::istream& is) impossible de lire l'image fournie dans is car la valeur maximale des champs de couleurs (R,G,B) d'un pixel est supérieure au maximum autorisé (maximum=255).");
    
    is.get();
    ColorImage *image=new ColorImage(w, h);
    is.read((char*)image->array, w*h*3);

    return image;
}

/// @brief Lit une image au format TGA.
/// @param is Flux d'entrée contenant l'image à transformer en ColorImage.
/// @return Pointeur sur une ColorImage qui aura été créée à partir de is.
ColorImage* ColorImage::readTGA(std::istream& is)
{
    char *header = new char[18];
    is.read(header, 18);

    uint16_t w = *reinterpret_cast<uint16_t*>(&header[12]),
             h = *reinterpret_cast<uint16_t*>(&header[14]);
    ColorImage* image = new ColorImage(w, h);

    is.seekg(header[0]+18);
        
    if (header[2]==2 && header[1]==0)
    {
        if (header[17]==0)
        {
            for (uint16_t y=h-1; y>0; y--)
                for (uint16_t x=0; x<w; x++)
                {
                    image->pixel(x, y).b = is.get();
                    image->pixel(x, y).g = is.get();
                    image->pixel(x, y).r = is.get();
                }
            for (uint16_t x=0; x<w; x++)
            {
                image->pixel(x, 0).b = is.get();
                image->pixel(x, 0).g = is.get();
                image->pixel(x, 0).r = is.get();
            }
        }
        else if (header[17]==32)
            for (uint16_t y=0; y<h; y++)
                for (uint16_t x=0; x<w; x++)
                {
                    image->pixel(x, y).b = is.get();
                    image->pixel(x, y).g = is.get();
                    image->pixel(x, y).r = is.get();
                }
        else
        {
            delete [] header;
            delete image;
            throw std::runtime_error("Erreur: dans ColorImage::readTGA(std::istream& is) impossible de lire l'image fournie dans is car la valeur du dernier octet du header TGA n'est ni 0 ni 32.");
        }
    }
    else if (header[2]==1 && header[1]==1)
    {
        uint16_t size = *reinterpret_cast<uint16_t*>(&header[5]);
        Color *palette = new Color[size];
        for (uint16_t i=0; i<size; i++)
        {
            palette[i].b = is.get();
            palette[i].g = is.get();
            palette[i].r = is.get();
        }

        if (header[17]==0)
        {
            for (uint16_t y=h-1; y>0; y--)
                for (uint16_t x=0; x<w; x++)
                {
                    uint16_t i = is.get();
                    image->pixel(x, y).r = palette[i].r;
                    image->pixel(x, y).g = palette[i].g;
                    image->pixel(x, y).b = palette[i].b;
                }
            for (uint16_t x=0; x<w; x++)
            {
                uint16_t i = is.get();
                image->pixel(x, 0).r = palette[i].r;
                image->pixel(x, 0).g = palette[i].g;
                image->pixel(x, 0).b = palette[i].b;
            }
        }

        else if (header[17]==32)
            for (uint16_t y=0; y<h; y++)
                for (uint16_t x=0; x<w; x++)
                {
                    uint16_t i = is.get();
                    image->pixel(x, y).r = palette[i].r;
                    image->pixel(x, y).g = palette[i].g;
                    image->pixel(x, y).b = palette[i].b;
                }
        else
        {
            delete [] header;
            delete [] palette;
            delete image;
            throw std::runtime_error("Erreur: dans ColorImage::readTGA(std::istream& is) impossible de lire l'image fournie dans is car la valeur du dernier octet du header TGA n'est ni 0 ni 32.");
        }
        delete [] palette;
    }
    else
    {
        delete [] header;
        delete image;
        throw std::runtime_error("Erreur: dans ColorImage::readTGA(std::istream& is) impossible de lire l'image fournie dans is car elle n'est ni au format TGA RGB non-compressé (header[2]==2 && header[1]==0) ni au format TGA avec palette 24bits non-compressé (header[2]==1 && header[1]==1).");
    }
    delete [] header;
    return image;
}

/// @brief Ecrit une image au format PPM à partir d'un objet ColorImage.
/// @param os Flux sortant contenant le fichier PPM où on va écrire l'instance courante de ColorImage.
void ColorImage::writePPM(std::ostream& os) const
{
    os << "P6\n"
       << "#Image sauvegardée par Robin HILAIRE\n"
       << width << " " << height << "\n"
       << "255\n";
    os.write((const char*)array, width*height*3);
}

/// @brief Ecrit une image au format TGA à partir d'un objet ColorImage.
/// @param os Flux sortant contenant le fichier TGA où on va écrire l'instance courante de ColorImage.
/// @param rle Bouléen indiquant si l'image à écrire doit être compressée (true par défaut) ou non-compressée (false).
void ColorImage::writeTGA(std::ostream& os, const bool& rle) const
{
    if (rle)
    {
        char *header = new char[18]
        {
            0, 0, 10, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 24, 32
        };
        *reinterpret_cast<uint16_t*>(&header[12]) = width;
        *reinterpret_cast<uint16_t*>(&header[14]) = height;
        os.write(header, 18);
        
        delete [] header;

        for (uint16_t y=0; y<height; y++)
        {
            uint8_t RL = 0;
            for (uint16_t x=0; x<width; x++)
            {
                if (
                    x<width-1 && RL<127 &&
                    (pixel(x, y).r==pixel(x+1, y).r &&
                     pixel(x, y).g==pixel(x+1, y).g &&
                     pixel(x, y).b==pixel(x+1, y).b)
                   )
                    RL++;
                else
                {
                    os.put(RL+128);
                    os.put(pixel(x, y).b);
                    os.put(pixel(x, y).g);
                    os.put(pixel(x, y).r);
                    RL = 0;
                }
            }
        }
    }
    else if (!rle)
    {
        char *header = new char[18]
        {
            0, 0, 2, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 24, 32
        };
        *reinterpret_cast<uint16_t*>(&header[12]) = width;
        *reinterpret_cast<uint16_t*>(&header[14]) = height;
        os.write(header, 18);
        
        delete [] header;

        for (int y=0; y<height; y++)
            for (int x=0; x<width; x++)
            {
                os.put(pixel(x, y).b);
                os.put(pixel(x, y).g);
                os.put(pixel(x, y).r);
            }
    }
}

/// @brief Efface l'image en mettant tous ses pixels à la valeur 'color'.
/// @param color Color réprésentant la couleur en RGB d'un pixel.
void ColorImage::clear(const Color& color)
{
    for (int i=0; i<width*height; i++)
        array[i] = color;
}

/// @brief Dessine un cadre rectangulaire d'un pixel d'épaisseur dans l'instance courante de ColorImage.
/// @param x Coordonnée sur l'axe des abcisses du coin supérieur gauche du cadre.
/// @param y Coordonnée sur l'axe des ordonnées du coin supérieur gauche du cadre.
/// @param w Largeur du cadre en pixels.
/// @param h Hauteur du cadre en pixels.
/// @param color Couleur de la classe Color (en RGB) du cadre à tracer.
void ColorImage::rectangle(const uint16_t& x, const uint16_t& y, const uint16_t& w, const uint16_t& h, const Color& color)
{
    if (x>width || y>height)
        throw std::runtime_error("Erreur: dans ColorImage::rectangle(...) impossible de dessiner le cadre car son ancrage de coordonnées (x, y) se situe en dehors de l'image.");
    if (w+x-1>width || h+y-1>height)
        throw std::runtime_error("Erreur: dans ColorImage::rectangle(...) impossible de dessiner le cadre car il dépasse / sort de l'image.");

    for (uint16_t i=x; i<w+x; i++)
        for (uint16_t j=y; j<h+y; j++)
            if (i==x || j==y || i==w+x-1 || j==h+y-1)
                pixel(i,j) = color;
}

/// @brief Dessine un rectangle dans l'instance courante de ColorImage.
/// @param x Coordonnée sur l'axe des abcisses du coin supérieur gauche du rectangle.
/// @param y Coordonnée sur l'axe des ordonnées du coin supérieur gauche du rectangle.
/// @param w Largeur du rectangle en pixels.
/// @param h Hauteur du rectangle en pixels.
/// @param color Couleur de la classe Color (en RGB) du rectangle à tracer. 
void ColorImage::fillRectangle(const uint16_t& x, const uint16_t& y, const uint16_t& w, const uint16_t& h, const Color& color)
{
    if (x>width || y>height)
        throw std::runtime_error("Erreur: dans ColorImage::fillRectangle(...) impossible de dessiner le rectangle car son ancrage de coordonnées (x, y) se situe en dehors de l'image.");
    if (w+x-1>width || h+y-1>height)
        throw std::runtime_error("Erreur: dans ColorImage::fillRectangle(...) impossible de dessiner le rectangle car il dépasse / sort de l'image.");

    for (uint16_t i=x; i<w+x; i++)
        for (uint16_t j=y; j<h+y; j++)
            pixel(i,j) = color;
}

/// @brief Méthode simple pour rééchantillonner une ColorImage.
/// @param w La largeur à laquelle sera rééchantillonnée l'instance courante de ColorImage.
/// @param h La hauteur à laquelle sera rééchantillonnée l'instance courante de ColorImage.
/// @return Pointeur sur une ColorImage qui représente l'instance courante de ColorImage rééchantillonnée.
ColorImage* ColorImage::simpleScale(const uint16_t& w, const uint16_t& h) const
{
    ColorImage* ret = new ColorImage(w, h);
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

/// @brief Méthode simple pour rééchantillonner une ColorImage.
/// @param w La largeur à laquelle sera rééchantillonnée l'instance courante de ColorImage.
/// @param h La hauteur à laquelle sera rééchantillonnée l'instance courante de ColorImage.
/// @return Pointeur sur une ColorImage qui représente l'instance courante de ColorImage rééchantillonnée.
ColorImage* ColorImage::bilinearScale(const uint16_t& w, const uint16_t& h) const
{
    ColorImage* ret = new ColorImage(w, h);
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
            const Color& p1 = pixel(xi, yi),
                         p2 = pixel(xip1, yi),
                         p3 = pixel(xi, yip1),
                         p4 = pixel(xip1, yip1);
            ret->pixel(xPrim, yPrim) = (1-mu)*((1-lambda)*p1+lambda*p2)+mu*((1-lambda)*p3+lambda*p4);
        }
    return ret;
}

/// @brief Trace une ligne en suivant l'algorithme de Bresenham dans l'instance courante de ColorImage.
/// @param x1 Coordonnée sur l'axe des abcisses du point d'origine de la ligne.
/// @param y1 Coordonnée sur l'axe des ordonnées du point d'origine de la ligne.
/// @param x2 Coordonnée sur l'axe des abcisses du point d'arrivée de la ligne.
/// @param y2 Coordonnée sur l'axe des ordonnées du point d'arrivée de la lignee.
/// @param pixel_value Couleur de la classe Color (en RGB) de la ligne à tracer.
void ColorImage::line(const uint16_t& x1, const uint16_t& y1, const uint16_t& x2, const uint16_t& y2, const Color& pixel_value)
{
    pixel(x2, y2) = pixel_value;

    const uint16_t longX = abs(x2-x1),
                   longY = abs(y2-y1);

    const short incX = x1<x2?1:-1,
                incY = y1<y2?1:-1;

    uint16_t x = x1,
             y = y1;

    if(longY<longX)
    {
        const int16_t c1 = 2*(longY-longX),
                      c2 = 2*longY;

        int16_t crit1 = 2*longY,
                crit2 = 2*(longY-longX);

        while(x!=x2)
        {
            pixel(x, y) = pixel_value;
            if((x<x2 && y<y2)||(x>x2 && y>y2))
            {
                if(crit1>=0)
                {
                    y += incY;
                    crit1 += c1;
                }
                else
                    crit1 += c2;
            }
            else
            {
                if(crit2>=0)
                {
                    y += incY;
                    crit2 += c1;
                }
                else
                    crit2 += c2;
            }
            x += incX;
        }
    }
    else
    {
        const int16_t c1 = 2*(longX-longY),
                      c2 = 2*longX;

        int16_t crit1 = 2*longX,
                crit2 = 2*(longX-longY);

        while(y!=y2)
        {
            pixel(x, y) = pixel_value;

            if((x<x2 && y<y2)||(x>x2 && y>y2))
            {
                if(crit1>=0)
                {
                    x += incX;
                    crit1 += c1;
                }
                else
                    crit1 += c2;
            }
            else
            {
                if(crit2>=0)
                {
                    x += incX;
                    crit2 += c1;
                }
                else
                    crit2 += c2;
            }
            y += incY;
        }
    }
}