#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include "surtidor.h"
#include "clasesf.h"
#include <string> //manejo strings
using namespace std;

Surtidor::Surtidor(string mod){
    codId = rand() % 100; // no repetido
    modelo = mod;
    activado=true;
}
Surtidor::Surtidor(){
    codId = rand() % 100; // no repetido
    modelo = "";
    activado = true;
}


// Getters
int Surtidor::getCodId() {
    return codId;
}
string Surtidor::getModelo() {
    return modelo;
}
bool Surtidor::getActivado() {
    return activado;
}

//setters
void Surtidor::setCodId(int  _codId) {
    codId = _codId;
}
void Surtidor::setModelo(string _modelo) {
    modelo = _modelo;
}
void Surtidor::setActivado(bool _activado) {
    modelo = _activado;
}

Surtidor::~Surtidor(){}

//metodos problema


