#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime> //obtener tiempo de venta
#include <fstream>

#include "clasesf.h"
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"

using namespace std;


EstServ* crearEst(Venta** arrayVenta, Tanque tanqueGas, Surtidor* surt){
    string nom;
    string ger;
    string reg;
    string ubi;
    Zona z;
    cout<<"ingrese el nombre de la estacion"<<endl;
    cin>>nom;
    cout<<"ingrese el nombre del gerente de la estacion"<<endl;
    cin>>ger;
    cout<<"ingrese la zona de la estacion (NORTE, CENTRO, SUR)"<<endl;
    cin>>reg;

    if (reg == "NORTE") {
        z = Zona::NORTE;
    } else if (reg == "CENTRO") {
        z = Zona::CENTRO;
    } else if (reg == "SUR") {
        z = Zona::SUR;
    }
    else {
        cerr << "Zona desconocida, asignando valor por defecto (NORTE)." <<endl;
        z = Zona::NORTE;
    }
    cout<<"ingrese la ubicacion GPS de la estacion (latitud y longitud)"<<endl;
    cin>>ubi;


    EstServ* est = new EstServ(nom, ger, z, ubi, arrayVenta, tanqueGas, surt);


    return est;
}

void simularVenta(EstServ* estacion, Surtidor** surtidores, int numSurtidores, Venta** arrayVenta, Tanque* tanqueGas) {
    if (!estacion || !surtidores || numSurtidores == 0 || !arrayVenta || !tanqueGas) {
        cout << "Error: Datos insuficientes para simular la venta." << endl;
        return;
    }

    // Asignar un surtidor aleatorio activo
    int surtidorAsignado = rand() % numSurtidores;
    cout << "Surtidor asignado: " << surtidores[surtidorAsignado]->getModelo() << " (ID: " << surtidores[surtidorAsignado]->getCodId() << ")" << endl;

    // Cantidad de gasolina a vender (entre 3 y 20 litros)
    int litrosVendidos = (rand() % 18) + 3; // genera entre 3 y 20 litros
    cout << "Cantidad de litros solicitados: " << litrosVendidos << " litros" << endl;

    // Obtener el precio por litro según la región
    float precioPorLitro = 0.0;
    Zona region = estacion->getRegion();
    switch (region) {
    case Zona::NORTE:
        precioPorLitro = 1.25; // Precio por litro para región Norte
        break;
    case Zona::CENTRO:
        precioPorLitro = 1.10; // Precio por litro para región Centro
        break;
    case Zona::SUR:
        precioPorLitro = 1.15; // Precio por litro para región Sur
        break;
    default:
        cout << "Error: Región desconocida." << endl;
        return;
    }
    cout << "Precio por litro según la región: $" << precioPorLitro << endl;

    // Calcular el monto total a pagar
    float montoTotal = litrosVendidos * precioPorLitro;
    cout << "Monto total a pagar: $" << montoTotal << endl;

    //Venta* ventaRealizada = new Venta(litrosVendidos, TComb::REGULAR, TPago::EFECTIVO, 123456, montoTotal);
    //arrayVenta[0] = ventaRealizada; // Almacena la venta en el array

    // Mostrar datos de la venta
    //ventaRealizada->mostrarVenta();
}

void guardarVentas(Venta** arrayVentas, int numVentas, const char* filename) {
    std::ofstream archivo(filename);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    for (int i = 0; i < numVentas; ++i) {
        archivo << *arrayVentas[i];  // Serializar cada venta
    }

    archivo.close();
}

void leerVentas(Venta** arrayVentas, int numVentas, const char* filename) {
    std::ifstream archivo(filename);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para leer." << std::endl;
        return;
    }

    for (int i = 0; i < numVentas; ++i) {
        arrayVentas[i] = new Venta();        // Crear nuevo objeto Venta
        archivo >> *arrayVentas[i];          // Deserializar cada venta
    }

    archivo.close();
}
