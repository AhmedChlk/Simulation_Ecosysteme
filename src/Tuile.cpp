#include "Tuile.hpp"

Tuile::Tuile(TypeTuile type): type(type) {}

void Tuile::setType(TypeTuile nouveauType) {
    type = nouveauType;
}
TypeTuile Tuile::getType() const {
    return type;
}

std::ostream& operator<<(std::ostream& os, const Tuile& tuile) {
    switch (tuile.getType()) {
        case TypeTuile::Eau:   os << "Eau"; break;
        case TypeTuile::Terre: os << "Terre"; break;
        case TypeTuile::Sable: os << "Sable"; break;
        default:               os << "Inconnu"; break;
    }
    return os;
}