int bright=0;
int fadeamt = 5;
const int led = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(led, bright);    
  bright += fadeamt;
  if (bright== 0 || bright== 255) {
     fadeamt = -fadeamt; 
  }  
  delay(30);
}
