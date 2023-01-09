#include "Simulator.h"
#include "UI.h"

int main() {
    int NL, NC;
    //srand(time(nullptr));
    Menu(NL, NC);
    Simulator simulator(NL, NC);
    return 0;
}
