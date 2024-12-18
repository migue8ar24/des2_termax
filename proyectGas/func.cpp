#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime> //obtener tiempo de venta
#include <fstream>

#include "clasesf.h"
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"

using namespace std;


EstServ* crearEst(Venta** arrayVenta, Tanque tanqueGas, Surtidor* surt, int cantV   ){
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


    EstServ* est = new EstServ(nom, ger, z, ubi, arrayVenta, tanqueGas, surt, cantV);


    return est;
}

int obtenerPrecioPorLitro(Zona region, TComb tipoCombustible) {
    int precio = 0;
    switch (region) {
    case Zona::CENTRO:
        if (tipoCombustible == TComb::REGULAR) precio = 10;
        else if (tipoCombustible == TComb::PREMIUM) precio = 12;
        else if (tipoCombustible == TComb::ECOEXTRA) precio = 11;
        break;
    case Zona::NORTE:
        if (tipoCombustible == TComb::REGULAR) precio = 9;
        else if (tipoCombustible == TComb::PREMIUM) precio = 11;
        else if (tipoCombustible == TComb::ECOEXTRA) precio = 10;
        break;
    case Zona::SUR:
        if (tipoCombustible == TComb::REGULAR) precio = 9;
        else if (tipoCombustible == TComb::PREMIUM) precio = 11;
        else if (tipoCombustible == TComb::ECOEXTRA) precio = 10;
        break;
    default:
        break;
    }
    return precio;
}

void simularVenta(EstServ& estacion, Surtidor* surtidores, int numSurtidores, Tanque& tanque, Venta** listaVentas, int cantVentas) {
    srand(time(nullptr));

    // Seleccionar surtidor activo aleatoriamente
    int surtidoresActivos[12];
    int numSurtidoresActivos = 0;
    for (int i = 0; i < numSurtidores; ++i) {
        if (surtidores[i].getActivado()) {
            surtidoresActivos[numSurtidoresActivos++] = i;
        }
    }
    if (numSurtidoresActivos == 0) {
        std::cout << "No hay surtidores activos disponibles." << std::endl;
        return;
    }

    int indiceSurtidorSeleccionado = surtidoresActivos[rand() % numSurtidoresActivos];
    Surtidor& surtidorSeleccionado = surtidores[indiceSurtidorSeleccionado];

    // Determinar cantidad de gasolina a vender
    int cantidadLitros = 3 + rand() % 18;  // Valor entre 3 y 20 litros

    // Seleccionar combustible aleatoriamente
    TComb tipoCombustible = static_cast<TComb>(rand() % 3);  // 0 = REGULAR, 1 = PREMIUM, 2 = ECOEXTRA

    // Determinar precio por litro y calcular precio total
    double precioPorLitro = obtenerPrecioPorLitro(estacion.getRegion(), tipoCombustible);
    double precioTotal = precioPorLitro * cantidadLitros;

    // Verificar y disminuir la cantidad de gasolina en el tanque
    bool ventaExitosa = false;
    switch (tipoCombustible) {
    case TComb::REGULAR:
        if (tanque.getDispRegular() >= cantidadLitros) {
            tanque.setDispRegular(tanque.getDispRegular() - cantidadLitros);
            ventaExitosa = true;
        }
        break;
    case TComb::PREMIUM:
        if (tanque.getDispPremium() >= cantidadLitros) {
            tanque.setDispPremium(tanque.getDispPremium() - cantidadLitros);
            ventaExitosa = true;
        }
        break;
    case TComb::ECOEXTRA:
        if (tanque.getDispEcoExtra() >= cantidadLitros) {
            tanque.setDispEcoExtra(tanque.getDispEcoExtra() - cantidadLitros);
            ventaExitosa = true;
        }
        break;
    }

    if (!ventaExitosa) {
        std::cout << "No hay suficiente combustible en el tanque para esta venta." << std::endl;
        return;
    }

    // Generar una venta (aleatoriamente elegimos tipo de pago y documento)
    TPago metodoPago = static_cast<TPago>(rand() % 3);
    int documentoCliente = 1000 + rand() % 9000;
    Venta nuevaVenta(cantidadLitros, tipoCombustible, metodoPago, documentoCliente, precioTotal, estacion.getNombre(), surtidorSeleccionado.getModelo());

    // Registrar la venta en la lista de ventas
    for (int i = 0; i < cantVentas; ++i) {
        if (listaVentas[i] == nullptr) {
            listaVentas[i] = new Venta(nuevaVenta);
            break;
        }
    }

    // Mostrar los datos de la venta
    cout << "Venta realizada exitosamente:" << endl;
    cout << "Surtidor: " << surtidorSeleccionado.getModelo() << endl;
    cout << "Combustible: " << (tipoCombustible == TComb::REGULAR ? "Regular" : tipoCombustible == TComb::PREMIUM ? "Premium" : "EcoExtra") << endl;
    cout << "Litros vendidos: " << cantidadLitros << endl;
    cout << "Precio total: $" << precioTotal << endl;
    cout << "Metodo de pago: " << (metodoPago == TPago::EFECTIVO ? "Efectivo" : metodoPago == TPago::TDEBITO ? "Tdebito" : "Tcredito") << endl;
    cout << "Documento cliente: " << documentoCliente << endl;
}

void guardarVentas(Venta** arrayVentas, int numVentas, const char* filename) {
    std::ofstream archivo(filename);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    for (int i = 0; i < numVentas; ++i) {
        archivo << *arrayVentas[i];  // Serializar cada venta
    }

    archivo.close();
}

void leerVentas(Venta** arrayVentas, int numVentas, const char* filename) {
    std::ifstream archivo(filename);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para leer." << std::endl;
        return;
    }

    for (int i = 0; i < numVentas; ++i) {
        arrayVentas[i] = new Venta();        // Crear nuevo objeto Venta
        archivo >> *arrayVentas[i];          // Deserializar cada venta
    }

    archivo.close();
}

EstServ* seleccionarEstacion(EstServ* estaciones, int numEstaciones, const string& nombreEstacion) {
    for (int i = 0; i < numEstaciones; ++i) {
        if (estaciones[i].getNombre() == nombreEstacion) {
            return &estaciones[i];  // Retorna el puntero a la estación encontrada
        }
    }
    return nullptr;  // Si no se encuentra la estación
}

void simularVentaEnEstacion(EstServ* estaciones, int numEstaciones, const string& nombreEstacion) {
    // Seleccionar la estación
    EstServ* estacionSeleccionada = seleccionarEstacion(estaciones, numEstaciones, nombreEstacion);

    if (estacionSeleccionada == nullptr) {
        cout << "La estación no fue encontrada." << endl;
        return;
    }

    // Simular la venta en la estación seleccionada
    simularVenta(*estacionSeleccionada, estacionSeleccionada->getSurtidores(), 12 , estacionSeleccionada->getObjetoTanque(), estacionSeleccionada->getListaVentas(), estacionSeleccionada->getCantVentas());
}

void verificarFugas(EstServ* estaciones, int numEstaciones, const string& nombreEstacion) {

    EstServ* estacionSeleccionada = seleccionarEstacion(estaciones, numEstaciones, nombreEstacion);

    if (estacionSeleccionada == nullptr) {
        cout << "La estación no fue encontrada." << endl;
        return;
    }

    estacionSeleccionada->calcularCantidadCombustibleVendida(estacionSeleccionada->getObjetoTanque());

}

void VentasCat(EstServ** estaciones, int cant){

    for (int i=0;i<cant;i++){
        unsigned int ventasReg=0;
        unsigned int ventasPrem=0;
        unsigned int ventasEco=0;
        Venta** ventaEstacion = estaciones[i]->getListaVentas();
        int cantVent = estaciones[i]->getCantVentas();
        for (int j=0; j<cantVent;j++){
            unsigned int ventaIndividual = ventaEstacion[j]->getPagado();
            TComb combustible = ventaEstacion[j]->getComb();

            if (combustible == TComb::REGULAR){
                ventasReg+= ventaIndividual;
            }
            if (combustible == TComb::PREMIUM){
                ventasPrem+= ventaIndividual;
            }
            if (combustible == TComb::ECOEXTRA){
                ventasEco+= ventaIndividual;
            }
        }
        cout<<"ventas combustible regular: "<<ventasReg<<endl;
        cout<<"ventas combustible premium: "<<ventasPrem<<endl;
        cout<<"ventas combustible EcoExtra: "<<ventasEco<<endl;
    }

}

void aSurtidor(EstServ** estaciones,int cant){
    cout<<"desea agregar o eliminar una estacion? presione 1 para agregar o 2 para eliminar"<<endl;
    unsigned short int opcion;
    cin>>opcion;
    if (opcion ==1){
        cout<<"en que estacion desea agregar?"<<endl;
        string estacion = "";
        cin>>estacion;
        for(int j=0;j<cant;j++){
            if(estaciones[j]->getNombre()==estacion){
                Surtidor* array = estaciones[j]->getSurtidores();
                for (int i=0; i<12;i++){
                    if(array[i].getModelo()== ""){
                        string modelo="";
                        cout<<"ingrese el modelo del surtidor"<<endl;
                        cin>>modelo;
                        int cod;
                        cout<<"ingrese el codigo del surtidor"<<endl;
                        cin>>cod;
                        array[i] = Surtidor(modelo,cod);
                        cout<<"surtidor creado"<<endl;
                        break;
                    }
                }
            }
        }
    }
    if (opcion == 2){
        cout<<"en que estacion desea eliminar?"<<endl;
        string estacion = "";
        cin>>estacion;
        for(int j=0;j<cant;j++){
            if(estaciones[j]->getNombre()==estacion){
                Surtidor* array = estaciones[j]->getSurtidores();
                int cod;
                cout<<"ingrese el codigo del surtidor que desea eliminar"<<endl;
                cin>>cod;
                for (int i=0; i<12;i++){
                    if(array[i].getCodId()== cod){
                        array[i] = Surtidor();
                        cout<<"surtidor eliminado"<<endl;
                        break;
                    }
                }
            }
        }
    }
}

void actSurtidor(EstServ** estaciones,int cant){
    cout<<"desea activar o desactivar una estacion? presione 1 para activar o 2 para desactivar"<<endl;
    unsigned short int opcion;
    cin>>opcion;
    if (opcion ==1){
        cout<<"en que estacion desea activar?"<<endl;
        string estacion = "";
        cin>>estacion;
        for(int j=0;j<cant;j++){
            if(estaciones[j]->getNombre()==estacion){
                Surtidor* array = estaciones[j]->getSurtidores();
                int cod;
                cout<<"ingrese el codigo del surtidor a activar"<<endl;
                cin>>cod;
                for (int i=0; i<12;i++){
                    if(array[i].getCodId()== cod){
                        array[i].setActivado(true);
                        cout<<"surtidor activado"<<endl;
                        break;
                    }
                }
            }
        }
    }
    if (opcion ==2){
        cout<<"en que estacion desea desactivar?"<<endl;
        string estacion = "";
        cin>>estacion;
        for(int j=0;j<cant;j++){
            if(estaciones[j]->getNombre()==estacion){
                Surtidor* array = estaciones[j]->getSurtidores();
                int cod;
                cout<<"ingrese el codigo del surtidor a desactivar"<<endl;
                cin>>cod;
                for (int i=0; i<12;i++){
                    if(array[i].getCodId()== cod){
                        array[i].setActivado(false);
                        cout<<"surtidor desactivado"<<endl;
                        break;
                    }
                }
            }
        }
    }
}

void imprimirVentasEst(EstServ** estaciones,int cant){
    cout<<"en que estacion desea conocer las ventas?"<<endl;
    string estacion = "";
    cin>>estacion;
    for(int j=0;j<cant;j++){
        if(estaciones[j]->getNombre()==estacion){
            Venta** ventaEstacion = estaciones[j]->getListaVentas();
            int cantVen = estaciones[j]->getCantVentas();
            for(int i =0; i<cantVen;i++){
                ventaEstacion[i]->mostrarVenta();
            }
        }
    }
}

void imprimirLitros(EstServ** estaciones, int cant){
    cout<<"en que estacion desea conocer los litros vendidos?"<<endl;
    string estacion = "";
    cin>>estacion;
    for(int j=0;j<cant;j++){
        if(estaciones[j]->getNombre()==estacion){
            unsigned int litrosReg=0;
            unsigned int litrosPrem=0;
            unsigned int litrosEco=0;
            Venta** ventaEstacion = estaciones[j]->getListaVentas();
            int cantVent = estaciones[j]->getCantVentas();
            for (int i=0; i<cantVent;i++){
                unsigned int ventaIndividual = ventaEstacion[i]->getCantidad();
                TComb combustible = ventaEstacion[i]->getComb();

                if (combustible == TComb::REGULAR){
                    litrosReg+= ventaIndividual;
                }
                if (combustible == TComb::PREMIUM){
                    litrosPrem+= ventaIndividual;
                }
                if (combustible == TComb::ECOEXTRA){
                    litrosEco+= ventaIndividual;
                }
            }
            cout<<"ventas combustible regular: "<<litrosReg<<endl;
            cout<<"ventas combustible premium: "<<litrosPrem<<endl;
            cout<<"ventas combustible EcoExtra: "<<litrosEco<<endl;
        }
    }

}

string zonaToString(Zona reg) {
    switch (reg) {
    case Zona::CENTRO: return "Centro";
    case Zona::NORTE: return "Norte";
    case Zona::SUR: return "Sur";
    default: return "Desconocido";
    }
}

void randCapacidad(EstServ** estaciones, int cant){
    cout << "Que estacion desea reconfigurar?" << endl;
    string estacion = "";
    cin>>estacion;
    for(int j=0;j<cant;j++){
        if(estaciones[j]->getNombre()==estacion){
            Tanque cambio = estaciones[j]->getTanquePrincipal();
            int capReg = cambio.getCapacidadRegular();
            int capPrem =cambio.getCapacidadPremium();
            int CapEco =cambio.getCapacidadEcoExtra();
            int gasDispReg = 100+ rand() % capReg;
            int gasDispPrem = 100+ rand() % capPrem;
            int gasDispEcoExtra = 100+ rand() % CapEco;
            estaciones[j]->setTanquePrincipal(Tanque(capReg,capPrem,CapEco,gasDispReg,gasDispPrem,gasDispEcoExtra));
            break;
        }
    }
}

void hacerVenta(EstServ** estaciones, int cant, int _precioRegN,int _precioPremN,int _precioEcoN,int _precioRegC,int _precioPremC,int _precioEcoC,int _precioRegS,int _precioPremS,int _precioEcoS) {

    string estacionVenta;
    int codSurt;
    int cantidad;
    TComb comb;
    string combustible;
    string tipoPago="";
    TPago pago;
    int documento;
    int pagado;


    cout<<"Ingrese la estacion donde se encuentra"<<endl;
    cin>>estacionVenta;
    cout<<"Ingrese el codigo del surtidor de compra"<<endl;
    cin>>codSurt;
    cout<<"Ingrese la cantidad de combustible que desea comprar"<<endl;
    cin>>cantidad;
    cout<<"Ingrese el tipo de combustible que desea comprar(REGULAR,PREMIUM,ECOEXTRA)"<<endl;
    cin>>combustible;
    if (combustible == "REGULAR") {
        comb = TComb::REGULAR;
    }
    else if (combustible == "PREMIUM") {
        comb = TComb::PREMIUM;
    }
    else if (combustible == "ECOEXTRA") {
        comb = TComb::ECOEXTRA;
    }
    else {
        cerr << "combustible desconocido, asignando valor por defecto (REGULAR)" <<endl;
        comb = TComb::REGULAR;
    }
    cout<<"Ingrese el tipo de pago(EFECTIVO,TDEBITO,TCREDITO)"<<endl;
    cin>>tipoPago;
    if (tipoPago == "EFECTIVO") {
        pago = TPago::EFECTIVO;
    }
    else if (tipoPago == "TDEBITO") {
        pago = TPago::TDEBITO;
    }
    else if (tipoPago == "TCREDITO") {
        pago = TPago::TCREDITO;
    }
    else {
        cerr << "metodo de pago desconocido, asignando valor por defecto (EFECTIVO)" <<endl;
        pago = TPago::EFECTIVO;
    }
    cout<<"Ingrese su documento"<<endl;
    cin>>documento;



    for(int j=0;j<cant;j++){
        if(estaciones[j]->getNombre()==estacionVenta){
            Venta** ventasEstacion = estaciones[j]->getListaVentas();
            Surtidor* arraySurt = estaciones[j]->getSurtidores();
            Tanque tanque = estaciones[j]->getTanquePrincipal();
            int cantVent = estaciones[j]->getCantVentas();


            Zona precioPorLitro = estaciones[j]->getRegion();
            unsigned int precioComb;
            if ((precioPorLitro == Zona::NORTE) && (comb == TComb::REGULAR)){
                precioComb = _precioRegN;
            }
            if ((precioPorLitro == Zona::NORTE) && (comb == TComb::PREMIUM)){
                precioComb = _precioPremN;
            }
            if ((precioPorLitro == Zona::NORTE) && (comb == TComb::ECOEXTRA)){
                precioComb = _precioEcoN;
            }
            if ((precioPorLitro == Zona::CENTRO) && (comb == TComb::REGULAR)){
                precioComb = _precioRegC;
            }
            if ((precioPorLitro == Zona::CENTRO) && (comb == TComb::PREMIUM)){
                precioComb = _precioPremC;
            }
            if ((precioPorLitro == Zona::CENTRO) && (comb == TComb::ECOEXTRA)){
                precioComb = _precioEcoC;
            }
            if ((precioPorLitro == Zona::SUR) && (comb == TComb::REGULAR)){
                precioComb = _precioRegS;
            }
            if ((precioPorLitro == Zona::SUR) && (comb == TComb::PREMIUM)){
                precioComb = _precioPremS;
            }
            if ((precioPorLitro == Zona::SUR) && (comb == TComb::ECOEXTRA)){
                precioComb = _precioEcoS;
            }

            pagado = cantidad*precioComb;


            // Verificar y disminuir la cantidad de gasolina en el tanque
            bool ventaExitosa = false;
            switch (comb) {
            case TComb::REGULAR:
                if (tanque.getDispRegular() >= cantidad) {
                    tanque.setDispRegular(tanque.getDispRegular() - cantidad);
                    ventaExitosa = true;
                }
                break;
            case TComb::PREMIUM:
                if (tanque.getDispPremium() >= cantidad) {
                    tanque.setDispPremium(tanque.getDispPremium() - cantidad);
                    ventaExitosa = true;
                }
                break;
            case TComb::ECOEXTRA:
                if (tanque.getDispEcoExtra() >= cantidad) {
                    tanque.setDispEcoExtra(tanque.getDispEcoExtra() - cantidad);
                    ventaExitosa = true;
                }
                break;
            }

            if (!ventaExitosa) {
                std::cout << "No hay suficiente combustible en el tanque para esta venta." << std::endl;
                return;
            }

            if (cantVent+1 > cantVent){
                unsigned short int nuevaCapacidad =  cantVent+10;
                Venta** nuevoArray = new Venta*[nuevaCapacidad];
                for (int i = 0; i <cantVent ; i++) {
                    nuevoArray[i] = ventasEstacion[i];
                }
                for (int i = cantVent ; i < nuevaCapacidad; i++) {
                    nuevoArray[i] = nullptr;
                }

                delete[] ventasEstacion;
                ventasEstacion = nuevoArray;
                estaciones[j]->setListaVentas(ventasEstacion);
            }

            for(int poSurt = 0; poSurt<12;poSurt++){
                if ((arraySurt[poSurt].getCodId()== codSurt) && (arraySurt[poSurt].getActivado() == true)){
                    ventasEstacion[estaciones[j]->getCantVentas()] = new Venta(cantidad, comb, pago, documento, pagado, estacionVenta, to_string(codSurt));
                    estaciones[j]->setCantVentas(cantVent+1);
                    cout << "Venta realizada exitosamente:" << endl;
                    cout << "Surtidor: " <<codSurt << endl;
                    cout << "Combustible: " << (comb == TComb::REGULAR ? "Regular" : comb == TComb::PREMIUM ? "Premium" : "EcoExtra") << endl;
                    cout << "Litros vendidos: " << cantidad << endl;
                    cout << "Precio total: $" << pagado << endl;
                    cout << "Metodo de pago: " << (pago == TPago::EFECTIVO ? "Efectivo" : pago == TPago::TDEBITO ? "Tdebito" : "Tcredito") << endl;
                    cout << "Documento cliente: " << documento << endl;
                }
            }

        }

    }



}
