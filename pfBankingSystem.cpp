#include <iostream>
#include <string>
#include <limits>
#include <fstream> 
#include <sstream>
#include <vector>


using namespace std;

//funciones
int  es_entero_opcion_menu();
int es_entero_for();
int registro_cliente();


//variables globales
double tasa_interes = 12.9;


//struct
struct Cliente {
	int     plazo_en_dias = 0;
	double  monto = 0.0;
	double  saldo_actual = 0.0;
	string  nombre;
	string  rfc;
	
};



int main(){
	/*
	funciones de fstream -
	leer el archivo (ios::in)
	escribir (ios::out)
	agregar un valor en la ultima posicion del archivo o arreglo (llamado "append") (ios::app)
	*/


	/*
	ofstream -
	solamente escribir (si el archivo ya existe, lo sobre escribe)
	*/
	
	
	/*
	ifstream -	
	solo leer
	*/	
	
	
	//variables  de main
	int opcion_menu = 0;
	
	
	
	while (opcion_menu != 4){
		system("cls");
		cout << " ----------------------- ";
		cout << "\n    Sistema Bancario     ";
		cout << "\n ----------------------- ";
		cout << "\n1: Registro de clientes ";
		cout << "\n2: Registro de abonos ";
		cout << "\n3: Listado general de todos los clientes ";	
		cout << "\n4: Cerrar programa ";
		cout << "\nIngrese el numero de opcion deseada: ";
		opcion_menu = es_entero_opcion_menu();
	
		switch (opcion_menu) {
			case 1:
				registro_cliente();
				break;
			case 2:
			
				break;
			case 3:
			
				break;
			default:
				cout << "\nSaliendo del programa... ";	
				break;
		}	
	}

	
	
	return 0;
}


//validacion de datos de entrada 
int es_entero_opcion_menu() {
    int valor;
   
    while (true) {
        if (cin >> valor && valor >= 0 && valor <= 4 ) {
            return valor;
        } else {
            cout << "\nError: El numero debe ser entre 1 y 4." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int es_entero_for() {
    int valor;
   
    while (true) {
        if (cin >> valor && valor >= 0 ) {
            return valor;
        } else {
            cout << "\nError: El numero debe ser mayor a 0. " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}



//funciones del menu
int registro_cliente(){
	Cliente   cliente_nuevo;
	int 	  clientes_a_registrar;
	int       plazo_en_dias_cliente_nuevo;
	double    monto_cliente_nuevo;
	double    saldo_actual_cliente_nuevo;
	string    nombre_cliente_nuevo;
	string    rfc_cliente_nuevo;
	
	ofstream outFile;
	outFile.open("info_de_usuario.csv", std::ios::out | std::ios::app);
	
	if (!outFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para escribir." << std::endl;
        return 1;
    }
	
	
	cout << "Cantidad de usuarios a registrar: ";
	clientes_a_registrar = es_entero_for();
	cin.ignore();
	
	for (int i = 0; i < clientes_a_registrar; i++){
		cout << "\nNombre del cliente nuevo: ";
		getline(cin, nombre_cliente_nuevo );
		//aqui funcion para confirmar que el nombre no exista
		cliente_nuevo.nombre = nombre_cliente_nuevo;
	
		cout << "\nRFC del cliente nuevo: ";
		cin >> rfc_cliente_nuevo;
		//aqui funcion para confirmar que el RFC  no exista  
		cliente_nuevo.rfc = rfc_cliente_nuevo;
	
		cout << "\nSaldo actual del cliente nuevo: ";
		cin >> saldo_actual_cliente_nuevo;
		cliente_nuevo.saldo_actual = saldo_actual_cliente_nuevo;
	
		cout << "\nMonto del cliente nuevo: ";
		cin >> monto_cliente_nuevo;
		cliente_nuevo.monto = monto_cliente_nuevo;
	
		cout << "\nPlazo en dias del cliente nuevo: ";
		cin >> plazo_en_dias_cliente_nuevo;
		cliente_nuevo.plazo_en_dias = plazo_en_dias_cliente_nuevo;
		cin.ignore();
		
		outFile << nombre_cliente_nuevo << "," << rfc_cliente_nuevo << "," << saldo_actual_cliente_nuevo
		<< "," << monto_cliente_nuevo << ","  << plazo_en_dias_cliente_nuevo << "\n";
		
		cout << "\nUsuario creado exitosamente.\n";
		
	}
	
	outFile.close();
	return 0;
}
