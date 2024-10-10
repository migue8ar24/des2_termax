#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime> //obtener tiempo de venta
#include "clasesf.h"
using namespace std;


int main()
{

    EstServ* estaciones = new EstServ[15];
    Tanque tanque(1000, 1000, 1000, 5000, 6000, 7000); // Cantidades y capacidades de ejemplo
    EstServ estacion("Estación A", "Gerente X", Zona::NORTE, "Ubicación X");

    // Cantidades vendidas de ejemplo
    int vendidoRegular = 4000;
    int vendidoPremium = 5000;
    int vendidoEcoExtra = 6000;

    estacion.verificarFugas(tanque, vendidoRegular, vendidoPremium, vendidoEcoExtra);


    cout<<"Bienvenido al sistema de manejo de TERMAX"<<endl;


}
