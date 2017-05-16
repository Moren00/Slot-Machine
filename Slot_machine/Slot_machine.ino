#include "Display.h"  //librerie create da me
#include "Play.h"
#include "Start.h"
#include "Bet.h"


#include <Wire.h>   //Librerie per display LCD
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

//----------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------!!!!!!!!VARIABILI!!!!!!!!!------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

int D1[11] = {53, 52, 51, 50, 36, 37, 38, 39, 40, 41, 14};   //PIN ASSOCIATI AI SINGOLI DISPLAY MESSI N VETTORI
int D2[11] = {49, 47, 48, 46, 29, 30, 31, 32, 33, 34, 35};
int D3[11] = {45, 44, 43, 42, 22, 23, 24, 25, 26, 27, 28};
int D4[11] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};

const int pulsante1 = A0;  //PLAY
const int pulsante2 = A1;  //BET
//const int pulsante3 = A2;  RETIRE        Tasti eliminati dalla configurazione originali causa problemi con il ciclo del 7 segmenti
//const int pulsante4 = A3;  INFO
const int pulsante5 = A4;  //START

int credito = 0;    //QUANTITA' DI DENARO DISPONIBILE

int puntate[4] = {50, 100, 150, 200};  //L'ENTITA' DELLE PUNTATE GIOCABILI
int puntata = puntate[0];

int PgInfo;   //VA AD INDICARE L'AVANZAMENTO DELLE "PAGINE" DI INFORMAZIONE SUL DISPLAY LCD

Display DIS1(D1);      //INIZIALIZZAZIONE OGGETTI RAPPRESENTANTI OGNI SINGOLO DISPLAY
Display DIS2(D2);
Display DIS3(D3);
Display DIS4(D4);

Play play(pulsante1);   //OGGETTO PULSANTE ATTO AL GIOCO

Start start(pulsante5); //PULSANTE ATTO AL REFILL CREDITO

Bet bet(pulsante2);     //PULSANTE PER INCREMENTARE LA PUNTATA

//Retire ret(pulsante3);  //PULSANTE PER "RITIRARE" LA SOMMA VINTA (RINIZIA IL GIOCO)

hd44780_I2Cexp LCD;  //Oggetto collegato al display LCD

const int LCD_ROWS = 2;  //Struttura del display (righe e colonne)
const int LCD_COLS = 16;

    //serie di flag per fare un clear una sola volta del display
  bool milleOver;          //settata se credito>1000
  bool cinquantaPun;  //settata se puntat = 50
  bool cinquantaCre;   //settata se credito = 50

//----------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------!!!!!!!!SETUP E LOOP!!!!!!!!!!!!------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

void setup() {

  //Serial.begin(9600);

  LCD.begin(LCD_COLS, LCD_ROWS); //Inizializzazione LCD

  Info();
    
}

void loop() {

    StandardPg();  //Pagina Iniziale e standard di gioco
    
    Refill();

    Punta();
    //Serial.println(puntata);
    if(credito > 0 && credito >= puntata) { //Per giocare è necessario avere credito e la puntata non deve superare il credito
      Gioca();
    }
    
    if(credito == 0) {  //Quando il credito va a 0 il display indica tutti zeri
      Restart();
    }
    
    Output();

    Serial.println(credito);
}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------!!!!!!!!FUNZIONI!!!!!!!!!------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
void Gioca() {
  
  if(play.Read(pulsante1)== LOW && play.block==false) {  //Premendo il pulsante vengono randomizzati i numeri
    
    randomSeed(millis());
    
    DIS1.Random();   //estrazione numeri
    DIS2.Random();
    DIS3.Random();
    DIS4.Random();
    
    play.block = true;  //blocco attivo

    ControlloVincite();
  }
  
  else if (play.Read(pulsante1)== HIGH && play.block==true) {  //Riasciando il pulsante è possibile ripremerlo e riestrarre numeri
    play.block = false;
  }

}

void Refill() {  //SIMULAZIONE INSERIMENTO MONETA
  
  if(start.Read(pulsante5)== LOW && start.block==false && credito == 0) {   //TIPICA STRUTTURA DI BLOCCO RIPETIZIONE A PRESSIONE
    credito = 200;
    start.block = true;
  }
  else if (start.Read(pulsante5)== HIGH && start.block==true) {  //Riasciando il pulsante è possibile ripremerlo e riestrarre numeri
    start.block = false;
  }
  
}

void Punta() {                //Funzione per gestire la selezione del valore da puntare
  if(bet.Read(pulsante2)== LOW && bet.block==false) {
    bet.select++;
    if(bet.select == 4) {
      bet.select = 0;  
    }
    puntata = puntate[bet.select];
    bet.block = true;
  }
  else if(bet.Read(pulsante2)== HIGH && bet.block==true){
    bet.block = false;
  }
}

void Output() {    //Raccoglimento di tutte le uscite
  DIS1.Output();
  DIS2.Output();
  DIS3.Output();
  DIS4.Output();
}

void Restart() {  //Raccoglimento di tutti i restart
  DIS1.Restart();
  DIS2.Restart();
  DIS3.Restart();
  DIS4.Restart();
}

void StandardPg() {  //Pagina standard o di gioco comune
  
 
    if(credito >= 1000) {
      milleOver = true;
    }
    if(credito<1000 && milleOver == true) {
      LCD.clear();
      LCD.setCursor(0,0);
      LCD.print("Credito = ");
      LCD.print(credito);
      LCD.setCursor(0,1);
      LCD.print("Bet = ");
      LCD.print(puntata);
      milleOver = false;
    }
    if(credito == 50 || puntata == 50) { 
      if(credito == 50) {  //essendo un valore di due cifre e gli altri di tre capita di visualizzare 500 quindi di cancella e riscrive
        LCD.clear();
        LCD.setCursor(0,0);
        LCD.print("Credito = ");
        LCD.print(credito);
        LCD.setCursor(0,1);
        LCD.print("Bet = ");
        LCD.print(puntata);
      }
      if(puntata == 50) {
        LCD.clear();
        LCD.setCursor(9,1);
        LCD.print(' ');
        LCD.setCursor(0,0);
        LCD.print("Credito = ");
        LCD.print(credito);
        LCD.setCursor(0,1);
        LCD.print("Bet = ");
        LCD.print(puntata);
      }
    }
    else {
      cinquantaCre = false;
      cinquantaPun = false;
      LCD.setCursor(0,0);
      LCD.print("Credito = ");
      LCD.print(credito);
      LCD.setCursor(0,1);
      LCD.print("Bet = ");
      LCD.print(puntata);
    }
  
  
}


void Info() { //Regole a tutela dell'utente
  const int Time = 5000;              //PAGINA 1
  LCD.setCursor(0,0);
  LCD.print("Gioco vietato ai");
  LCD.setCursor(0,1);
  LCD.print("minori di 18");
  delay(Time);
  LCD.clear();
  
  LCD.setCursor(0,0);              //PAGINA 2
  LCD.print("Fai tris o poker");
  LCD.setCursor(0,1);
  LCD.print("per vincere EURO");
  delay(Time);
  LCD.clear();

  LCD.setCursor(0,0);              //PAGINA 3
  LCD.print("Play: estrai num");
  LCD.setCursor(0,1);
  LCD.print("Bet: puntata up");
  delay(Time);
  LCD.clear();

  LCD.setCursor(0,0);             //PAGINA 4
  LCD.print("Start: iniziare");
  LCD.setCursor(0,1);
  LCD.print("Divertiti!");
  delay(Time);
  LCD.clear();

  LCD.setCursor(0,0);               //PAGINA 5
  LCD.print("Gioca con");
  LCD.setCursor(0,1);
  LCD.print("la testa");
  delay(Time);
  LCD.clear();
}


void ControlloVincite() {  //Controllando tutte le possibili combinazioni
  int multi=0;  //variabile che memorizza tris e poker sottoforma di molti plicatore

  //-----------------------Prima riga DIS1---------------------------------
  
  if(DIS1.N1 == DIS1.N2 && DIS1.N2 == DIS1.N3 && DIS1.N3 == DIS1.N4) {        //ORIZZONTALI
    multi += puntata*2;  
  }
  else if(DIS1.N1 == DIS1.N2 && DIS1.N2 == DIS1.N3) {    //se non ci sono poker provare con i tris
    multi += puntata;
  }
  else if(DIS1.N2 == DIS1.N3 && DIS1.N3 == DIS1.N4) {
    multi += puntata;
  }
 //-----------------------Seconda riga DIS2---------------------------------
 
  if(DIS2.N1 == DIS2.N2 && DIS2.N2 == DIS2.N3 && DIS2.N3 == DIS2.N4) {
    multi += puntata*2;   
  }
  else if(DIS2.N1 == DIS2.N2 && DIS2.N2 == DIS2.N3) {
    multi += puntata;
  }
  else if(DIS2.N2 == DIS2.N3 && DIS2.N3 == DIS2.N4) {
    multi += puntata;
  }

 //----------------------Terza riga DIS3-----------------------------------
  if(DIS3.N1 == DIS3.N2 && DIS3.N2 == DIS3.N3 && DIS3.N3 == DIS3.N4) {
    multi += puntata*2;    
  }
  else if(DIS3.N1 == DIS3.N2 && DIS3.N2 == DIS3.N3) {
    multi += puntata;
  }
  else if(DIS3.N2 == DIS3.N3 && DIS3.N3 == DIS3.N4) {
    multi += puntata;
  }

 //---------------------Quarta riga DIS4-----------------------------------
  if(DIS4.N1 == DIS4.N2 && DIS4.N2 == DIS4.N3 && DIS4.N3 == DIS4.N4) {
    multi += puntata*2;  
  }
  else if(DIS4.N1 == DIS4.N2 && DIS4.N2 == DIS4.N3) {
    multi += puntata;
  }
  else if(DIS4.N2 == DIS4.N3 && DIS4.N3 == DIS4.N4) {
    multi += puntata;
  }

 //---------------------Prima colonna N1-----------------------------------
  if(DIS1.N1 == DIS2.N1 && DIS2.N1 == DIS3.N1 && DIS3.N1 == DIS4.N1) {       //VERTICALI
    multi += puntata*2;
  }
  else if(DIS1.N1 == DIS2.N1 && DIS2.N1 == DIS3.N1) {
    multi += puntata;
  }
  else if(DIS2.N1 == DIS3.N1 && DIS3.N1 == DIS4.N1) {
    multi += puntata;
  }

 //---------------------Seconda colonna N2--------------------------------
  if(DIS1.N2 == DIS2.N2 && DIS2.N2 == DIS3.N2 && DIS3.N2 == DIS4.N2) {       
    multi += puntata*2;
  }
  else if(DIS1.N2 == DIS2.N2 && DIS2.N2 == DIS3.N2) {
    multi += puntata;
  }
  else if(DIS2.N2 == DIS3.N2 && DIS3.N2 == DIS4.N2) {
    multi += puntata;
  }

 //---------------------Terza colonna N3----------------------------------
  if(DIS1.N3 == DIS2.N3 && DIS2.N3 == DIS3.N3 && DIS3.N3 == DIS4.N3) {       
    multi += puntata*2;
  }
  else if(DIS1.N3 == DIS2.N3 && DIS2.N3 == DIS3.N3) {
    multi += puntata;
  }
  else if(DIS2.N3 == DIS3.N3 && DIS3.N3 == DIS4.N3) {
    multi += puntata;
  }
  
 //--------------------Quarta colonna N4----------------------------------
  if(DIS1.N4 == DIS2.N4 && DIS2.N4 == DIS3.N4 && DIS3.N4 == DIS4.N4) {       
    multi += puntata*2;
  }
  else if(DIS1.N4 == DIS2.N4 && DIS2.N4 == DIS3.N4) {
    multi += puntata;
  }
  else if(DIS2.N4 == DIS3.N4 && DIS3.N4 == DIS4.N4) {
    multi += puntata;
  }

 //--------------------Obliquo da sx a dx--------------------------------
  if(DIS1.N1 == DIS2.N2 && DIS2.N2 == DIS3.N3 && DIS3.N3 == DIS4.N4) {       //OBLIQUI
    multi += puntata*2;
  }
  else if(DIS1.N1 == DIS2.N2 && DIS2.N2 == DIS3.N3) {
    multi += puntata;
  }
  else if(DIS2.N2 == DIS3.N3 && DIS3.N3 == DIS4.N4) {
    multi += puntata;
  }

 //--------------------Obliquo da dx a sx--------------------------------
  if(DIS1.N4 == DIS2.N3 && DIS2.N3 == DIS3.N2 && DIS3.N2 == DIS4.N1) {      
    multi += puntata*2;
  }
  else if(DIS1.N4 == DIS2.N3 && DIS2.N3 == DIS3.N2) {
    multi += puntata;
  }
  else if(DIS2.N3 == DIS3.N2 && DIS3.N2 == DIS4.N1) {
    multi +=puntata;
  }
  //-----------------SERIE DI OBLIQUI SOLO TRIS-------------------------
  if(DIS2.N1 == DIS3.N2 && DIS3.N2 == DIS4.N3) {
    multi += puntata;
  }
  if(DIS1.N2 == DIS2.N3 && DIS2.N3 == DIS3.N4) {
    multi += puntata;
  }
  if(DIS1.N3 == DIS2.N2 && DIS2.N2 == DIS3.N3) {
    multi += puntata;
  }
  if(DIS2.N4 == DIS3.N3 && DIS3.N3 == DIS4.N2) {
    multi += puntata;
  }

 if(multi > 0) {          //verifica di valore con moltiplicazione e sottrazione
    credito += multi;  
  }
  else {
    credito -= puntata;
  }
  
}



