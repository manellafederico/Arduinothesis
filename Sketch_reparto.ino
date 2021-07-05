/*In questo sketch è presente il controllo delle luci e del contatore di ogni singolo reparto. Per reparto si intende  un unico contenitore
  che contine componenti dello stesso tipo. Tale sketch sarà eseguito da un arduino nano, il quale controllerà 4 reparti, impegnando tutti i pin digitali.
  Di segutio è riportato il codice per due reparti. Raddoppiando le variabili e i pins si può estendere lo stesso codice a tutti e 4 i reparti. I reparti
  sono organizzati in funzioni. Nel void Loop () è presente solo la chiamata al singolo reparto.
*/

//============================================================VARIABILI GLOBALI==================================================================//
#include <Wire.h> //inclusione della libreria wire per il protocollo I2C

#define datasize 2 //dimensione di data
int data1 [datasize]; //vettore che contiene le informazioni relative ai contatori dei singoli contatori che vanno trasmesse al master

//============================================================VARIABILI REPARTO 1================================================================//
#define red1 2 //pin digitale 2 per accensione della luce rossa
#define green1 3 //pin digitale 3 per l'accesione della luce verde
#define button1 4 //pin digitale di lettura del contatore
int cont1 = 100; //numero di pezzi a magazzino
int limit1 = 10; //numero minimo di pezzi a magazzino prima che il magazzino venga considerato vuoto

//============================================================VARIABILI REPARTO 2================================================================//
#define red2 5 //pin digitale 2 per accensione della luce rossa
#define green2 6 //pin digitale 3 per l'accesione della luce verde
#define button2 7 //pin digitale di lettura del contatore
int cont2 = 100; //numero di pezzi a magazzino
int limit2 = 10; //numero minimo di pezzi a magazzino prima che il magazzino venga considerato vuoto

void setup()
{

  //============================================================SETUP GLOBALI==================================================================//
  Wire.begin(1); //1 sarà l'indirizzo dello slave


  //============================================================SETUP REPARTO 1================================================================//
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(button1, INPUT);

  //============================================================SETUP REPARTO 2================================================================//
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(button2, INPUT);

}


void loop()
{
  reparto_1();
  reparto_2();
  data1 [cont1, cont2]; //aggiornamento del vettore data ogni volt ache vengono esegute le funzioni reparto_i

  Wire.onRequest(rispondi); //funzione che viene eseguta quando il master chiama lo slave
  Wire.onReceive(ricevi); //funzione che viene esegutia quando il lo slave riceve dati dal master
}

//////////////////////////////////////////////////////////////////PROTOCOLLO I2C//////////////////////////////////////////////////////////////////////////

void rispondi() //invia i dati al master quando la chimata viene eseguita
{
  for (int i = 0; i <= datasize; i = i + 1 )//invia tutti gli elementi del vettore data1 al master
  {
    Wire.write(data1[i]);
  }
}

void ricevi() //riceve i dati del master relativi agli aggiornamenti degli stock a magazzino.
{
  while (Wire.available()) //finanto che la comunicazione I2C è disponibile ricevi i dati
  {
    for (int i = 0; i <= datasize; i = i + 1 )//aggiorna il vettore data1 con le info che arrivano dal master, nel caso nuovi stock fossero messi a magazzino
    {
      data1[i] = Wire.read();
    }
  }
}

/*una volta concluse queste operazioni il vettoro data1 è stato aggiornato con le informazioni del master e la chimata alle funzioni reparto_1 e reparto_2
  permette di aggiornare le luci dei ogni reparto. */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
