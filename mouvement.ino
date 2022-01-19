void setup()
{
  Serial.begin(9600);  // set baud rate as 9600
  pinMode(6,INPUT); // set Pin mode as input
}
 
void loop()
{
  int state = digitalRead(6); // read from PIR sensor
  if (state == 1)
  Serial.println("y a quelqu'un");  // When there is a response
  else
  Serial.println("na pu");  // Far from PIR sensor
}
