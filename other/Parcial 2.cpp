#include<iostream>
#include <string>
#include"linked_list.h"
#include<math.h>

using namespace std;

class Avion {
	int id;
	int asientos;
public:
	Avion() {
		id = -1;
		asientos = -1;
	}

	Avion(int i, int a) {
		id = i;
		asientos = a;
	}

	int getId() const {
		return id;
	}

	string to_string() const{
		return '(' + std::to_string(id) + ", " + std::to_string(asientos) + ')';
	}

    friend std::ostream& operator<<(std::ostream& os, const Avion& a) {
        return os << a.to_string();
    }

	/*1. Completar la clase Avion*/
	int getAsientos() const{
		return asientos;
	}

	void addAsientos(int a){
		asientos += a;
	}

    bool operator<(const Avion& a){
		if(asientos == a.getAsientos()){
			return id > a.getId();
		}
        return this->asientos < a.getAsientos();
    }

    bool operator>(const Avion& a){
		if(asientos == a.getAsientos()){
			return id < a.getId();
		}
        return this->asientos > a.getAsientos();
    }

    bool operator<=(const Avion& a){
		if(asientos == a.getAsientos()){
			return id >= a.getId();
		}
        return this->asientos <= a.getAsientos();
    }

    bool operator>=(const Avion& a){
		if(asientos == a.getAsientos()){
			return id <= a.getId();
		}
        return this->asientos >= a.getAsientos();
    }

    bool operator==(const Avion& a){
		if(asientos == a.getAsientos()){
			return id == a.getId();
		}
        return this->asientos == a.getAsientos();
    }

    bool operator!=(const Avion& a){
		if(asientos == a.getAsientos()){
			return id != a.getId();
		}
        return this->asientos != a.getAsientos();
    }
};

class Ruta {
	int id;
	int contAviones;
	int asientosTotales;
	LinkedList<Avion*> lista;
public:
	Ruta() {
		id = -1;
		contAviones = 0;
		asientosTotales = 0;
	}

	Ruta(int i) {
		id = i;
		contAviones =0;
		asientosTotales = 0;
	}

	LinkedList<Avion*>* getAviones(){
		return &lista;
	}

	void addAvion(int asientos) {
		Avion* av = new Avion(id*100+contAviones++,asientos);
		lista.append(av);
		asientosTotales += asientos;
	}

	Avion* getAvion(int i) {
		return lista.get(i);
	}


	int getID() {
		return id;
	}

	int getAsientosTotales() const{
		return asientosTotales;
	}

	void actualizarAsientosTotales(){
		asientosTotales = 0;
		for(int i = 0; i < lista.getSize(); i++){
			asientosTotales += lista.get(i)->getAsientos();
		}
	}

	void print() {
		cout<<"ID :"<<id<<": ";
		for(int i = 0; i < lista.getSize(); i++){
			cout << lista.get(i)->to_string();
		}
	}

	friend std::ostream& operator<<(std::ostream& os, Ruta& b) {
		return os << b.to_string();
	}

	string to_string() {
		string s = "ID :"+std::to_string(id)+" : ";
		for(int i=0; i<lista.getSize(); i++) {
			s += lista.get(i)->to_string()+", ";
		}
		s += "total: " + std::to_string(asientosTotales);
		return s;
	}



    bool operator<(const Ruta& r){
        return this->asientosTotales < r.getAsientosTotales();
    }

    bool operator>(const Ruta& r){
        return this->asientosTotales > r.getAsientosTotales();
    }

    bool operator<=(const Ruta& r){
        return this->asientosTotales <= r.getAsientosTotales();
    }

    bool operator>=(const Ruta& r){
        return this->asientosTotales >= r.getAsientosTotales();
    }

    bool operator==(const Ruta& r){
        return this->asientosTotales == r.getAsientosTotales();
    }

    bool operator!=(const Ruta& r){
        return this->asientosTotales != r.getAsientosTotales();
    }

	int getSize() {
		return lista.getSize();
	}

	/*2. Hacer el método de ordenamiento quick sort*/
	void sort(){
		lista.sort("quickSort", true);
	}
};


class Viaje_Seguro {
	LinkedList<Ruta> Rutas;
public:
	Viaje_Seguro() {

	}

	void addRuta(Ruta l) {
		Rutas.append(l);
	}

	void print() {
		for(int i = 0; i < Rutas.getSize(); i++){
			cout << Rutas.get(i).to_string() << "\n";
		}
		cout << '\n';
	}

	int getSize() {
		return Rutas.getSize();
	}

   /*4. Hacer el método de ordenamiento Merge Sort*/
	void sort(){
		for(int i = 0; i < Rutas.getSize(); i++){
			Rutas.getPtr(i)->sort();
		}
		Rutas.sort("MergeSort", true);
	}
   
   
//    5. En el siguiente código aplique la búqueda binaria
	Avion* getAvion(int id) {
		int rutaid = id;
		rutaid /= 100;
		bool found = false;
		for(int i = 0; i < Rutas.getSize(); i++){
			if(Rutas.get(i).getID() == rutaid){
				found = true;
				rutaid = i;
				break;
			}
		}
		if(!found){
			rutaid = -1;
		}
		LinkedList<Avion*> aviones = *(Rutas.get(rutaid).getAviones());
		if(id >= 0) {
			int low = 0;
			int high = aviones.getSize() - 1;
			int mid;
			while(low <= high){
				mid = low + (high-low) / 2;
				if(aviones.get(mid)->getId() == id){
					return aviones.get(mid);
				}
				if(aviones.get(mid)->getId() < id){
					low = mid + 1;
				}
				else{
					high = mid - 1;
				}
			}
		}
		return nullptr;
	}

	bool reservar(int id, int num) {
		Avion* av = getAvion(id);
		if(av != nullptr){
			if(av->getAsientos() >= num) {
				av->addAsientos(-num);
				for(int i = 0; i < Rutas.getSize(); i++){
					Rutas.getPtr(i)->actualizarAsientosTotales();
				}
				return true;
			}
		}
		return false;
	}

};


int main()
{
	srand(1234);
	const int MAX_AVIONES = 8;
	const int MAX_ASIENTOS = 21;
	int numRutas = 5;
	int numAviones;
	Ruta l;
	Viaje_Seguro vs;

	for(int i=0; i<numRutas; i++) {
		l = Ruta(i);
		numAviones = rand()%MAX_AVIONES+3;
		for(int j=0; j<numAviones; j++) {
			l.addAvion(rand()%MAX_ASIENTOS+1);
		}
		vs.addRuta(l);
	}

	vs.print();
	vs.sort();
	cout<<"Rutas ordenadas por total de asientos disponibles"<<endl;
	vs.print();

	int cod;
	int num;
	bool reservar;

	do {
		cout<<"Inserte el id unico (101, 307, 9) del Avion que quiere reservar: ";
		cin>>cod;
		cout<<"Inserte el numero de asientos del Avion que quiere reservar: ";
		cin>>num;
		reservar = vs.reservar(cod, num);
		if(reservar) {
			cout<<"Se pudo realizar la reserva!"<<endl;
		} else {
			cout<<"No se pudo realizar la reserva!"<<endl;
		}
	} while(!reservar);

	cout<<"Inventario final: "<<endl;
	vs.sort();
	vs.print();

	return 0;
}