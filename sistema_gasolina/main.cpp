#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime> //obtener tiempo de venta
#include "clasesf.h"
#include <fstream>
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
                    surtidores[i] = Surtidor();  // Crear objetos dinamicamente
                }

                // Crear un tanque de gas
                Tanque tanqueG;

                // Llamar a crearEst pasando el array de ventas y el tanque
                estaciones[contEstaciones] = crearEst(arrayVentas, tanqueG, surtidores, cantVent);

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
                        break; //verificar
                    }
                }


            }
            else if (accionRed == 3){
                cout<<"verificar ventas en cada E/S del pais por categoria"<<endl;

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
/*

    Venta miVenta(50, TComb::REGULAR, TPago::EFECTIVO, 123456, 1000, "Estación A", "Surtidor 1");

    // Guardar la venta en un archivo binario
    std::ofstream archivoSalida("ventaData.bin", std::ios::binary);
    if (archivoSalida.is_open()) {
        miVenta.guardarVentaBinario(archivoSalida);
        archivoSalida.close();
    } else {
        std::cerr << "Error al abrir el archivo para guardar." << std::endl;
    }

    // Cargar la venta desde un archivo binario
    Venta ventaCargada;
    std::ifstream archivoEntrada("ventaData.bin", std::ios::binary);
    if (archivoEntrada.is_open()) {
        ventaCargada.cargarVentaBinario(archivoEntrada);
        archivoEntrada.close();
        ventaCargada.mostrarVenta();
    } else {
        std::cerr << "Error al abrir el archivo para cargar." << std::endl;
    }

    Tanque miTanque;

    // Guardar el objeto Tanque en un archivo binario
    ofstream archivoSalida2("tanqueData.bin", ios::binary);
    if (archivoSalida2.is_open()) {
        miTanque.guardarTanqueBinario(archivoSalida2);
        archivoSalida2.close();
    } else {
        cerr << "Error al abrir el archivo para guardar." << endl;
    }

    // Cargar el objeto Tanque desde un archivo binario
    ifstream archivoEntrada2("tanqueData.bin", ios::binary);
    if (archivoEntrada2.is_open()) {
        miTanque.cargarTanqueBinario(archivoEntrada2);
        archivoEntrada2.close();
    } else {
        cerr << "Error al abrir el archivo para cargar." << endl;
    }

    cout << "Atributos del tanque cargado:" << endl;
    cout << "Capacidad Regular: " << miTanque.getCapacidadRegular() << endl;
    cout << "Capacidad Premium: " << miTanque.getCapacidadPremium() << endl;
    cout << "Capacidad EcoExtra: " << miTanque.getCapacidadEcoExtra() << endl;
    cout << "Gasolina Disponible Regular: " << miTanque.getDispRegular() << endl;
    cout << "Gasolina Disponible Premium: " << miTanque.getDispPremium() << endl;
    cout << "Gasolina Disponible EcoExtra: " << miTanque.getDispEcoExtra() << endl;

    Surtidor miSurtidor("Modelo A");

    // Guardar el surtidor en un archivo binario
    ofstream archivoSalida3("surtidorData.bin", ios::binary);
    if (archivoSalida3.is_open()) {
        miSurtidor.guardarSurtidorBinario(archivoSalida3);
        archivoSalida3.close();
    } else {
        cerr << "Error al abrir el archivo para guardar." << endl;
    }

    // Cargar el surtidor desde un archivo binario
    Surtidor surtidorCargado;
    ifstream archivoEntrada3("surtidorData.bin", ios::binary);
    if (archivoEntrada3.is_open()) {
        surtidorCargado.cargarSurtidorBinario(archivoEntrada3);
        archivoEntrada3.close();
    } else {
        cerr << "Error al abrir el archivo para cargar." << endl;
    }

    cout << "Atributos del surtidor cargado:" << endl;
    cout << "CodId: " << surtidorCargado.getCodId() << endl;
    cout << "Modelo: " << surtidorCargado.getModelo() << endl;
    cout << "Activado: " << surtidorCargado.getActivado() << endl;

    Venta* listaVentas[10];  // Suponiendo un arreglo de 10 ventas
    for (int i = 0; i < 10; ++i) {
        listaVentas[i] = new Venta(100, TComb::REGULAR, TPago::EFECTIVO, 12345, 1000, "Estacion A", "Surtidor 1");
    }

    Surtidor surtidores[12] = { Surtidor("Modelo A"), Surtidor("Modelo B"), Surtidor("Modelo C") };
    Tanque tanque;

    EstServ estacion("Estacion A", "Gerente 1", Zona::NORTE, "Ubicacion A", listaVentas, tanque, surtidores, 10);

    // Guardar el objeto en un archivo binario
    ofstream archivoSalida4("estacionData.bin", ios::binary);
    if (archivoSalida4.is_open()) {
        estacion.guardarEstServBinario(archivoSalida4);
        archivoSalida4.close();
    } else {
        cerr << "Error al abrir el archivo para guardar." << endl;
    }

    // Cargar el objeto desde un archivo binario
    EstServ estacionCargada;
    ifstream archivoEntrada4("estacionData.bin", ios::binary);
    if (archivoEntrada4.is_open()) {
        estacionCargada.cargarEstServBinario(archivoEntrada4);
        archivoEntrada4.close();
    } else {
        cerr << "Error al abrir el archivo para cargar." << endl;
    }

    std::cout << "Nombre de la estacion: " << estacionCargada.getNombre() << std::endl;
    std::cout << "Codigo de la estacion: " << estacionCargada.getCodigo() << std::endl;
    std::cout << "Gerente: " << estacionCargada.getGerente() << std::endl;
    std::cout << "Region: " << zonaToString(estacionCargada.getRegion()) << std::endl;  // Convertir enum a int para imprimir
    std::cout << "Ubicacion: " << estacionCargada.getUbicacion() << std::endl;
*/
    return 0;

}
