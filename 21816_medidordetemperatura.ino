/*Ana Beatriz de Oliveira  RA:21816
Aula do dia 15/06/2022 -- Atividade no tinkercad 1 */

// Bibliotecas
#include <LiquidCrystal.h>

// Inicializa os pinos LCD
LiquidCrystal lcd(12,11,5,4,3,2); 

// Define o pino analogico A0 
int SensorTempPino=0;

// Criação de um char de grau para mostrar no Monitor serial
char c = '°';

/*Array que faz o desenho do simbolo grau. 
Feito no site: <http://cfbcursos.com.br/compositor/compositor_de_caracteres_display_Arduino.html>
*/
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};

void setup() {
  //Inicializa a serial e mostra os textos
	Serial.begin(9600); 
  	Serial.println("Iniciando o programa");
  	Serial.println("Temperatura na escala Celsius: ");
  
  // Inicia o LCD e limpa a tela
	lcd.begin(16,2); 
  	lcd.clear();  
  
  //Cria o caracter do grau
  	lcd.createChar(1, grau);
}

void loop() {
  
  /*O programa lerá qual é o valor do sinal no pino A0, que varia
    de 0 a 1023, onde 0 corresponde a 0 Volts e 1023 corresponde 
    a 5 Volts. 1ºC é igual a 10mV.
  
    Pelo fato da temperatura poder assumir valores racionais
    e o arduinos nos retornar um inteiro,declaramos a 
    temperatura como float.
     
    Quando multiplicamos uma variavel inteira por um racional, 
    o programa considera que o resultado deve ser inteiro,
    eliminando a parte decimal da variável. Diante disso, 
    devemos transformar o número inteiro em um número racional,
    como foi feito nas linhas abaixo. 
    Pegamos o resultado lido no "analogRead" e transformamos em
    um float.
*/
 
  // Faz a leitura da tensao no Sensor de Temperatura
	int SensorTempTensao = analogRead(SensorTempPino);

 // Converte a tensao lida
	float Tensao = SensorTempTensao*5;
	Tensao/= 1024;

 // Converte a tensao lida em Graus Celsius
	float TempC = (Tensao-0.5)*100;

 // Mostra na primeira linha o RA 
  	lcd.setCursor(0,0);
  	lcd.print("RA:21816");  
	
  // Mostra a mensagem da temperatura e muda o cursor para a 5ºcoluna e 1°linha
	lcd.setCursor(0,1); //Aqui coloca na segunda linha coluna zero
	lcd.print("Temp: "); 
	lcd.setCursor(5,1);
	lcd.print(TempC);
  	lcd.write(1); //Mostra o simbolo de grau
  	lcd.print("C");
  	

 // Mostra mensagem de temperatura no Monitor Serial com o char de grau
  	Serial.print (TempC);
  	Serial.print (c);
    Serial.println("C");
  	
 // Delay de 1 segundo
  	delay(1000); 
  	lcd.clear();
}