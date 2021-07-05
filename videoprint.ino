void videoprint ()
{
#define gap 1000
  byte i = 0;
  byte j = 0;
  int cont = millis();

  if ((millis() - cont) >  gap) //ogni gap aggiorna le info a monitor printando quelle del reparto successivo
  {
    int store = (i * 4 + j);
    if (store < 16) //controlla di aver stampato a video ogni reparto
    {
      lcd.print("reparto:"); //stamap il valore del reparto di riferimento
      lcd.print(store);
      lcd.setCursor(1, 2); //sposta il cursore alla riga inferiore
      lcd.print(alldata [i][j]); //stampa il valore dei pezzi a stock. Tale informazione è contenuta in alldata.

      i = i + 1;
      j = j + 1;
    }
    else //se tutti i reparti sono stati stampati si ricomincia da capo
    {
      i = 0;
      j = 0;
    }
  }

}
