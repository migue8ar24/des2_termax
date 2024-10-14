#include <iostream>
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include "surtidor.h"
#include "clasesf.h"
#include <string> //manejo strings
using namespace std;

EstServ:: EstServ(string nom, string ger, Zona reg, string ubi, Venta** arrayVenta, Tanque tanqueGas, Surtidor* arraySurtidor ){
    nombre = nom;
    codigo = rand() % 100; //verificacion de no existente
    gerente = ger;
    region = reg;
    ubicacion = ubi;
    listaVentas = arrayVenta;
    tanquePrincipal = tanqueGas;
    arraySurtidores = new Surtidor[12];
    for (int i = 0; i < 12; i++) {
        arraySurtidores[i] = arraySurtidor[i];  // Asignar el arreglo recibido
    }

}

EstServ::EstServ(): nombre(""), codigo(0), gerente(""), region(Zona::CENTRO), ubicacion(""), listaVentas(nullptr), tanquePrincipal(),arraySurtidores(nullptr){
}

// Getters
string EstServ:: getNombre() {
    return nombre;
}
int EstServ::getCodigo() {
    return codigo;
}
string EstServ::getGerente() {
    return gerente;
}
Zona EstServ::getRegion() {
    return region;
}
string EstServ::getUbicacion() {
    return  ubicacion;
}
Venta EstServ::getListaVentas() {
    return  **listaVentas;
}
Tanque EstServ::getTanquePrincipal() {
    return  tanquePrincipal;
}

Surtidor* EstServ::getSurtidores() {
    return  arraySurtidores;
}

//setters
void EstServ::setNombre(string _nombre) {
    nombre = _nombre;
}
void EstServ::setCodigo(int _codigo) {
    codigo = _codigo;
}
void EstServ::setGerente(string _gerente) {
    gerente = _gerente;
}
void EstServ::setRegion(Zona _region) {
    region = _region;
}
void EstServ::setUbicacion(string _ubicacion) {
    ubicacion = _ubicacion;
}
void EstServ::setListaVentas(Venta** _listaVentas) {
    listaVentas = _listaVentas;
}
void EstServ::setTanquePrincipal(Tanque _tanque) {
    tanquePrincipal = _tanque;
}
void EstServ::setSurtidores(Surtidor* _arraySurtidor) {
    arraySurtidores = _arraySurtidor;
}

EstServ::~EstServ() {
    for (int i = 0; i < 10; i++) {  // O el tamaño adecuado para el arreglo
        delete listaVentas[i];  // Eliminar cada objeto Venta
    }
    delete[] listaVentas;  // Eliminar el arreglo de
    delete[] arraySurtidores;



}

//metodos problema

void EstServ::verificarFugas(Tanque &tanque, int vendidoRegular, int vendidoPremium, int vendidoEcoExtra) {
    // Verificación para combustible Regular
    int totalRegular = vendidoRegular + tanque.getDispRegular();
    if (totalRegular < 0.95 * tanque.getCapacidadRegular()) {
        cout << "Posible fuga detectada en combustible Regular." << endl;
    }

    // Verificación para combustible Premium
    int totalPremium = vendidoPremium + tanque.getDispPremium();
    if (totalPremium < 0.95 * tanque.getCapacidadPremium()) {
        cout << "Posible fuga detectada en combustible Premium." << endl;
    }

    // Verificación para combustible EcoExtra
    int totalEcoExtra = vendidoEcoExtra + tanque.getDispEcoExtra();
    if (totalEcoExtra < 0.95 * tanque.getCapacidadEcoExtra()) {
        cout << "Posible fuga detectada en combustible Extra." << endl;
    }

    // Si no hay fugas
    if (totalRegular > 0.95 * tanque.getCapacidadRegular() && totalPremium > 0.95 * tanque.getCapacidadPremium() && totalEcoExtra > 0.95 * tanque.getCapacidadEcoExtra())
        cout << "No se detectaron fugas en la estacion." << endl;
}

