#include <iostream>
#include<string>
using namespace std;



struct Rosca {
	int fila;
	int columna;
	bool entregada;
	string cliente;
};


void inicializarMesa(Rosca mesa[2][6], int FILAS, int COLUMNAS){
	for(int i=0;i<FILAS;i++){
		for(int j=0;j<COLUMNAS;j++){
            mesa[i][j].fila = i;
            mesa[i][j].columna = j;
            mesa[i][j].entregada = false;
            mesa[i][j].cliente = "";			
		}
	}	
}


void registrarEntrega( Rosca mesa[2][6]){
	int fila, columna;
	cout<<"\nIngrese la fila (0 - 1): ";
	cin>>fila;
	cout<<"\nIngrese la columna (0 - 5): ";
	cin>>columna;
	
	if(fila < 0 || fila >=2 || columna < 0 || columna >=6){
		cout<<"Error. Fila corerecta. \n";
		return;
	}
	if(mesa[fila][columna].entregada){
		cout<<"Posicion ya ocupada. Intentelo de nuevo.\n";
	}else{
		cout<<"Ingresa el nombre del cliente: ";
		cin.ignore();
		getline(cin, mesa[fila][columna].cliente);;
		mesa[fila][columna].entregada = true;	
	}
}



void mostrarMesa(Rosca mesa[2][6], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if(mesa[i][j].entregada){
				cout<<"[x]";
			}else{
				cout<<"[ ]";
			}
        }
        cout<<endl;
    }
}

void mostrarDisponibles(Rosca mesa[2][6]) {
    int disponibles = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            if (!mesa[i][j].entregada)
                disponibles++;
        }
    }

    cout << "\nRoscas disponibles: " << disponibles << endl;
}

int main (){
	const int FILAS = 2;
	const int COLUMNAS = 6;
	Rosca mesa[FILAS][COLUMNAS];
	int opcion;
	inicializarMesa(mesa, FILAS, COLUMNAS);
	do{
		cout<<"\n=== MENU ===\n";
		cout<<"1. Registrar entrega de rosca\n";
		cout<<"2. Mostrar mesa roscas\n";
		cout<<"3. Mostrar roscas disponibles\n";
		cout<<"4. Salir\n";
		cout<<"Seleciione una opcion: ";
		cin>>opcion;
		switch (opcion) {
			case 1:
				registrarEntrega(mesa);
				break;
			case 2:
				mostrarMesa(mesa, FILAS, COLUMNAS);
				break;
			case 3:
				mostrarDisponibles(mesa);
				break;
			case 4:
				cout<<"\nSalir del sistema.\n";
				break;
			default:
				cout<<"\nOpciom invalida. Intentelo de nuevo.\n";
				break;
		}
	}while(opcion!=4);

	
	
	return 0;
}
