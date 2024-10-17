#include <fstream>
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

Venta::~Venta() {}

std::ostream& operator<<(std::ostream& os, TComb comb) {
    switch (comb) {
    case TComb::REGULAR:
        os << "Regular";
        break;
    case TComb::PREMIUM:
        os << "Premium";
        break;
    case TComb::ECOEXTRA:
        os << "EcoExtra";
        break;
    default:
        os << "Desconocido";
        break;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, TPago pago) {
    switch (pago) {
    case TPago::EFECTIVO:
        os << "Efectivo";
        break;
    case TPago::TDEBITO:
        os << "Debito";
        break;

    case TPago::TCREDITO:
        os << "Credito";
        break;

    default:
        os << "Desconocido";
        break;
    }
    return os;
}


// Sobrecarga del operador de salida <<
std::ostream& operator<<(std::ostream& os, const Venta& venta) {
    os << venta.fecha << '\n';
    os << venta.hora << '\n';
    os << venta.cantidad << '\n';
    os << static_cast<int>(venta.comb) << '\n';   // Serializar enum como int
    os << static_cast<int>(venta.pago) << '\n';   // Serializar enum como int
    os << venta.documento << '\n';
    os << venta.pagado << '\n';
    return os;
}

// Sobrecarga del operador de entrada >>
std::istream& operator>>(std::istream& is, Venta& venta) {
    std::getline(is, venta.fecha);
    std::getline(is, venta.hora);
    is >> venta.cantidad;

    int combInt;
    is >> combInt;
    venta.comb = static_cast<TComb>(combInt);     // Deserializar int como enum

    int pagoInt;
    is >> pagoInt;
    venta.pago = static_cast<TPago>(pagoInt);     // Deserializar int como enum

    is >> venta.documento;
    is >> venta.pagado;
    is.ignore();  // Ignorar el salto de línea

    return is;
}
//Metodos

// Función para guardar la venta en un archivo binario
void Venta::guardarVentaBinario(std::ofstream& archivo) const {
    size_t length;

    // Guardar fecha
    length = fecha.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Guardar el tamaño de la cadena
    archivo.write(fecha.c_str(), length);  // Guardar la cadena

    // Guardar hora
    length = hora.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length));
    archivo.write(hora.c_str(), length);

    // Guardar cantidad
    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

    // Guardar combustible
    archivo.write(reinterpret_cast<const char*>(&comb), sizeof(comb));

    // Guardar método de pago
    archivo.write(reinterpret_cast<const char*>(&pago), sizeof(pago));

    // Guardar número de documento
    archivo.write(reinterpret_cast<const char*>(&documento), sizeof(documento));

    // Guardar cantidad pagada
    archivo.write(reinterpret_cast<const char*>(&pagado), sizeof(pagado));

    // Guardar estación
    length = estacion.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length));
    archivo.write(estacion.c_str(), length);

    // Guardar surtidor
    length = surtidor.size();
    archivo.write(reinterpret_cast<const char*>(&length), sizeof(length));
    archivo.write(surtidor.c_str(), length);
}

// Función para cargar la venta desde un archivo binario
void Venta::cargarVentaBinario(std::ifstream& archivo) {
    size_t length;
    char* buffer;

    // Cargar fecha
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));  // Leer el tamaño de la cadena
    buffer = new char[length + 1];  // +1 para el carácter nulo
    archivo.read(buffer, length);   // Leer la cadena
    buffer[length] = '\0';  // Agregar el carácter nulo al final
    fecha = buffer;  // Asignar a la cadena fecha
    delete[] buffer;

    // Cargar hora
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));
    buffer = new char[length + 1];
    archivo.read(buffer, length);
    buffer[length] = '\0';
    hora = buffer;
    delete[] buffer;

    // Cargar cantidad
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

    // Cargar combustible
    archivo.read(reinterpret_cast<char*>(&comb), sizeof(comb));

    // Cargar método de pago
    archivo.read(reinterpret_cast<char*>(&pago), sizeof(pago));

    // Cargar número de documento
    archivo.read(reinterpret_cast<char*>(&documento), sizeof(documento));

    // Cargar cantidad pagada
    archivo.read(reinterpret_cast<char*>(&pagado), sizeof(pagado));

    // Cargar estación
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));
    buffer = new char[length + 1];
    archivo.read(buffer, length);
    buffer[length] = '\0';
    estacion = buffer;
    delete[] buffer;

    // Cargar surtidor
    archivo.read(reinterpret_cast<char*>(&length), sizeof(length));
    buffer = new char[length + 1];
    archivo.read(buffer, length);
    buffer[length] = '\0';
    surtidor = buffer;
    delete[] buffer;
}

// Método opcional para mostrar detalles de la venta
void Venta::mostrarVenta() {
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "Cantidad: " << cantidad << endl;
    cout << "Combustible: " << comb << endl; // salida string de clase
    cout << "Tipo de Pago: " << pago << endl; //salida string de clase
    cout << "Documento: " << documento << endl;
    cout << "Monto Pagado: " << pagado << endl;
}
