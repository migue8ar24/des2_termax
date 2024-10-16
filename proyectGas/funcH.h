#include <iostream>
#include "clasesf.h"
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include <string> //manejo strings
using namespace std;

#ifndef FUNCH_H
#define FUNCH_H

string zonaToString(Zona reg);
EstServ* crearEst(Venta** arrayVenta, Tanque tanqueGas, Surtidor* surt, int cantV);
EstServ* seleccionarEstacion(EstServ* estaciones, int numEstaciones, const string& nombreEstacion);

void simularVenta(EstServ& estacion, Surtidor* surtidores, int numSurtidores, Tanque& tanque, Venta** listaVentas, int cantVentas);
void guardarVentas(Venta** arrayVentas, int numVentas, const char* filename);
void leerVentas(Venta** arrayVentas, int numVentas, const char* filename);
void VentasCat(EstServ** estaciones, int tamano);
void verificarFugas(EstServ* estaciones, int numEstaciones, const string& nombreEstacion);
double obtenerPrecioPorLitro(Zona region, TComb tipoCombustible);
void simularVentaEnEstacion(EstServ* estaciones, int numEstaciones, const string& nombreEstacion);
void aSurtidor(EstServ** estaciones,int cant);
void actSurtidor(EstServ** estaciones,int cant);
void imprimirVentasEst(EstServ** estaciones,int cant);
void imprimirLitros(EstServ** estaciones, int cant);
#endif // FUNCH_H


