#include <iostream>
#include "clasesf.h"
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include <string> //manejo strings
using namespace std;

#ifndef FUNCH_H
#define FUNCH_H


EstServ* crearEst(Venta** arrayVenta, Tanque* tanqueGas);
void simularVenta(EstServ* estacion, Surtidor** surtidores, int numSurtidores, Venta** arrayVenta, Tanque* tanqueGas);
void guardarVentas(Venta** arrayVentas, int numVentas, const char* filename);
void leerVentas(Venta** arrayVentas, int numVentas, const char* filename);

#endif // FUNCH_H
