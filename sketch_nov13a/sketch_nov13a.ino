int infra1 = 2;
int infra2 = 3;
int infra3 = 11;
int infra4 = 12;

boolean sinal1;
boolean sinal2;
boolean sinal3;
boolean sinal4;

boolean entrando1Esteira1;
boolean entrando2Esteira1;
boolean entrando3Esteira1;
boolean entrando1Esteira2;
boolean entrando2Esteira2;
boolean entrando3Esteira2;

boolean saindo1Esteira1;
boolean saindo2Esteira1;
boolean saindo3Esteira1;
boolean saindo1Esteira2;
boolean saindo2Esteira2;
boolean saindo3Esteira2;

unsigned int quantidadeEsteira1;

unsigned long timer1;
unsigned long timer2;
unsigned long timer3;
unsigned long timer4;

void setup()
{
    pinMode(infra1, INPUT);
    pinMode(infra2, INPUT);
    pinMode(infra3, INPUT);
    pinMode(infra4, INPUT);

    Serial.begin(9600);
}

void loop()
{
    if(millis()-timer1 >= 100)
    {
      timer1 = millis();
      sinal1 = !digitalRead(infra1);
      sinal2 = !digitalRead(infra2);
      sinal3 = !digitalRead(infra3);
      sinal4 = !digitalRead(infra4);
    }
    
    if(millis()-timer2 >= 1000)
    {
      timer2 = millis();
      Serial.print("------- ");
      Serial.println(timer2);
      Serial.print(sinal1);
      Serial.print(sinal2);
      Serial.print('-');
      Serial.print(entrando1Esteira1);
      Serial.print(entrando2Esteira1);
      Serial.print(entrando3Esteira1);
      Serial.print('-');
      Serial.print(saindo1Esteira1);
      Serial.print(saindo2Esteira1);
      Serial.println(saindo3Esteira1);
      Serial.print(sinal3);
      Serial.println(sinal4);
    }
    
    if(millis()-timer3 >= 1000)
    {
      timer3 = millis();
      if(sinal1 && !sinal2 && !saindo2Esteira1)
      {
        Serial.println("Entrando na esteira 1, passo 1");
        entrando1Esteira1 = true;
      }
      else if(sinal1 && sinal2 && (entrando1Esteira1 || entrando3Esteira1))
      {
        Serial.println("Entrando na esteira 1, passo 2");
        entrando1Esteira1 = false;
        entrando2Esteira1 = true;
        entrando3Esteira1 = false;
      }
      else if(!sinal1 && sinal2 && entrando2Esteira1)
      {
        Serial.println("Entrando na esteira 1, passo 3");
        entrando2Esteira1 = false;
        entrando3Esteira1 = true;
      }
      else if(!sinal1 && !sinal2 && entrando3Esteira1)
      {
        Serial.print("Entrou na esteira 1: ");
        Serial.print(++quantidadeEsteira1);
        Serial.println(" itens.");
        entrando3Esteira1 = false;
      }
      
// ------------------------------------------------------------------------------

      if(!sinal1 && sinal2 && (!entrando2Esteira1 || !entrando3Esteira1))
      {
        Serial.println("Saindo da esteira 1, passo 1");
        saindo1Esteira1 = true;
      }
      else if(sinal1 && sinal2 && (saindo1Esteira1 || saindo3Esteira1))
      {
        Serial.println("Saindo da esteira 1, passo 2");
        saindo1Esteira1 = false;
        saindo2Esteira1 = true;
        saindo3Esteira1 = false;
      }
      else if(sinal1 && !sinal2 && saindo2Esteira1)
      {
        Serial.println("Saindo da esteira 1, passo 3");
        saindo2Esteira1 = false;
        saindo3Esteira1 = true;
      }
      else if(!sinal1 && !sinal2 && saindo3Esteira1)
      {
        Serial.println("Saiu da esteira 1");
        saindo3Esteira1 = false;
      }
    }
}
