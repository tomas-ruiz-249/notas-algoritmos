#include <iostream>
#include <string>

using namespace std;

const double IVA = 0.19;

double calcSubtotal(double precioProducto, int cantidad){
    return cantidad * precioProducto;
}

double calcIva(double precioProducto, int cantidad){
    return calcSubtotal(precioProducto, cantidad) * IVA;
}

double calcDescuento(double subtotal,int cantidad){
    if(cantidad < 10){
        return 0.4 * subtotal;
    }
    else if(cantidad >= 10 && cantidad < 20){
        return 0.3 * subtotal;
    }
    else if(cantidad > 50){
        return 0.2 * subtotal;
    }
    else return 0;
}

double precioAPagar(double precio, double cantidad){
    double subtotal = calcSubtotal(precio, cantidad);
    double iva = calcIva(precio, cantidad);
    double descuento = calcDescuento(subtotal, cantidad);
    return subtotal - descuento + iva;
}

int main(){
    string nombreCliente;
    string nombreProducto;
    double precio;
    int cantidad;
    cout << "cual es su nombre?\n";
    cin >> nombreCliente;
    cout << "ingrese el nombre del producto que desea comprar\n";
    cin >> nombreProducto;
    cout << "ingrese el precio del producto\n";
    cin >> precio;
    cout << "ingrese cuantas unidades desea comprar del producto\n";
    cin >> cantidad;

    double subtotal = calcSubtotal(precio, cantidad);
    double iva = calcIva(precio, cantidad);
    double descuento = calcDescuento(subtotal, cantidad);
    double total = precioAPagar(precio, cantidad);

    cout << "---recibo de compra---\n";
    cout << "nombre del cliente: " << nombreCliente << "\n";
    cout << nombreProducto << " : " << precio << " x " << cantidad << " = " << subtotal << "\n";
    cout << "subtotal descontado: " << subtotal << " - " << descuento << " = " << subtotal - descuento << "\n";
    cout << "IVA :" << iva << "\n";
    cout << "total a pagar: " << total << "\n";
    return 0;
}