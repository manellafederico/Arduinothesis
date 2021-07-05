int conversion () //funzione necessaria per convertire le infor contenute in key sequence in dati utilizzabili
{
  byte counter = 0;
  byte newcounter = 0;
  //------------------------------ CICLO CHE ESTRAPOLA DA KEYSEQUENCE IL VALORE DEI PEZZI AGGIUNTI A STOCK-----------//
  byte i = 0;
  while ( keysequence[i] != '#')
  {
    i = i + 1;
    counter = i ; //sono presenti counter cifre prima di '#'
  }
  for (byte j = 0; j <= counter; j = j + 1)
  {
    keydata = keydata + keysequence[j] * (counter - j) * 10;
  } //ho ottenuto il valore di pezzi che sono stati aggiunti  a stock

  //--------------- CICLO CHE ESTRAPOLA DA KEYSEQUENCE IL VALORE DEL REPARTO DOVE SONO STATI AGGIUNTI I PEZZI A STOCK-----------//
  byte f = counter + 1;
  while ( keysequence[i] > f && keysequence[i] != '*') //cerco il valore del reparto da aggiornare
  {
    f = f + 1;
    newcounter = f ; //sono presenti newcounter cifre prima di '*'
  }
  byte save = newcounter - counter;
  for (byte j = f + 1; j <= newcounter; j = j + 1)
  {
    byte h = 0;
    reparto = reparto + keysequence[j] * (save - h) * 10;
    h = h + 1;
  } //ho ottenuto il valore del reparto dove sono stati aggiunti i pezzi


  return reparto; //restituisce il valore di reparto
  return keydata; //resitituisce il valore di pezzi a stock
}
