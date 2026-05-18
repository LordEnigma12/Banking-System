/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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

int calcular_plazo_en_dias() {//para que al ingresar el plazo solo sea en dias 
    int opcion;
    cout << "\n¿Desea ingresar el plazo en?\n";
    cout << "1. Años\n";
    cout << "2. Meses\n";
    cout << "Seleccione una opción: ";
    opcion = es_entero_for();

    int total_meses = 0;

    if (opcion == 1) {
        int anios;
        cout << "\nIngrese el número de años: ";
        anios = es_entero_for();
        total_meses = anios * 12;
    } else if (opcion == 2) {
        int meses;
        cout << "\nIngrese el número de meses: ";
        meses = es_entero_for();
        total_meses = meses;
    } else {
        cout << "\nOpción inválida.\n";
        return -1;
    }

    // Validar rango (mínimo 1 mes, máximo 72 meses)
    if (total_meses < 12 || total_meses > 72) {
        cout << "\nError: El plazo debe estar entre 1 año y 6 años.\n";
        return -1;
    }

    // Convertir meses a días (aprox. 30 días por mes)
    int plazo_en_dias = total_meses * 30;
    return plazo_en_dias;
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
	
	    cliente_nuevo.plazo_en_dias = calcular_plazo_en_dias();
        cin.ignore();
		
		
		outFile << nombre_cliente_nuevo << "," << rfc_cliente_nuevo << "," << saldo_actual_cliente_nuevo
		<< "," << monto_cliente_nuevo << ","  << plazo_en_dias_cliente_nuevo << "\n";
		
		cout << "\nUsuario creado exitosamente.\n";
		
	}
	
	outFile.close();
	return 0;
}
