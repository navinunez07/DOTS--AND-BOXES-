#include <iostream>
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include "GOTOXY.h"

using namespace std;

class CJugador{
private:
    string nombre_jugador;
    int puntaje = 0;
public:
    CJugador()=default;
    void asignar_nombre(const string& nombre){nombre_jugador=nombre;}
    void agregar_punto(int punto){puntaje += punto;}
    string get_nombre(){return nombre_jugador;}
    int get_puntaje() const{return puntaje;}
};
class CTablero{
private:
    CJugador jugador_A;
    CJugador jugador_B;
    string Symbolo;
    //string **tablero;
    int lado;
public:
    string **tablero;
    explicit CTablero(int lado):lado(lado){
        tablero = new string*[lado];
        for (int i = 0; i < lado; ++i){tablero[i]=new string[lado];}
        for (int i = 0; i < lado; ++i) {
            for (int j = 0; j < lado; ++j) {
                if (i % 2 == 0)
                    if (j % 2 == 0)
                        tablero[i][j] = "+";
            }
        }
    }
    void asignar_nombre(const string& jugador_1, const string& jugador_2){
        jugador_A.asignar_nombre(jugador_1);
        jugador_B.asignar_nombre(jugador_2);
    }
    void agregar_linia(vector<string> cordenada ) const{
        tablero[stoi(cordenada[0])][stoi(cordenada[1])] = cordenada[2];
    }
    void agregar_punto(int punto,const string& nombre){
        if(nombre == jugador_A.get_nombre())
            jugador_A.agregar_punto(punto);
        if(nombre == jugador_B.get_nombre())
            jugador_B.agregar_punto(punto);
    }
    void agregar_symbolo(const int *punto, const string& symbolo ) const{ //agreaga el inicial de la letra
        tablero[punto[0]][punto[1]]=symbolo;
    }
    int get_punto_jugador1(){return jugador_A.get_puntaje();}
    int get_punto_jugador2(){return jugador_B.get_puntaje();}

    void imprimir_tablero() const{//--> imprime el tablero de la clase
        for (int i = 0; i < lado; ++i) {
            for (int j = 0; j < lado; ++j) {
                cout << tablero[i][j];
            }
            cout << endl;
        }
    }

};
string letra_inicial(const string& nombre){//extrae la inicial de la letra de cada nombre para usar de simbolo
    string inicial;
    inicial = nombre[0];
    return inicial;
}
void validar_dato(string &opcion,const int num_opciones){ //valida los datos de entrada, asi como tambien las opciones
    vector<string>numero_opciones;
    numero_opciones.reserve(num_opciones);
    for (int i = 0; i < num_opciones; ++i) {
        numero_opciones.push_back(to_string(i));
    }
    while (true){
        getline(cin, opcion);
        auto it = find(begin(numero_opciones),end(numero_opciones),opcion );
        if(it == end(numero_opciones))
            cout << "ingresa una opcion valida"<<endl;
        else
            break;
    }
}
vector<string> movimiento(const int *inicio, const int *final){ //---> genera el punto donde se
    int x, y;                                                         // pondra el aspa dependiendo la entrada
    vector<string> cordenada;
    string aspa = "|", guion="-";
    if(inicio[0]<final[0]){ y = inicio[0]+1;}
    if(inicio[0]>final[0]){ y = final[0]+1;}
    if(inicio[0]==final[0]){ y = inicio[0];}

    if(inicio[1]<final[1]){ x = inicio[1]+1;}
    if(inicio[1]>final[1]){ x = final[1]+1;}
    if(inicio[1]==final[1]){ x = inicio[1];}

    cordenada.push_back(to_string(y));
    cordenada.push_back(to_string(x));
    if(inicio[0] < stoi(cordenada[0])){cordenada.push_back(aspa);}
    if(inicio[1] < stoi(cordenada[1])){cordenada.push_back(guion);}
    return cordenada;
}
void decifrando_laterales(vector<string> punto, int **punto_return) {// --->> decifra los puntos laterales del aspa
    int punto1, punto2;
    if (punto[2] == "|") { //varian las x
        punto1 = stoi(punto[1]) - 1;
        punto2 = stoi(punto[1]) + 1;
        //llenando el primer punto
        punto_return[0][0] = stoi(punto[0]); //-----> Y
        punto_return[0][1] = punto1; //----> X
        //llenando segundo punto
        punto_return[1][0] = stoi(punto[0]);//----> Y
        punto_return[1][1] = punto2;// ----X
    }
    if (punto[2] == "-") {// varian las y
        punto1 = stoi(punto[0]) - 1;
        punto2 = stoi(punto[0]) + 1;
        //llenando el primer punto
        punto_return[0][0] = punto1;//----> Y
        punto_return[0][1] = stoi(punto[1]);//----X
        //llenando el segundo punto
        punto_return[1][0] = punto2;//----> Y
        punto_return[1][1] = stoi(punto[1]);//----> X
    }
}
int validando_laterales(int **puntos, CTablero *Tablero, const string& N){ //----> valida los puntos laterales
    int punto1[2], punto2[2], cont = 0;
    punto1[0] = puntos[0][0]; // Y1 punto1
    punto1[1] = puntos[0][1]; // X1 punto1
    punto2[0] = puntos[1][0]; // Y2 punto2
    punto2[1] = puntos[1][1]; // X2 punto2
    //Tablero->agregar_symbolo(punto1,N);
    //                 [         ][           ]
    if(punto1[0] >= 0 & punto1[1] >= 0)
        if(!Tablero->tablero[punto1[0]][punto1[1]+1].empty())
            if(!Tablero->tablero[punto1[0]][punto1[1]-1].empty())
                if(!Tablero->tablero[punto1[0]+1][punto1[1]].empty())
                    if(!Tablero->tablero[punto1[0]-1][punto1[1]].empty()) {
                        Tablero->agregar_symbolo(punto1,N);
                        cont += 1;
                    }
    if(punto2[0] >= 0 & punto2[1] >= 0)
        if(!Tablero->tablero[punto2[0]][punto2[1]+1].empty())
            if(!Tablero->tablero[punto2[0]][punto2[1]-1].empty())
                if(!Tablero->tablero[punto2[0]+1][punto2[1]].empty())
                    if(!Tablero->tablero[punto2[0]-1][punto2[1]].empty()) {
                        Tablero->agregar_symbolo(punto2,N);
                        cont += 1;
                    }
    return cont;
}
vector<string> punto_alea(int lado, CTablero *Tablero){ //----> genera los puntos aleatorios del bot
    vector<string> vect;
    for (int i = 0; i < lado ; ++i) {
        for (int j = 0; j < lado ; ++j) {
            if(i % 2 != 0 & j % 2 != 0){}
            else if(i % 2 == 0 & j % 2 == 0){}
            else{
                if(!Tablero->tablero[i][j].empty()){}
                else{
                    vect.push_back(to_string(i));
                    vect.push_back(to_string(j));
                    if(i%2==0)
                        vect.emplace_back("-");
                    else
                        vect.emplace_back("|");
                }
            }
        }
    }
    return vect;
}
void ejecutando_operaciones(int lado,int n_casillas, const string& jugador1, const string& jugador2,const string& play){
    auto *Tablero = new CTablero(lado);
    int cont = 0,**punto_return, punto;
    vector<string> cordenada;
    int inicio[2], final[2];

    punto_return = new int*[2];
    for (int i = 0; i < 2; ++i) punto_return[i]=new int[2];
    //asignado nombre a los jugadores
    Tablero->asignar_nombre(jugador1,jugador2);
    //Tablero->imprimir_tablero();
    if(play == "multijugador") {
        while (true) {
            cont += 1;
            cout << "------------- Turno de " << jugador1 << " -------------" << endl;
            cout << "Ingrese el inicio: " << endl;
            for (int &i: inicio)cin >> i;
            cout << "Ingrese el final: " << endl;
            for (int &i: final)cin >> i;
            Tablero->agregar_linia(movimiento(inicio, final));
            decifrando_laterales(movimiento(inicio, final), punto_return);
            punto = validando_laterales(punto_return, Tablero, letra_inicial(jugador1));
            Tablero->agregar_punto(punto, jugador1);
            Tablero->imprimir_tablero();

            cout << "------------- Turno de " << jugador2 << " -------------" << endl;
            cout << "Ingrese el inicio: " << endl;
            for (int &i: inicio)cin >> i;
            cout << "Ingrese el final: " << endl;
            for (int &i: final)cin >> i;
            Tablero->agregar_linia(movimiento(inicio, final));
            decifrando_laterales(movimiento(inicio, final), punto_return);
            punto = validando_laterales(punto_return, Tablero, letra_inicial(jugador2));
            Tablero->agregar_punto(punto, jugador2);
            Tablero->imprimir_tablero();
            if (cont == n_casillas)
                break;
        }
        if(Tablero->get_punto_jugador1() != Tablero->get_punto_jugador2()){
            cout<<"*======== GANADOR PRIMER PUESTO ========*"<<endl;
            if(Tablero->get_punto_jugador1() > Tablero->get_punto_jugador2()) {
                cout <<"      **** " << jugador1 << " ****" << endl;
                cout <<"      PUNTAJE "<<Tablero->get_punto_jugador1()<<" puntos."<<endl;
            }
            if(Tablero->get_punto_jugador1() < Tablero->get_punto_jugador2()) {
                cout <<"      **** " << jugador2 << " ****" << endl;
                cout <<"      PUNTAJE "<<Tablero->get_punto_jugador2()<<" puntos."<<endl;
            }
        }

        if(Tablero->get_punto_jugador1() == Tablero->get_punto_jugador2()) {
            cout<<"*======== !! EMPATE !! ========*"<<endl;
            cout <<"  PUNTAJE "<<Tablero->get_punto_jugador1()<<" puntos."<<endl;
            cout <<"  El publico pide revancha........!!!"<<endl;
        }
    }
    if(play =="un_solo_jugador"){
        while (true){
            // movimientos del usuario
            cont += 1;
            cout << "------------- Turno de " << jugador1 << " -------------" << endl;
            cout << "Ingrese el inicio: " << endl; // se pide que ingrese el inicio del punto
            for (int &i: inicio)cin >> i;
            cout << "Ingrese el final: " << endl;// se pide que ingrese el final del punto
            for (int &i: final)cin >> i;
            Tablero->agregar_linia(movimiento(inicio, final)); //---> se agrega el aspa en el punto designado
            decifrando_laterales(movimiento(inicio, final), punto_return); //--->decifra los puntos laterales
            punto = validando_laterales(punto_return, Tablero, letra_inicial(jugador1)); //--->valida los laterales para darle el puntaje
            Tablero->agregar_punto(punto, jugador1);//----> se agrega el punto si en caso halla cerrado un recuadro
            Tablero->imprimir_tablero();//----> se imprime el tablero

            // bot jugador ---> movimientos del la consola bot
            cout << "------------- Turno del " << jugador2 << " -------------" << endl;
            Tablero->agregar_linia(punto_alea(lado,Tablero));
            decifrando_laterales(movimiento(inicio, final), punto_return);
            punto = validando_laterales(punto_return, Tablero, letra_inicial(jugador2));
            Tablero->agregar_punto(punto, jugador2);
            Tablero->imprimir_tablero();
            if (cont == n_casillas)
                break;
        }
        if(Tablero->get_punto_jugador1() != Tablero->get_punto_jugador2()){
            cout<<"*======== GANADOR PRIMER PUESTO ========*"<<endl;
            if(Tablero->get_punto_jugador1() > Tablero->get_punto_jugador2()) {
                cout <<"      **** " << jugador1 << " ****" << endl;
                cout <<"      PUNTAJE "<<Tablero->get_punto_jugador1()<<" puntos."<<endl;
            }
            if(Tablero->get_punto_jugador1() < Tablero->get_punto_jugador2()) {
                cout <<"      **** " << jugador2 << " ****" << endl;
                cout <<"      PUNTAJE "<<Tablero->get_punto_jugador2()<<" puntos."<<endl;
            }
        }

        if(Tablero->get_punto_jugador1() == Tablero->get_punto_jugador2()) {
            cout<<"*======== !! EMPATE !! ========*"<<endl;
            cout <<"  PUNTAJE "<<Tablero->get_punto_jugador1()<<" puntos."<<endl;
            cout <<"  El publico pide revancha........!!!"<<endl;
        }

    }

}
void menu() {
    string opcion;
    string jugador1, jugador2;
    cout << "*========= BIENVENIDOS A DOTS AND BOXES ========*"<<endl;
    cout << "|               1. Tablero 6x6                  |"<< endl;
    cout << "|               2. Tablero 10 x 10              |"<< endl;
    cout << "|               0. Salir                        |"<< endl;
    cout << "|              * Seleccione la opcion:          |"<< endl;
    cout << "*===============================================*"<<endl;
    validar_dato(opcion,3);
    if(opcion =="1") {
        cout << "*========= TABLERO 6x6 ========*"<<endl;
        cout << "|     1. Un Solo jugador       |" << endl;
        cout << "|     2. Multijugador          |"<<endl;
        cout << "|     0. Volver al Menu        |"<<endl;
        cout << "|     Seleccione la opcion:    |"<< endl;
        cout << "*==============================*"<<endl;
        string opcion2;
        validar_dato(opcion2,3);
        if(opcion2 == "1"){
            jugador2 = "Bot";
            cout <<"*======= DOTS AND BOXES =======*"<<endl;
            cout <<"  Ingrese tu nombre: "<<endl;
            getline(cin,jugador1);
            cout <<"  !!ya casi esta listo......."<<endl;
            cout <<"!! preparando tablero 6 x 6 ......."<<endl;
            cout <<"*==============================*"<<endl;
            ejecutando_operaciones(11,30,jugador1,jugador2,"un_solo_jugador");

        }
        if(opcion2 == "2"){
            cout <<"*======= DOTS AND BOXES =======*"<<endl;
            cout <<"  Ingrese nombre de jugador 1: "<<endl;
            getline(cin,jugador1);
            cout <<"  Ingrese nombre de jugador 2: "<<endl;
            getline(cin,jugador2);
            cout <<"  !!ya casi esta listo......."<<endl;
            cout <<"!! preparando tablero 6 x 6 ......."<<endl;
            cout <<"*==============================*"<<endl;
            ejecutando_operaciones(11,30,jugador1,jugador2,"multijugador");
        }
        if(opcion2 == "0"){
            menu();
        }

    }
    if(opcion =="2") {
        cout << "1. Un Solo jugador" << endl;
        cout << "2. Multijugador "<<endl;
        cout << "0. Volver al Menu"<<endl;
        cout << "Seleccione la opcion: " << endl;
        string opcion3;
        validar_dato(opcion3,3);
        system("cls");
        if(opcion3 == "1"){
            jugador2 = "Bot";
            cout <<"*======= DOTS AND BOXES =======*"<<endl;
            cout <<"  Ingrese tu nombre: "<<endl;
            getline(cin,jugador1);
            cout <<"  !!ya casi esta listo......."<<endl;
            cout <<"!! preparando tablero 6 x 6 ......."<<endl;
            cout <<"*==============================*"<<endl;
            ejecutando_operaciones(19,60,jugador1,jugador2,"un_solo_jugador");

        }
        if(opcion3 == "2"){
            cout <<"*======= DOTS AND BOXES =======*"<<endl;
            cout <<"  Ingrese nombre de jugador 1: "<<endl;
            getline(cin,jugador1);
            cout <<"  Ingrese nombre de jugador 2: "<<endl;
            getline(cin,jugador2);
            cout <<"  !! ya casi esta listo......."<<endl;
            cout <<"!! preparando tablero 10 x 10 ......."<<endl;
            cout <<"*==============================*"<<endl;
            ejecutando_operaciones(19,60,jugador1,jugador2,"multijugador");
            //goo_juego(19,60);
        }
        if(opcion3 == "0"){
            menu();
        }
    }
    if(opcion == "0") {
        cout << "Saliendo del programa" << endl;
        exit(1);
    }


}





int main() {
    //ejecutando_operaciones(11,30,"Ivan","Lia");
    menu();

    return 0;
}
