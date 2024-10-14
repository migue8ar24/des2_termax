#ifndef CLASSESTSERVICIO_H
#define CLASSESTSERVICIO_H
#include "clasesf.h"
#include "venta.h"
#include "tanque.h"
#include "surtidor.h"
#include <string> //manejo strings
using namespace std;

class EstServ{
private:
    string nombre;
    int codigo;
    string gerente;
    Zona region;
    string ubicacion;
    Venta** listaVentas;
    Tanque tanquePrincipal;
    Surtidor* arraySurtidores;


public:
    EstServ(string nom, string ger, Zona reg, string ubi, Venta** arrayVenta, Tanque tanqueGas, Surtidor* arraySurtidores);
    EstServ();

    // Getters
    string getNombre();
    int getCodigo();
    string getGerente();
    Zona getRegion() ;
    string getUbicacion();
    Venta getListaVentas();
    Tanque getTanquePrincipal();
    Surtidor* getSurtidores();

    //setters
    void setNombre(string _nombre);
    void setCodigo(int _codigo) ;
    void setGerente(string _gerente) ;
    void setRegion(Zona _region) ;
    void setUbicacion(string _ubicacion) ;
    void setListaVentas(Venta** _listaVentas);
    void setTanquePrincipal(Tanque _tanque);
    void setSurtidores(Surtidor* _arraySurtidores);

    //metodos problema
    void guardarEstServBinario(std::ofstream& archivo) const;
    void cargarEstServBinario(std::ifstream& archivo);
    void verificarFugas(Tanque &tanque, int vendidoRegular, int vendidoPremium, int vendidoEcoExtra);

    ~EstServ();
};





#endif // CLASSESTSERVICIO_H
