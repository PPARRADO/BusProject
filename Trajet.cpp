//
// Created by pascal on 24/11/16.
//

#include "Trajet.h"

int Trajet::getPointDepart() const {
    return PointDepart;
}

void Trajet::setPointDepart(int PointDepart) {
    Trajet::PointDepart = PointDepart;
}

int Trajet::getNumeroDeLigne() const {
    return NumeroDeLigne;
}

void Trajet::setNumeroDeLigne(int NumeroDeLigne) {
    Trajet::NumeroDeLigne = NumeroDeLigne;
}

int Trajet::getPointArrivee() const {
    return PointArrivee;
}

void Trajet::setPointArrivee(int PointArrivee) {
    Trajet::PointArrivee = PointArrivee;
}

int Trajet::getHeureDepart() const {
    return HeureDepart;
}

void Trajet::setHeureDepart(int HeureDepart) {
    Trajet::HeureDepart = HeureDepart;
}

int Trajet::getHeureArrivee() const {
    return HeureArrivee;
}

void Trajet::setHeureArrivee(int HeureArrivee) {
    Trajet::HeureArrivee = HeureArrivee;
}

int Trajet::getDistance() const {
    return Distance;
}

void Trajet::setDistance(int Distance) {
    Trajet::Distance = Distance;
}

int Trajet::getTemps() const {
    return Temps;
}

void Trajet::setTemps(int Temps) {
    Trajet::Temps = Temps;
}

char Trajet::getSens() const {
    return sens;
}

void Trajet::setSens(char sens) {
    Trajet::sens = sens;
}

Trajet::Trajet(int NumeroDeLigne, int PointDepart, int PointArrivee, int HeureDepart, int HeureArrivee, int Temps,
               int Distance, char sens) : NumeroDeLigne(NumeroDeLigne), PointDepart(PointDepart),
                                          PointArrivee(PointArrivee), HeureDepart(HeureDepart),
                                          HeureArrivee(HeureArrivee), Temps(Temps), Distance(Distance), sens(sens) {}
