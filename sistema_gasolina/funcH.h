#include <iostream>
#include "clasesf.h"
using namespace std;

#ifndef FUNCH_H
#define FUNCH_H


EstServ* crearEst(Venta** arrayVenta, Tanque* tanqueGas);
void simularVenta(EstServ* estacion, Surtidor** surtidores, int numSurtidores, Venta** arrayVenta, Tanque* tanqueGas);

#endif // FUNCH_H
