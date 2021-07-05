void slaveconversion (int address) //aggiorno la matrice alldata con i vettori datan derivanti dagli slaves
{
  switch (address)
  {
    case 1: 
      for (int j = 0; j < alldatadimensioncolumns; j = j + 1)
      {
        alldata [address - 1][j] = alldata [address - 1][j] + slavesequence [j];
      }
      break;

    case 2:
      for (int j = 0; j < alldatadimensioncolumns; j = j + 1)
      {
        alldata [address - 1][j] = alldata [address - 1][j] + slavesequence [j];
      }
      break;

    case 3:
      for (int j = 0; j < alldatadimensioncolumns; j = j + 1)
      {
        alldata [address - 1][j] = alldata [address - 1][j] + slavesequence [j];
      }
      break;

    case 4:
      for (int j = 0; j < alldatadimensioncolumns; j = j + 1)
      {
        alldata [address - 1][j] = alldata [address - 1][j] + slavesequence [j];
      }
      break;
      
    default:
      break;

  }

}
