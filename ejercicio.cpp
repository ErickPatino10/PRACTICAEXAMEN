#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<windows.h>

using namespace std;

//Estructura de datos
struct Corredor {
    int numeroCorredor; //identificador
    string nombres;
    string apellidos;
    string categoria; //Elite, Amateur, Senior
    float tiempoMinutos; //0.0 significa que aun no compitio y falta de registrar tiempo
};

const string archivoDatos= "corredores.txt";

void guardarCorredor(Corredor& c) {
    //Escribimos al final del archivo nuestro nuevo corredor
    ofstream archivo(archivoDatos, ios::app);
    if (archivo.is_open()) {
        archivo<<c.numeroCorredor<<";"
        <<c.nombres<<";"
        <<c.apellidos<<";"
        <<c.categoria<<";"
        <<c.tiempoMinutos<<"\n";

    }else {
        cerr<<"No se pudo abrir el archivo para guardar\n";
    }

}

//Sobreescribir todo el archivo, para borrar el contenido anterior y escribir
//todo el vector, necesario para modificar o eliminar registros existentes
//ya que los archivos de texto no permite edicion secuencial (in situ).
void guardarTodos(vector<Corredor>& corredores) {
    ofstream archivo(archivoDatos);
    if (archivo.is_open()) {
        //Recorro todo el vector y lo sobrescribo en el archivo
        for (auto& c : corredores) {
            archivo<<c.numeroCorredor<<";"
            <<c.nombres<<";"
            <<c.apellidos<<";"
            <<c.categoria<<";"
            <<c.tiempoMinutos<<"\n";
        }
    }
}

//Cargar todos los corredores desde el archivo
//Leer linea por linea, parsea los campos separados por ";"
//y construir un vector de objetos corredor.
vector<Corredor> cargarCorredores() {
    vector<Corredor> corredores;
    ifstream archivo(archivoDatos);

    if (archivo.is_open()) {
        string linea;

        //Leer linea por linea hasta el final del archivo
        while (getline(archivo,linea)) {
            //Ignorar lineas en blanco o vacias
            if (linea.empty()) {
                continue;
            }
            //Parseo de la linea, tomar datos usando ";"como delimitador
            vector<string> campos;
            size_t pos = 0;
            //Buscar cada ";" y extrae el texto antes de el
            while ((pos = linea.find(";")) != string::npos) {
                campos.push_back(linea.substr(0,pos)); //Extrae campo
                linea.erase(0,pos+1); //Elimina lo extraido
            }
            campos.push_back(linea);
            if (campos.size() == 5) {
                Corredor c;
                c.numeroCorredor = stoi(campos[0]);
                c.nombres = campos[1];
                c.apellidos = campos[2];
                c.categoria = campos[3];
                c.tiempoMinutos = stof(campos[4]);
                corredores.push_back(c);
            }
        }
    }
    return corredores;
}

void inscribirCorredor() {
    Corredor nuevo;
    cout<<"---Nueva Inscripción---\n";
    cout<<"Ingrese el número del Corredor: ";
    cin>>nuevo.numeroCorredor;
    cin.ignore();
    cout<<"Nombres Completos: ";
    getline(cin,nuevo.nombres);
    cout<<"Apellidos Completos: ";
    getline(cin,nuevo.apellidos);
    cout<<"Categoria(Elite,Senior,Amateur): ";
    getline(cin,nuevo.categoria);
    nuevo.tiempoMinutos = 0.0f; //Tiempo esta pendiente
    guardarCorredor(nuevo);
    cout<<"Corredor inscrito y guardado en el archivo\n";
}
//Mostrar lista de inscritos

void verInscritos() {
    vector<Corredor> corredores = cargarCorredores();
    cout<<"\n---Lista de Corredores inscritos---\n";

    if (corredores.empty()) {
        cout<<"No hay corredores inscritos.\n";
    }else {
        for (auto& corredor : corredores) {
            cout<<"--------------------\n";
            cout<<"Numero Corredor: "<<corredor.numeroCorredor<<"\n";
            cout<<"Nombres: "<<corredor.nombres<<"\n";
            cout<<"Apellidos: "<<corredor.apellidos<<"\n";
            cout<<"Categoria: "<<corredor.categoria<<"\n";
          //Mostrar tiempo pendiente si es que aun no llega
            if (corredor.tiempoMinutos > 0.0f) {
                cout<<"Tiempo: "<<corredor.tiempoMinutos<< "min\n";
            }else {
                cout<<"Tiempo pendiente\n";
            }
        }
    }
}
//Registrar tiempo de llegada
//1. Cargar todo el archivo en memoria(vector)
//2. Buscar el corredor y modificar su tiempo en el vector en memoria
//3. Sobreescribir todo el archivo , porque los archivos de texto son sencuenciales
// Es decir no permiten editar una linea especifica sin reescribir todo.
void registrarTiempo() {
    //Paso 1 , cargar todos los datos a memoria en un vector
    vector<Corredor> corredores = cargarCorredores();

    int numBuscar;
    bool encontrado = false;

    cout<<"\n --- Registrar Tiempo de llegada---\n";
    cout<<"Ingrese el número de corredor: ";
    cin>>numBuscar;

    //Paso 2. Buscar y modificar en el vector en memoria
    for (auto& corredor : corredores) {
        if (corredor.numeroCorredor == numBuscar) {
            cout<<"Corredor: "<<corredor.nombres<<" "<<corredor.apellidos<<endl;
            cout<<"Ingrese el tiempo final en minutos: ";
            cin>>corredor.tiempoMinutos; //Modificamos los minutos en el objeto del vector
            encontrado = true;
            cout<<"Tiempo registrado exitosamente.\n";
            break;
        }
    }

    if (!encontrado) {
        cout<<"No se encontro al corredor con ese número\n";
    }

    //Paso 3. Sobreescribir archivo completo con los cambios
    guardarTodos(corredores);
}

int main() {
    //Configurar consola para tildes y ñ

    system("chcp 65001 > nul");
    int opcion = 0;

    //bucle do while para el menu
    do {
        cout << "\n---Sistema de Registro 'Quito Ruta de las Iglesias 10K'---\n";
        cout << "1. Inscribir corredor\n";
        cout << "2. Ver lista de inscritos\n";
        cout << "3. Registrar tiempo de llegada\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
    //Estructura de las opciones
        if (opcion == 1) {
            inscribirCorredor();
        }else if (opcion == 2) {
            verInscritos();
        }else if (opcion == 3) {
          registrarTiempo();
        }else if (opcion == 4) {
            cout<<"Saliendo del sistema...\n";
        }else {
            cout<<"Opción no válida. Ingresa un número del 1 al 4";
        }


    } while (opcion != 4);

    return 0;
}
