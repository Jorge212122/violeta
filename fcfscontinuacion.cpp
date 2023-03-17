#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <queue>
#include <string>

using namespace std;

struct Procesos{
    int id = 0, ope = 0, num1 = 0, num2 = 0, tme = 0, TT = 0, TTB = 0, estado = 0, TLLE = 0, TFIN = 0, TSER = 0, TESP = 0, TRET = 0, TRES = 0, Res = 0;
    string operacion = "";
    bool error = false, respuesta = false, tabla = false, bloqueado = false, listo = false, terminado = false;
};

int inicio(){
    srand(time(NULL));
    int auxentrada = 0, primero = 0, nprocesos = 0, idglobal = 1, clock = 0, finalizados = 0, pos = 0, s, limite = 4, contaux = 0;
    char entrada;
    bool pausa = false, vacio = false;
    queue<int>almacen;
    queue<int>cola;
    queue<int>colabloq;
    srand(time(NULL));

    cout<<"\n-----FCFS-----"<<endl;
    cout << "Ingrese el numero de procesos: ";
    cin >> nprocesos;
    system("cls");

    cout << endl;
    Procesos proceso[100], procesoaux[100];

    for(int i = 0; i < nprocesos; i++){ //en este for se estan inicializando los datos de las variables
        proceso[i].ope = 1+rand()%(6-1);
        proceso[i].num1 = 1+rand()%(101-1);
        proceso[i].num2 = 1+rand()%(101-1);
        proceso[i].tme = 5+rand()%(16-5);
        proceso[i].TT = 0;
        proceso[i].id = idglobal;
        almacen.push(i);
        if(proceso[i].ope == 1){
            proceso[i].Res = (proceso[i].num1 + proceso[i].num2);
            proceso[i].operacion = to_string(proceso[i].num1) + " + " + to_string(proceso[i].num2);
        }
        else if(proceso[i].ope == 2){
            proceso[i].Res = (proceso[i].num1 - proceso[i].num2);
            proceso[i].operacion = to_string(proceso[i].num1) + " - " + to_string(proceso[i].num2);
        }
        else if(proceso[i].ope == 3){
            proceso[i].Res = (proceso[i].num1 * proceso[i].num2);
            proceso[i].operacion = to_string(proceso[i].num1) + " * " + to_string(proceso[i].num2);
        }
        else if(proceso[i].ope == 4){
            proceso[i].Res = (proceso[i].num1 / proceso[i].num2);
            proceso[i].operacion = to_string(proceso[i].num1) + " / " + to_string(proceso[i].num2);
        }
        else if(proceso[i].ope == 5){
            proceso[i].Res = (proceso[i].num1 % proceso[i].num2);
            proceso[i].operacion = to_string(proceso[i].num1) + " % " + to_string(proceso[i].num2);
        }
        idglobal++;
    }

    int mem = 0, auxMem = 0, actual = 0, timeT = 0, timeME = 0, auxPos = 0, listos = 0, nuevos = 0, auxnuevos = 4;

    while(finalizados != nprocesos){

        if((nprocesos - finalizados) < 4){
            auxMem = nprocesos - finalizados;
        }else{
            auxMem = 4;
        }

        while(mem < auxMem){
            primero = almacen.front();
            almacen.pop();
            cola.push(primero);
            mem++;

            //Tiempo de llegada
            proceso[primero].TLLE = clock;
        }

        if(cola.size() > 0){
            listos = cola.size();
            actual = cola.front();
            cola.pop();
            timeT = proceso[actual].TT;
            timeME = proceso[actual].tme;
        }else{
            listos = 0;
            timeME = 1;
            timeT = 0;
        }

        for(s = timeT; s < timeME; s++){ //contador de segundos
            nuevos = (nprocesos - finalizados) - auxnuevos;
            if(nuevos <= 0){
                cout<<"NUEVOS: 0"<<endl;
            }else{
                cout<<"NUEVOS: "<< nuevos <<endl;
            }
            cout<<"LISTOS:"<<"\nID:\tTME\tTT"<<endl; //aqui inicia el proceso de listos
            if(cola.size()< 3 && cola.size()>0 && almacen.size()>0 && vacio == false){
                int auxalma = almacen.front();
                almacen.pop();
                cola.push(auxalma);
            }
            for(int b = 0; b < cola.size(); b++){// se imprimen los datos listos de la cola
                auxPos = cola.front();
                cola.pop();
                cola.push(auxPos);
                proceso[auxPos].bloqueado = false;
                proceso[auxPos].listo = true;
                cout << proceso[auxPos].id << "\t" << proceso[auxPos].tme <<"\t"<< proceso[auxPos].TT << endl;
            };

            cout<<"\nBLOQUEADOS: \nID:\tTTB:"<<endl;

            int sizeCola = colabloq.size();

            for(int b = 0; b < sizeCola; b++){
                auxPos = colabloq.front();
                colabloq.pop();
                cout<<proceso[auxPos].id<<"\t"<<proceso[auxPos].TTB<<endl;

                if((proceso[auxPos].TTB) == 1){
                cola.push(auxPos);
                }else{
                colabloq.push(auxPos);
                }
                proceso[auxPos].TTB--;
            }

            cout<<"\n\nPROCESO EN EJECUCION: ";
            if(listos > 0){
                int ejecucion = actual;
                proceso[ejecucion].tabla = true;
                cout<< "\nID:\t\t" <<proceso[ejecucion].id<<endl;
                cout<< "OPE:\t\t" <<proceso[ejecucion].operacion<<endl;
                cout<<"TME:\t\t"<<proceso[ejecucion].tme<<endl;
                cout<<"TT:\t\t" << s <<endl;
                cout<<"TR:\t\t" << proceso[ejecucion].tme - s <<endl;
            }else{
                cout<<"\nTodos los procesos bloqueados"<<endl;
            }

            cout<<"\nTERMINADOS:"<<endl;
            cout<< "ID:\t OPE:\t\t RES:\n"<<endl;
            for(int j=0; j < finalizados; j++){
                if(procesoaux[j].error == true){
                    cout<< procesoaux[j].id<<"        "<<proceso[j].operacion<<"\t " << "Error en el proceso" << endl;
                }
                else if(procesoaux[j].error == false){
                    cout<< procesoaux[j].id<<"        "<<proceso[j].operacion<<"\t "<<proceso[j].Res<<endl;
                }
            }

            //tiempo respuesta
            if(proceso[actual].respuesta == false){
                proceso[actual].TRES = clock - proceso[actual].TLLE;
                proceso[actual].respuesta = true;
            }
            //tiempo servicio
            if(listos > 0){
                proceso[actual].TSER = s;
            }

            //tiempo finalizacion, retorno y espera
            if(s == (proceso[actual].tme-1)){
                proceso[actual].TFIN = clock+1;
                proceso[actual].TRET = (proceso[actual].TFIN - proceso[actual].TLLE);
                proceso[actual].TESP = proceso[actual].TRET - (proceso[actual].TSER+1);
                proceso[actual].tabla = true;
            }

            cout<<"\nCONTADOR GENERAL: "<< clock <<endl;
            Sleep(1000);
            auxentrada = 0;
            if(kbhit() != 0){
                entrada = getch();
                entrada = toupper(entrada);
                if(entrada == 'I' && listos > 0){
                    //validacion para no permitir que se registre otro tiempo de llegada despues de bloquear
                    auxentrada = 1;
                    proceso[actual].bloqueado = true;
                    proceso[actual].tabla = false;
                    proceso[actual].listo = false;
                    proceso[actual].terminado = false;
                    proceso[actual].TT = s;
                    proceso[actual].TTB = 8;
                    colabloq.push(actual);
                    s = proceso[actual].tme;
                }
                else if(entrada == 'N'){
                    int pronuevos = nprocesos;
                    proceso[pronuevos].ope = 1+rand()%(6-1);
                    proceso[pronuevos].num1 = 1+rand()%(101-1);
                    proceso[pronuevos].num2 = 1+rand()%(101-1);
                    proceso[pronuevos].tme = 5+rand()%(16-5);
                    proceso[pronuevos].TT = 0;
                    proceso[pronuevos].id = idglobal;
                    almacen.push(pronuevos);
                    idglobal++;
                    nprocesos++;

                    if((nprocesos - finalizados) < 4){
                        auxMem = nprocesos - finalizados;
                    }else{
                        auxMem = 4;
                    }

                    while(mem < auxMem){
                        primero = almacen.front();
                        almacen.pop();
                        cola.push(primero);
                        mem++;

                        //Tiempo de llegada
                        proceso[primero].TLLE = clock;
                    }

                }
                else if (entrada == 'T'){
                    system("cls");
                    cout << "\n\t\t\t\t\t\tProcesamiento FCFS\n" << endl;
                    cout << "\t\t\t\t\t\tTabla de Procesos " << endl << endl;
                    cout << "\t\t\t\t\t\tContador Global: " << clock << endl << endl;
                    cout << "ID:\tTME:\tRES:\tOPE:\tDato 1:\tDato 2:\t   TT:\tESTADO:\t\tTBLO:\tTLLE:\tTFIN:\tTSER:\tTESP:\tTRET:\tTRES:"<<endl;
                    for(int j = 0; j < nprocesos; j++){
                        if(proceso[j].error == true){
                            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<"Error"<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<proceso[j].TT<<"\t"<<"Terminado"<<"\t"<<"--"<<"\t"<<proceso[j].TLLE<<"\t"<<proceso[j].TFIN<<"\t"<<proceso[j].TT<<"\t"<<proceso[j].TESP<<"\t"<<proceso[j].TRET<<"\t"<<proceso[j].TRES<<endl;
                        }
                        else if(proceso[j].tabla == true){
                            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<"--"<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<proceso[j].TT<<"\t"<<"Ejecutandose"<<"\t"<<"--"<<"\t"<<proceso[j].TLLE<<"\t"<<"--"<<"\t"<<proceso[j].TT<<"\t"<<(clock-(proceso[j].TLLE - proceso[j].TT))<<"\t"<<"--"<<"\t"<<proceso[j].TRES<<endl;
                        }
                        else if(proceso[j].bloqueado == true){
                            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<"--"<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<proceso[j].TT<<"\t"<<"Bloqueado   "<<"\t"<<(8-proceso[j].TTB)<<"\t"<<proceso[j].TLLE<<"\t"<<"--"<<"\t"<<proceso[j].TT<<"\t"<<proceso[j].TESP<<"\t"<<"--"<<"\t"<<proceso[j].TRES<<endl;
                        }
                        else if(proceso[j].listo == true){
                            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<"--"<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<proceso[j].TT<<"\t"<<"Listo       "<<"\t"<<"--"<<"\t"<<proceso[j].TLLE<<"\t"<<"--"<<"\t"<<proceso[j].TT<<"\t"<<proceso[j].TESP<<"\t"<<"--"<<"\t"<<"--"<<endl;
                        }
                        else if(proceso[j].terminado == true && proceso[j].error == false){
                            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<proceso[j].Res<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<proceso[j].TT<<"\t"<<"Terminado   "<<"\t"<<"--"<<"\t"<<proceso[j].TLLE<<"\t"<<proceso[j].TFIN<<"\t"<<proceso[j].TT<<"\t"<<proceso[j].TESP<<"\t"<<proceso[j].TRET<<"\t"<<proceso[j].TRES<<endl;
                        }
                        else{
                            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<"--"<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<"--"<<"\t"<<"Nuevos      "<<"\t"<<"--"<<"\t"<<"--"<<"\t"<<"--"<<"\t"<<"--"<<"\t"<<"--"<<"\t"<<"--"<<"\t"<<"--"<<endl;
                        }
                    }
                    while(pausa == false){
                        if(kbhit() != 0){
                            entrada = getch();
                            entrada = toupper(entrada);
                            if(entrada == 'C'){
                                pausa = true;
                            }
                        }
                    }
                    pausa = false;
                    //system("pause");
                }
                else if(entrada =='E' && listos > 0){
                    auxentrada = 2;
                    proceso[actual].TT = s;
                    s = proceso[actual].tme;
                    proceso[actual].tabla = false;
                    proceso[actual].error = true;
                    proceso[actual].listo = false;
                    proceso[actual].terminado = true;
                    //tiempo finalizacion, retorno y espera
                    proceso[actual].TFIN = clock;
                    proceso[actual].TRET = (proceso[actual].TFIN - proceso[actual].TLLE);
                    proceso[actual].TESP = proceso[actual].TRET - proceso[actual].TSER;
                }
                else if(entrada == 'P'){
                    while(pausa == false){
                        if(kbhit() != 0){
                            entrada = getch();
                            entrada = toupper(entrada);
                            if(entrada == 'C'){
                                pausa = true;
                            }
                        }
                    }
                    pausa = false;
                }
            }
            if(nprocesos < 3){
                vacio = false;
            }else{
                vacio = true;
            }
            clock++;
            system("cls");
        }

        if(auxentrada == 0 && listos > 0){
            proceso[actual].TSER = s;
            proceso[actual].TT = s;
        }

        s = 0;

        if(auxentrada != 1 && listos > 0){
            procesoaux[finalizados] = proceso[actual];
            finalizados++;
            mem--;
        }
        proceso[actual].terminado = true;
        proceso[actual].tabla = false;
        auxentrada = 0;
        actual = 0;
    }
    system("cls");

    cout<<"NUEVOS: 0" <<endl;
    cout<<"LISTOS: 0"<<endl <<endl;
    cout<<"BLOQUEADOS: 0"<<endl;
    cout<<"\n\nPROCESO EN EJECUCION: " << endl << endl;
    cout<<"\nTERMINADOS:" << endl;

    cout<< "ID:\t OPE:\t\t RES:\n"<<endl;
    for(int j=0; j < finalizados; j++){
        if(procesoaux[j].error == true){
            cout<< procesoaux[j].id<<"        "<<proceso[j].operacion<<"\t " << "Error en el proceso" << endl;
        }
        else if(procesoaux[j].error == false){
            cout<< procesoaux[j].id<<"        "<<proceso[j].operacion<<"\t "<< proceso[j].Res<<endl;
        }
    }
    cout<<"\nCONTADOR GENERAL: "<<clock<<endl;
    system("pause");
    system("cls");

    cout << "\n\t\t\t\t\t\tProcesamiento FCFS\n" << endl;
    cout << "ID:\tTME:\tRES:\tOPE:\tDato 1:\tDato 2:\t   TT:\tESTADO:\t\tTBLO:\tTLLE:\tTFIN:\tTSER:\tTESP:\tTRET:\tTRES:"<<endl;
    for(int j = 0; j < nprocesos; j++){
        if(proceso[j].error == true){
            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<"Error"<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<proceso[j].TT<<"\t"<<"Terminado"<<"\t"<<"--"<<"\t"<<proceso[j].TLLE<<"\t"<<proceso[j].TFIN<<"\t"<<proceso[j].TT<<"\t"<<proceso[j].TESP<<"\t"<<proceso[j].TRET<<"\t"<<proceso[j].TRES<<endl;
        }else{
            //cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<proceso[j].Res<<"\t"<<proceso[j].operacion<<"\t   "<<proceso[j].TT<<"\t"<<"Terminado"<<"\t"<<proceso[j].TLLE<<"\t"<<proceso[j].TFIN<<"\t"<<proceso[j].TT<<"\t"<<proceso[j].TESP<<"\t"<<proceso[j].TRET<<"\t"<<proceso[j].TRES<<endl;
            cout<<proceso[j].id<<"\t"<<proceso[j].tme<<"\t"<<proceso[j].Res<<"\t"<<proceso[j].operacion<<"\t"<<proceso[j].num1<<"\t"<<proceso[j].num2<<"\t   "<<proceso[j].TT<<"\t"<<"Terminado   "<<"\t"<<"--"<<"\t"<<proceso[j].TLLE<<"\t"<<proceso[j].TFIN<<"\t"<<proceso[j].TT<<"\t"<<proceso[j].TESP<<"\t"<<proceso[j].TRET<<"\t"<<proceso[j].TRES<<endl;
        }
    }
}

int main() {
    inicio();
    system("pause");
    return 0;
}

//(s-(proceso[j].TLLE - proceso[j].TT))
