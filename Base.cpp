//
// Created by pascal on 25/11/16.
//

#include "Base.h"

Base::Base(const std::vector<Trajet> &HorairEs, const std::vector<Trajet> &HorairHs) : HorairEs(HorairEs),
                                                                                       HorairHs(HorairHs) {}

const std::vector<Trajet> &Base::getHorairEs() const {
    return HorairEs;
}

void Base::setHorairEs(const std::vector<Trajet> &HorairEs) {
    Base::HorairEs = HorairEs;
}

const std::vector<Trajet> &Base::getHorairHs() const {
    return HorairHs;
}

void Base::setHorairHs(const std::vector<Trajet> &HorairHs) {
    Base::HorairHs = HorairHs;
}

int &Base::getHorairHsSize() {
    return HorairHsSize;
}

void Base::setHorairHsSize(int h_size) {
    Base::HorairHsSize = h_size;
}

const Trajet Base::getHorairHsAtPos(int from_terminus, int to_terminus) const {
    return HorairHs[HorairHsSize*from_terminus+to_terminus];
}
