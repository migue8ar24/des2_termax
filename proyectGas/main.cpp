#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime> //obtener tiempo de venta
#include "clasesf.h"
#include "funcH.h"
using namespace std;


int main()
{
    unsigned short int accion = 0;
    unsigned short int contObj = 0;
    EstServ* estaciones = new EstServ[15];

    cout<<"bienvenido al sistema de manejo de TERMAX"<<endl;
    cout<<"Que Accion desea realizar? presione para: \n gestion de red: 1 \n Gestion de estaciones de servicio:2 \n verificacion de fugas: 3 \n Simulacion de ventas: 4"<<endl;
    cin>>accion;
    if (accion == 1){
        cout<<"Que Accion desea realizar? presione para: \n agregar estacion: 1 \n Eliminar E/S (si no posee surtidores activos): 2 \n Calcular ventas totales(por categoria): 3 \n Fijar los precios de red: 4"<<endl;
        unsigned short int accionRed = 0;
        cin>>accionRed;
        if (accionRed == 1){
            estaciones[contObj]= crearEst();
            contObj+=1;
        }
        else if (accionRed == 2){
            cout<<"a"<<endl;
        }
        else if (accionRed == 3){
            cout<<"a"<<endl;
        }
        else if (accionRed == 4){
            cout<<"a"<<endl;
        }
        else{
            cout<<"a"<<endl;
        }
    }
    else if (accion == 2){
        cout<<"a"<<endl;
    }
    else if (accion == 3){
        cout<<"a"<<endl;
    }
    else if (accion == 4){
        cout<<"a"<<endl;
    }
    else {
        cout<<"a"<<endl;
    }
    delete[] estaciones;
}
