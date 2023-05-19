int stock = 10; 
bool lowStockNotified = false; 

void irsensor()
{
  int sensorValue = digitalRead(2);
  if (sensorValue == LOW && stock > 0)
  { 
    stock--;
    Serial.print("Stock: "); 
    Serial.println(stock); 
    delay(500);
  }
  
  if (stock < 3 && !lowStockNotified)
  { 
    Serial.println("Stock Low"); 
    lowStockNotified = true; 
  }
  
  if (stock == 0) 
  {
    Serial.println("Finish Product");
    while (true) {} 
  }
}

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
irsensor();
  
}
