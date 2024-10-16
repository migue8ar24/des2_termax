#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include "surtidor.h"
#include "clasesf.h"
#include <string> //manejo strings
using namespace std;

EstServ:: EstServ(string nom, string ger, Zona reg, string ubi, Venta** arrayVenta, Tanque tanqueGas, Surtidor* arraySurtidor, int cantV ){
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
    cantVentas = cantV;

}

EstServ::EstServ(): nombre(""), codigo(0), gerente(""), region(Zona::CENTRO), ubicacion(""), listaVentas(nullptr), tanquePrincipal(),arraySurtidores(nullptr),cantVentas(1){
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
Venta EstServ::getObjetoVenta() {
    return  **listaVentas;
}
Venta** EstServ::getListaVentas(){
    return listaVentas;
}

Tanque EstServ::getTanquePrincipal() {
    return  tanquePrincipal;
}

Surtidor* EstServ::getSurtidores() {
    return  arraySurtidores;
}
int EstServ:: getCantVentas() {
    return cantVentas;
}
Tanque& EstServ::getObjetoTanque() {
    return tanquePrincipal;
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

void EstServ::setCantVentas(int _cantVentas) {
    cantVentas = _cantVentas;
}


EstServ::~EstServ() {
    // Liberar la memoria asignada para los surtidores
    if (arraySurtidores) {
        delete[] arraySurtidores;  // Arreglo dinámico de surtidores
        arraySurtidores = nullptr;
    }

    // Liberar la memoria asignada para las ventas
    if (listaVentas) {
        cout << cantVentas;
        for (int i = 0; i < cantVentas; ++i) {
            delete listaVentas[i];  // Eliminar cada venta
        }
        delete[] listaVentas;  // Eliminar el arreglo dinámico de ventas
        listaVentas = nullptr;
    }
}

void EstServ::guardarEstServBinario(std::ofstream& archivo) const {
    size_t length;

    // Guardar nombre
    length = nombre.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length));
    archivo.write(nombre.c_str(), length);

    // Escribir gerente de la estación
    length = gerente.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length));
    archivo.write(gerente.c_str(), length);

    // Escribir la región
    archivo.write(reinterpret_cast<const char*>(&region), sizeof(region));

    // Escribir ubicación
    length = ubicacion.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length));
    archivo.write(ubicacion.c_str(), length);

    // Escribir el código de la estación
    archivo.write(reinterpret_cast<const char*>(&codigo), sizeof(codigo));

    // Escribir el tanque principal (llamar a la función de serialización de tanque)
    tanquePrincipal.guardarTanqueBinario(archivo);

    // Escribir cantidad de ventas (nuevo atributo)
    archivo.write(reinterpret_cast<const char*>(&cantVentas), sizeof(cantVentas));

    // Escribir las ventas
    for (int i = 0; i < cantVentas; i++) {
        if (listaVentas[i] != nullptr) {
            listaVentas[i]->guardarVentaBinario(archivo); // Asegurar que Venta tiene su propia función de serialización
        }
    }

    // Escribir los surtidores
    for (int i = 0; i < 12; i++) {
        arraySurtidores[i].guardarSurtidorBinario(archivo);  // Asumimos que Surtidor tiene una función de serialización
    }
}

void EstServ::cargarEstServBinario(std::ifstream& archivo) {
    size_t length;
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));
    nombre.resize(length);
    archivo.read(&nombre[0], length);

    // Leer el gerente de la estación
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));
    gerente.resize(length);
    archivo.read(&gerente[0], length);

    // Leer la región
    archivo.read(reinterpret_cast<char*>(&region), sizeof(region));

    // Leer la ubicación
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));
    ubicacion.resize(length);
    archivo.read(&ubicacion[0], length);

    // Leer el código de la estación
    archivo.read(reinterpret_cast<char*>(&codigo), sizeof(codigo));

    // Leer el tanque principal (llamar a la función de deserialización de tanque)
    tanquePrincipal.cargarTanqueBinario(archivo);

    // Leer cantidad de ventas (nuevo atributo)
    archivo.read(reinterpret_cast<char*>(&cantVentas), sizeof(cantVentas));

    // Leer las ventas
    listaVentas = new Venta*[cantVentas]; // Asegurar que listaVentas está inicializado
    for (int i = 0; i < cantVentas; i++) {
        listaVentas[i] = new Venta();  // Asegurar que se inicializan los objetos Venta
        listaVentas[i]->cargarVentaBinario(archivo); // Asegurar que Venta tiene su propia función de deserialización
    }

    // Leer los surtidores
    arraySurtidores = new Surtidor[12];
    for (int i = 0; i < 12; i++) {
        arraySurtidores[i].cargarSurtidorBinario(archivo); // Asumimos que Surtidor tiene una función de deserialización
    }
}

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

void EstServ::calcularCantidadCombustibleVendida(Tanque &tanque) {
    int cantidadRegular = 0, cantidadPremium = 0, cantidadEcoExtra = 0;

    for (int i = 0; i < cantVentas; i++) {
        if (listaVentas[i] != nullptr) {  // Verificar que la venta no sea nula
            TComb tipoCombustible = listaVentas[i]->getComb(); // Asumiendo que tienes un método para obtener el tipo de combustible
            int cantidad = listaVentas[i]->getCantidad(); // Asumiendo que tienes un método para obtener la cantidad

            switch (tipoCombustible) {
            case TComb::REGULAR:
                cantidadRegular += cantidad;
                break;
            case TComb::PREMIUM:
                cantidadPremium += cantidad;
                break;
            case TComb::ECOEXTRA:
                cantidadEcoExtra += cantidad;
                break;
            }
        }
    }

    // Invocar la función verificarFugas con las cantidades vendidas
    verificarFugas(tanque, cantidadRegular, cantidadPremium, cantidadEcoExtra);
}
