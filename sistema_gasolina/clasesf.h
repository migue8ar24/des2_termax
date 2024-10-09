#ifndef CLASESF_H
#define CLASESF_H

#include <iostream>
#include <string> //manejo strings
#include <cstdlib> // numeros aleatorios
#include <ctime>


using namespace std;


enum class TComb{
    REGULAR,
    PREMIUM,
    ECOEXTRA
};

enum class TPago{
    EFECTIVO,
    TDEBITO,
    TCREDITO
};
enum class Zona{
    NORTE,
    CENTRO,
    SUR
};


class EstServ{
private:
    string nombre;
    int codigo;
    string gerente;
    Zona region;
    string ubicacion;

public:
    EstServ(string nom, string ger, Zona reg, string ubi);
    EstServ();

    // Getters
    string getNombre();
    int getCodigo();
    string getGerente();
    Zona getRegion() ;
    string getUbicacion();

    //setters
    void setNombre(string _nombre);
    void setCodigo(int _codigo) ;
    void setGerente(string _gerente) ;
    void setRegion(Zona _region) ;
    void setUbicacion(string _ubicacion) ;

    //metodos problema

    ~EstServ();
};

class Tanque{
private:
    TComb tipoGas;
    int gasDisp;
    int capacidad;

public:
    Tanque(TComb tipo, int disp, int cap);

    // Getters
    TComb getTipo() ;
    int getDisp();
    int getCapacidad();

    //setters
    void setGas(TComb _tipoGas);
    void setDisp(int _gasDisp);
    void setCapacidad(int _capacidad);

    //metodos problema

    ~Tanque();


};

class Surtidor{
private:
    int codId;
    string modelo;
public:
    Surtidor(string mod);

    // Getters
    int getCodId();
    string getModelo();

    //setters
    void setCodId(int  _codId);
    void setModelo(string _modelo);

    //metodos problema

    ~Surtidor();
};


class Venta{
private:
    string fecha;
    string hora;
    int cantidad;
    TComb comb;
    TPago pago;
    int documento;
    int pagado;
public:
    Venta(int _cantidad, TComb _comb, TPago _pago, int _documento,int _pagado);

    // Getters
    string getFecha() ;
    string getHora();
    int getCantidad();
    TComb getComb();
    TPago getPago();
    int getDocumento();
    int getPagado();

    // Setters
    void setFecha(string f);
    void setHora(string h);
    void setCantidad(int cant);
    void setComb(TComb c);
    void setPago(TPago p) ;
    void setDocumento(int doc);
    void setPagado(int pag) ;

    // Método opcional para mostrar detalles de la venta
    void mostrarVenta();
};


#endif // CLASESF_H
