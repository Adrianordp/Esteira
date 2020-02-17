// DEFINIÇÃO DE VARIÁVEIS -----------------------------------------------
// Registra portas digitais onde os sensores estão ligados
int infra1 = 2;
int infra2 = 3;
int infra3 = 11;
int infra4 = 12;

// Registra o estado lógico de cada sensor
boolean sinal1; // 0: nada na frente, 1: algo na frente
boolean sinal2; // 0: nada na frente, 1: algo na frente
boolean sinal3; // 0: nada na frente, 1: algo na frente
boolean sinal4; // 0: nada na frente, 1: algo na frente

// Registra quando tem algo entrando ou saindo de cada esteira
boolean algoEntrandoEsteira1; // 0: nada entrando na esteira 1, 1: algo está entrando na esteira 1
boolean algoEntrandoEsteira2; // 0: nada entrando na esteira 2, 1: algo está entrando na esteira 2
boolean algoSaindoEsteira1  ; // 0: nada saindo da esteira 1, 1: algo está saindo da esteira 1
boolean algoSaindoEsteira2  ; // 0: nada saindo da esteira 2, 1: algo está saindo da esteira 2

// Caminho lógico que o item faz ao entrar ou sair da esteira
//     Entrando             Saindo
// (externo,interno)  (externo,interno)
//        0,0                0,0
//        1,0 passo 1        0,1 passo 1
//        1,1 passo 2        1,1 passo 2
//        0,1 passo 3        1,0 passo 3
//        0,0 entrou         0,0 saiu
// Registra em qual etapa de entrada ou saída o objeto se encontra
boolean entrandoEsteira1Passo1; // 1: Apenas o sensor mais externo encontra o objeto
boolean entrandoEsteira1Passo2; // 1: Após o passo 1, ambos os sensores encontram o objeto
boolean entrandoEsteira1Passo3; // 1: Após o passo 2, apenas o sensor mais interno encontra o objeto
// Após o passo 3, se os sensores retornarem (0,0), o objeto entrou

boolean entrandoEsteira2Passo1; // Mesma ideia do objeto entrando na esteira 1
boolean entrandoEsteira2Passo2; //
boolean entrandoEsteira2Passo3; //

boolean saindoEsteira1Passo1; // 1: Apenas o sensor mais interno encontra o objeto
boolean saindoEsteira1Passo2; // 1: Após o passo 1, ambos os sensores encontram o objeto
boolean saindoEsteira1Passo3; // 1: Após o passo 2, apenas o sensor mais externo encontra o objeto
// Após o passo 3, se os sensores retornarem (0,0), o objeto saiu

boolean saindoEsteira2Passo1; // Mesma ideia do objeto saindo da esteira 1
boolean saindoEsteira2Passo2; //
boolean saindoEsteira2Passo3; //

// Registra quantos itens exitem após a esteira. 'unsigned' significa que o número deve ser positivo
unsigned int qtdItensEsteira1;
unsigned int qtdItensEsteira2;

// Registra o tempo de funcionamento em milissegundos. 'long' é para aceitar números maiores
unsigned long timer1;
unsigned long timer2;

void setup() // Configura o Arduino
{
  pinMode(infra1, INPUT); // Configura a porta de número 'infra1' como entrada digital
  pinMode(infra2, INPUT); // Configura a porta de número 'infra2' como entrada digital
  pinMode(infra3, INPUT); // Configura a porta de número 'infra3' como entrada digital
  pinMode(infra4, INPUT); // Configura a porta de número 'infra4' como entrada digital

  // Habilita comunicação serial com baud rate de 9600 bytes/s
  Serial.begin(9600);
}

void loop() // Executa infinitamente e repetidamente
{
  // Temporizador que capta os dados dos sensores
  if (millis() - timer1 >= 5) // Lê sensores a cada 5 milissegundos
  {
    timer1 = millis(); // Atualiza timer
    sinal1 = !digitalRead(infra1); // Lê sensor infra1. 0: nada na frente, 1: algo na frente
    sinal2 = !digitalRead(infra2); // Lê sensor infra2. 0: nada na frente, 1: algo na frente
    sinal3 = !digitalRead(infra3); // Lê sensor infra3. 0: nada na frente, 1: algo na frente
    sinal4 = !digitalRead(infra4); // Lê sensor infra4. 0: nada na frente, 1: algo na frente

    // Verifica se algo está entrando na esteira 1
    if (algoEntrandoEsteira1 == 1)
    {
      acompanhaEntrandoEsteira1();
    }
    // Verifica se algo está saindo da esteira 1
    else if (algoSaindoEsteira1 == 1)
    {
      acompanhaSaindoEsteira1();
    }
    // Se não tiver nada entrando nem saindo da esteira 1
    else
    {
      verificaEsteira1();
    }

    // Verifica se algo está entrando na esteira 2
    if (algoEntrandoEsteira2 == 1)
    {
      acompanhaEntrandoEsteira2();
    }
    // Verifica se algo está saindo da esteira 2
    else if (algoSaindoEsteira2 == 1)
    {
      acompanhaSaindoEsteira2();
    }
    // Se não tiver nada entrando nem saindo da esteira 2
    else
    {
      verificaEsteira2();
    }
  }

  // Exibe a contagem das esteiras pela comunicação serial
  if (millis() - timer2 >= 1000)
  {
    timer2 = millis();
    Serial.print("------- ");
    Serial.println(timer2 / 1000); // Imprime o tempo em segundos
//     Descomentar as linhas de baixo para verificar melhor a lógica por trás do programa!!
//        Serial.print(sinal1);
//        Serial.print(sinal2);
//        Serial.print('-');
//        Serial.print(entrandoEsteira1Passo1);
//        Serial.print(entrandoEsteira1Passo2);
//        Serial.print(entrandoEsteira1Passo3);
//        Serial.print('-');
//        Serial.print(saindoEsteira1Passo1);
//        Serial.print(saindoEsteira1Passo2);
//        Serial.println(saindoEsteira1Passo3);
//        Serial.print(sinal3);
//        Serial.print(sinal4);
//        Serial.print('-');
//        Serial.print(entrandoEsteira2Passo1);
//        Serial.print(entrandoEsteira2Passo2);
//        Serial.print(entrandoEsteira2Passo3);
//        Serial.print('-');
//        Serial.print(saindoEsteira2Passo1);
//        Serial.print(saindoEsteira2Passo2);
//        Serial.println(saindoEsteira2Passo3);

    // Imprime a quantidade de itens na esteira 1
    Serial.print("Esteira 1: ");
    Serial.println(qtdItensEsteira1);
    // Imprime a quantidade de itens na esteira 2
    Serial.print("Esteira 2: ");
    Serial.println(qtdItensEsteira2);
  }
}

// Funções da esteira 1 -------------------------------------------------
void acompanhaEntrandoEsteira1()
{
  if (sinal1==1 && sinal2==0) // Se algo está entrando e sinal 1,0 -> passo 1
  {
    // Algo entrando na esteira 1 no primeiro passo
    entrandoEsteira1Passo1 = true ;
    entrandoEsteira1Passo2 = false;
    entrandoEsteira1Passo3 = false;
  }
  else if (sinal1==1 && sinal2==1) // Se algo está entrando e sinal 1,1 -> passo 2
  {
    // Algo entrando na esteira 1 no segundo passo
    entrandoEsteira1Passo1 = false;
    entrandoEsteira1Passo2 = true ;
    entrandoEsteira1Passo3 = false;
  }
  else if (sinal1==0 && sinal2==1) // Se algo está entrando e sinal 0,1 -> passo 3
  {
    // Algo entrando na esteira 1 no terceiro passo
    entrandoEsteira1Passo1 = false;
    entrandoEsteira1Passo2 = false;
    entrandoEsteira1Passo3 = true ;
  }
  else if (sinal1==0 && sinal2==0 && entrandoEsteira1Passo3==1) // Se algo está entrando, o sinal é 0,0 e estava no passo 3 -> entrou
  {
    // Algo entrou na esteira 1
    qtdItensEsteira1 = qtdItensEsteira1 + 1;
    entrandoEsteira1Passo1 = false;
    entrandoEsteira1Passo2 = false;
    entrandoEsteira1Passo3 = false;
  }
  else if (sinal1==0 && sinal2==0)  // Se algo está entrando e sinal 0,0 -> objeto voltou pra fora
  {
    // Algo estava entrando na esteira voltou pra fora
    algoEntrandoEsteira1 = false;
    entrandoEsteira1Passo1 = false;
    entrandoEsteira1Passo2 = false;
    entrandoEsteira1Passo3 = false;
  }
}

void acompanhaSaindoEsteira1()
{
  if (sinal1==0 && sinal2==1) // Se algo está saindo e sinal 0,1 -> passo 1
  {
    // Algo saindo da esteira 1 no primeiro passo de saída
    saindoEsteira1Passo1 = true;
    saindoEsteira1Passo2 = false;
    saindoEsteira1Passo3 = false;
  }
  else if (sinal1==1 && sinal2==1) // Se algo está saindo e sinal 1,1 -> passo 2
  {
    // Algo saindo da esteira 1 no segundo passo de saída
    saindoEsteira1Passo1 = false;
    saindoEsteira1Passo2 = true;
    saindoEsteira1Passo3 = false;
  }
  else if (sinal1==1 && sinal2==0) // Se algo está saindo e sinal 1,0 -> passo 3
  {
    // Algo saindo da esteira 1 no terceiro passo de saída
    saindoEsteira1Passo1 = false;
    saindoEsteira1Passo2 = false;
    saindoEsteira1Passo3 = true;
  }
  else if (sinal1==0 && sinal2==0 && saindoEsteira1Passo3==1) // Se algo está saindo, o sinal é 0,0 e estava no passo 3 -> saiu
  {
    if (qtdItensEsteira1==0) // Se haviam zero itens na esteira
    {
      // Impossível algo ter saído de lá
      Serial.println("Situação impossível!!! Não havia nada na esteira 1.");
    }
    else // Caso contrário
    {
      // Algo saiu da esteira
      qtdItensEsteira1 = qtdItensEsteira1 - 1;
    }
    saindoEsteira1Passo1 = false;
    saindoEsteira1Passo2 = false;
    saindoEsteira1Passo3 = false;
  }
  else if (sinal1==0 && sinal2==0) // Se algo está saindo e sinal 0,0 -> objeto voltou para dentro
  {
    // Algo que estava saindo da esteira voltou para dentro
    algoSaindoEsteira1 = false;
    saindoEsteira1Passo1 = false;
    saindoEsteira1Passo2 = false;
    saindoEsteira1Passo3 = false;
  }
}

void verificaEsteira1()
{
  if (sinal1==1 && sinal2==0) // Verifica se agora tem algo entrando
  {
    algoEntrandoEsteira1 = true;
  }
  else if (sinal1==0 && sinal2==1) // Ou se agora tem algo saindo
  {
    algoSaindoEsteira1 = true;
  }
  else  // Ou se continua sem ter algo entrando ou saindo
  {
    algoEntrandoEsteira1 = false;
    algoSaindoEsteira1 = false;
  }
}


// Funções da esteira 2 -------------------------------------------------
void acompanhaEntrandoEsteira2()
{
  if (sinal3==1 && sinal4==0) // Se algo está entrando e sinal 1,0 -> passo 1
  {
    // Algo entrando na esteira 1 no primeiro passo
    entrandoEsteira2Passo1 = true ;
    entrandoEsteira2Passo2 = false;
    entrandoEsteira2Passo3 = false;
  }
  else if (sinal3==1 && sinal4==1) // Se algo está entrando e sinal 1,1 -> passo 2
  {
    // Algo entrando na esteira 2 no segundo passo
    entrandoEsteira2Passo1 = false;
    entrandoEsteira2Passo2 = true ;
    entrandoEsteira2Passo3 = false;
  }
  else if (sinal3==0 && sinal4==1) // Se algo está entrando e sinal 0,1 -> passo 3
  {
    // Algo entrando na esteira 2 no terceiro passo
    entrandoEsteira2Passo1 = false;
    entrandoEsteira2Passo2 = false;
    entrandoEsteira2Passo3 = true ;
  }
  else if (sinal3==0 && sinal4==0 && entrandoEsteira2Passo3==1) // Se algo está entrando, o sinal é 0,0 e estava no passo 3 -> entrou
  {
    // Algo entrou na esteira 2
    qtdItensEsteira2 = qtdItensEsteira2 + 1;
    entrandoEsteira2Passo1 = false;
    entrandoEsteira2Passo2 = false;
    entrandoEsteira2Passo3 = false;
  }
  else if (sinal3==0 && sinal4==0)  // Se algo está entrando e sinal 0,0 -> objeto voltou pra fora
  {
    // Algo estava entrando na esteira voltou pra fora
    algoEntrandoEsteira2 = false;
    entrandoEsteira2Passo1 = false;
    entrandoEsteira2Passo2 = false;
    entrandoEsteira2Passo3 = false;
  }
}

void acompanhaSaindoEsteira2()
{
  if (sinal3==0 && sinal4==1) // Se algo está saindo e sinal 0,1 -> passo 1
  {
    // Algo saindo da esteira 2 no primeiro passo de saída
    saindoEsteira2Passo1 = true;
    saindoEsteira2Passo2 = false;
    saindoEsteira2Passo3 = false;
  }
  else if (sinal3==1 && sinal4==1) // Se algo está saindo e sinal 1,1 -> passo 2
  {
    // Algo saindo da esteira 2 no segundo passo de saída
    saindoEsteira2Passo1 = false;
    saindoEsteira2Passo2 = true;
    saindoEsteira2Passo3 = false;
  }
  else if (sinal3==1 && sinal4==0) // Se algo está saindo e sinal 1,0 -> passo 3
  {
    // Algo saindo da esteira 2 no terceiro passo de saída
    saindoEsteira2Passo1 = false;
    saindoEsteira2Passo2 = false;
    saindoEsteira2Passo3 = true;
  }
  else if (sinal3==0 && sinal4==0 && saindoEsteira2Passo3==1) // Se algo está saindo, o sinal é 0,0 e estava no passo 3 -> saiu
  {
    if (qtdItensEsteira2==0) // Se haviam zero itens na esteira
    {
      // Impossível algo ter saído de lá
      Serial.println("Situação impossível!!! Não havia nada na esteira 2.");
    }
    else // Caso contrário
    {
      // Algo saiu da esteira
      qtdItensEsteira2 = qtdItensEsteira2 - 1;
    }
    saindoEsteira2Passo1 = false;
    saindoEsteira2Passo2 = false;
    saindoEsteira2Passo3 = false;
  }
  else if (sinal3==0 && sinal4==0) // Se algo está saindo e sinal 0,0 -> objeto voltou para dentro
  {
    // Algo que estava saindo da esteira voltou para dentro
    algoSaindoEsteira2 = false;
    saindoEsteira2Passo1 = false;
    saindoEsteira2Passo2 = false;
    saindoEsteira2Passo3 = false;
  }
}

void verificaEsteira2()
{
  if (sinal3==1 && sinal4==0) // Verifica se agora tem algo entrando
  {
    algoEntrandoEsteira2 = true;
  }
  else if (sinal3==0 && sinal4==1) // Ou se agora tem algo saindo
  {
    algoSaindoEsteira2 = true;
  }
  else  // Ou se continua sem ter algo entrando ou saindo
  {
    algoEntrandoEsteira2 = false;
    algoSaindoEsteira2 = false;
  }
}
