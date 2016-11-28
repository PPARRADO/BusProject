//
// Created by pascal on 24/11/16.
//

#ifndef BUSPROJECT_VOYAGE_H
#define BUSPROJECT_VOYAGE_H


class Trajet {

private:
    int NumeroDeLigne;
    int PointDepart;
    int PointArrivee;
    int HeureDepart;        //En minute
    int HeureArrivee;       //En minute
    int Temps;              //En minute
    int Distance;           //En mètre
    char sens;              // 'a' ou 'r' pour aller ou retour


public:
    int getPointDepart() const;

    void setPointDepart(int PointDepart);

    int getNumeroDeLigne() const;

    void setNumeroDeLigne(int NumeroDeLigne);

    int getPointArrivee() const;

    void setPointArrivee(int PointArrivee);

    int getHeureDepart() const;

    void setHeureDepart(int HeureDepart);

    int getHeureArrivee() const;

    void setHeureArrivee(int HeureArrivee);

    int getDistance() const;

    void setDistance(int Distance);

    Trajet(int NumeroDeLigne, int PointDepart, int PointArrivee, int HeureDepart, int HeureArrivee, int Temps,
           int Distance, char sens);

    int getTemps() const;

    void setTemps(int Temps);

    char getSens() const;

    void setSens(char sens);

};


#endif //BUSPROJECT_VOYAGE_H
