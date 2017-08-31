//Teste LDR usando pino analogico
//Desenvolvido por: Stella Marques
const int LDR = A0;             // Pino analógico que o LDR está conectado
int LDRvalor = 0;              // valor lido no LDR
int intensidade = 300;         //Intensidade da luminosidade que atinge o LDR                   

void setup() {
  Serial.begin(9600);                    // inicializa a comunicação porta serial
}

void loop() {
  
  LDRvalor = analogRead(LDR);           // Faz a leitura do pino analógico
  
  Serial.print("sensor = " );            // Imprime o resultado no monitor serial
  Serial.println(LDRvalor);      
  
  if(LDRvalor < intensidade){
  
    Serial.println("Valor abaixo do limite!"); 
  
  } else {
   
   Serial.println("Valor acima do limite!");
  
  }

  delay(2);                              // Aguarda 2 milisegundos para estabilizar o conversor ADC                  
}
  
