class Play {

  private:
  int pin;
  
  public:
  bool state;
  bool block;   //per evitare che il pulsante rimanendo premuto possa eseguire il suo compito più volta con una sola pressione
  
  Play(const int p) {  //costruttore
    set(p);
    pin = p;
    block = false;
  }

  void set(const int pin) {  //settaggio dei pin
    pinMode(pin, INPUT);  
  }

  int Read(const int pin) {  //lettura dello stato con ritorno del valore
    int state = digitalRead(pin);
    return state;
  }
  
};
