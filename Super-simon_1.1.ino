//Simon

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Initialisation des LEDs et boutons poussoirs.
int led1 = 2; //LED rouge
int led2 = 3; //LED verte
int led3 = 4; //LED bleue
int led4 = 5; //LED jaune
int bouton1 = 6; //Bouton rouge
int bouton2 = 7; //Bouton vert
int bouton3 = 8; //Bouton bleu
int bouton4 = 9; //Bouton jaune
int speaker = 10; //Speaker

//Information du Port Serial
String inData ="" ;

//Fréquences des sons de chaque couleur
int son[] = {261, 330, 392, 523};
//            Do,  Mi, Sol,  Do

//Tableau de séquence à jouer
int sequence[50];
//Personne ne dépasse jamais le niveau 50...

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void setup()
{
  //Initialisation des entrées/sorties
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(bouton4, INPUT);
  pinMode(speaker, OUTPUT);
  Serial.begin(9600);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void loop()
{
  randomSeed(analogRead(A0));


  //Attente de pression sur une touche ou du lancement sur visual studio
  lectureBouton();
  inData ="";

  //Son de lancement du jeu.
  melodieLancement();
  delay(2000);

  //Début du jeu
  boolean gameOver = false;
  int presse;
  int niveau = 0;
  while (!gameOver)
  {
    nouvelleNote(niveau);
    jouerSequence(niveau);

    for (int i = 0; i <= niveau; i++) //Attend que le joueur tape chaque note de la séquence
    {
      presse = lectureBouton(); //Lecture du bouton appuyé par le joueur
      jouerNote(presse); //Joue la note du joueur
      if (presse != sequence[i])
      {
        gameOver = true;
        melodieGameOver();
      }
      if (gameOver) {
        Serial.println("P");
        break;
      }
    }
    niveau++;
    if (!gameOver)Serial.println("G");
    delay(1000);

  }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int lectureBouton()
{



  int boutonPresse = 0;

  while (!boutonPresse && inData!="L")
  {
    if (Serial.available() > 0)
    {
      inData = Serial.readStringUntil('#') ;
      Serial.println(inData);
    }

    if (digitalRead(bouton1))
    {
      boutonPresse = 1;
    }
    if (digitalRead(bouton2))
    {
      boutonPresse = 2;
    }
    if (digitalRead(bouton3))
    {
      boutonPresse = 3;
    }
    if (digitalRead(bouton4))
    {
      boutonPresse = 4;
    }
  }
  return boutonPresse;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void jouerNote(int numero)
{
  switch (numero)
  {
    case 1:
      digitalWrite(led1, HIGH);
      break;
    case 2:
      digitalWrite(led2, HIGH);
      break;
    case 3:
      digitalWrite(led3, HIGH);
      break;
    case 4:
      digitalWrite(led4, HIGH);
      break;
  }
  tone(speaker, son[numero - 1]);
  delay(300);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  noTone(speaker);

  delay(200);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Joue toute la séquence

void jouerSequence(int niveau)
{
  for (int i = 0; i <= niveau; i++)
  {
    jouerNote(sequence[i]);
  }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Nouvelle note aléatoire

void nouvelleNote(int niveau)
{
  sequence[niveau] = (int)random(1, 5);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Témoin lancement (petite séquence lumineuse)

void melodieLancement()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[0]);
  delay(300);
  tone(speaker, son[1]);
  delay(300);
  tone(speaker, son[2]);
  delay(300);
  tone(speaker, son[3]);
  delay(300);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  noTone(speaker);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Témoin Game Over
void melodieGameOver()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[3]);
  delay(150);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(150);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[2]);
  delay(150);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[1]);
  delay(150);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[0]);
  delay(150);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(500);
  noTone(speaker);
}


