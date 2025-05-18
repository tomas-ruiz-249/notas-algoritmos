#include "red_social.cpp"
#include "cartero.cpp"

int main(){
    srand(time(0));
    GrafoCartero g;
    auto impares = g.nodosImpares();
    GrafoCartero::EmparejamientoMinimo e;
    g.emparejamientosMenorCosto(impares, e);
    impares = g.nodosImpares();
    cout << "nodos impares: " << impares.size() << "\n";
}