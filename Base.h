//
// Created by pascal on 25/11/16.
//

#ifndef BUSPROJECT_BASE_H
#define BUSPROJECT_BASE_H


#include <vector>
#include "Trajet.h"

class Base {

public:
    Base(const std::vector<Trajet> &HorairEs, const std::vector<Trajet> &HorairHs);

    const std::vector<Trajet> &getHorairEs() const;

    void setHorairEs(const std::vector<Trajet> &HorairEs);

    const std::vector<Trajet> &getHorairHs() const;

    void setHorairHs(const std::vector<Trajet> &HorairHs);

    int &getHorairHsSize();

    void setHorairHsSize(int h_size);

    const Trajet getHorairHsAtPos(int from_terminus, int to_terminus) const;

private:
    std::vector<Trajet>            HorairEs;
    std::vector<Trajet>            HorairHs;
    int                            HorairHsSize;

};


#endif //BUSPROJECT_BASE_H
