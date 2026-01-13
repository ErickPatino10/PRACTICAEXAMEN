#include <iostream>
#include <string>
#include <iomanip> // Para setprecision
using namespace std;

// Función para calcular subtotal de un registro
void calcularSubtotal(const string &registro, float &subtotal, string &hora, string &encargado, string &tipoRosca) {
    size_t pos1 = registro.find("//");
    size_t pos2 = registro.find("//", pos1 + 2);
    size_t pos3 = registro.find("//", pos2 + 2);
    size_t pos4 = registro.find("//", pos3 + 2);

    hora = registro.substr(0, pos1);
    encargado = registro.substr(pos1 + 2, pos2 - pos1 - 2);
    tipoRosca = registro.substr(pos2 + 2, pos3 - pos2 - 2);

    int cantidad = stoi(registro.substr(pos3 + 2, pos4 - pos3 - 2));
    float precio = stof(registro.substr(pos4 + 2));

    subtotal = cantidad * precio;
}

// Función para actualizar total por encargado
void actualizarTotalEncargado(const string &encargado, float subtotal, float &totalAna, float &totalUnis, float &totalPedro) {
    if (encargado == "Ana") 
		totalAna += subtotal;
    else if (encargado == "Unis") 
		totalUnis += subtotal;
    else if (encargado == "Pedro") 
		totalPedro += subtotal;
}

// Función para mostrar detalle de entrega
void mostrarEntrega(const string &hora, const string &encargado, const string &tipoRosca, float subtotal) {
    cout << hora << " | " << encargado << " | " << tipoRosca << " | Subtotal: $" << subtotal << endl;
}

// Función para mostrar totales y mayor entrega
void mostrarTotales(float totalGeneral, float totalAna, float totalUnis, float totalPedro, float mayorSubtotal, const string &horaMayor) {
    cout << "\nTotal general recaudado: $" << totalGeneral << endl;
    cout << "\nTotal por encargado:" << endl;
    cout << "Ana: $" << totalAna << endl;
    cout << "Unis: $" << totalUnis << endl;
    cout << "Pedro: $" << totalPedro << endl;
    cout << "\nLa mayor entrega se realizó a las " << horaMayor << " con un monto de $" << mayorSubtotal << endl;
}

int main() {
    string entregas[] = { 
        "08:30//Ana//Rosca Tradicional//3//8.50", 
        "09:50//Unis//Rosca Chocolate//2//10.00",
        "09:10//Ana//Rosca Reliena//1//12.75",
        "09:30//Pedro//Rosca Tradicional//4//8.50",
        "09:50//Unis//Rosca Mini//16//4.00",
        "10:10//Ana//Rosca Chocolate//2//10.00",
        "10:30//Pedro//Rosca Rellena//1//12.75", 
        "10:50//Unis//Rosca Tradicional//3//8.50"
    };

    const int n = sizeof(entregas)/sizeof(entregas[0]);

    float totalGeneral = 0.0;
    float totalAna = 0.0, totalUnis = 0.0, totalPedro = 0.0;
    float mayorSubtotal = 0.0;
    string horaMayor;

    cout << fixed << setprecision(2); // Para mostrar decimales

    // Procesar cada entrega
    for (int i = 0; i < n; i++) {
        float subtotal;
        string hora, encargado, tipoRosca;

        calcularSubtotal(entregas[i], subtotal, hora, encargado, tipoRosca);
        mostrarEntrega(hora, encargado, tipoRosca, subtotal);

        totalGeneral += subtotal;
        actualizarTotalEncargado(encargado, subtotal, totalAna, totalUnis, totalPedro);

        if (subtotal > mayorSubtotal) {
            mayorSubtotal = subtotal;
            horaMayor = hora;
        }
    }

    mostrarTotales(totalGeneral, totalAna, totalUnis, totalPedro, mayorSubtotal, horaMayor);

    return 0;
}
