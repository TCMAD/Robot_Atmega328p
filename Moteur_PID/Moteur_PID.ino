//Vitesse désirée
int omega_d=0;
float  u;
float omega;
float omega_prev=0.0;
bool inc_dec_omega = true; // décide de l'incrémentation de omega
float delta_omega_prev = 0;
int temps_loop = 0;
//Paramètres correcteur
float Kp = 8;
float Kd = 1;
float Ki = 2;
float Kc = 0.5;

//variable de temps
unsigned long temps;
unsigned long delta_t1;
unsigned long tmp_prev1;
unsigned long delta_t2;
unsigned long tmp_prev2; 
float tmoy;
float tps_s_prev = 0;
//--------------------------------------------

int trou;

// variable d'état du moteur 
int etatP1, etatP1_prev;
int etatP2, etatP2_prev;
int set=0;
//-------------------------------------------
// tableau de capture de la vitesse
float v[10];
//--------------------------------------------

ISR(TIMER1_OVF_vect){
  PORTB^=(1<<PORTB1);
  TCNT1=65376; //Timer 10 microsecondes
  temps++;
}

ISR(PCINT2_vect){
  etatP1=PIND & 0b10000000; //Etat Pin 7
  //interruption du PIN 7
  if ( etatP1!=etatP1_prev){
    if(etatP1 > etatP1_prev){ // passage du front montant
      if (etatP1/128==(PIND & 0b01000000)/64){  // verification du sens de rotation 
        set=1; 
      }
      else 
      {
        set=-1;
      }
       delta_t1 = temps-tmp_prev1;
       trou++;
    }
    tmp_prev1=temps;
    etatP1_prev=etatP1;
  }
  
  etatP2=PIND & 0b01000000; // Etat Pin 6
  //interruption du PIN 6
  if (etatP2 != etatP2_prev){
    if (etatP2 > etatP2_prev){
      delta_t2 = temps-tmp_prev2;
    }
     tmp_prev2=temps;
     etatP2_prev=etatP2;
  }    
 }

  
void setup() {
  
  Serial.begin(115200);
  TCCR1A=0;
  TCCR1B=0b00000001;
  TIMSK1=0b00000001;
  sei();
  DDRB=255;
  PCICR=0b00000100; // Selection des PCINT  PCINT23..16
  PCMSK2=0b11000000; // Masque sur la pin 7 et 6
  DDRD = 0;
  //PWM TIMER2
  TCCR2A = 0b10000001;
  TCCR2B = 0b00000001;
  TCNT2 = 0;
}

void loop() {
  omega_prev = omega;
   tmoy = (float)1e-5*(delta_t1 + delta_t2)/2; // Moyenne des differences de temps
   if(tmoy == 0){
    omega = 0;
   }else{
    omega = (4.0/tmoy)*(2*M_PI)/360; // vitesse angulaire rad/s 
   }
   
   float tps_s = temps*1e-5; // Temps convertie en seconde en fonction du TIMER1 10 microsecondes

//   // Alternance toute les 2 secondes du PWM
//   if(tps_s >= tps_s_prev + 2){
//    OCR2A ^= 255;
//    tps_s_prev = tps_s;
//   }

//   // Capture de la décélération  
//   if(OCR2A == 0){
//    for(int i = 0; i < length(v);i
//   }

///////////////////////// Asservissement : controle de la vitesse désirée ///////////////////////////////////////  

//////////////// Incrémentation & décrementation toute les 1 sec
//   if( tps_s >= tps_s_prev + 1){ // Détection 1 seconde
//    tps_s_prev = tps_s;
//    if(inc_dec_omega == true){
//      omega_d = omega_d + 5; 
//      if(omega_d > 50){
//        inc_dec_omega = false; 
//      }
//    }
//   
//    if(inc_dec_omega == false){
//      omega_d = omega_d - 5; 
//      if(omega_d <= 0){
//        inc_dec_omega = true; 
//      }
//    
//    }
//   }

////////////// signal de commande avec un sinus
//omega_d=15*sin(6*temps*1e-5)+35;


////////////// signal de commande avec un sinus à 3Hz
//omega_d=(float) 15*sin(2*(M_PI)*4*temps*1e-5)+25;


/////////// signal carrée
if(tps_s >= tps_s_prev + 10){
  tps_s_prev = tps_s;
// switch(omega_d){
//  case 0: omega_d = 50;
//  case 50: omega_d = 0;
// }
  if(omega_d == 45){
    omega_d = 0;
  }else{
  omega_d = 45;
  }
}

////////////////// Dérivateur 
 float delta_omega = omega_d - omega;
 float d_delta_omega = (((delta_omega-delta_omega_prev)*1e5)/(temps-temps_loop));
 delta_omega_prev = delta_omega;
// temps_loop = temps;
 //u = Kc*(delta_omega*Kp+d_delta_omega*Kd); // Valeur du rapport cyclique

////////////////Intégrateur

float i_delta_omega = 0;
i_delta_omega = i_delta_omega + delta_omega*(temps - temps_loop)*1e-5;
float i_d_delta_omega = (((delta_omega-delta_omega_prev)*1e5)/(temps-temps_loop));
 temps_loop = temps;
 u =  delta_omega*Kp+i_delta_omega*Ki+d_delta_omega*Kd;//Kc*(delta_omega*Kp+d_delta_omega*Kd+i_delta_omega*Ki);
 



if(u>255){
  u=255;
}
if(u<0){
  u=0;
}
OCR2A=(int) u;
   //Dead reckoning : Remise a zero de la vitesse
   if(temps-tmp_prev1 > 5000){
    omega = 0;
   }

   
//   Serial.print();
//   Serial.print("\t");
  if(omega_prev - omega <= 5){
//    Serial.print(temps);
//       Serial.print("\t");
   Serial.print(omega); // vitesse angulaire rad/s
   Serial.print("\t");
   Serial.println(omega_d); 
  }
   
//   Serial.print("\t");
//   Serial.println(OCR2A);
}
