void indexresearch() //funzione che associa il valore di reparto alla posizone nella matrice alldata
/* i reparti sono numerati da 0 a 15, e tale valore sarà riportato su una label all'interno del magazzino. */
{
  byte i = 0;//indice righe
  byte j = 0;//indice colonne
  byte counter = 0; //contatore per trovare il valore di indice
  for ( i = 0; i < alldatadimensionrows; i++) //ciclo per scorrere nelle colonne
  {
    for ( j = 0; j < alldatadimensioncolumns; j++) //ciclo per scorrere nelle righe
    {
      counter = i * 4 + j;
      if (reparto == counter)
      {
        alldata[i][j] = alldata[i][j] + keydata; //aggiorno le informazioni della matrice alldata
      }
    }
  }
}
