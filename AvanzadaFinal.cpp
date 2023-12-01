#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

class Jugador
{
    public:
    int colores[5];
    int lista_colores[5];
    int pivotes[5] = {0};
    struct InfoJuego {
        vector<pair<string, string>> intentos; // Primer string es el intento, segundo es la respuesta
        string cod;
        bool gano;
    };

    static InfoJuego ultimoJuego;


    Jugador()
    {
        colores[0] = colores[1] = colores[2] = colores[3] = colores[4] = 0;
    }

    void agregar_colores_manualmente(string n, int i)
    {
        if(n == "rojo")
            colores[i] = 1;
        else if(n == "verde")
            colores[i] = 2;
        else if(n == "amarillo")
            colores[i] = 3;
        else if(n == "azul")
            colores[i] = 4;
        else if(n == "negro")
            colores[i] = 5;
    }

    void agregar_colores_aleatoriamente()
    {
        float x;
        srand(time(NULL));
        for(int i = 0; i < 5; i++)
            { 
                x=rand()%5 + 1;
                colores[i] = x;
            }
    }

    void mostrar_colores()
    {
        for(int i = 0; i < 5; i++)
            cout << colores[i] << "\t";
        cout << endl;
    }

    int posicion_color(int vec[5], int n){
        for(int i = 0; i < 5; ++i){
            if(vec[i] == n){
                return i;
            }
        }
        return -1;
    }

    bool comprobar_win(int vec[5]){
        int cont = 0;
        for(int i = 0; i < 5; ++i){
            if(vec[i] == colores[i]){
                cont++;
            }
        }
        if(cont == 5) return true;
        return false;
    }

void descrifrar_pc() {    
    int opc, correct_color, opc1, n, pos;
    string opc_s;
    int vec[5] = {1,2,3,4,5};
    int usado[5] = {0};
    int t = 10;
    while(t--){
        cout << "Tus colores elegidos fueron: " << endl; 
        mostrar_colores();
        cout << "Colores propuestos por la computadora: " << endl;
        for(int i = 0;i  < 5; ++i){
            cout << vec[i] << "\t ";
        }
        cout << endl << "0 significa posición incorrecta 1 posición correcta" << endl;
        for(int i = 0; i < 5; ++i){
            cout << usado[i] << " ";
        }
        cout << endl << "Algun color aparece en tu codigo secreto? 1.- si/ 2.- no" << endl;
        cin >> opc;
        if(opc == 1){
            cout << "Está en la posición correcta? 1.- si/ 2.- no" << endl;
            cin >> opc1;
            if(opc1 == 1){
                cout << "Que posición está?" << endl;
                cin >> opc;
                usado[opc - 1] = 1;
            }
            else{
                cout << "Que color es? - Pon en numero" << endl;
                cin >> n;
                pos = posicion_color(vec, n);
                if(pos < 4){
                    while(true){
                        if(usado[pos] == 0){
                            break;
                        }
                        pos++;
                    }
                    vec[pos + 1] = vec[pos];
                    pos = pos + 1;
                }
                else{
                     while(true){
                        if(usado[pos] == 0){
                            break;
                        }
                        pos--;
                    }
                    vec[0] = vec[pos];
                    pos = 0;
                }
                for(int i = 0; i < 5; ++i){
                    if(i != pos && usado[i] == 0){
                        vec[i] = rand() % 5 + 1;
                    }
                }

            }
        }
        else{
            for(int i = 0; i < 5; ++i){
                if(usado[i] == 0){
                    vec[i] = rand() % 5 + 1;
                }
            }
        }
    system("clear");
    if(comprobar_win(vec)){
        cout << "La computadora ha ganado con el vector: " << endl;
        for(int i = 0; i < 5; ++i){
            cout << vec[i] << "\t";
        }
        cout << endl;
        break;
    }
    }
    ofstream archivoBinario("ultimo_juego.bin", ios::binary);
    if (archivoBinario) {
        archivoBinario.write(reinterpret_cast<const char*>(&ultimoJuego), sizeof(InfoJuego));
        archivoBinario.close();
    } else {
        cout << "Error al guardar la información del juego." << endl;
    }
}

    void intentos(string n, int i)
    {
        if(n == "rojo")
            lista_colores[i] = 1;
        else if(n == "verde")
            lista_colores[i] = 2;
        else if(n == "amarillo")
            lista_colores[i] = 3;
        else if(n == "azul")
            lista_colores[i] = 4;
        else if(n == "negro")
            lista_colores[i] = 5;
    }

    void descifrador_humano()
    {
        string n;
        int aux;
        int intentosRestantes = 5; 
        bool haGanado = false;

        do
        {
            aux = 0;
            cout << "Ingresar los colores de tu eleccion:" << endl;

            for (int i = 0; i < 5; i++)
            {
                cout << "Color " << i + 1 << ":" << endl;
                cin >> n;
                intentos(n, i);
                //cout<<lista_colores[i]<<endl;
            }

            for (int i = 0; i < 5; i++)
            {
                if (colores[i] == lista_colores[i])
                {
                    pivotes[i] = 1; //Negro -> Mismo color y posición
                }
                else
                    for (int j = 0; j < 5; j++)
                    {
                        if (colores[j] == lista_colores[i]) //&& pivotes[j] == 0
                            pivotes[i] = 2; //Blanco -> Se encuentra en el arreglo
                    }
            }

            cout << "Tu intento: " << endl;
            for (int k = 0; k < 5; k++)
                cout << lista_colores[k] << "\t";
            cout << endl;

            cout << "Pivotes" << endl;
            for (int k = 0; k < 5; k++)
                cout << pivotes[k] << "\t";
            cout << endl;

            for (int k = 0; k < 5; k++)
                if (pivotes[k] == 1)
                    aux++;

            intentosRestantes--;

            if (aux == 5)
            {
                haGanado = true;
                break;
            }

            if (intentosRestantes > 0)
                cout << "Intentos restantes: " << intentosRestantes << endl;
            else
                cout << "Lo siento, has agotado tus intentos. Perdiste." << endl;

        } while (intentosRestantes > 0);

        if (haGanado)
            cout << "¡Felicidades, lo has logrado!" << endl;

        

    
    ofstream archivoBinario("ultimo_juego.bin", ios::binary);
    if (archivoBinario) {
        archivoBinario.write(reinterpret_cast<const char*>(&ultimoJuego), sizeof(InfoJuego));
        archivoBinario.close();
    } else {
        cout << "Error al guardar la información del juego." << endl;
    }
    }
        
        
void GuardarJuego() {
    ifstream archivoBinario("ultimo_juego.bin", ios::binary);
    if (archivoBinario) {
        InfoJuego juego;
        archivoBinario.read(reinterpret_cast<char*>(&juego), sizeof(InfoJuego));
        archivoBinario.close();

        cout << "Codigo Secreto: " << juego.cod << endl;
        cout << (juego.gano ? "Juego Ganado" : "Juego Perdido") << endl;
        for (const auto& intento : juego.intentos) {
            cout << "Intento: " << intento.first << " - Respuesta: " << intento.second << endl;
        }
    } else {
        cout << "No hay información del último juego disponible." << endl;
    }
}

void GuardarJuegoTxt() {
    ofstream archivoTexto("ultimo_juego.txt");
    if (archivoTexto) {
        archivoTexto << "Codigo Secreto: " << ultimoJuego.cod << endl;
        archivoTexto << (ultimoJuego.gano ? "Juego Ganado" : "Juego Perdido") << endl;
        for (const auto& intento : ultimoJuego.intentos) {
            archivoTexto << "Intento: " << intento.first << " - Respuesta: " << intento.second << endl;
        }
        cout << "El juego ha sido exportado a ultimo_juego.txt" << endl;
    } else {
        cout << "Error al abrir el archivo para escritura." << endl;
    }
}

};
Jugador::InfoJuego Jugador::ultimoJuego;


int main()
{
    int opcion;
    Jugador jugador1;
    string n;
    cout << "Los colores disponibles son:\n" << "rojo, verde, amarillo, azul y negro" << endl;
    cout << "Los numeros 1, 2, 3, 4 y 5 representan los colores respectivamente" << endl;
    cout << "EL numero 0 significa que el color no esta, el numero 1 significa que el color se encuentra en la posicion \n correcta y el 2 que el color esta en el codigo secreto pero no en su posicion " << endl;
    cout << "Comenzemos...\n" << endl;
                
    do {
        cout << "--------MENU--------" << endl;
        cout << "1. Creador de codigo (PC) vs Descifrador(Humano)\n2. Creador de codigo (Humano) vs Descifrador(PC)\n3. Listar el ultimo juego\n";
        cout << "4. Mandar el último juego a un TXT\n5. Salir\n--------------------\n";
        cin >> opcion;
        switch(opcion)
        {
            case 1:
                jugador1.agregar_colores_aleatoriamente();
                cout << "Tus colores asignados fueron: " << endl; 
                jugador1.mostrar_colores();
                jugador1.descifrador_humano();
                break;
            case 2:
                for(int i = 0; i < 5; i++)
                    {
                        cout << "Color " << i+1 << ":" << endl;
                        cin >> n;
                        jugador1.agregar_colores_manualmente(n, i);
                    }
                cout << "Tus colores elegidos fueron: " << endl; 
                jugador1.mostrar_colores();
                break;
            case 3:
                jugador1.GuardarJuego();
                break;
            case 4:
                jugador1.GuardarJuegoTxt();
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Numero invalido, intenta de nuevo..." << endl;
                break;
        }

    } while (opcion != 5);

    return 0;
}
