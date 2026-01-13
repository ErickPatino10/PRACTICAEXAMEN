#include <iostream>
#include<string>
#include<vector>
using namespace std;



struct Direccion {
	string callePrincipal;
	string calleSecundaria;
	int numero;
};

struct Beneficiario {
	int codigo;
	string nombre;
	Direccion direccion;
	int roscasRecibidas;
};

void iniciarMatriz(int entregas[4][5]){
	for (int i = 0; i < 4; i++)
	    for (int j = 0; j < 5; j++)
	        entregas[i][j] = 0;
}


void registrarBeneficiario(vector<Beneficiario>& beneficiarios){
	Beneficiario b;
	cout<<"Codigo: ";
	cin>>b.codigo;
	cin.ignore();
	cout<<"Nombre: ";
	getline(cin, b.nombre);
	cout << "Calle principal: ";
 	getline(cin, b.direccion.callePrincipal);
    cout << "Calle secundaria: ";
    getline(cin, b.direccion.calleSecundaria);
    cout << "Numero: ";
    cin >> b.direccion.numero;
    cout << "Roscas recibidas: ";
    cin >> b.roscasRecibidas;
    beneficiarios.push_back(b);
}

void mostrarBeneficiarios(vector<Beneficiario>& beneficiarios){
	if(beneficiarios.empty()){
		cout<<"\nNo hay beneficiarios registrados\n";
		return;
	}
	cout<<"\nLista de beneficiarios"<<endl;
	for(auto& b : beneficiarios ){
        cout << "\nCodigo: " << b.codigo;
        cout << "\nNombre: " << b.nombre;
        cout << "\nDireccion: " << b.direccion.callePrincipal
             << " y " << b.direccion.calleSecundaria
             << " #" << b.direccion.numero;
        cout << "\nRoscas recibidas: " << b.roscasRecibidas << endl;		
	}
}

void registrarEntrega(int entregas[4][5], string voluntarios[4]){
	int voluntario, dia, cantidad;
	for(int i=0;i<4;i++){
		cout<<i<<", "<<voluntarios[i]<<endl;	
	}
	cout<<"Voluntarios (0-3):";
	cin>>voluntario;
	cout<<"Dia: ";
	cin>>dia;
	cout<<"Cantidad: ";
	cin>> cantidad;
	entregas[voluntario][dia] += cantidad;
    if (voluntario >= 0 && voluntario < 4 && dia >= 0 && dia < 5) {
        entregas[voluntario][dia] += cantidad;
    } else {
        cout << "ERROR: voluntario o dia fuera de rango\n";
    }	
}

void mostrarEntregas(int entregas[4][5], string voluntarios[4]){
	cout << "\nVOLUNTARIO   L  M  X  J  V\n";
	for(int i=0;i<4;i++){
		cout<<voluntarios[i]<<" ";
		for(int j=0;j<5;j++){
			cout<<entregas[i][j]<<" ";
		}
		cout<<endl;
	}
}



int main (){
	vector<Beneficiario> beneficiarios;
	string voluntarios [4] = {
		"Ana Torres", 
		"Luis Mendoza", 
		"Pedro Salazar",
		"Maria Gomez"
	};
	int entregas[4][5];
    int op;
    iniciarMatriz(entregas);
    do {
        cout << "\n--- MENU ---\n";
        cout << "1 Registrar beneficiario\n";
        cout << "2 Mostrar beneficiarios\n";
        cout << "3 Registrar entrega\n";
        cout << "4 Mostrar entregas\n";
        cout << "5 Actualizar direccion\n";
        cout << "6 Eliminar beneficiario\n";
        cout << "7 Total por voluntario\n";
        cout << "0 Salir\n";
        cout<<"Ingrese una opcion: ";
        cin >> op;

        switch (op) {
            case 1: 
				registrarBeneficiario(beneficiarios); 
				break;
            case 2: 
				mostrarBeneficiarios(beneficiarios); 
				break;
            case 3: 
				registrarEntrega(entregas, voluntarios); 
				
				break;
            case 4: 
				mostrarEntregas(entregas, voluntarios); 
				break;
            case 5: 
				//actualizarDireccion(beneficiarios); 
				break;
            case 6: 
				//eliminarBeneficiario(beneficiarios); 
				break;
            case 7: 
				//totalPorVoluntario(entregas, voluntarios); 
				break;
        }
    } while (op != 0);
	return 0;
}
