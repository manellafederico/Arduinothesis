//============================================================REPARTO 1================================================================//
void reparto_1 ()
{

  //------------------------------------------------------------GESTIONE CONTATORE-------------------------------------------------------//
  digitalRead(button1);
  if (button1 == HIGH) //decremento il contatore quando prelevo un pezzo a magazzino
  {
    cont1 = cont1 - 1;
  }
  //-------------------------------------------------------------------------------------------------------------------------------------//


  //------------------------------------------------------------GESTIONE LUCI------------------------------------------------------------//
  if (cont1 < limit1 ) //magazzino vuoto
  {
    digitalWrite(red1, HIGH); //luce rossa on
    digitalWrite(green1, LOW); //luce verde off
  }
  else //magazzino non vuoto
  {
    digitalWrite(red1, LOW); //luce rossa off
    digitalWrite(green1, HIGH); //luce verde on
  }
  //------------------------------------------------------------------------------------------------------------------------------------//

}
