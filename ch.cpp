#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

const string archivos = "archivoD2.txt";


// ================== GUARDAR UN REGISTRO ==================
void guardarBeneficiario(const Beneficiario &b) {
    ofstream archivo(archivos, ios::app);
    if (archivo.is_open()) {
        archivo << b.codigo << ";"
                << b.nombre << ";"
                << b.direccion.callePrincipal << ";"
                << b.direccion.calleSecundaria << ";"
                << b.direccion.numero << ";"
                << b.roscasRecibidas << endl;
        archivo.close();
    }
}

// ================== GUARDAR TODO ==================
void guardarTodo(const vector<Beneficiario> &beneficiarios) {
    ofstream archivo(archivos);
    if (archivo.is_open()) {
        for (size_t i = 0; i < beneficiarios.size(); i++) {
            archivo << beneficiarios[i].codigo << ";"
                    << beneficiarios[i].nombre << ";"
                    << beneficiarios[i].direccion.callePrincipal << ";"
                    << beneficiarios[i].direccion.calleSecundaria << ";"
                    << beneficiarios[i].direccion.numero << ";"
                    << beneficiarios[i].roscasRecibidas << endl;
        }
        archivo.close();
    }
}

// ================== CARGAR DESDE ARCHIVO ==================
void cargarDesdeArchivo(vector<Beneficiario> &beneficiarios) {
    ifstream archivo(archivos);
    if (!archivo.is_open()) 
		return;

    Beneficiario b;
    char separador;

    while (archivo >> b.codigo >> separador) {
        getline(archivo, b.nombre, ';');
        getline(archivo, b.direccion.callePrincipal, ';');
        getline(archivo, b.direccion.calleSecundaria, ';');
        archivo >> b.direccion.numero >> separador;
        archivo >> b.roscasRecibidas;

        beneficiarios.push_back(b);
    }
    archivo.close();
}



// ================== REGISTRAR CLIENTE ==================
void registrarCliente(vector<Beneficiario> &beneficiarios) {
    Beneficiario b;

    cout << "Codigo: ";
    cin >> b.codigo;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, b.nombre);

    cout << "Calle principal: ";
    getline(cin, b.direccion.callePrincipal);

    cout << "Calle secundaria: ";
    getline(cin, b.direccion.calleSecundaria);

    cout << "Numero de casa: ";
    cin >> b.direccion.numero;

    b.roscasRecibidas = 0;

    beneficiarios.push_back(b);
    guardarBeneficiario(b);

    cout << "Cliente registrado correctamente.\n";
}

// ================== MOSTRAR CLIENTES ==================
void mostrarClientes(const vector<Beneficiario> &beneficiarios) {
    if (beneficiarios.empty()) {
        cout << "No hay clientes registrados.\n";
        return;
    }

    for (size_t i = 0; i < beneficiarios.size(); i++) {
        cout << "\nCodigo: " << beneficiarios[i].codigo;
        cout << "\nNombre: " << beneficiarios[i].nombre;
        cout << "\nDireccion: "
             << beneficiarios[i].direccion.callePrincipal << " y "
             << beneficiarios[i].direccion.calleSecundaria
             << " #" << beneficiarios[i].direccion.numero;
        cout << "\nRoscas recibidas: "
             << beneficiarios[i].roscasRecibidas << endl;
    }
}

// ================== REGISTRAR ENTREGA ==================
void registrarEntrega(vector<Beneficiario> &beneficiarios) {
    int codigo, cantidad;
    cout << "Codigo del beneficiario: ";
    cin >> codigo;

    cout << "Cantidad de roscas: ";
    cin >> cantidad;

    for (size_t i = 0; i < beneficiarios.size(); i++) {
        if (beneficiarios[i].codigo == codigo) {
            beneficiarios[i].roscasRecibidas += cantidad;
            guardarTodo(beneficiarios);
            cout << "Entrega registrada.\n";
            return;
        }
    }
    cout << "Beneficiario no encontrado.\n";
}

// ================== ELIMINAR CLIENTE ==================
void eliminarCliente(vector<Beneficiario> &beneficiarios) {
    int codigo;
    cout << "Codigo a eliminar: ";
    cin >> codigo;

    for (size_t i = 0; i < beneficiarios.size(); i++) {
        if (beneficiarios[i].codigo == codigo) {
            beneficiarios.erase(beneficiarios.begin() + i);
            guardarTodo(beneficiarios);
            cout << "Cliente eliminado.\n";
            return;
        }
    }
    cout << "Cliente no encontrado.\n";
}

// ================== MAIN ==================
int main() {
    vector<Beneficiario> beneficiarios;
    int opcion;

    cargarDesdeArchivo(beneficiarios);

    do {
        cout << "\n==== MENU ====\n";
        cout << "1. Registrar cliente\n";
        cout << "2. Ver clientes\n";
        cout << "3. Registrar entrega\n";
        cout << "4. Eliminar cliente\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarCliente(beneficiarios);
                break;
            case 2:
                mostrarClientes(beneficiarios);
                break;
            case 3:
                registrarEntrega(beneficiarios);
                break;
            case 4:
                eliminarCliente(beneficiarios);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);

    return 0;
}
