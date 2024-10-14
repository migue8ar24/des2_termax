#ifndef VENTA_H
#define VENTA_H
#include <string> //manejo
#include "clasesf.h"
using namespace std;

class Venta{
private:
    string fecha;
    string hora;
    int cantidad;
    TComb comb;
    TPago pago;
    int documento;
    int pagado;
    string estacion;
    string surtidor;
public:
    Venta(int _cantidad, TComb _comb, TPago _pago, int _documento,int _pagado, string estacion, string surtidor);
    Venta();

    // Getters
    string getFecha() ;
    string getHora();
    int getCantidad();
    TComb getComb();
    TPago getPago();
    int getDocumento();
    int getPagado();
    string getEstacion();
    string getSurtidor();

    // Setters
    void setFecha(string f);
    void setHora(string h);
    void setCantidad(int cant);
    void setComb(TComb c);
    void setPago(TPago p) ;
    void setDocumento(int doc);
    void setPagado(int pag) ;
    void setEstacion(string est);
    void setSurtidor(string surt);

    // Método opcional para mostrar detalles de la venta
    void mostrarVenta();
};


#endif // VENTA_H
