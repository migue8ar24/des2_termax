#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include "surtidor.h"
#include "clasesf.h"
#include <string> //manejo strings
using namespace std;

Tanque::Tanque() {
    capacidadRegular = 100+ rand() % 200;
    capacidadPremium = 100+ rand() % 200;
    capacidadEcoExtra = 100+ rand() % 200;
    gasDispRegular = 100+ rand() % capacidadRegular;
    gasDispPremium = 100+ rand() % capacidadPremium;
    gasDispEcoExtra = 100+ rand() % capacidadEcoExtra;

}



// Getters
int Tanque::getDispRegular() {
    return gasDispRegular;
}

int Tanque::getDispPremium() {
    return gasDispPremium;
}

int Tanque::getDispEcoExtra() {
    return gasDispEcoExtra;
}

int Tanque::getCapacidadRegular() {
    return capacidadRegular;
}

int Tanque::getCapacidadPremium() {
    return capacidadPremium;
}

int Tanque::getCapacidadEcoExtra() {
    return capacidadEcoExtra;
}


// Setters
void Tanque::setDispRegular(int _gasDispRegular) {
    gasDispRegular = _gasDispRegular;
}

void Tanque::setDispPremium(int _gasDispPremium) {
    gasDispPremium = _gasDispPremium;
}

void Tanque::setDispEcoExtra(int _gasDispEcoExtra) {
    gasDispEcoExtra = _gasDispEcoExtra;
}

void Tanque::setCapacidadRegular(int _capacidadRegular) {
    capacidadRegular = _capacidadRegular;
}

void Tanque::setCapacidadPremium(int _capacidadPremium) {
    capacidadPremium = _capacidadPremium;
}

void Tanque::setCapacidadEcoExtra(int _capacidadEcoExtra) {
    capacidadEcoExtra = _capacidadEcoExtra;
}

Tanque::~Tanque() {
}

//metodos problema


