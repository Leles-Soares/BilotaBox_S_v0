void jogo(int qtAcerto, int minino, int maximo, char *msg)
{
  int sorteio[100];
  int i          = 0;
  int j          = 0;
  int aux        = 0;
  int numero     = 0;
  
  maximo++;
  
  for (i = 0; i < qtAcerto; i++)
  {
    sorteio[i] = 0;
  }
  
  for (i = 0; i < qtAcerto; i++) //Laço para o sorteio dos 6 números   
  {          
  
    numero = random(minino,maximo); //Sorteia um número de 1 a 60     
    
    for (j = 0;j < qtAcerto; j++) //Laço para o sorteio caso o número seja repetido     
    {       
    
      if (numero == sorteio[j]) //Se o número for repetiro       
      {         
        numero = random(minino,maximo); //Sorteia um número de 1 a 60       
      }       
    
    }     
    
    sorteio[i] = numero; //Armazena o número sorteado na respectiva posição da contagem     
  }     

  
  //Aplicação de bubble sort para ordenação dos numeros sorteados   
  for (i = 0; i<(qtAcerto-1) ; i++)   
  {     
    for (j = i ; j < qtAcerto ; j++)     
    {         
      if (sorteio[j] < sorteio[i])       
      {         
        aux = sorteio[i];         
        sorteio[i] = sorteio[j];         
        sorteio[j] = aux;       
      }     
    }
    colocaZero(msg, sorteio[i]);

  }
  colocaZero(msg, sorteio[qtAcerto-1]);
  
  
  for(i = 0; i < qtAcerto; i++) 
  {
    Serial.print("jogo: ");
    Serial.println(sorteio[i]);
  }
  Serial.println("\n\n");
  Serial.print("msg: ");
  Serial.println(msg);
}

void colocaZero(char *msg, int numero)
{
  char strAux[5];
  
  memset(strAux, 0, sizeof(strAux));
  
  if(numero <= 9)
  {
    sprintf(strAux, "0%d ", numero);
    strcat(msg, strAux);
  }
  else
  {
    sprintf(strAux, "%d ", numero);
    strcat(msg, strAux);
  }

}

void apostaMega()
{
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(2);
  memset(str, 0, sizeof(str));
  jogo(6, 1, 60, str);
  alinharMensagem(G, 2, "Mega", C, 0);
  alinharMensagem(W, 2, str, E, 4);
  alinharMensagem(W, 2, (str + 11), C, 5);
  
  delay(100);
}
