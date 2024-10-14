#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime> //obtener tiempo de venta
#include "clasesf.h"
#include "funcH.h"
using namespace std;


int main()
{
    unsigned short int sistema =1;
    unsigned short int tam = 15;
    unsigned short int accion = 0;
    unsigned short int contEstaciones = 0;
    //unsigned short int precioReg= 10000;
    //unsigned short int precioPrem=10000;
    //unsigned short int precioEco=10000;

    EstServ** estaciones = new EstServ*[tam];
    for (int i = 0; i < tam; ++i) {
        estaciones[i] = new EstServ();
    }
    //se crea el arreglo principal de estaciones que es un arreglo de punteros a objetos vacios(construidos por defecto)

    while (sistema == 1){
        cout<<"bienvenido al sistema de manejo de TERMAX"<<endl;
        cout<<"Que Accion desea realizar? presione para: \n gestion de red: 1 \n Gestion de estaciones de servicio:2 \n verificacion de fugas: 3 \n Simulacion de ventas: 4"<<endl;
        cin>>accion;

        if (accion == 1){
            cout<<"Que Accion desea realizar? presione para: \n agregar estacion: 1 \n Eliminar E/S (si no posee surtidores activos): 2 \n Calcular ventas totales(por categoria): 3 \n Fijar los precios de red: 4"<<endl;
            unsigned short int accionRed = 0;
            cin>>accionRed;

            if (accionRed == 1) {
                cout << "Agregar estacion" << endl;

                //crear array de 1 venta en 0 para ser expandida en el futuro
                int cantVent = 1;
                Venta** arrayVentas = new Venta*[cantVent];
                for (int i = 0; i < cantVent; ++i) {
                    arrayVentas[i] = new Venta();
                }

                Surtidor surtidores[12];
                for (int i = 0; i < 12; i++) {
                    surtidores[i] = Surtidor();  // Crear objetos dinámicamente
                }

                // Crear un tanque de gas
                Tanque tanqueG;

                // Llamar a crearEst pasando el array de ventas y el tanque
                estaciones[contEstaciones] = crearEst(arrayVentas, tanqueG, surtidores);

                // Incrementar el contador de estaciones
                contEstaciones++;


            }
            else if (accionRed == 2){
                cout<<"Eliminar E/S (si no posee surtidores activos): 2"<<endl;
                cout<<"Que estacion desea eliminar?(ingrese el nombre de la estacion))"<<endl;
                string delStation = "";
                bool desact = true;
                cin>>delStation;
                for (int i=0;i<=tam;i++){
                    if (estaciones[i]->getNombre()==delStation){
                        for(int j= 0; j<=12;j++){
                            Surtidor* verificar = estaciones[i]->getSurtidores();
                            if (verificar[j].getActivado()==true){
                                desact = false;
                                break;
                            }
                        }

                    }
                    if (desact==true){
                        delete estaciones[i];
                        contEstaciones-=1;
                        cout<<"estacion borrada"<<endl;
                        break;
                    }
                }


            }
            else if (accionRed == 3){
                cout<<"a"<<endl;
            }
            else if (accionRed == 4){


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
            cout<<"Accion no disponible"<<endl;
        }

        cout<<"desea cerrar el sistema?(presione un numero distinto a 1 para salir)"<<endl;
        cin>>sistema;
    }
    delete[] estaciones;

}
