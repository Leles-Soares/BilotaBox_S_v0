//fdsf
/*
 * fgdfgd
 */

void sorteio(void)//char *strApostaMega
{
  int jogo[6]         = {0};
  int jogoOrdenado[6] = {0};
  int randNumber      = 0;
  int countN          = 0;
  int i               = 0;
  int maior           = 0;
  int menor           = 0;
  int todos           = 0;

  Serial.println("entro!");

  while (countN < 6)
  {
    for(i = 0; i < 6; i++) 
    {
      randNumber = random(1,61) + random(1,10);
      //Serial.print("Rn: ");
      //Serial.println(randNumber);
      if(randNumber != jogo[i] && randNumber <= 60)
      {
        todos++;
        //Serial.print("todos: ");
        //Serial.println(todos);
      }
    }

    if(todos == 5)
    {
      jogo[countN] = randNumber;
      countN++;
    }

    todos = 0;
    //delay(2000);
  }

  Serial.println("jogo completo");

  for(i = 0; i < 6; i++) 
  {
    Serial.print("i: ");
    Serial.print(i);
    Serial.print(" - jogo: ");
    Serial.println(jogo[i]);
  }
  maior = 0;
  menor = 10000;
  for(i = 0; i < 6; i++) 
  {
    if(jogo[i]>maior)
    {
      maior = jogo[i];
    }
    if(jogo[i]<menor)
    {
      menor = jogo[i];
    }
  }

  Serial.print("Maior: ");
  Serial.print(maior);
  Serial.print(" - Menor: ");
  Serial.println(menor);

  jogoOrdenado[0] = menor;
  jogoOrdenado[5] = maior;

  maior = 0;
  menor = 10000;
  for(i = 0; i < 6; i++) 
  {
    if(jogo[i]>maior && jogo[i] != jogoOrdenado[0] && jogo[i] != jogoOrdenado[5])
    {
      maior = jogo[i];
    }
    if(jogo[i]<menor && jogo[i] != jogoOrdenado[0] && jogo[i] != jogoOrdenado[5])
    {
      menor = jogo[i];
    }
  }

  jogoOrdenado[1] = menor;
  jogoOrdenado[4] = maior;

  maior = 0;
  menor = 10000;

  for(i = 0; i < 6; i++) 
  {
    if(jogo[i]>maior && jogo[i] != jogoOrdenado[0] && jogo[i] != jogoOrdenado[5] && jogo[i] != jogoOrdenado[1] && jogo[i] != jogoOrdenado[4])
    {
      maior = jogo[i];
    }
    if(jogo[i]<menor && jogo[i] != jogoOrdenado[0] && jogo[i] != jogoOrdenado[5] && jogo[i] != jogoOrdenado[1] && jogo[i] != jogoOrdenado[4])
    {
      menor = jogo[i];
    }
  }
  jogoOrdenado[2] = menor;
  jogoOrdenado[3] = maior;
  Serial.println("jogo ordenado");

  for(i = 0; i < 6; i++) 
  {
    Serial.print("i: ");
    Serial.print(i);
    Serial.print(" - jogo: ");
    Serial.println(jogoOrdenado[i]);
  }

  
}
