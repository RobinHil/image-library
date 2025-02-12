# Bibliothèque Image

Une bibliothèque C++ moderne pour la lecture, l'écriture et le traitement d'images en niveaux de gris et en couleurs RGB.

## Fonctionnalités

### Formats d'images supportés

- **PGM (Portable GrayMap)**
  - Lecture des formats P2 (ASCII) et P5 (Binaire)
  - Écriture au format P5 (Binaire)

- **PPM (Portable PixMap)**
  - Lecture des formats P3 (ASCII) et P6 (Binaire)
  - Écriture au format P6 (Binaire)

- **TGA (Truevision Graphics Adapter)**
  - Lecture des images non compressées en niveaux de gris et RGB
  - Support des images avec palette de couleurs 24 bits
  - Écriture avec ou sans compression RLE (Run-Length Encoding)

- **Format Maison (.mai)**
  - Lecture d'images au format propriétaire CMY

### Fonctionnalités de traitement

#### Images en niveaux de gris (GrayImage)
- Création et manipulation d'images 8 bits
- Dessin de rectangles (pleins ou vides)
- Redimensionnement d'images:
  - Méthode simple (plus proche voisin)
  - Méthode bilinéaire (meilleure qualité)

#### Images couleur (ColorImage)
- Manipulation d'images RGB 24 bits
- Dessin de rectangles (pleins ou vides)
- Tracé de lignes avec l'algorithme de Bresenham
- Redimensionnement d'images:
  - Méthode simple (plus proche voisin)
  - Méthode bilinéaire (meilleure qualité)
- Support des espaces de couleurs RGB et CMY

## Utilisation

### Installation

```bash
git clone https://github.com/RobinHil/image-library.git
cd image-library
```

### Exemples d'utilisation

#### Création et manipulation d'une image en niveaux de gris

```cpp
// Création d'une image 150x300
GrayImage *img = new GrayImage(150, 300);

// Remplissage avec du blanc
img->clear(255);

// Dessin d'un rectangle noir
img->fillRectangle(1, 2, 50, 72, 0);

// Sauvegarde au format PGM
std::ofstream os("image.pgm", std::ios::binary);
img->writePGM(os);

delete img;
```

#### Lecture et redimensionnement d'une image couleur

```cpp
// Lecture d'une image PPM
std::ifstream is("input.ppm", std::ios::binary);
ColorImage *img = ColorImage::readPPM(is);

// Redimensionnement bilinéaire
ColorImage *resized = img->bilinearScale(823, 400);

// Sauvegarde au format TGA avec compression RLE
std::ofstream os("output.tga", std::ios::binary);
resized->writeTGA(os, true);

delete img;
delete resized;
```

## Détails techniques

### Classes principales

- **GrayImage** : Gestion des images en niveaux de gris (8 bits)
- **ColorImage** : Gestion des images couleur RGB (24 bits)
- **Color** : Classe utilitaire pour la manipulation des couleurs
