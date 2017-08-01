//Programa : Controle de Acesso via cartão RFID mostrando dados no LCD Arduino
/*Modificado por: Stella Azevedo Marques*/
 
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria a instancia do tipo MFRC522.
 
// Inicializa o display no endereco 0x3f
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3, POSITIVE);
  
char st[20];
 
void setup() 
{
  // Inicia a serial
  Serial.begin(9600);
  // Inicia  SPI bus para o funcionamento do Cartão RFID
  SPI.begin();
  // Inicia MFRC522
  mfrc522.PCD_Init();
  Serial.println("Aproxime a TAG");
  Serial.println();
  //Define o número de colunas e linhas do LCD:  
  lcd.begin(16, 2);  
  mensageminicial();
}
 
void loop() 
{
  // Verifica se existe um novo cartão
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // verifica existencia do cartão
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  // Parte de teste do cartão
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "2A 81 D2 C4") //UID 1 - chaveiro 1
  {
    Serial.println("Stella !");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Stella !");
    lcd.setCursor(0,1);
    lcd.print("Acesso liberado!");
    delay(3000);
    mensageminicial();
  }
 
  if (conteudo.substring(1) == "8A E8 CE C4") //UID 2 - chaveiro 2
  {
    Serial.println("Chaveiro !");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Chaveiro !");
    lcd.setCursor(0,1);
    lcd.print("Acesso Liberado !");
    delay(3000);
    mensageminicial();
  }else{
    if((conteudo.substring(1) != "2A 81 D2 C4")&&(conteudo.substring(1) != "8A E8 CE C4")){
        Serial.println("Acesso Negado!");
        Serial.println();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Desconhecido !");
        lcd.setCursor(0,1);
        lcd.print("Acesso Negado !");
        delay(3000);
        mensageminicial();
    }
    
  }
} 

//Mensagem inicial do LCD
void mensageminicial()
{
  lcd.clear();
  lcd.print(" Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}
