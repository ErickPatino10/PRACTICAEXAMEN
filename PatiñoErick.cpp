#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct Afiliado{
	int cedula;
	string nombre;
	int tipoAfiliacion;
	int sueldo;
	float aporteMensual;
	int diaDescuento;
	int fechaLimite;
	int numeroCuentaBancaria;
	bool tipoCuentaBancaria;
};

const string archivoAfiliados = "IESS2026.txt";

void guardarAfiliado(Afiliado &a){
	ofstream archivo(archivoAfiliados, ios::app);
	if(archivo.is_open()){
		archivo<<a.cedula<<";"
		<<a.nombre<<";"
		<<a.tipoAfiliacion<<";"
		<<a.sueldo<<";"
		<<a.aporteMensual<<";"
		<<a.diaDescuento<<";"
		<<a.fechaLimite<<";"
		<<a.numeroCuentaBancaria<<";"
		<<(a.tipoCuentaBancaria? "Corriente":"Ahorros")<<"\n";
	}else{
		cerr<<"NO SE PUEDE ABRIR EL ARCHIVO";
	}
}

void guardarTodos(vector<Afiliado> &afiliados){
	Afiliado a;
	ofstream archivo(archivoAfiliados);
	for(auto &a:afiliados){
		archivo<<a.cedula<<";"
		<<a.nombre<<";"
		<<a.tipoAfiliacion<<";"
		<<a.sueldo<<";"
		<<a.aporteMensual<<";"
		<<a.diaDescuento<<";"
		<<a.fechaLimite<<";"
		<<a.numeroCuentaBancaria<<";"
		<<(a.tipoCuentaBancaria? "Corriente":"Ahorros")<<"\n";		
	}	
}

void cargarDesdeArchivo(vector<Afiliado> &afiliados){
	ifstream archivo(archivoAfiliados);
	Afiliado a;
	string tipoCuenta;
	char espacio;
	if(archivo.is_open()){
		while(archivo>>a.cedula>>espacio){
			getline(archivo,a.nombre,';');
			archivo>>a.tipoAfiliacion>>espacio;
			archivo>>a.sueldo>>espacio;
			archivo>>a.aporteMensual>>espacio;
			archivo>>a.diaDescuento>>espacio;
			archivo>>a.fechaLimite>>espacio;
			archivo>>a.numeroCuentaBancaria>>espacio;
			getline(archivo, tipoCuenta);
			a.tipoCuentaBancaria = (tipoCuenta == "Corriente");
			afiliados.push_back(a);
		}
	}
}




void registrarAfiliado(vector<Afiliado> &afiliados){
	Afiliado a;
	cout<<"\nIngrese su cedula: ";
	cin>>a.cedula;
	cin.ignore();
	cout<<"Ingrese su nombre: ";
	getline(cin,a.nombre);
	cout<<"Elija su sueldo basico(1. Medio Sueldo Basico 2. Sueldo Basico Completo 3.  Sueldo Mayor Basico): ";
	cin>>a.tipoAfiliacion;
	if(a.tipoAfiliacion == 1){
		a.sueldo = 240;
		float descuento = 240*0.05;
		a.aporteMensual = descuento;
	}else if(a.tipoAfiliacion == 2){
		a.sueldo = 480;
		float descuento = 480*0.07;
		a.aporteMensual = descuento;
	}else if(a.tipoAfiliacion == 3){
		cout<<"Ingrese su sueldo: ";
		cin>>a.sueldo;
		if(a.sueldo<480){
			cout<<"Error. Cantidad invalida";	
			return;
		}else{
			a.aporteMensual = a.sueldo*0.09;
			
		}
	}else {
		cout<<"\nOpcion invalida.\n";
		return;
	}
	cout<<"Elegir dia de descuento (Rango 2do dias hasta 10mo dia): ";
	cin>>a.diaDescuento;
	if(a.diaDescuento >= 2 && a.diaDescuento<=10){
		int plazoFijo = 5;
		int fechaLiquidacion = a.diaDescuento + plazoFijo;
		a.fechaLimite= fechaLiquidacion;
	}else{
		cout<<"\nError. Rango invalido.\n";
	}
	cout<<"Ingreso de datos bancarios\n";
	cout<<"Numero de cuenta: ";
	cin>>a.numeroCuentaBancaria;
	cout<<"Tipo de cuenta (0.Ahorros  1.Corriente):  ";
	cin>>a.tipoCuentaBancaria;
	
	afiliados.push_back(a);
	guardarAfiliado(a);
}



void consultarValoresPago(vector<Afiliado> &afiliados){
		if(afiliados.empty()){
			cout<<"No hay afiliados registrados. ";
			return;
		}
		int cedulaBuscada ;
		cout<<"\n Ingresa tu cedula: ";
		cin>>cedulaBuscada;
		for(auto &a: afiliados){
			if(cedulaBuscada == a.cedula){
				cout<<"\n================================================================\n";
				cout<<"\n Comprobante del afiliado \n";
				cout<<"Nombre: "<<a.nombre<<endl;
				cout<<"Tipo de afilicion: "<<a.tipoAfiliacion<<endl;
				cout<<"Sueldo: "<<a.sueldo<<endl;
				cout<<"Aporte: "<<a.aporteMensual<<endl;
				cout<<"Tipo de cuenta Bancaria: "<<(a.tipoCuentaBancaria? "Corriente":"Ahorros")<<endl;
				cout<<"Numero de cuenta Bancaria: "<<a.numeroCuentaBancaria<<endl;
				cout<<"Dia de descuento: "<<a.diaDescuento<<endl;
				cout<<"Fecha limite: "<<a.fechaLimite<<endl;
				cout<<"\n================================================================\n";
				return;							
			}
		}
		cout<<"No se encontro al usiario\n";
}


void imprimirResumen(vector<Afiliado> &afiliados){
	if(afiliados.empty()){
		cout<<"No hay afiliados registrados. ";
		return;
	}
	for(auto &a: afiliados){
		cout<<"\n Comprobante del afiliado \n";
		cout<<"Nombre: "<<a.nombre<<endl;
		cout<<"Tipo de afilicion: "<<a.tipoAfiliacion<<endl;
		cout<<"Sueldo: "<<a.sueldo<<endl;
		cout<<"Aporte: "<<a.aporteMensual<<endl;
		cout<<"Tipo de cuenta Bancaria: "<<(a.tipoCuentaBancaria? "Corriente":"Ahorros")<<endl;
		cout<<"Numero de cuenta Bancaria: "<<a.numeroCuentaBancaria<<endl;
		cout<<"Dia de descuento: "<<a.diaDescuento<<endl;
		cout<<"Fecha limite: "<<a.fechaLimite<<endl;
		cout<<"\n================================================================\n";
	}
}

void actualizarInformacion(vector<Afiliado> &afiliados){
		if(afiliados.empty()){
			cout<<"No hay afiliados registrados. ";
			return;
		}
		int cedulaBuscada ;
		cout<<"\n Ingresa tu cedula: ";
		cin>>cedulaBuscada;
		cin.ignore();
			for(auto &a: afiliados){
			if(cedulaBuscada == a.cedula){
				cout<<"Ingrese su nombre: ";
				getline(cin,a.nombre);
				cout<<"Elija su sueldo basico(1. Medio Sueldo Basico 2. Sueldo Basico Completo 3.  Sueldo Mayor Basico): ";
				cin>>a.tipoAfiliacion;
				if(a.tipoAfiliacion == 1){
					a.sueldo = 240;
					float descuento = 240*0.05;
					a.aporteMensual = descuento;
				}else if(a.tipoAfiliacion == 2){
					a.sueldo = 480;
					float descuento = 480*(0.07);
					a.aporteMensual = descuento;
				}else if(a.tipoAfiliacion == 3){
					cout<<"Ingrese su sueldo: ";
					cin>>a.sueldo;
					if(a.sueldo<480){
						cout<<"Error. Cantidad invalida";	
					}else{
						a.aporteMensual = a.sueldo*0.09;
						
					}
				}else {
					cout<<"Opcion invalida.";
					return;
				}
				cout<<"Elegir dia de descuento (Rango 2do dias hasta 10mo dia): ";
				cin>>a.diaDescuento;
				if(a.diaDescuento >= 2 && a.diaDescuento<=10){
					int plazoFijo = 5;
					int fechaLiquidacion = a.diaDescuento + plazoFijo;
					a.fechaLimite= fechaLiquidacion;
				}else{
					cout<<"Error. Rango invalido.";
				}
				cout<<"Ingreso de datos bancarios\n";
				cout<<"Numero de cuenta";
				cin>>a.numeroCuentaBancaria;
				cout<<"Tipo de cuenta (0.Ahorros  1.Corriente): ";
				cin>>a.tipoCuentaBancaria;
				}
		}
		cout<<"Usuario no encontrado\n";
		
}


void eliminarInformacion(vector<Afiliado> &afiliados){
		int cedulaBuscada ;
		cout<<"\n Ingresa tu cedula: ";
		cin>>cedulaBuscada;
		for(size_t i=0;i<afiliados.size();i++){
			if(afiliados[i].cedula == cedulaBuscada){
				afiliados.erase(afiliados.begin()+i);
				cout<<"\nInformacion eliminada\n";
				return;
			}
		}
		cout<<"\n Usuario no encontrado\n";
}




int main (){
	vector<Afiliado> afiliados;
	cargarDesdeArchivo(afiliados);
	int opcion;
	do{

		cout<<"\nMENU\n";
		cout<<"1.Registrar Afiliado. \n";
		cout<<"2.Consultar valor a pagar. \n";
		cout<<"3.Imprimir resumen completo \n";
		cout<<"4.Guardar resumen en archivo. \n";
		cout<<"5.Actualizar la informacion del usuario afiliado por medio de la cedula. \n";
		cout<<"6.Eliminar informacion de un afiliado por medio de cedula. \n";
		cout<<"7. Salir\n";
		cout<<"Elige una opcion: ";
		cin>>opcion;
		switch (opcion) {
			case 1:
				registrarAfiliado(afiliados);
				break;
			case 2:
				consultarValoresPago(afiliados);
				break;
			case 3:
				imprimirResumen(afiliados);
				break;
			case 4:
				guardarTodos(afiliados);
				
				break;
			case 5:
				actualizarInformacion(afiliados);
				break;
			case 6:
				eliminarInformacion(afiliados);
				break;	
			case 7:
				cout<<"\n Saliendo del sistema\n";
				
				break;																			
			default:
				cout<<"\0 Opcion invalida\n";
				break;
		}
	}while(opcion !=7);
	
	
	return 0;
}
