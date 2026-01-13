#include <iostream>
#include <string>
using namespace std;

// Función para procesar un registro y separar los campos
void procesarRegistro(const string& registro, string& hora, string& estudiante, string& materia, int& asistencias) {
    size_t pos1 = registro.find("|");
    size_t pos2 = registro.find("|", pos1 + 1);
    size_t pos3 = registro.find("|", pos2 + 1);

    hora = registro.substr(0, pos1);
    estudiante = registro.substr(pos1 + 1, pos2 - pos1 - 1);
    materia = registro.substr(pos2 + 1, pos3 - pos2 - 1);
    asistencias = stoi(registro.substr(pos3 + 1));
}

// Función para mostrar un registro
void mostrarRegistro(const string& hora, const string& estudiante, const string& materia, int asistencias) {
    cout << hora << " | " << estudiante << " | " << materia << " | Asistencia: " << asistencias << endl;
}

// Función para acumular asistencias por materia
void acumularAsistenciaPorMateria(const string& materia, int asistencias, int& prog, int& mate, int& fisica) {
    if (materia == "Programación") prog += asistencias;
    else if (materia == "Matemáticas") mate += asistencias;
    else if (materia == "Física") fisica += asistencias;
}

int main() {
    string asistencia[] = {
        "07:00|Carlos|Programación|1",
        "07:45|María|Matemáticas|1",
        "08:30|Luis|Programación|1",
        "09:15|Ana|Física|1",
        "10:00|Pedro|Matemáticas|1"
    };

    int totalAsistencias = 0;
    int prog = 0, mate = 0, fisica = 0;

    int n = sizeof(asistencia)/sizeof(asistencia[0]);

    cout << "Detalle de registros de asistencia:\n";

    for(int i = 0; i < n; i++) {
        string hora, estudiante, materia;
        int asistencias;

        procesarRegistro(asistencia[i], hora, estudiante, materia, asistencias);
        mostrarRegistro(hora, estudiante, materia, asistencias);

        totalAsistencias += asistencias;
        acumularAsistenciaPorMateria(materia, asistencias, prog, mate, fisica);
    }

    cout << "\nTotal de asistencias registradas: " << totalAsistencias << endl;
    cout << "\nAsistencias por materia:\n";
    cout << "Programación: " << prog << endl;
    cout << "Matemáticas: " << mate << endl;
    cout << "Física: " << fisica << endl;

    return 0;
}
