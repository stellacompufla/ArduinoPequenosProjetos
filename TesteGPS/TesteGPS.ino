//Programa : Teste GPS
//Programa desenvolvido por Stella Marques
//Data : 23/08/2017
//Lavras - MG
//Hora da compilação - 17:16hs
//Versão : 1.0

 /*
 Inormações tecnicas:
  GPS: 
   2 - RXGPS
   3 - TXGPS
*/

//Incluindo bibliotecas

#include <SPI.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
int i =0;

// The TinyGPS++ object
TinyGPSPlus gps;
TinyGPSDate data;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  ss.begin(GPSBaud); //Inicializa GPS
  Serial.begin(9600);
  SPI.begin();      // Inicia  SPI bus
}

void loop()
{ 
   Serial.println("Conectando GPS");
   leituraGPS2(gps);
   //Verifica se o GPS conectou
   while((!gps.course.isValid()) && (i<10)){
     leituraGPS2(gps);
     i++;
   }
   //leituraGPS(gps); //Imprime a Primeira conexão do GPS
   delay(2000);
    leituraGPS2(gps);
}

void leituraGPS2(TinyGPSPlus &gps){
  
  cordenadas(gps.location.lat(), gps.location.isValid(), 11, 6);
  cordenadas(gps.location.lng(), gps.location.isValid(), 12, 6);
  DataHora(gps.date, gps.time);
  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("Nenhum dado recebido GPS."));
}

static void cordenadas(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    //Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    //for (int i=flen; i<len; ++i)
     // Serial.print(' ');
 /// }
  smartDelay(0);
}
}

static void DataHora(TinyGPSDate &d, TinyGPSTime &t)
{
  if ((!d.isValid())&&(!t.isValid()))
  {
    Serial.print(F("********** "));
  }
  else
  {
    char data[32];
    sprintf(data, "%02d/%02d/%02d", d.day() ,d.month(), d.year());
    char hora[32];
    sprintf(hora, "%02d:%02d:%02d", t.hour() , t.minute(), t.second());
    String texto= ("'"+String(gps.location.lat(),6)+","+String(gps.location.lng(),6)+"';'"+data+"';'"+hora+"'");
    Serial.println(texto);
    //Serial.print(sz);
  }
  smartDelay(0);
}

//Esta versão de delay () garante que o objeto gps
// está sendo "alimentado"
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.day() ,d.month(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    //Para imprimir com horario de Lavras
    /*int hora =0;
    hora = t.hour() - 3;
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ",hora, t.minute(), t.second());
    Serial.print("Lavras");*/ 
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour() , t.minute(), t.second());
    Serial.print(sz);
  }

  //printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
