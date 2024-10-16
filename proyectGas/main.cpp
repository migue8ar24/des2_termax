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
    unsigned short int accionRed = 0;
    unsigned short int contEstaciones = 0;
    unsigned short int precioRegN= 10000;
    unsigned short int precioPremN=10000;
    unsigned short int precioEcoN=10000;
    unsigned short int precioRegC= 10000;
    unsigned short int precioPremC=10000;
    unsigned short int precioEcoC=10000;
    unsigned short int precioRegS= 10000;
    unsigned short int precioPremS=10000;
    unsigned short int precioEcoS=10000;

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
                    surtidores[i] = Surtidor();
                }

                // Crear un tanque de gas
                Tanque tanqueG;

                // Llamar a crearEst pasando el array de ventas y el tanque
                estaciones[contEstaciones] = crearEst(arrayVentas, tanqueG, surtidores,cantVent);

                // Incrementar el contador de estaciones
                contEstaciones++;


            }

            else if (accionRed == 2){
                cout<<"Eliminar E/S (si no posee surtidores activos): 2"<<endl;
                cout<<"Que estacion desea eliminar?(ingrese el nombre de la estacion))"<<endl;
                string delStation = "";
                bool desact = true;
                cin>>delStation;
                for (int i=0;i<tam;i++){
                    if (estaciones[i]->getNombre()==delStation){
                        for(int j= 0; j<=12;j++){
                            Surtidor* verificar = estaciones[i]->getSurtidores();
                            if (verificar[j].getActivado()==true){ //set todas como desactivadas
                                desact = false;
                                break;
                            }
                        }

                    }
                    if (desact==true){
                        delete estaciones[i];
                        contEstaciones-=1;
                        cout<<"estacion borrada"<<endl;
                        break; //verificar borrado con depurador
                    }
                }


            }
            else if (accionRed == 3){
                cout<<"verificar ventas en cada E/S del pais por categoria"<<endl;
                VentasCat(estaciones,contEstaciones);
            }
            else if (accionRed == 4){
                cout<<"Fijar los precios del combustible para toda la red. "<<endl;
                unsigned short int _precioRegN;
                unsigned short int _precioPremN;
                unsigned short int _precioEcoN;
                unsigned short int _precioRegC;
                unsigned short int _precioPremC;
                unsigned short int _precioEcoC;
                unsigned short int _precioRegS;
                unsigned short int _precioPremS;
                unsigned short int _precioEcoS;
                cout<<"ingrese el precio del combustible regular en el norte"<<endl;
                cin>>_precioRegN;
                precioRegN =_precioRegN;
                cout<<"ingrese el precio del combustible premium en el norte"<<endl;
                cin>>_precioPremN;
                precioPremN =_precioPremN;
                cout<<"ingrese el precio del combustible Eco en el norte"<<endl;
                cin>>_precioEcoN;
                precioEcoN =_precioEcoN;
                cout<<"ingrese el precio del combustible regular en el centro"<<endl;
                cin>>_precioRegC;
                precioRegC =_precioRegC;
                cout<<"ingrese el precio del combustible premium en el centro"<<endl;
                cin>>_precioPremC;
                precioPremC=_precioPremC;
                cout<<"ingrese el precio del combustible Eco en el centro"<<endl;
                cin>>_precioEcoC;
                precioEcoC=_precioEcoC;
                cout<<"ingrese el precio del combustible regular en el sur"<<endl;
                cin>>_precioRegS;
                precioRegS=_precioRegS;
                cout<<"ingrese el precio del combustible premium en el sur"<<endl;
                cin>>_precioPremS;
                precioPremS=_precioPremS;
                cout<<"ingrese el precio del combustible Eco en el sur"<<endl;
                cin>>_precioEcoS;
                precioEcoS=_precioEcoS;
            }
            else{
                cout<<"Accion no disponible"<<endl;
            }
            accionRed=0;
        }
        else if (accion == 2){
            cout<<"Que Accion desea realizar? presione para: \n Agregar/eliminar un surtidor de una E/S: 1 \n"
                <<" Activar/desactivar un surtidor de una E/S: 2 \n Consultar el historico de transacciones de cada surtidor de la E/S: 3 \n"
                <<" Reportar la cantidad de litros vendida segun cada categoria de combustible: 4 \n Simular una venta de combustible: 5 \n"
                <<" Asignar la capacidad del tanque de suministro, con un valor aleatorio entre 100 y 200 litros para cada una de las categorias: 6"<<endl;
            cin>>accionRed;
            if (accionRed == 1) {
                cout << "Agregar/eliminar un surtidor de una E/S" << endl;
                aSurtidor(estaciones,contEstaciones);
            }
            else if (accionRed == 2) {
                cout << "Activar/desactivar un surtidor de una E/S" << endl;
                actSurtidor(estaciones,contEstaciones);
            }
            else if (accionRed == 3) {
                cout << "Consultar el historico de transacciones de cada surtidor de la E/S:" << endl;
                imprimirVentasEst(estaciones,contEstaciones);
            }
            else if (accionRed == 4) {
                cout << "Reportar la cantidad de litros vendida segun cada categoria de combustible" << endl;
                imprimirLitros(estaciones, contEstaciones);
            }
            else if (accionRed == 5) {
                cout << "hacer una venta de combustible" << endl;
            }
            else if (accionRed == 6) {
                cout<< "Asignar la capacidad del tanque de suministro, con un valor aleatorio entre \n"
                    <<"100 y 200 litros para cada una de las categorias" << endl;
                cout << "Que estacion desea reconfigurar?" << endl;
                /*string estacion = "";
                cin>>estacion;
                for(int j=0;j<cant;j++){
                    if(estaciones[j]->getNombre()==estacion){
                        estaciones[j]->setTanquePrincipal(Tanque())

                    }
                */
            }
            else{
                cout<<"Accion no disponible"<<endl;
            }
            accionRed=0;
        }
        else if (accion == 3){
            // Solicitar el nombre de la estación al usuario
            string nombreEstacion;
            cout << "Ingrese el nombre de la estacion para verificar fugas: ";
            cin >> nombreEstacion;

            verificarFugas(*estaciones, tam, nombreEstacion);
        }
        else if (accion == 4){
            // Solicitar el nombre de la estación al usuario
            string nombreEstacion;
            cout << "Ingrese el nombre de la estacion: ";
            cin >> nombreEstacion;

            // Llamar a la función para simular la venta en la estación seleccionada
            simularVentaEnEstacion(*estaciones, tam , nombreEstacion);
        }
        else {
            cout<<"Accion no disponible"<<endl;
        }

        cout<<"desea cerrar el sistema?(presione un numero distinto a 1 para salir)"<<endl;
        cin>>sistema;
    }
    delete[] estaciones;

}
