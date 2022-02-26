#include "Camera.hpp"
#include "Rayon.hpp"
#include <thread>
#include <mutex>

std::mutex mutexImage;
std::mutex mutexCout;

Camera::Camera() {
    position = Point(0.0, 0.0, 2.0);;
    cible = Point(0.0, 0.0, 0.0);
    distance = 2.0;
}

Camera::~Camera() {}

void Camera::genererImage(const Scene &sc, Image &im, int profondeur) {
    // Calcul des dimensions d'un pixel par rapport
    // à la résolution de l'image - Les pixels doivent être carrés
    // pour éviter les déformations de l'image.
    // On fixe :
    // - les dimensions en largeur de l'écran seront comprises dans [-1, 1]
    // - les dimensions en hauteur de l'écran soront comprises dans [-H/L, H/L]
    float cotePixel = 2.0 / im.getLargeur();

    // Pour chaque pixel
    for (int i = 0; i < im.getLargeur(); i++) {
        for (int j = 0; j < im.getHauteur(); j++) {

            // calcul des coordonnées du centre du pixel
            float milieuX = -1 + (i + 0.5f) * cotePixel;
            float milieuY = (float) im.getHauteur() / (float) im.getLargeur()
                            - (j + 0.5f) * cotePixel;

            Point centre(milieuX, milieuY, 0);

            // Création du rayon
            Vecteur dir(position, centre);
            dir.normaliser();
            Rayon ray(position, dir);

            // Lancer du rayon primaire
            Intersection inter;
            if (sc.intersecte(ray, inter)) {
                im.setPixel(i, j, inter.getCouleur(sc, position, profondeur));
            } else
                im.setPixel(i, j, sc.getFond());

        }// for j

    }// for i
}


ostream &operator<<(ostream &out, const Camera &c) {

    out << " position = " << c.position << " - cible = " << c.cible;
    out << " - distance = " << c.distance << flush;
    return out;
}

void Camera::genererImageParallele(const Scene &sc, Image &im, int profondeur, int nbThreads) {
    currentImage=0;
    std::thread threads[nbThreads];

    for (int t = 0; t < nbThreads; ++t) {

        threads[t] = std::thread(calculeZone, std::cref(sc), std::ref(*&im), profondeur,
                                 std::cref(position));
    }

    for (int i = 0; i < nbThreads; ++i) {
        threads[i].join();
    }

}

void Camera::calculeZone(const Scene &sc, Image &im, int profondeur, const Point &position) {


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    mutexImage.lock();
    zone zone = zoneSuivante(im);
    mutexImage.unlock();

    int pick = 0;

    while (zone.hauteur != -1) {

        pick++;

//        mutexCout.lock();
//        std::cout << "Thread -> Zone X:" << zone.x << " y:" << zone.y << " hauteur:" << zone.hauteur << " largeur:"
//                  << zone.largeur << std::endl;
//        mutexCout.unlock();

        float cotePixel = 2.0 / im.getLargeur();
        for (int i = zone.x; i < zone.x + zone.largeur; i++) {
            for (int j = zone.y; j < zone.y + zone.hauteur; j++) {

                // calcul des coordonnées du centre du pixel
                float milieuX = -1 + (i + 0.5f) * cotePixel;

                mutexImage.lock();
                float milieuY = (float) im.getHauteur() / (float) im.getLargeur()
                                - (j + 0.5f) * cotePixel;
                mutexImage.unlock();

                Point centre(milieuX, milieuY, 0);

                // Création du rayon
                Vecteur dir(position, centre);
                dir.normaliser();
                Rayon ray(position, dir);

                // Lancer du rayon primaire

                Intersection inter;
                if (sc.intersecte(ray, inter)) {
                    im.setPixel(i, j, inter.getCouleur(sc, position, profondeur));
                } else {
                    im.setPixel(i, j, sc.getFond());
                }
            }// for j

        }// for i



        mutexImage.lock();
        zone = zoneSuivante(im);
        mutexImage.unlock();

    }

    mutexCout.lock();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "fin thread " << this_thread::get_id() << " en "
              << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000 << "s"
              << " Demandes " << pick
              << std::endl;
    mutexCout.unlock();
}

zone Camera::zoneSuivante(const Image &im) {
    int nbImageLargeur = im.getLargeur() / LARGZONE;
    int nbImageHauteur = im.getHauteur() / HAUTZONE;

    int currentLargeur = currentImage % nbImageLargeur;
    int currentHauteur = currentImage / nbImageLargeur;

    if (currentHauteur >= nbImageHauteur) {
        zone zone;
        zone.largeur = -1;
        zone.hauteur = -1;
        zone.x = -1;
        zone.y = -1;
        return zone;

    }
    zone zone;
    zone.x = currentLargeur * LARGZONE;
    zone.y = currentHauteur * HAUTZONE;
    zone.hauteur = HAUTZONE;

    if (currentLargeur == nbImageLargeur - 1) {
        zone.largeur = im.getLargeur() - zone.x;
    } else {
        zone.largeur = LARGZONE;
    }

    if (currentHauteur == nbImageHauteur - 1) {
        zone.hauteur = im.getHauteur() - zone.y;
    } else {
        zone.hauteur = HAUTZONE;
    }


    currentImage++;
    return zone;
}
