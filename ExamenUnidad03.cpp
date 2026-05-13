#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>
using namespace std;

float notas[5];
float resultadoOp = 0;
string nombreEstudiante = "";
bool hayResultado = false;
bool hayNotas = false;

string obtenerFecha() {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tiempoLocal);
    return string(buffer);
}

void operacionesBasicas() {
    int opcion;
    float a, b;

    cout << "\n===== OPERACIONES BASICAS =====\n";
    cout << "Ingresa el primer numero: ";
    cin >> a;
    cout << "Ingresa el segundo numero: ";
    cin >> b;

    cout << "\nQue operacion deseas realizar?\n";
    cout << "  1. Suma\n";
    cout << "  2. Resta\n";
    cout << "  3. Multiplicacion\n";
    cout << "  4. Division\n";
    cout << "Elige: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            resultadoOp = a + b;
            cout << "\nResultado: " << a << " + " << b << " = " << resultadoOp << endl;
            break;
        case 2:
            resultadoOp = a - b;
            cout << "\nResultado: " << a << " - " << b << " = " << resultadoOp << endl;
            break;
        case 3:
            resultadoOp = a * b;
            cout << "\nResultado: " << a << " * " << b << " = " << resultadoOp << endl;
            break;
        case 4:
            if (b == 0) {
                cout << "\nError: No se puede dividir entre cero.\n";
                return;
            }
            resultadoOp = a / b;
            cout << "\nResultado: " << a << " / " << b << " = " << resultadoOp << endl;
            break;
        default:
            cout << "\nOpcion invalida.\n";
            return;
    }
    hayResultado = true;
}

void registrarNotas() {
    cout << "\n===== REGISTRO DE NOTAS =====\n";

    for (int i = 0; i < 5; i++) {
        do {
            cout << "Ingresa la nota " << (i + 1) << " (0 a 10): ";
            cin >> notas[i];
            if (notas[i] < 0 || notas[i] > 10) {
                cout << "  Nota fuera de rango, intenta de nuevo.\n";
            }
        } while (notas[i] < 0 || notas[i] > 10);
    }

    float suma = 0;
    float mayor = notas[0];
    float menor = notas[0];
    int aprobados = 0;
    int reprobados = 0;

    for (int i = 0; i < 5; i++) {
        suma = suma + notas[i];
        if (notas[i] > mayor) mayor = notas[i];
        if (notas[i] < menor) menor = notas[i];
        if (notas[i] >= 7) {
            aprobados++;
        } else {
            reprobados++;
        }
    }

    float promedio = suma / 5;

    cout << "\n--- Resultados ---\n";
    cout << "Promedio:           " << promedio << endl;
    cout << "Nota mayor:         " << mayor << endl;
    cout << "Nota menor:         " << menor << endl;
    cout << "Aprobados (>=7):    " << aprobados << endl;
    cout << "Reprobados (<7):    " << reprobados << endl;

    hayNotas = true;
}

void guardarResultados() {
    if (!hayResultado && !hayNotas) {
        cout << "\nNo hay datos para guardar. Usa primero las opciones 1 y 2.\n";
        return;
    }

    if (nombreEstudiante.empty()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nIngresa tu nombre completo: ";
        getline(cin, nombreEstudiante);
    }

    // Abrir en modo append para acumular todos los estudiantes
    ofstream archivo("Resultados.txt", ios::app);
    if (!archivo.is_open()) {
        cout << "\nError al abrir el archivo.\n";
        return;
    }

    archivo << "=========================================\n";
    archivo << "         REPORTE DE RESULTADOS\n";
    archivo << "=========================================\n";
    archivo << "Estudiante : " << nombreEstudiante << "\n";
    archivo << "Fecha      : " << obtenerFecha() << "\n";
    archivo << "Lenguaje   : C++\n";
    archivo << "-----------------------------------------\n";

    if (hayResultado) {
        archivo << "\n[Operacion matematica]\n";
        archivo << "Ultimo resultado: " << resultadoOp << "\n";
    }

    if (hayNotas) {
        float suma = 0;
        float mayor = notas[0];
        float menor = notas[0];
        int aprobados = 0, reprobados = 0;

        for (int i = 0; i < 5; i++) {
            suma += notas[i];
            if (notas[i] > mayor) mayor = notas[i];
            if (notas[i] < menor) menor = notas[i];
            if (notas[i] >= 7) aprobados++; else reprobados++;
        }

        archivo << "\n[Notas registradas]\n";
        for (int i = 0; i < 5; i++) {
            archivo << "  Nota " << (i + 1) << ": " << notas[i] << "\n";
        }
        archivo << "\nPromedio  : " << suma / 5 << "\n";
        archivo << "Mayor     : " << mayor << "\n";
        archivo << "Menor     : " << menor << "\n";
        archivo << "Aprobados : " << aprobados << "\n";
        archivo << "Reprobados: " << reprobados << "\n";
    }

    archivo << "\n=========================================\n\n";
    archivo.close();

    cout << "\nArchivo actualizado correctamente en 'Resultados.txt'.\n";
}

int main() {
    int opcion;

    cout << "Bienvenido al aplicativo de evaluacion\n";
    cout << "Ingresa tu nombre: ";
    getline(cin, nombreEstudiante);

    do {
        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "  1. Operaciones basicas\n";
        cout << "  2. Registro de notas\n";
        cout << "  3. Guardar resultados\n";
        cout << "  4. Salir\n";
        cout << "=====================================\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                operacionesBasicas();
                break;
            case 2:
                registrarNotas();
                break;
            case 3:
                guardarResultados();
                break;
            case 4:
                cout << "\nHasta luego, " << nombreEstudiante << "!\n";
                break;
            default:
                cout << "\nOpcion no valida. Intenta de nuevo.\n";
        }

    } while (opcion != 4);

    return 0;
}
