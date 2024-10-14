#include <iostream>
#include "clasesf.h"
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include <string> //manejo strings
using namespace std;


#ifndef FUNCH_H
#define FUNCH_H


EstServ* crearEst(Venta** arrayVenta, Tanque tanqueGas,Surtidor* surt);

#endif // FUNCH_H
