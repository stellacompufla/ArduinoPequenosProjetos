/*
 Ligações:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 
 */
#include <SPI.h>
#include <SD.h>

File root;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; ///Espera pela porta serial para conectar. Conexão com porta USB necessária.
  }

  Serial.print("Inicializando SD card...");

  if (!SD.begin(4)) {
    Serial.println("Falha!"); //Falha na inicialização
    return;
  }
  Serial.println("Concluido."); //Inicialização Concluida

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("OK!");
}

void loop() {
  //Não faz nada.
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // Acabaram os arquivos
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      //Tamanho dos arquivos
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}



