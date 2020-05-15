//--capteur--
bool burst = 0;
int count = 1;
int cap_count = 0;
//--distance--
 unsigned long tim;
 unsigned long delta_tim;
 unsigned long tmp_prev;
float distance;

//--Moteur--
unsigned long count1 = 0;
 unsigned long etatH = 225; // theorique 150
bool sens = 0;
bool var_angle = true; // variation d'angle au bout de 10 mesures
int count_mes = 0;

ISR(TIMER1_OVF_vect) {
  TCNT1 = 65400;
  count1++;
 cap_count++;
  //mise a l'etat haut pendant un durée definie par etatH
  if (count1 <= etatH ) {
    PORTD = 255 & 0b10000000;
  } else {
    PORTD = 0 ;
  }

  //Apres un total de 20ms remise a 0 de count
  
    if (cap_count==10){
      if (count1 >= 20000) {
        count1 = 0;
        if(var_angle == true){
          if(sens == 0){
          etatH = etatH + 10;  
          }
          else {
            cap_count=0;
            etatH = etatH - 10;
          } 
        }
      }
    }
  
  
  //--capteur parts--
  if (burst == 0) {
    PORTB = 255 & 0b00000000;
    count++;
  }
  if (burst == 1) {
    PORTB = 255 & 0b00000010;
    burst = 0;
  }

  if (count == 10000) {
    burst = 1;
    count = 1;
  }
  tim++;
}

ISR(PCINT0_vect) {
  delta_tim = tim - tmp_prev;
  tmp_prev = tim;
  count_mes++;
}



void setup() {
  TCCR1A = 0;
  TCCR1B = 0b00000001; //PSA
  TIMSK1 = 1;
  sei();
  DDRD = 255;
  PCICR = 0b00000001;
  PCMSK0 = 0b00000001;
  DDRB = 255 & 0b11111110;
  Serial.begin(115200);
}

void loop() {
  //sens moteur capteur
 
  if (etatH == 225) {
    sens = 1;
  }
  if (etatH == 45)// theorique 150
  {
    sens = 0;
  }

// calcule des variables
  distance = (float)(delta_tim * 10 ^ 6) / 58;
  float theta = (etatH - 60)*(180/165);
  if (distance > 0 ) {
    Serial.print((tim / 10 ^ 5)/10000); // temps en seconde
    Serial.print(" | ");
    Serial.print(theta); // theta en degres
    Serial.print(" | ");
    Serial.print(var_angle);
    Serial.print(" | ");
    Serial.print(count_mes);
    Serial.print(" | ");
    Serial.println(distance); // distance en cm
  }

  // Comptage de 10 mesures
  if(count_mes >= 20){
    count_mes = 0;
    var_angle = true;
  }else{
    var_angle = false;
  }
}
