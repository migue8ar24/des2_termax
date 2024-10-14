#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include "surtidor.h"
#include "clasesf.h"
#include <string> //manejo strings
using namespace std;
#include <iostream>

Venta::Venta(int _cantidad, TComb _comb, TPago _pago, int _documento,int _pagado, string _estacion, string _surtidor){
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
    estacion= _estacion;
    surtidor= _surtidor;
}
Venta::Venta(): cantidad(0), comb(TComb::REGULAR), pago(TPago::EFECTIVO), documento(0), pagado(0),estacion(""), surtidor(""){
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
string Venta::getEstacion()  {
    return estacion;
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
    cout<< "Fecha: " << fecha << endl;
    cout<< "Hora: " << hora << endl;
    cout<< "Cantidad: " << cantidad << endl;
    cout<< "Combustible: " << "comb" << endl; // salida string de clase con condicionales, se puede sobrecargar pero no es necesario
    cout<< "Tipo de Pago: " << "pago" << endl; //salida string de clase
    cout<< "Documento: " << documento << endl;
    cout<< "Monto Pagado: " << pagado << endl;
}
