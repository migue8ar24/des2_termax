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

string zonaToString(Zona reg) {
    switch (reg) {
    case Zona::CENTRO: return "Centro";
    case Zona::NORTE: return "Norte";
    case Zona::SUR: return "Sur";
    default: return "Desconocido";
    }
}

EstServ* crearEst(Venta** arrayVenta, Tanque tanqueGas, Surtidor* surt, int cantV){
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


    EstServ* est = new EstServ(nom, ger, z, ubi, arrayVenta, tanqueGas, surt, cantV);


    return est;
}

double obtenerPrecioPorLitro(Zona region, TComb tipoCombustible) {
    double precio = 0.0;
    switch (region) {
    case Zona::CENTRO:
        if (tipoCombustible == TComb::REGULAR) precio = 10.0;
        else if (tipoCombustible == TComb::PREMIUM) precio = 12.0;
        else if (tipoCombustible == TComb::ECOEXTRA) precio = 11.0;
        break;
    case Zona::NORTE:
        if (tipoCombustible == TComb::REGULAR) precio = 9.5;
        else if (tipoCombustible == TComb::PREMIUM) precio = 11.5;
        else if (tipoCombustible == TComb::ECOEXTRA) precio = 10.5;
        break;
    case Zona::SUR:
        if (tipoCombustible == TComb::REGULAR) precio = 9.0;
        else if (tipoCombustible == TComb::PREMIUM) precio = 11.0;
        else if (tipoCombustible == TComb::ECOEXTRA) precio = 10.0;
        break;
    default:
        break;
    }
    return precio;
}

// Función para simular ventas
void simularVenta(EstServ& estacion, Surtidor* surtidores, int numSurtidores, Tanque& tanque, Venta** listaVentas, int cantVentas) {
    srand(time(nullptr));

    // Seleccionar surtidor activo aleatoriamente
    int surtidoresActivos[12];
    int numSurtidoresActivos = 0;
    for (int i = 0; i < numSurtidores; ++i) {
        if (surtidores[i].getActivado()) {
            surtidoresActivos[numSurtidoresActivos++] = i;
        }
    }
    if (numSurtidoresActivos == 0) {
        std::cout << "No hay surtidores activos disponibles." << std::endl;
        return;
    }

    int indiceSurtidorSeleccionado = surtidoresActivos[rand() % numSurtidoresActivos];
    Surtidor& surtidorSeleccionado = surtidores[indiceSurtidorSeleccionado];

    // Determinar cantidad de gasolina a vender
    int cantidadLitros = 3 + rand() % 18;  // Valor entre 3 y 20 litros

    // Seleccionar combustible aleatoriamente
    TComb tipoCombustible = static_cast<TComb>(rand() % 3);  // 0 = REGULAR, 1 = PREMIUM, 2 = ECOEXTRA

    // Determinar precio por litro y calcular precio total
    double precioPorLitro = obtenerPrecioPorLitro(estacion.getRegion(), tipoCombustible);
    double precioTotal = precioPorLitro * cantidadLitros;

    // Verificar y disminuir la cantidad de gasolina en el tanque
    bool ventaExitosa = false;
    switch (tipoCombustible) {
    case TComb::REGULAR:
        if (tanque.getDispRegular() >= cantidadLitros) {
            tanque.setDispRegular(tanque.getDispRegular() - cantidadLitros);
            ventaExitosa = true;
        }
        break;
    case TComb::PREMIUM:
        if (tanque.getDispPremium() >= cantidadLitros) {
            tanque.setDispPremium(tanque.getDispPremium() - cantidadLitros);
            ventaExitosa = true;
        }
        break;
    case TComb::ECOEXTRA:
        if (tanque.getDispEcoExtra() >= cantidadLitros) {
            tanque.setDispEcoExtra(tanque.getDispEcoExtra() - cantidadLitros);
            ventaExitosa = true;
        }
        break;
    }

    if (!ventaExitosa) {
        std::cout << "No hay suficiente combustible en el tanque para esta venta." << std::endl;
        return;
    }

    // Generar una venta (aleatoriamente elegimos tipo de pago y documento)
    TPago metodoPago = static_cast<TPago>(rand() % 2);  // 0 = EFECTIVO, 1 = TARJETA
    int documentoCliente = 1000 + rand() % 9000;
    Venta nuevaVenta(cantidadLitros, tipoCombustible, metodoPago, documentoCliente, precioTotal, estacion.getNombre(), surtidorSeleccionado.getModelo());

    // Registrar la venta en la lista de ventas
    for (int i = 0; i < cantVentas; ++i) {
        if (listaVentas[i] == nullptr) {
            listaVentas[i] = new Venta(nuevaVenta);
            break;
        }
    }

    // Mostrar los datos de la venta
    cout << "Venta realizada exitosamente:" << endl;
    cout << "Surtidor: " << surtidorSeleccionado.getModelo() << endl;
    cout << "Combustible: " << (tipoCombustible == TComb::REGULAR ? "Regular" : tipoCombustible == TComb::PREMIUM ? "Premium" : "EcoExtra") << endl;
    cout << "Litros vendidos: " << cantidadLitros << endl;
    cout << "Precio total: $" << precioTotal << endl;
    cout << "Método de pago: " << (metodoPago == TPago::EFECTIVO ? "Efectivo" : metodoPago == TPago::TDEBITO ? "Tdebito" : "Tcredito") << endl;
    cout << "Documento cliente: " << documentoCliente << endl;
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

EstServ* seleccionarEstacion(EstServ* estaciones, int numEstaciones, const string& nombreEstacion) {
    for (int i = 0; i < numEstaciones; ++i) {
        if (estaciones[i].getNombre() == nombreEstacion) {
            return &estaciones[i];  // Retorna el puntero a la estación encontrada
        }
    }
    return nullptr;  // Si no se encuentra la estación
}

void simularVentaEnEstacion(EstServ* estaciones, int numEstaciones, const string& nombreEstacion) {
    // Seleccionar la estación
    EstServ* estacionSeleccionada = seleccionarEstacion(estaciones, numEstaciones, nombreEstacion);

    if (estacionSeleccionada == nullptr) {
        cout << "La estación no fue encontrada." << endl;
        return;
    }

    // Simular la venta en la estación seleccionada
    simularVenta(*estacionSeleccionada, estacionSeleccionada->getSurtidores(), 12 , estacionSeleccionada->getTanquePrincipal(), estacionSeleccionada->getListaVentas(), estacionSeleccionada->getCantVentas());
}

void verificarFugas(EstServ* estaciones, int numEstaciones, const string& nombreEstacion) {

    EstServ* estacionSeleccionada = seleccionarEstacion(estaciones, numEstaciones, nombreEstacion);

    if (estacionSeleccionada == nullptr) {
        cout << "La estación no fue encontrada." << endl;
        return;
    }

    estacionSeleccionada->calcularCantidadCombustibleVendida(estacionSeleccionada->getTanquePrincipal());

}
