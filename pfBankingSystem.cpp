#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────
//  CONSTANTES GLOBALES
// ─────────────────────────────────────────
const double TASA_INTERES_ANUAL = 12.9;        // Porcentaje anual
const double TASA_SEGURO_MENSUAL = 0.0005;     // 0.05% del monto original por mes
const string ARCHIVO_CSV = "info_de_usuario.csv";


// ─────────────────────────────────────────
//  STRUCT
// ─────────────────────────────────────────
struct Cliente {
    string  nombre;
    string  rfc;
    double  monto         = 0.0;   // Monto original del credito
    int     plazo_meses   = 0;     // Plazo total en meses
    double  saldo_actual  = 0.0;   // Saldo pendiente por pagar
    double  mensualidad   = 0.0;   // Pago mensual fijo (con seguro incluido)
};


// ─────────────────────────────────────────
//  PROTOTIPOS
// ─────────────────────────────────────────
int    validar_entero_rango(int min, int max);
double validar_double_positivo();
string validar_string_no_vacio();

double calcular_mensualidad(double monto, int plazo_meses);
bool   rfc_existe(const vector<Cliente>& clientes, const string& rfc);

void   cargar_csv(vector<Cliente>& clientes);
void   guardar_csv(const vector<Cliente>& clientes);

void   registrar_cliente(vector<Cliente>& clientes);
void   registrar_abono(vector<Cliente>& clientes);
void   mostrar_listado(const vector<Cliente>& clientes);


// ─────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────
int main() {
    vector<Cliente> clientes;
    cargar_csv(clientes);

    int opcion = 0;

    while (opcion != 4) {
        system("cls");

        cout << " ─────────────────────────── \n";
        cout << "      Sistema Bancario        \n";
        cout << " ─────────────────────────── \n";
        cout << " 1: Registro de clientes      \n";
        cout << " 2: Registro de abonos        \n";
        cout << " 3: Listado general           \n";
        cout << " 4: Cerrar programa           \n";
        cout << " ─────────────────────────── \n";
        cout << " Opcion: ";

        opcion = validar_entero_rango(1, 4);

        switch (opcion) {
            case 1:
                registrar_cliente(clientes);
                break;
            case 2:
                registrar_abono(clientes);
                break;
            case 3:
                mostrar_listado(clientes);
                break;
            case 4:
                cout << "\n Saliendo del programa...\n";
                break;
        }
    }

    return 0;
}


// ─────────────────────────────────────────
//  VALIDACIONES
// ─────────────────────────────────────────

// Pide un entero y lo valida dentro de [min, max]
int validar_entero_rango(int min, int max) {
    int valor;
    while (true) {
        if (cin >> valor && valor >= min && valor <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << " Error: ingrese un numero entre " << min << " y " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Pide un numero decimal positivo
double validar_double_positivo() {
    double valor;
    while (true) {
        if (cin >> valor && valor > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << " Error: ingrese un valor numerico mayor a 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Pide una cadena no vacia
string validar_string_no_vacio() {
    string valor;
    while (true) {
        getline(cin, valor);
        if (!valor.empty()) return valor;
        cout << " Error: el campo no puede estar vacio. Intente de nuevo: ";
    }
}


// ─────────────────────────────────────────
//  CALCULO DE MENSUALIDAD
//  Formula de amortizacion francesa:
//  M = P * [r(1+r)^n] / [(1+r)^n - 1]  +  seguro
// ─────────────────────────────────────────
double calcular_mensualidad(double monto, int plazo_meses) {
    double tasa_mensual = (TASA_INTERES_ANUAL / 100.0) / 12.0;
    double factor       = pow(1.0 + tasa_mensual, plazo_meses);
    double pago_base    = monto * (tasa_mensual * factor) / (factor - 1.0);
    double seguro       = monto * TASA_SEGURO_MENSUAL;
    return pago_base + seguro;
}


// ─────────────────────────────────────────
//  VERIFICAR RFC DUPLICADO
// ─────────────────────────────────────────
bool rfc_existe(const vector<Cliente>& clientes, const string& rfc) {
    for (int i = 0; i < (int)clientes.size(); i++) {
        if (clientes[i].rfc == rfc) return true;
    }
    return false;
}


// ─────────────────────────────────────────
//  LEER CSV AL INICIAR
//  Formato: nombre,rfc,monto,plazo_meses,saldo_actual,mensualidad
// ─────────────────────────────────────────
void cargar_csv(vector<Cliente>& clientes) {
    ifstream archivo(ARCHIVO_CSV);
    if (!archivo.is_open()) return; // Si no existe el archivo, se inicia vacio

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        Cliente c;
        string monto_str, plazo_str, saldo_str, mensualidad_str;

        getline(ss, c.nombre,        ',');
        getline(ss, c.rfc,           ',');
        getline(ss, monto_str,       ',');
        getline(ss, plazo_str,       ',');
        getline(ss, saldo_str,       ',');
        getline(ss, mensualidad_str, ',');

        // Saltar lineas incompletas o con campos vacios para evitar crash
        if (c.nombre.empty() || c.rfc.empty() ||
            monto_str.empty() || plazo_str.empty() ||
            saldo_str.empty() || mensualidad_str.empty()) {
            continue;
        }

        c.monto        = stod(monto_str);
        c.plazo_meses  = stoi(plazo_str);
        c.saldo_actual = stod(saldo_str);
        c.mensualidad  = stod(mensualidad_str);

        clientes.push_back(c);
    }

    archivo.close();
    cout << " Datos cargados correctamente (" << clientes.size() << " clientes).\n";
    cout << " Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// ─────────────────────────────────────────
//  GUARDAR CSV (sobreescribe todo)
//  Formato: nombre,rfc,monto,plazo_meses,saldo_actual,mensualidad
// ─────────────────────────────────────────
void guardar_csv(const vector<Cliente>& clientes) {
    ofstream archivo(ARCHIVO_CSV, ios::out);

    if (!archivo.is_open()) {
        cerr << " Error: no se pudo abrir el archivo para guardar.\n";
        return;
    }

    for (int i = 0; i < (int)clientes.size(); i++) {
        archivo << fixed << setprecision(2)
                << clientes[i].nombre       << ","
                << clientes[i].rfc          << ","
                << clientes[i].monto        << ","
                << clientes[i].plazo_meses  << ","
                << clientes[i].saldo_actual << ","
                << clientes[i].mensualidad  << "\n";
    }

    archivo.close();
}


// ─────────────────────────────────────────
//  REGISTRO DE NUEVOS CLIENTES
// ─────────────────────────────────────────
void registrar_cliente(vector<Cliente>& clientes) {
    system("cls");
    cout << " ─────────────────────────── \n";
    cout << "    Registro de Clientes      \n";
    cout << " ─────────────────────────── \n";

    cout << " Cantidad de clientes a registrar: ";
    int cantidad = validar_entero_rango(1, 100);

    for (int i = 0; i < cantidad; i++) {
        Cliente c;
        system("cls");
        cout << " ─────────────────────────── \n";
        cout << "  Cliente " << (i + 1) << " de " << cantidad << "\n";
        cout << " ─────────────────────────── \n";

        // Nombre
        cout << " Nombre completo: ";
        c.nombre = validar_string_no_vacio();

        // RFC (sin duplicados)
        while (true) {
            cout << " RFC: ";
            c.rfc = validar_string_no_vacio();
            if (!rfc_existe(clientes, c.rfc)) break;
            cout << " Error: ese RFC ya esta registrado. Intente con otro.\n";
        }

        // Monto del credito
        cout << " Monto del credito ($): ";
        c.monto = validar_double_positivo();

        // Plazo en años (1–6), se convierte a meses
        cout << " Plazo en anios (1 a 6): ";
        int plazo_anios  = validar_entero_rango(1, 6);
        c.plazo_meses    = plazo_anios * 12;

        // Calculos automaticos
        c.mensualidad  = calcular_mensualidad(c.monto, c.plazo_meses);
        c.saldo_actual = c.monto; // Saldo inicial = monto total del credito

        // Resumen antes de confirmar
        cout << "\n ── Resumen del cliente ── \n";
        cout << fixed << setprecision(2);
        cout << " Nombre       : " << c.nombre         << "\n";
        cout << " RFC          : " << c.rfc             << "\n";
        cout << " Monto        : $" << c.monto          << "\n";
        cout << " Plazo        : " << plazo_anios << " anios (" << c.plazo_meses << " meses)\n";
        cout << " Mensualidad  : $" << c.mensualidad    << " (incluye seguro)\n";
        cout << " Saldo inicial: $" << c.saldo_actual   << "\n";
        cout << "\n Confirmar registro? (1=Si / 2=No): ";
        int confirmar = validar_entero_rango(1, 2);

        if (confirmar == 1) {
            clientes.push_back(c);
            guardar_csv(clientes);
            cout << " Cliente registrado exitosamente.\n";
        } else {
            cout << " Registro cancelado.\n";
            i--; // Repetir este turno
        }

        cout << " Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// ─────────────────────────────────────────
//  REGISTRO DE ABONOS
// ─────────────────────────────────────────
void registrar_abono(vector<Cliente>& clientes) {
    system("cls");
    cout << " ─────────────────────────── \n";
    cout << "    Registro de Abonos        \n";
    cout << " ─────────────────────────── \n";

    if (clientes.empty()) {
        cout << " No hay clientes registrados.\n";
        cout << " Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // Buscar cliente por RFC
    cout << " Ingrese el RFC del cliente: ";
    string rfc_buscar = validar_string_no_vacio();

    int indice = -1;
    for (int i = 0; i < (int)clientes.size(); i++) {
        if (clientes[i].rfc == rfc_buscar) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << " Error: no se encontro un cliente con ese RFC.\n";
        cout << " Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    Cliente& c = clientes[indice];

    cout << fixed << setprecision(2);
    cout << "\n Cliente encontrado: " << c.nombre << "\n";
    cout << " Saldo actual      : $" << c.saldo_actual << "\n";
    cout << " Mensualidad       : $" << c.mensualidad  << "\n";

    if (c.saldo_actual <= 0) {
        cout << " Este cliente ya liquido su credito.\n";
        cout << " Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\n Monto del abono ($): ";
    double abono = validar_double_positivo();

    // El abono no puede superar el saldo actual
    if (abono > c.saldo_actual) {
        cout << " Aviso: el abono supera el saldo. Se ajustara al saldo pendiente ($"
             << c.saldo_actual << ").\n";
        abono = c.saldo_actual;
    }

    c.saldo_actual -= abono;

    guardar_csv(clientes);

    cout << "\n Abono de $" << abono << " registrado correctamente.\n";
    cout << " Nuevo saldo: $" << c.saldo_actual << "\n";

    if (c.saldo_actual == 0)
        cout << " Felicidades, el credito ha sido liquidado!\n";

    cout << " Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// ─────────────────────────────────────────
//  LISTADO GENERAL DE CLIENTES
// ─────────────────────────────────────────
void mostrar_listado(const vector<Cliente>& clientes) {
    system("cls");
    cout << " ─────────────────────────────────────────────────────────────────\n";
    cout << "                     Listado General de Clientes                  \n";
    cout << " ─────────────────────────────────────────────────────────────────\n";

    if (clientes.empty()) {
        cout << " No hay clientes registrados.\n";
        cout << " Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << fixed << setprecision(2);

    for (int i = 0; i < (int)clientes.size(); i++) {
        const Cliente& c = clientes[i];

        // Calcular pagos realizados aproximados y meses restantes
        double pagos_al_capital = c.monto - c.saldo_actual;
        int    meses_restantes  = 0;
        if (c.mensualidad > 0 && c.saldo_actual > 0) {
            // Estimacion simple: saldo / mensualidad
            meses_restantes = (int)ceil(c.saldo_actual / c.mensualidad);
            if (meses_restantes > c.plazo_meses) meses_restantes = c.plazo_meses;
        }

        cout << "\n [" << (i + 1) << "] " << c.nombre << "\n";
        cout << "     RFC             : " << c.rfc                    << "\n";
        cout << "     Monto original  : $" << c.monto                 << "\n";
        cout << "     Plazo           : " << c.plazo_meses << " meses (" << (c.plazo_meses / 12) << " anios)\n";
        cout << "     Mensualidad     : $" << c.mensualidad            << " (con seguro)\n";
        cout << "     Pagado al capital: $" << pagos_al_capital        << "\n";
        cout << "     Saldo pendiente : $" << c.saldo_actual           << "\n";

        if (c.saldo_actual <= 0)
            cout << "     Estado          : LIQUIDADO\n";
        else
            cout << "     Meses restantes : ~" << meses_restantes << "\n";

        cout << " ─────────────────────────────────────────────────────────────────\n";
    }

    cout << " Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
