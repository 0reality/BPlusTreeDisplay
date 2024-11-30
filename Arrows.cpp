#include "Arrows.h"

void ArrowOverlay::addArrow(const QPoint &start, const QPoint &end) {
    arrows.emplace_back(ArrowData{start, end, true});
    update();
}

bool ArrowOverlay::removeArrow(int index) {
    if (index >= 0 && index < arrows.size()) {
        arrows.erase(arrows.begin() + index);
        update();
        return true;
    }
    return false;
}

void ArrowOverlay::clearArrows() {
    arrows.clear();
    update();
}


