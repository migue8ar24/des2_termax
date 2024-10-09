#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime>

#include "clasesf.h"

using namespace std;



EstServ:: EstServ(string nom, string ger, Zona reg, string ubi){
        nombre = nom;
        codigo = rand() % 100; //verificacion de no existente
        gerente = ger;
        region = reg;
        ubicacion = ubi;
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

    //metodos problema




    Tanque::Tanque(TComb tipo, int disp, int cap){
        tipoGas = tipo; //revisar el enum
        gasDisp= disp;
        capacidad=cap;
    }

    // Getters
    TComb Tanque::getTipo() {
        return tipoGas;
    }
    int Tanque::getDisp() {
        return gasDisp;
    }
    int Tanque::getCapacidad() {
        return capacidad;
    }

    //setters
    void Tanque::setGas(TComb _tipoGas) {
        tipoGas = _tipoGas;
    }
    void Tanque::setDisp(int _gasDisp) {
        gasDisp = _gasDisp;
    }
    void Tanque::setCapacidad(int _capacidad) {
        capacidad = _capacidad;
    }

    //metodos problema






    Surtidor::Surtidor(string mod){
        codId = rand() % 100; // no repetido
        modelo = mod;
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

