//==================================================PROTOCOLLO I2C=====================================================//
#include <Wire.h> //include la libreria Wire all'interno dello sketch 
#define slavesequencedimension 8 //dimensione di slavesequence
int slavesequence [slavesequencedimension] = {}; //vettore che contiene datan inviato dallo slave al master

//==================================================TASTIERINO=========================================================//
#include <Keypad.h> //include la libreria per leggere i dati dal tastierino 
#define ROWS 4 // Quattro righe
#define COLS 4 // Quattro colonne
byte rowPins[ROWS] = { 8, 7, 6, 5 }; //vettore che contiene i pins di arduino al quale sono collegate le righe
byte colPins[COLS] = { 12, 11, 10, 9}; //vettore che contiene i ins di arduino al quale sono collegate le colonne
char keys[ROWS][COLS] = {   // Definizione mappa della tastiera
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //istruzione da librerira per creare l'oggetto "keypad"
int keydata = 0; //variabile che contine quanti pezzi a stock sono stati aggiunti al reparto "reparto"
int reparto = 0; //variabile che contine il reparto nel quale sono aggiunti pezzi a stock
#define keysequencedimension 8 //dimensione di keysequence
char keysequence [keysequencedimension] = {};

//====================================================MONITOR===========================================================//
#include <LiquidCrystal.h>

/*
  Circuito:
   pin RS collegato al pin digitale 12
   pin E (Enable) collegato al pin digitale 11
   pin D4 collegato al pin digitale 5
   pin D5 collegato al pin digitale 4
   pin D6 collegato al pin digitale 3
   pin D7 collegato al pin digitale 2
   pin R/W collegato al GND
   pin 1 e pin 4 collegati a GND
   pin 2 collegato a +Vcc
   centrale del potenziometro/trimmer da 10 KOhm collegato al pin 3 del'LCD
   pin SX potenziometro/trimmer collegato a +Vcc
   pin DX potenziometro/trimmer collegato a GND
   i pin SX e DX del potenziometro/trimmer possono essere interscambiati
*/

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Viene creata l'istanza dell'oggetto LiquidCrystal chiamata lcd in cui
//sono indicati i pin dell'LCD collegati alle uscite digitali di Arduino

//==================================================STORAGE DATA=========================================================//
/*In questa sezione vengono definite tutte le matrici per immagazzinare i keydata/datan di ogni reparto. I keydata sono tutti i numeri
  di pezzi aggiunti  a stock da parte di un operaio attraverso l'utilizzo della tastiera. I datan (con n che va da 1 a 4) sono tutti i
  dati che arrivano dagli slave derivanti dal conteggio attraverso i buttons inseriti in ogni reparto. I vettori datan contengono quindi
  ognuno 4 valori, ripsettivamente cont1, cont2, cont3 e cont4 che sono i contatori di pezzi a magazzino dei 4 reparti gestiti da uno slave.
  I valori di reaprto vengono utilizzati come indice della matrice alldata. */

#define alldatadimensionrows 4 //numero di righe della matrice che contiene tutti i data
#define alldatadimensioncolumns 4 //numero di colonne della matrice che contiene tutti i data
int alldata [alldatadimensionrows][alldatadimensioncolumns] = {};//matrice che contiene i valori dei pezzi  a stock per ogni reparto


void setup()
{
  Wire.begin(); //avvio della comunicazione attraverso il protocollo I2C
  lcd.begin(16, 2); //imposta il numero di righe e il numero di colonne. Si utilizza un LCD con 2 righe e 16 colonne.
}

/*Nel loop verrà gestito il tastierino. L'operatore che aggiorna il numero di pezzi a magazzino dovra digitare sul tastierino il valore
  numerico di pezzi che intende aggiungere a stock. A seguito di ciò dovrà premere il tasto "#" e indicare il reparto dove aggiungerà tali pezzi.
  Infine il tasto "*" per confermare l'operazione.
  Ad esempio, la sequenza risulta essere: "500#3*". Sono stati aggiunti 500 pezzi al reparto 3. */

void loop()
{
  //-----------------------------------------------LETTURA DAGLI SLAVES--------------------------------------------------//
  byte address = 1; //variabile che gestisce l'indirizzo dello slave con cui voglio comunicare
  switch (address)
  {
    case 1: //avviata la comunicazione con l'indirizzo 1
      I2Creceive (address);
      slaveconversion (address); //funzione che riporta le info contenute in slavesequence all'interno derlla matrice alldata
      I2Ctransmission (address);
      address = address + 1;
      break;

    case 2: //avviata la comunicazione con l'indirizzo 2
      I2Creceive (address);
      slaveconversion (address); //funzione che riporta le info contenute in slavesequence all'interno derlla matrice alldata
      I2Ctransmission (address);
      address = address + 1;
      break;

    case 3: //avviata la comunicazione con l'indirizzo 3
      I2Creceive (address);
      slaveconversion (address); //funzione che riporta le info contenute in slavesequence all'interno derlla matrice alldata
      I2Ctransmission (address);
      address = address + 1;
      break;

    case 4: //avviata la comunicazione con l'indirizzo 4
      I2Creceive (address);
      slaveconversion (address);//funzione che riporta le info contenute in slavesequence all'interno derlla matrice alldata
      I2Ctransmission (address);
      address = 1;
      break;
    default:
      break;
  }

  //---------------------------------------------------------------------------------------------------------------------//

  //-----------------------------------------------LETTURA DA TASTIERINO--------------------------------------------------//
  char key = 0; //accedi al ciclo while
  int i = 0; //indice del ciclo
  while ( key != '*') //costruisce l'array keysequence che contiene le informazioni necessarie ad aggiornare gli stock
  {
    key = kpd.getKey(); //assegna alla variabile key il carattere premuto sul tastierino
    keysequence [i] = key;
    i = i + 1;
  } //il vettore keysequence contiene [numero di pezzi,#, numero reparto, *]

  conversion (); //converto i valori letti dal tastierino in infomazioni utili agli slaves. Ritorna keydata e reparto.
  indexresearch (); //ricerca dell'indice dato il valore di reparto
  //---------------------------------------------------------------------------------------------------------------------//

  //-----------------------------------------------STAMPAGGIO A VIDEO----------------------------------------------------//
  videoprint(); //funzione che permette di stampare a video i valori di alldata
  //---------------------------------------------------------------------------------------------------------------------//

}
