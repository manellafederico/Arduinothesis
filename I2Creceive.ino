void I2Creceive ( int address)
{
  //------------------------------------------------SLAVE TO MASTER------------------------------------------------//
  Wire.requestFrom(address, 2); //richiede la disponibilità a comunicare allo slave di indirizzo address
  int i = 0; //indice di slavesequence
  while (Wire.available())
  {
    slavesequence [i] = Wire.read(); //copio le informazioni del vettore datan in ingresso in un vettore slavesequence 
    i = i + 1;
  }
}
