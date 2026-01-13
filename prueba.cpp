#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* ===== ESTRUCTURAS ===== */

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

/* ===== FUNCIONES CREATE ===== */

void registrarBeneficiario(vector<Beneficiario>& beneficiarios) {
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

    cout << "Numero: ";
    cin >> b.direccion.numero;

    cout << "Roscas recibidas: ";
    cin >> b.roscasRecibidas;

    beneficiarios.push_back(b);
}

void registrarEntrega(int entregas[4][5], string voluntarios[4]) {
    int v, d, cant;

    cout << "\nVoluntarios:\n";
    for (int i = 0; i < 4; i++)
        cout << i << ". " << voluntarios[i] << endl;

    cout << "Seleccione voluntario (0-3): ";
    cin >> v;

    cout << "Dia (0=Lun 1=Mar 2=Mie 3=Jue 4=Vie): ";
    cin >> d;

    cout << "Cantidad de roscas: ";
    cin >> cant;

    entregas[v][d] += cant;
}

/* ===== FUNCIONES READ ===== */

void mostrarBeneficiarios(const vector<Beneficiario>& beneficiarios) {
    for (auto b : beneficiarios) {
        cout << "\nCodigo: " << b.codigo;
        cout << "\nNombre: " << b.nombre;
        cout << "\nDireccion: " << b.direccion.callePrincipal
             << " y " << b.direccion.calleSecundaria
             << " #" << b.direccion.numero;
        cout << "\nRoscas recibidas: " << b.roscasRecibidas << endl;
    }
}

void mostrarVoluntarios(string voluntarios[4]) {
    cout << "\nLista de voluntarios:\n";
    for (int i = 0; i < 4; i++)
        cout << voluntarios[i] << endl;
}

void mostrarEntregas(int entregas[4][5], string voluntarios[4]) {
    cout << "\nVOLUNTARIO   L  M  X  J  V\n";
    for (int i = 0; i < 4; i++) {
        cout << voluntarios[i] << "  ";
        for (int j = 0; j < 5; j++)
            cout << entregas[i][j] << "  ";
        cout << endl;
    }
}

void beneficiariosMasDeX(const vector<Beneficiario>& beneficiarios) {
    int x;
    cout << "Ingrese X: ";
    cin >> x;

    for (auto b : beneficiarios) {
        if (b.roscasRecibidas > x)
            cout << b.nombre << " - " << b.roscasRecibidas << endl;
    }
}

/* ===== FUNCIONES UPDATE ===== */

void actualizarDireccion(vector<Beneficiario>& beneficiarios) {
    int codigo;
    cout << "Codigo del beneficiario: ";
    cin >> codigo;
    cin.ignore();

    for (auto &b : beneficiarios) {
        if (b.codigo == codigo) {
            cout << "Nueva calle principal: ";
            getline(cin, b.direccion.callePrincipal);
            cout << "Nueva calle secundaria: ";
            getline(cin, b.direccion.calleSecundaria);
            cout << "Nuevo numero: ";
            cin >> b.direccion.numero;
            return;
        }
    }
    cout << "Beneficiario no encontrado\n";
}

void actualizarRoscasBeneficiario(vector<Beneficiario>& beneficiarios) {
    int codigo;
    cout << "Codigo: ";
    cin >> codigo;

    for (auto &b : beneficiarios) {
        if (b.codigo == codigo) {
            cout << "Nueva cantidad de roscas: ";
            cin >> b.roscasRecibidas;
            return;
        }
    }
}

void modificarEntrega(int entregas[4][5]) {
    int v, d, cant;
    cout << "Voluntario (0-3): ";
    cin >> v;
    cout << "Dia (0-4): ";
    cin >> d;
    cout << "Nueva cantidad: ";
    cin >> cant;

    entregas[v][d] = cant;
}

/* ===== FUNCIONES DELETE ===== */

void eliminarBeneficiario(vector<Beneficiario>& beneficiarios) {
    int codigo;
    cout << "Codigo a eliminar: ";
    cin >> codigo;

    for (int i = 0; i < beneficiarios.size(); i++) {
        if (beneficiarios[i].codigo == codigo) {
            beneficiarios.erase(beneficiarios.begin() + i);
            return;
        }
    }
}

void reducirEntrega(int entregas[4][5]) {
    int v, d, cant;
    cout << "Voluntario (0-3): ";
    cin >> v;
    cout << "Dia (0-4): ";
    cin >> d;
    cout << "Cantidad a reducir: ";
    cin >> cant;

    if (entregas[v][d] >= cant)
        entregas[v][d] -= cant;
}

/* ===== CALCULOS ===== */

void totalPorVoluntario(int entregas[4][5], string voluntarios[4]) {
    for (int i = 0; i < 4; i++) {
        int suma = 0;
        for (int j = 0; j < 5; j++)
            suma += entregas[i][j];
        cout << voluntarios[i] << ": " << suma << endl;
    }
}

void totalGeneral(int entregas[4][5]) {
    int total = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            total += entregas[i][j];

    cout << "Total general semanal: " << total << endl;
}

void promedioBeneficiarios(const vector<Beneficiario>& beneficiarios) {
    int suma = 0;
    for (auto b : beneficiarios)
        suma += b.roscasRecibidas;

    if (!beneficiarios.empty())
        cout << "Promedio por beneficiario: "
             << (float)suma / beneficiarios.size() << endl;
}

void voluntarioMayor(int entregas[4][5], string voluntarios[4]) {
    int max = 0, pos = 0;

    for (int i = 0; i < 4; i++) {
        int suma = 0;
        for (int j = 0; j < 5; j++)
            suma += entregas[i][j];

        if (suma > max) {
            max = suma;
            pos = i;
        }
    }

    cout << "Voluntario con mayor entrega: "
         << voluntarios[pos] << " (" << max << ")\n";
}

/* ===== MAIN ===== */

int main() {

    vector<Beneficiario> beneficiarios;

    string voluntarios[4] = {
        "Ana Torres",
        "Luis Mendoza",
        "Pedro Salazar",
        "Maria Gomez"
    };

    int entregas[4][5] = {0};

    int op;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1 Registrar beneficiario\n";
        cout << "2 Mostrar beneficiarios\n";
        cout << "3 Mostrar voluntarios\n";
        cout << "4 Registrar entrega\n";
        cout << "5 Mostrar entregas\n";
        cout << "6 Beneficiarios con mas de X roscas\n";
        cout << "7 Actualizar direccion\n";
        cout << "8 Actualizar roscas beneficiario\n";
        cout << "9 Modificar entrega\n";
        cout << "10 Eliminar beneficiario\n";
        cout << "11 Reducir entrega\n";
        cout << "12 Calculos\n";
        cout << "0 Salir\n";
        cin >> op;

        switch (op) {
            case 1: 
				registrarBeneficiario(beneficiarios); 
				break;
            case 2: 
				mostrarBeneficiarios(beneficiarios); 
				break;
            case 3: 
				mostrarVoluntarios(voluntarios); 
				break;
            case 4: 
				registrarEntrega(entregas, voluntarios); 
				break;
            case 5: 
				mostrarEntregas(entregas, voluntarios); 
				break;
            case 6: 
				beneficiariosMasDeX(beneficiarios); 
				break;
            case 7: 
				actualizarDireccion(beneficiarios); 
				break;
            case 8: 
				actualizarRoscasBeneficiario(beneficiarios); 
				break;
            case 9: 
				modificarEntrega(entregas); 
				break;
            case 10: 
				eliminarBeneficiario(beneficiarios); 
				break;
            case 11:
				reducirEntrega(entregas); 
				break;
            case 12:
                totalPorVoluntario(entregas, voluntarios);
                totalGeneral(entregas);
                promedioBeneficiarios(beneficiarios);
                voluntarioMayor(entregas, voluntarios);
                break;
        }

    } while (op != 0);

    return 0;
}
