#ifndef SURTIDOR_H
#define SURTIDOR_H
#include "classestservicio.h"
#include "venta.h"
#include "tanque.h"
#include "clasesf.h"
#include <string> //manejo strings
using namespace std;

class Surtidor{
private:
    int codId;
    string modelo;
    bool activado;
public:
    Surtidor(string mod);
    Surtidor();
    // Getters
    int getCodId();
    string getModelo();
    bool getActivado();

    //setters
    void setCodId(int  _codId);
    void setModelo(string _modelo);
    void setActivado(bool _activado);
    //metodos problema

    void guardarSurtidorBinario(std::ofstream& archivo) const;
    void cargarSurtidorBinario(std::ifstream& archivo);

    ~Surtidor();
};


#endif // SURTIDOR_H
