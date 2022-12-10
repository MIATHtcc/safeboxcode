#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

struct MusicStruct {
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
}Music;

struct LengthStruct {
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
}Length;

int tempo = 400;


LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);

int pinoServo = 13;
int pinoServo2 = 3;
String senha ="3A6B";
String fecharsenha= "1234";
String buf = "";
Servo s, s2;
int i =0;
int ledA = 2;
int ledV = 1;
int buzzer_pin = 12;

const byte ROWS = 4;
const byte COLS = 4;
char keys [ROWS] [COLS] = 
 {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins [ROWS] = {11, 10, 9, 8};
byte colPins [COLS] = {7, 6, 5, 4};
Keypad keypad = Keypad (makeKeymap (keys),
                              rowPins, colPins, ROWS, COLS);

void setup()
{
 Serial.begin(9600); 
 s.attach(pinoServo);
 s2.attach(pinoServo2);
 s.write(0);
 s2.write(0); 
 pinMode(ledA, OUTPUT);
 pinMode(ledV, OUTPUT);
 pinMode(buzzer_pin, OUTPUT);
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("CARREGANDO...");
 delay(1500);
 lcd.setCursor(0,0);
 lcd.print("Pressione *  ");
 lcd.setCursor(0,1);
 lcd.print("para iniciar ");
}

void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}

void loop()
{
char key = keypad.getKey();
 if (key != NO_KEY) {
   if (key == '*'){
     i = 0;
     lcd.clear();
     buf = "";
     password();
 } 
 }
}

void password(){
  while(i<4){
  lcd.setCursor(0,0);
  lcd.print("SENHA: ");
    
  char key = keypad.getKey();
    if(key != NO_KEY){
    buf+= key;
      lcd.print(buf);
    i++;
    }
  }
  if(buf == senha){
  lcd.setCursor(0,1);
  lcd.print("SENHA CORRETA");
    digitalWrite(ledA, HIGH);
    delay(500);
    s.write(180);
    s2.write(180);
    delay(30);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pressione *");
    lcd.setCursor(0,1);
    lcd.print("novamente ");
    
    setTone(buzzer_pin, Music.B, tempo * Length.one);
  setTone(buzzer_pin, Music.E, tempo * Length.one_half);
  setTone(buzzer_pin, Music.G, tempo * Length.half);
  setTone(buzzer_pin, Music.F, tempo * Length.one);
  setTone(buzzer_pin, Music.E, tempo * Length.two);
  setTone(buzzer_pin, Music.B2, tempo * Length.one);
  setTone(buzzer_pin, Music.A2, tempo * Length.two_half);
  setTone(buzzer_pin, Music.Fs, tempo * Length.two_half);
  
  setTone(buzzer_pin, Music.E, tempo * Length.one_half);
  setTone(buzzer_pin, Music.G, tempo * Length.half);
  setTone(buzzer_pin, Music.F, tempo * Length.one);
  setTone(buzzer_pin, Music.Ds, tempo * Length.two);
  setTone(buzzer_pin, Music.F, tempo * Length.one);
  setTone(buzzer_pin, Music.B, tempo * Length.two_half);
  //delay(500000);
  }
  else if(buf == fecharsenha){
    s.write(0);
    s2.write(0);
    lcd.clear();
    lcd.setCursor(0,0);
    delay(2500);
    digitalWrite(ledA, LOW);
    lcd.print("Pressione *");
    lcd.setCursor(0,1);
    lcd.print("");
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("Pressione *");
    lcd.setCursor(0,1);
  lcd.print("SENHA INCORRETA ");
    tone(buzzer_pin, 261, 600);
    delay(900);
    delay(3500);
    lcd.setCursor(0,0);
  lcd.print("Pressione *");
    lcd.setCursor(0,1);
  lcd.print("TENTE NOVAMENTE ");
    digitalWrite(ledV, HIGH);
    delay(1000);
    digitalWrite(ledV, LOW);
  }
}
