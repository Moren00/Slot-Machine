class Display {
 // --------------------------------------------------PRIVATE--------------------------------------------------------------
   private:         //Pin messi in private visto che non saranno utili all'esterno della classe stessa
   int P1,P2,P3,P4,PA,PB,PC,PD,PE,PF,PG;
  
   void Zero(int linea) {   //Accensione dei led sul display corrispondenti al numero
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, HIGH);
    digitalWrite(PE, HIGH);
    digitalWrite(PF, HIGH);
    digitalWrite(PG, LOW);
  }
  
  void Uno(int linea) {
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, LOW);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, LOW);
    digitalWrite(PE, LOW);
    digitalWrite(PF, LOW);
    digitalWrite(PG, LOW);
  }
  
  void Due(int linea) {
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, LOW);
    digitalWrite(PD, HIGH);
    digitalWrite(PE, HIGH);
    digitalWrite(PF, LOW);
    digitalWrite(PG, HIGH);
  }
  
  void Tre(int linea) {
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, HIGH);
    digitalWrite(PE, LOW);
    digitalWrite(PF, LOW);
    digitalWrite(PG, HIGH);
  }
  
  void Quattro(int linea) {
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, LOW);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, LOW);
    digitalWrite(PE, LOW);
    digitalWrite(PF, HIGH);
    digitalWrite(PG, HIGH);
  }
  
  void Cinque(int linea) {
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, LOW);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, HIGH);
    digitalWrite(PE, LOW);
    digitalWrite(PF, HIGH);
    digitalWrite(PG, HIGH);
  }
  
  void Sei(int linea) {
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, LOW);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, HIGH);
    digitalWrite(PE, HIGH);
    digitalWrite(PF, HIGH);
    digitalWrite(PG, HIGH);
  }
  
  void Sette(int linea) {
    Reset();
    digitalWrite(linea,LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, LOW);
    digitalWrite(PE, LOW);
    digitalWrite(PF, LOW);
    digitalWrite(PG, LOW);
  }
  
  void Otto(int linea) {
    Reset();
    digitalWrite(linea ,LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, HIGH);
    digitalWrite(PE, HIGH);
    digitalWrite(PF, HIGH);
    digitalWrite(PG, HIGH);
  }
  
  void Nove(int linea) {
    Reset();
    digitalWrite(linea, LOW);
    digitalWrite(PA, HIGH);
    digitalWrite(PB, HIGH);
    digitalWrite(PC, HIGH);
    digitalWrite(PD, HIGH);
    digitalWrite(PE, LOW);
    digitalWrite(PF, HIGH);
    digitalWrite(PG, HIGH);
  }

  void Scelta(int n, int linea) {  //scelta del numero esatratto da scrivere
    
    switch(n){
      case 0:
        Zero(linea);
        break;
      case 1:
        Uno(linea);
        break;
      case 2:
        Due(linea);
        break;
      case 3:
        Tre(linea);
        break;
      case 4:
        Quattro(linea);
        break;
      case 5:
        Cinque(linea);
        break;
      case 6:
        Sei(linea);
        break;
      case 7:
        Sette(linea);
        break;
      case 8:
        Otto(linea);
        break;
      case 9:
        Nove(linea);
        break;
      default:
        break;
    }
  }

//-------------------------------------------------PUBLIC----------------------------------------------------------------------------   
   public:         //I numeri casuali saranno messi disponibili all'esterno cos� come i metodi
   int N1,N2,N3,N4;

   Display(int P[]) {   //costruttore utilizzato solamente per il set dei pin fornendo un array in input
     P1=P[0];
     P2=P[1]; 
     P3=P[2]; 
     P4=P[3]; 
     PA=P[4]; 
     PF=P[5]; 
     PB=P[6]; 
     PE=P[7]; 
     PD=P[8]; 
     PC=P[9]; 
     PG=P[10];  
     for(int i; i<12; i++) {
        pinMode(P[i], OUTPUT);
     }
     
   }

   void Reset(){  //funzione per resettare il display per poter fare una nuova stampa
      
        digitalWrite(P1, HIGH);

        digitalWrite(P2, HIGH);

        digitalWrite(P3, HIGH);
  
        digitalWrite(P4, HIGH);
      
   }

   void Random() { //generazione dei numeri casuali
     N1 = int(random(10));
     N2 = int(random(10));
     N3 = int(random(10));
     N4 = int(random(10));
   }

   void Output() { //Stampa sul display dei risultati ottenuti
     Scelta(N1, P1);
     delayMicroseconds(600);
     Scelta(N2, P2);
     delayMicroseconds(600);
     Scelta(N3, P3);
     delayMicroseconds(600);
     Scelta(N4, P4);
     delayMicroseconds(600);
     Reset();  //Modifica in modo da avere un colore uniforme a tutti i display
   }

   void Restart() {
    N1 = 0;
    N2 = 0;
    N3 = 0;
    N4 = 0;
   }
   
   
};

