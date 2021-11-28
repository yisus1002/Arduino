#include <LiquidCrystal.h> 
//Libreria para controlar el LCD

LiquidCrystal lcd(7, 6, 5, 4, 3 , 2); 
        // (RS, E, DB4, DB5, DB6, DB7)


// Metodo para obtener el valor de los grados en el sensor
//Temperatura
float centi(){ 
  int dato;
  float c;
  dato = analogRead(A0);//Obtener dato del A0
  c = ((500.0*dato)/1024)-50;
  return (c);
}

//Metodo para obtener el porcentage de humedad
//En el sensor de Humedad(Potenciometro)
float hume(){
 int dato;
  float h;
  dato=analogRead(A1);//Obtener dato del A1
  // 25/256= 0.09765625
  h= (dato*0.097751);
  return (h);
}

int gas; //Variable para almacenar el valor del sensor de gas

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
byte grado[8] =    //Creamos el grado en binario
 {
    0b00001100,     
    0b00010010,
    0b00010010,
    0b00001100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
 };
  lcd.createChar (1, grado); //Creamos el caracter grado

}

void loop()
{     
    lcd.clear(); //limpiar pantalla del lcd
 	float Centigrados = centi(); //LLAmamos el metodo centi()
  	float Humedad = hume();
  
    gas= analogRead(A2);//Obtener dato del A2 del sensor de gas
  
       lcd.setCursor(0,0); // Escribir en la columna, fila
       lcd.write("HUMEDAD"); //Ingresar el texto
       lcd.setCursor(8,0); // Escribir en la columna, fila
 	   lcd.print(Humedad,2);  //mostramos 2 decimales
  	   lcd.setCursor(13,0); // Escribir en la columna, fila
       lcd.print("%") ;
 	   lcd.setCursor(0,1);  
       lcd.print("T = ") ;
  	   lcd.setCursor(4,1);
  	   lcd.print(Centigrados,2);//Mostramos 2 decimales
  	   lcd.setCursor(10,1);	
  	   lcd.write((byte)1); //Escribimos el simbolo de grado
  	   lcd.write("C") ;
  
// condicional para el control y aviso de temperatura
  
  if (centi()>25){
    digitalWrite(9, HIGH); //Encender LED RGB Rojo
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
  else if (centi()<20){
    digitalWrite(10, HIGH); //Encender LED RGB Azul
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
  }else{
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH); //Encender LED RGB Verde
  }
  
  //condicional para el control y aviso del sensor de humedad
  
  if(hume()>=50 && hume()<=60){
    digitalWrite(8, LOW); //Apagar LED Amarillo
  }else if (hume()<40){
    digitalWrite(12, HIGH); //Encender LED Blanco (Electrobomba)
  }else{
     digitalWrite(8, HIGH); //Encender LED Amarillo
    digitalWrite(12, LOW); //Apagar LED Blanco (Electrobomba)
  }
  
  //Condicion para generar alarma si el sensor de gas detecta humo
  if(gas > 400){
    digitalWrite(13, HIGH); //Encender LED Naranja
  }else{
    digitalWrite(13, LOW); //Apagar LED Naranja
  }
  
  Serial.println(gas);//Imprimimos en el monitor el valor del gas
  
  delay (1000);
 

 
 
}