#include <fstream>
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

void Surtidor::guardarSurtidorBinario(std::ofstream& archivo) const {
    size_t length;

    // Guardar codId
    archivo.write(reinterpret_cast<const char*>(&codId), sizeof(codId));

    // Guardar modelo (string)
    length = modelo.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Guardar el tamaño de la cadena
    archivo.write(modelo.c_str(), length);  // Guardar la cadena

    // Guardar activado
    archivo.write(reinterpret_cast<const char*>(&activado), sizeof(activado));
}

// Función para cargar el surtidor desde un archivo binario
void Surtidor::cargarSurtidorBinario(std::ifstream& archivo) {
    size_t length;
    char* buffer;

    // Cargar codId
    archivo.read(reinterpret_cast<char*>(&codId), sizeof(codId));

    // Cargar modelo (string)
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));  // Leer el tamaño de la cadena
    buffer = new char[length + 1];  // +1 para el carácter nulo
    archivo.read(buffer, length);   // Leer la cadena
    buffer[length] = '\0';  // Agregar el carácter nulo al final
    modelo = buffer;  // Asignar a la cadena modelo
    delete[] buffer;

    // Cargar activado
    archivo.read(reinterpret_cast<char*>(&activado), sizeof(activado));
}

Surtidor::~Surtidor(){}

//metodos problema
