#include <fstream>
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
    gasDispRegular = capacidadRegular;
    gasDispPremium = capacidadPremium;
    gasDispEcoExtra = capacidadEcoExtra;

}
Tanque::Tanque(int _capacidadRegular,int _capacidadPremium,int _capacidadEcoExtra,int _gasDispRegular,int _gasDispPremium,int _gasDispEcoExtra) {
    capacidadRegular = _capacidadRegular;
    capacidadPremium = _capacidadPremium;
    capacidadEcoExtra = _capacidadEcoExtra;
    gasDispRegular = _gasDispRegular;
    gasDispPremium = _gasDispPremium;
    gasDispEcoExtra = _gasDispEcoExtra;
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

void Tanque::guardarTanqueBinario(std::ofstream& archivo) const {
    archivo.write(reinterpret_cast<const char*>(&capacidadRegular), sizeof(capacidadRegular));
    archivo.write(reinterpret_cast<const char*>(&capacidadPremium), sizeof(capacidadPremium));
    archivo.write(reinterpret_cast<const char*>(&capacidadEcoExtra), sizeof(capacidadEcoExtra));
    archivo.write(reinterpret_cast<const char*>(&gasDispRegular), sizeof(gasDispRegular));
    archivo.write(reinterpret_cast<const char*>(&gasDispPremium), sizeof(gasDispPremium));
    archivo.write(reinterpret_cast<const char*>(&gasDispEcoExtra), sizeof(gasDispEcoExtra));
}

// Función para cargar los datos del tanque desde un archivo binario
void Tanque::cargarTanqueBinario(std::ifstream& archivo) {
    archivo.read(reinterpret_cast<char*>(&capacidadRegular), sizeof(capacidadRegular));
    archivo.read(reinterpret_cast<char*>(&capacidadPremium), sizeof(capacidadPremium));
    archivo.read(reinterpret_cast<char*>(&capacidadEcoExtra), sizeof(capacidadEcoExtra));
    archivo.read(reinterpret_cast<char*>(&gasDispRegular), sizeof(gasDispRegular));
    archivo.read(reinterpret_cast<char*>(&gasDispPremium), sizeof(gasDispPremium));
    archivo.read(reinterpret_cast<char*>(&gasDispEcoExtra), sizeof(gasDispEcoExtra));
}
