
String IncomingData = "";
String Temp = "";
char var;
char angles[100];
double theta[7];
double curr[7];
String Serialdata;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  get_data_from_serial();
  //  Serial.println(100);
}

void get_data_from_serial()
{
  if (Serial.available())
  {
    IncomingData = "";
    //    delayMicroseconds(10);
    while (true)
    {
      if (Serial.available())
      {
        var = Serial.read();
        if (var == 'X')
        {
          break;
        }
        IncomingData += String(var);
      }
    }
//    Serial.print("incoming data len ");
//    Serial.println(IncomingData.length());
    Serial.println(IncomingData);
    //Serial.println("\n");
    for(int i=0;i<30;i+=5)
    {
      theta[i/5 +1 ]=IncomingData.substring(i,i+5).toDouble();
    }
    for(int i=30;i<60;i+=5){
      curr[(i-30)/5 +1]=IncomingData.substring(i,i+5).toDouble();
    }
    for(int i=1;i<=6;i++)
    {
      Serial.print(i);Serial.print(" ");
      Serial.print(theta[i]);Serial.print(" ");
      Serial.print(curr[i]);  
      Serial.print(' ');
    }
    Serial.println();
  } 
}

