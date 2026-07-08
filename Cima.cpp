#include <iostream>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <random>

using namespace std;


struct jugador {
    int vida=1;
    int daño=1;
    int nivel=1;
};
struct enemigo {
    int vid=25;
    int dan=2;
};

void numgene(int &m);
void nuvju(jugador &x, string b);
void contju(jugador &x, string b, string f);
void guardar(jugador x, string b);
void niveles(jugador &x, string p, bool &k);
void jugadorcombate(jugador &x, enemigo &y);
fstream archivo;

int main(){ 
    string carpeta = ".";
    jugador play1; //el jugador
    enemigo play2; //los enemigos
    int lvl, coin, n, m=0;
    bool Tesoro = false;//requerimiento para llegar al final del juego
    string nompart;//para nombrar el nombre de la partida
    string pausa;
    lvl = 1;
    n=1;
    while(n != 4){
        system("cls");
        cout << "Batalla a la cima" << endl;
        cout << "Elija una de las opciones" << endl;
        cout << "1) Nuevo Juego" << endl;
        cout << "2) continuar" << endl;
        cout << "3) Configurar" << endl;
        cout << "4) Salir" << endl;
        cin >> n;
        cin.ignore();
        switch(n){
        case 1:
            cout << "nuevo juego" << endl;
            cout << "como nombrara su partida?" << endl;
            cin >> nompart;
            nuvju(play1, nompart);
            niveles(play1, pausa, Tesoro);
            break;
        case 2:
            cout << "Continuar" << endl;
            contju(play1, nompart, carpeta);
            getline(cin, pausa);
            niveles(play1, pausa, Tesoro);
            break;
        case 3:
            cout << "Configurar" << endl;
            break; 
        case 4:
            cout << "adios" << endl;
            break;  
        default:
            cout << "no valido" << endl;
        }
    cout << "Menu principal. Pulse <Ente> para continuar...";
    getline(cin, pausa);

    } 
return 0;
}

void numgene(int &m){
    static random_device rd;
    static mt19937 gen(rd());          
    uniform_int_distribution<> dist(1, 10);

    m = dist(gen);
}// codigo generado con ayuda de AI

void nuvju(jugador &x, string b){
    x.vida = 10;
    x.daño = 10;
    x.nivel = 1;
    b+=".dat";

    
    archivo.open(b, ios::out | ios::binary);
    if(archivo.is_open()){
        archivo.write((char *)&x, sizeof(jugador));
        archivo.close();
        cout << "Archivo escrito correctamente" << endl;
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
} //para crear un dat con datos predeterminados

void contju(jugador &x, string b, string f){
    cout << "por favor seleccione su partida guardada" << endl;
    
    for (const auto& archivo : std::filesystem::directory_iterator(f)) {
    if (archivo.path().extension() == ".dat") {
        cout << archivo.path().filename() << endl;
        }// chatgpt fue usado para este bucle for
    }
    cout << "escriba el nombre de su partida" << endl;
    cin >> b;
    b+=".dat";
    string ruta = f+"/"+b;
    ifstream archivo(ruta, ios::binary);
    if(archivo.is_open()){
        archivo.read(reinterpret_cast<char*>(&x), sizeof(jugador));
        cout << endl << x.daño << endl << x.vida << endl;
        archivo.close();
    } else{
        cout << "Error al abrir el archivo" << endl;
    }

} //para leer el juego anterior

/*void conf() */

/*void difi*()para cambiar dificultad*/

void guardar(jugador x, string b){
    archivo.open(b, ios::out | ios::binary);
    if(archivo.is_open()){
        archivo.write(reinterpret_cast<const char*>(&x), sizeof(jugador));
        archivo.close();
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
} //para guardar partida

void niveles(jugador &x, string p, bool &k){
    enemigo play2 = {25, 2};
    int r;
    int pasos =6;
    
    while(k == false){
        switch(x.nivel){
        case(1):
        cout << endl << "te encuentras en un bosque, puedes ver la cima a lo lejos" << endl;
        cout << "dirigete hacia la montaña" << endl;
        for(int i = 1; i < pasos; i++ ){
            //if (i == 5){}
            cout << "presiona enter para avanzar" << endl;
            //cin.ignore();
            getline(cin, p);
            numgene(r);
            if(r <= 3){
                enemigo play2;
                jugadorcombate(x, play2);
                if(x.vida<=0) {
                cout<<"PERDISTE";
                return;
        }   
        } 
    }x.nivel ++;
        case(2):
        system("cls");
        cout << endl << "llegaste al pie de la motana" << endl;
        cout << "sigue avanzando hasta llegar al tesoro" << endl;
        for(int j = 1; j < pasos; j++){
            //if(j == 5){}
            cout << "presiona enter para avanzar" << endl;
            //cin.ignore();
            getline(cin, p);
            numgene(r);
            if(r <= 3){
                enemigo play2;
                jugadorcombate(x, play2);
           if(x.vida<=0) {
                cout<<"PERDISTE";
                return;
        } 
        }}
        k = true;
        break;
    }
} if(k == true){
    system("cls");
    cout << "CONSEGUISTE EL TESORO, MUY BIEN" << endl;
    cout << "presione enter para volver al menu" << endl;
    cin.ignore();
    getline(cin, p);
    return;
}
}

void jugadorcombate(jugador &x, enemigo &y){
    int r;
    int opcion;
    while (x.vida > 0 && y.vid > 0){
        cout << "Vida del jugador: " << x.vida << endl;
        cout << "Vida del enemigo: " << y.vid << endl;
        cout << "1) Atacar" << endl;
        cout << "2) Huir" << endl;
        cout << "Seleccione una opcion: " << endl;
        cin >> opcion;

        switch (opcion) {
        case 1:
            // Ataque del jugador
            y.vid -= x.daño;
            cout << "Atacaste al enemigo y le hiciste "
                 << x.daño << " de daño." << endl;

            if (y.vid <= 0) {
                y.vid = 0;
                cout << "¡Has derrotado al enemigo!" << endl;
                break;
            }

            // Ataque del enemigo
            x.vida -= y.dan;
            cout << "El enemigo te ataco y te hizo "
                 << y.dan << " de daño." << endl;

            if (x.vida <= 0) {
                x.vida = 0;
                cout << "¡Has sido derrotado!" << endl;
            }
            break;

        case 2:
            numgene(r);
            if (r <= 5){
                cout << "Has huido del combate." << endl;
                return;
            } else {
                cout << "fallaste al huir" << endl;
                break;
            }
            

        default:
            cout << "Opcion invalida." << endl;
        }
    }

}
     
