#include <iostream>
#include <ctime>

using namespace std;

class Jugador
{
    public:
    int colores[5];
    int lista_colores[5];
    int pivotes[5] = {0};


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

    void descrifrar_pc() 
    {    
        int adivinar[5] = {1};
        int contador = 0;
        int adivinado[5] = {0};
        while(true){
            for(int i = 0; i < 5; ++i){
                if(adivinar[i] == colores[i] && adivinado[i] != 1){
                    adivinado[i] = 1;
                    contador++;
                }
            }
            for(int i = 0; i < 5; ++i){
                if(adivinado[i] == 0){
                    adivinar[i]++;
                }
            }
            if(contador == 5){
                cout << "Se resolvio el juego: " << endl;
                for(int i = 0; i < 5; ++i){
                    cout << adivinar[i] << "   ";
                }
                cout << endl;
                break;
            }
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
    }
};

int main()
{
    int opcion;
    Jugador jugador1;
    string n;
    cout << "Los colores disponibles son:\n" << "rojo, verde, amarillo, azul y negro" << endl;
    cout << "Los numeros 1, 2, 3, 4 y 5 representan los colores respectivamente" << endl;
    cout << "Comenzemos...\n" << endl;
                
    do{
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
                break;
            case 4:
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Numero invalido, intenta de nuevo..." << endl;
                break;
        }

    }while(opcion != 5);
}
