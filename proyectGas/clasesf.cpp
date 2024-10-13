#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime>

#include "clasesf.h"

using namespace std;





Tanque::Tanque(Surtidor* arraySurtidor[12]) {
    capacidadRegular = 100+ rand() % 200;
    capacidadPremium = 100+ rand() % 200;
    capacidadEcoExtra = 100+ rand() % 200;
    gasDispRegular = 100+ rand() % capacidadRegular;
    gasDispPremium = 100+ rand() % capacidadPremium;
    gasDispEcoExtra = 100+ rand() % capacidadEcoExtra;
    activo = true;
    for (int i = 0; i < 12; i++) {
        arraySurtidores[i] = arraySurtidor[i];  // Asignar el arreglo recibido
    }
}



// Getters
int Tanque::getDispRegular() {
    return gasDispRegular;
}

int Tanque::getDispPremium() {
    return gasDispPremium;
}

int Tanque::getDispEcoExtra() {
    return gasDispEcoExtra;
}

int Tanque::getCapacidadRegular() {
    return capacidadRegular;
}

int Tanque::getCapacidadPremium() {
    return capacidadPremium;
}

int Tanque::getCapacidadEcoExtra() {
    return capacidadEcoExtra;
}
bool Tanque::getActivo() {
    return activo;
}

// Setters
void Tanque::setDispRegular(int _gasDispRegular) {
    gasDispRegular = _gasDispRegular;
}

void Tanque::setDispPremium(int _gasDispPremium) {
    gasDispPremium = _gasDispPremium;
}

void Tanque::setDispEcoExtra(int _gasDispEcoExtra) {
    gasDispEcoExtra = _gasDispEcoExtra;
}

void Tanque::setCapacidadRegular(int _capacidadRegular) {
    capacidadRegular = _capacidadRegular;
}

void Tanque::setCapacidadPremium(int _capacidadPremium) {
    capacidadPremium = _capacidadPremium;
}

void Tanque::setCapacidadEcoExtra(int _capacidadEcoExtra) {
    capacidadEcoExtra = _capacidadEcoExtra;
}
void Tanque::setActivo(bool _activo) {
    activo = _activo;
}

Tanque::~Tanque() {
    delete[] arraySurtidores;
}

//metodos problema





Surtidor::Surtidor(string mod){
    codId = rand() % 100; // no repetido
    modelo = mod;
}
Surtidor::Surtidor(){
    codId = rand() % 100; // no repetido
    modelo = "";
}


// Getters
int Surtidor::getCodId() {
    return codId;
}
string Surtidor::getModelo() {
    return modelo;
}

//setters
void Surtidor::setCodId(int  _codId) {
    codId = _codId;
}
void Surtidor::setModelo(string _modelo) {
    modelo = _modelo;
}

//metodos problema



Venta::Venta(int _cantidad, TComb _comb, TPago _pago, int _documento,int _pagado){
    time_t ahora = time(nullptr);
    tm* tiempo = localtime(&ahora);
    string _fecha(11, '\0');
    strftime(&_fecha[0], _fecha.size() + 1, "%d/%m/%Y", tiempo);
    fecha = _fecha;
    string _hora(9, '\0');
    strftime(&_hora[0],_hora.size() + 1, "%H:%M:%S", tiempo);
    hora = _hora;
    cantidad = _cantidad;
    comb = _comb;
    pago =_pago;
    documento = _documento;
    pagado = _pagado;
}
Venta::Venta(): cantidad(0), comb(TComb::REGULAR), pago(TPago::EFECTIVO), documento(0), pagado(0){
}

// Getters
string Venta::getFecha() {
    return fecha;
}
string Venta::getHora() {
    return hora;
}
int Venta::getCantidad() {
    return cantidad;
}
TComb Venta::getComb() {
    return comb;
}
TPago Venta::getPago() {
    return pago;
}
int Venta::getDocumento() {
    return documento;
}
int Venta::getPagado() {
    return pagado;
}

// Setters
void Venta::setFecha(string f) {
    fecha = f;
}
void Venta::setHora(string h) {
    hora = h;
}
void Venta::setCantidad(int cant) {
    cantidad = cant;
}
void Venta::setComb(TComb c) {
    comb = c;
}
void Venta::setPago(TPago p) {
    pago = p;
}
void Venta::setDocumento(int doc) {
    documento = doc;
}
void Venta::setPagado(int pag) {
    pagado = pag;
}

// Método opcional para mostrar detalles de la venta
void Venta::mostrarVenta() {
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "Cantidad: " << cantidad << endl;
    cout << "Combustible: " << "comb" << endl; // salida string de clase
    cout << "Tipo de Pago: " << "pago" << endl; //salida string de clase
    cout << "Documento: " << documento << endl;
    cout << "Monto Pagado: " << pagado << endl;
}


EstServ:: EstServ(string nom, string ger, Zona reg, string ubi, Venta** arrayVenta, Tanque* tanqueGas ){
    nombre = nom;
    codigo = rand() % 100; //verificacion de no existente
    gerente = ger;
    region = reg;
    ubicacion = ubi;
    listaVentas = arrayVenta;
    tanquePrincipal = tanqueGas;

}

EstServ::EstServ(): nombre(""), codigo(0), gerente(""), region(Zona::CENTRO), ubicacion(""), listaVentas(nullptr), tanquePrincipal(nullptr){
}

// Getters
string EstServ:: getNombre() {
    return nombre;
}
int EstServ::getCodigo() {
    return codigo;
}
string EstServ::getGerente() {
    return gerente;
}
Zona EstServ::getRegion() {
    return region;
}
string EstServ::getUbicacion() {
    return  ubicacion;
}
Venta EstServ::getListaVentas() {
    return  **listaVentas;
}
Tanque EstServ::getTanquePrincipal() {
    return  *tanquePrincipal;
}


//setters
void EstServ::setNombre(string _nombre) {
    nombre = _nombre;
}
void EstServ::setCodigo(int _codigo) {
    codigo = _codigo;
}
void EstServ::setGerente(string _gerente) {
    gerente = _gerente;
}
void EstServ::setRegion(Zona _region) {
    region = _region;
}
void EstServ::setUbicacion(string _ubicacion) {
    ubicacion = _ubicacion;
}
void EstServ::setListaVentas(Venta** _listaVentas) {
    listaVentas = _listaVentas;
}
void EstServ::setTanquePrincipal(Tanque* _tanque) {
    tanquePrincipal = _tanque;
}

EstServ::~EstServ() {
    delete[] listaVentas;
}

//metodos problema

void EstServ::verificarFugas(Tanque &tanque, int vendidoRegular, int vendidoPremium, int vendidoEcoExtra) {
    // Verificación para combustible Regular
    int totalRegular = vendidoRegular + tanque.getDispRegular();
    if (totalRegular < 0.95 * tanque.getCapacidadRegular()) {
        cout << "Posible fuga detectada en combustible Regular." << endl;
    }

    // Verificación para combustible Premium
    int totalPremium = vendidoPremium + tanque.getDispPremium();
    if (totalPremium < 0.95 * tanque.getCapacidadPremium()) {
        cout << "Posible fuga detectada en combustible Premium." << endl;
    }

    // Verificación para combustible EcoExtra
    int totalEcoExtra = vendidoEcoExtra + tanque.getDispEcoExtra();
    if (totalEcoExtra < 0.95 * tanque.getCapacidadEcoExtra()) {
        cout << "Posible fuga detectada en combustible Extra." << endl;
    }

    // Si no hay fugas
    if (totalRegular > 0.95 * tanque.getCapacidadRegular() && totalPremium > 0.95 * tanque.getCapacidadPremium() && totalEcoExtra > 0.95 * tanque.getCapacidadEcoExtra())
        cout << "No se detectaron fugas en la estacion." << endl;
}
