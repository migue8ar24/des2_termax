#ifndef TANQUE_H
#define TANQUE_H
#include "classestservicio.h"
#include "venta.h"
#include "surtidor.h"
#include "clasesf.h"
#include <string> //manejo strings
using namespace std;

class Tanque{
private:
    int gasDispRegular;   // Cantidad disponible de Regular
    int gasDispPremium;   // Cantidad disponible de Premium
    int gasDispEcoExtra;  // Cantidad disponible de EcoExtra
    int capacidadRegular; // Capacidad total de Regular
    int capacidadPremium; // Capacidad total de Premium
    int capacidadEcoExtra;// Capacidad total de EcoExtra

public:
    Tanque();
    // Getters
    int getDispRegular();
    int getDispPremium();
    int getDispEcoExtra();
    int getCapacidadRegular();
    int getCapacidadPremium();
    int getCapacidadEcoExtra();

    // Setters
    void setDispRegular(int _gasDispRegular);
    void setDispPremium(int _gasDispPremium);
    void setDispEcoExtra(int _gasDispEcoExtra);
    void setCapacidadRegular(int _capacidadRegular);
    void setCapacidadPremium(int _capacidadPremium);
    void setCapacidadEcoExtra(int _capacidadEcoExtra);

    //metodos problema, funciones amigas
    void guardarTanqueBinario(ofstream& archivo) const;
    void cargarTanqueBinario(ifstream& archivo);
    ~Tanque();
};


#endif // TANQUE_H
