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


class Surtidor{
private:
    int codId;
    string modelo;
public:
    Surtidor(string mod);
    Surtidor();
    // Getters
    int getCodId();
    string getModelo();

    //setters
    void setCodId(int  _codId);
    void setModelo(string _modelo);

    //metodos problema

    ~Surtidor();
};


class Tanque{
private:
    int gasDispRegular;   // Cantidad disponible de Regular
    int gasDispPremium;   // Cantidad disponible de Premium
    int gasDispEcoExtra;  // Cantidad disponible de EcoExtra
    int capacidadRegular; // Capacidad total de Regular
    int capacidadPremium; // Capacidad total de Premium
    int capacidadEcoExtra;// Capacidad total de EcoExtra
    bool activo;
    Surtidor* arraySurtidores[12];


public:
    Tanque(Surtidor* arraySurtidor[12]);
    Tanque();
    // Getters
    int getDispRegular();
    int getDispPremium();
    int getDispEcoExtra();
    int getCapacidadRegular();
    int getCapacidadPremium();
    int getCapacidadEcoExtra();
    bool getActivo();

    // Setters
    void setDispRegular(int _gasDispRegular);
    void setDispPremium(int _gasDispPremium);
    void setDispEcoExtra(int _gasDispEcoExtra);
    void setCapacidadRegular(int _capacidadRegular);
    void setCapacidadPremium(int _capacidadPremium);
    void setCapacidadEcoExtra(int _capacidadEcoExtra);
    void setActivo(bool _activo);

    //metodos problema, funciones amigas

    ~Tanque();
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
    Venta();

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

class EstServ{
private:
    string nombre;
    int codigo;
    string gerente;
    Zona region;
    string ubicacion;
    Venta** listaVentas;
    Tanque* tanquePrincipal;


public:
    EstServ(string nom, string ger, Zona reg, string ubi, Venta** arrayVenta, Tanque* tanqueGas );
    EstServ();

    // Getters
    string getNombre();
    int getCodigo();
    string getGerente();
    Zona getRegion() ;
    string getUbicacion();
    Venta getListaVentas();
    Tanque getTanquePrincipal();

    //setters
    void setNombre(string _nombre);
    void setCodigo(int _codigo) ;
    void setGerente(string _gerente) ;
    void setRegion(Zona _region) ;
    void setUbicacion(string _ubicacion) ;
    void setListaVentas(Venta** _listaVentas);
    void setTanquePrincipal(Tanque* _tanque);

    //metodos problema
    void verificarFugas(Tanque &tanque, int vendidoRegular, int vendidoPremium, int vendidoEcoExtra);

    ~EstServ();
};





#endif // CLASESF_H
