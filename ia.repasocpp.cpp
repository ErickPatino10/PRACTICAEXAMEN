#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

// ======================================================
// STRUCT
// ======================================================
struct Afiliado{
    int id;
    string nombre;
    int edad;
    float peso;
    float altura;
    float mensualidad;
    bool estado;
};

const string archivoDatos = "archivo.txt";


// ======================================================
// GUARDAR UNO (APPEND)
// ======================================================
void guardarAfiliado(Afiliado &a){
    ofstream archivo(archivoDatos, ios::app);

    archivo<<a.id<<";"
           <<a.nombre<<";"
           <<a.edad<<";"
           <<a.peso<<";"
           <<a.altura<<";"
           <<a.mensualidad<<";"
           <<a.estado<<"\n";
}


// ======================================================
// GUARDAR TODO (SOBRESCRIBIR)
// ======================================================
void guardarTodo(vector<Afiliado> &afiliados){

    ofstream archivo(archivoDatos);

    for(auto &a : afiliados){
        archivo<<a.id<<";"
               <<a.nombre<<";"
               <<a.edad<<";"
               <<a.peso<<";"
               <<a.altura<<";"
               <<a.mensualidad<<";"
               <<a.estado<<"\n";
    }
}


// ======================================================
// CARGAR DESDE ARCHIVO (ESTILO INGENIERO)
// ======================================================
void cargarDesdeArchivo(vector<Afiliado> &afiliados){

    ifstream archivo(archivoDatos);

    if(!archivo.is_open())
        return;

    Afiliado a;
    char separador;

    while(archivo >> a.id >> separador){

        getline(archivo, a.nombre, ';');

        archivo >> a.edad >> separador;
        archivo >> a.peso >> separador;
        archivo >> a.altura >> separador;
        archivo >> a.mensualidad >> separador;
        archivo >> a.estado;

        afiliados.push_back(a);
    }

    archivo.close();
}


// ======================================================
// CREAR
// ======================================================
void registrarAfiliado(vector<Afiliado> &afiliados){

    Afiliado a;

    cout<<"ID: ";
    cin>>a.id;
    cin.ignore();

    cout<<"Nombre: ";
    getline(cin,a.nombre);

    cout<<"Edad: ";
    cin>>a.edad;

    cout<<"Peso: ";
    cin>>a.peso;

    cout<<"Altura: ";
    cin>>a.altura;

    cout<<"Mensualidad: ";
    cin>>a.mensualidad;

    cout<<"Estado (1 activo / 0 inactivo): ";
    cin>>a.estado;

    afiliados.push_back(a);
    guardarAfiliado(a);
}


// ======================================================
// LISTAR
// ======================================================
void listarAfiliados(vector<Afiliado> &afiliados){

    if(afiliados.empty()){
        cout<<"\nNo hay afiliados\n";
        return;
    }

    for(auto &a : afiliados){
        cout<<"\n-------------------\n";
        cout<<"ID: "<<a.id<<"\n";
        cout<<"Nombre: "<<a.nombre<<"\n";
        cout<<"Edad: "<<a.edad<<"\n";
        cout<<"Peso: "<<a.peso<<"\n";
        cout<<"Altura: "<<a.altura<<"\n";
        cout<<"Mensualidad: "<<a.mensualidad<<"\n";
        cout<<"Estado: "<<(a.estado?"Activo":"Inactivo")<<"\n";
    }
}


// ======================================================
// BUSCAR
// ======================================================
void buscarAfiliado(vector<Afiliado> &afiliados){

    int id;
    cout<<"ID: ";
    cin>>id;

    for(auto &a : afiliados){
        if(a.id==id){
            cout<<"Encontrado: "<<a.nombre<<"\n";
            return;
        }
    }

    cout<<"No encontrado\n";
}


// ======================================================
// ACTUALIZAR
// ======================================================
void actualizarAfiliado(vector<Afiliado> &afiliados){

    int id;
    cout<<"ID a actualizar: ";
    cin>>id;

    for(auto &a : afiliados){

        if(a.id==id){

            cin.ignore();

            cout<<"Nuevo nombre: ";
            getline(cin,a.nombre);

            cout<<"Edad: ";
            cin>>a.edad;

            cout<<"Peso: ";
            cin>>a.peso;

            cout<<"Altura: ";
            cin>>a.altura;

            cout<<"Mensualidad: ";
            cin>>a.mensualidad;

            cout<<"Estado (1/0): ";
            cin>>a.estado;

            guardarTodo(afiliados);
            cout<<"Actualizado correctamente\n";
            return;
        }
    }

    cout<<"No encontrado\n";
}


// ======================================================
// ELIMINAR
// ======================================================
void eliminarAfiliado(vector<Afiliado> &afiliados){

    int id;
    cout<<"ID a eliminar: ";
    cin>>id;

    for(int i=0;i<afiliados.size();i++){

        if(afiliados[i].id==id){
            afiliados.erase(afiliados.begin()+i);
            guardarTodo(afiliados);
            cout<<"Eliminado\n";
            return;
        }
    }

    cout<<"No encontrado\n";
}


// ======================================================
// ESTADISTICAS
// ======================================================
void estadisticas(vector<Afiliado> &afiliados){

    int activos=0;
    float ingreso=0, edadProm=0, imcProm=0;

    for(auto &a: afiliados){
        if(a.estado) activos++;
        ingreso += a.mensualidad;
        edadProm += a.edad;
        imcProm += a.peso/(a.altura*a.altura);
    }

    int total = afiliados.size();

    cout<<"\n% Activos: "<<activos*100.0/total;
    cout<<"\n% Inactivos: "<<(total-activos)*100.0/total;
    cout<<"\nIngreso total: "<<ingreso;
    cout<<"\nEdad promedio: "<<edadProm/total;
    cout<<"\nIMC promedio: "<<imcProm/total<<"\n";
}


// ======================================================
// MATRIZ PAGOS
// ======================================================
void matrizPagos(vector<Afiliado> &afiliados){

    float pagos[12][100]={0};

    for(int i=0;i<afiliados.size();i++)
        for(int m=0;m<12;m++)
            pagos[m][i]=afiliados[i].mensualidad;

    cout<<"Matriz generada correctamente\n";
}


// ======================================================
// LISTA ENLAZADA ACTIVOS
// ======================================================
struct Nodo{
    Afiliado dato;
    Nodo* sig;
};

void listaActivos(vector<Afiliado> &afiliados){

    Nodo* cabeza=nullptr;

    for(auto &a: afiliados){
        if(a.estado){
            Nodo* nuevo=new Nodo{a,cabeza};
            cabeza=nuevo;
        }
    }

    Nodo* aux=cabeza;

    while(aux){
        cout<<aux->dato.nombre<<"\n";
        aux=aux->sig;
    }
}


// ======================================================
// MAIN
// ======================================================
int main(){

    vector<Afiliado> afiliados;

    cargarDesdeArchivo(afiliados); // CRÍTICO

    int opcion;

    do{
        cout<<"\n=== MENU ===\n";
        cout<<"1 Crear\n2 Listar\n3 Buscar\n4 Actualizar\n5 Eliminar\n6 Estadisticas\n7 Matriz\n8 Lista activos\n9 Guardar\n10 Salir\n";

        cin>>opcion;

        switch(opcion){

            case 1: registrarAfiliado(afiliados); break;
            case 2: listarAfiliados(afiliados); break;
            case 3: buscarAfiliado(afiliados); break;
            case 4: actualizarAfiliado(afiliados); break;
            case 5: eliminarAfiliado(afiliados); break;
            case 6: estadisticas(afiliados); break;
            case 7: matrizPagos(afiliados); break;
            case 8: listaActivos(afiliados); break;
            case 9: guardarTodo(afiliados); break;

        }

    }while(opcion!=10);

    return 0;
}
