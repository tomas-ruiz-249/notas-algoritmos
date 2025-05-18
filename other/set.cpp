#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(){
    set<string> invitados;
    int n;

    cout << "cuantos nombres vas a ingresar?\n";
    cin >> n;
    for(int i = 0; i < n; i++){
        string nombre;
        cin >> nombre;
        invitados.insert(nombre);
    }

    cout << "\nlista de invitados ordenada\n";
    for(auto& invitado : invitados){
        cout << "-" << invitado << "\n";
    }
}