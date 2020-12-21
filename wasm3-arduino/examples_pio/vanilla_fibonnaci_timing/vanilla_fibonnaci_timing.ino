unsigned long beginTime, endTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  beginTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  fib(24);
  endTime = millis();
  Serial.println(endTime - beginTime);
  beginTime = millis();
}

unsigned long fib(int n) {
  unsigned long beginning[] = {0,1};
  if (n < 2)
    return beginning[n];
  else {
    return fib(n-1) + fib(n-2);  
  }
}
