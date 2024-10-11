#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime> //obtener tiempo de venta
#include "clasesf.h"
using namespace std;


EstServ crearEst(){
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

    EstServ est(nom,ger,z, ubi);


    return est;
}
