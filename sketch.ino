// Declare variables
  boolean halt = false;
  int radd = 0;
  int op = 0;

void setup() {
  Serial.begin(9600);

  // Initialize pins
  for (int i = 0; i < 17; i++) 
  {
    pinMode(i, OUTPUT);
  }
  // Initialize more pins
  for(int i = 22; i <= 28; i += 2)
  {
    pinMode(i, OUTPUT);
  }
  // Initialize the input pins
  for (int i = 53; i >= 23; i -= 2) 
  {
    pinMode(i, INPUT);
  }
  // Reset the PC
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);  
}


void loop() {

  if (!halt) 
  {
    // Turn the pin low to allow the pc value to flow into the address bus of the ram
    digitalWrite(8, LOW);

    // Enable the read pin on ram
    digitalWrite(9, HIGH);

    for (int i = 53; i >= 23; i -= 2) 
    {
      int value = digitalRead(i);
      // Process the value as needed
      Serial.print("Pin ");
      Serial.print(i);
      Serial.print(" value: ");
      Serial.println(value);
    }
    delay(1000);
    digitalWrite(9, LOW);
    // Calcuate the op code
    int j = 0;
    op = 0;
    for (int i = 29; i >= 23; i -= 2) 
    {
      op |= (digitalRead(i) << j);
      j++;
    }
    Serial.println(op);
    // Take decisions according to op code
    if (op == 0) {
      // Load instruction
      Serial.println("load");
      // Read the register address
      j = 0;
      radd = 0;
      for (int i = 37; i >= 31; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the memory address into the output address pins
      j = 0;
      for (int i = 53; i >= 39; i -= 2) {
        if(j == 0 || j == 1)
        digitalWrite((2*j) + 30,digitalRead(i));
        else
          digitalWrite(j, digitalRead(i));
        j++;
      }
      // Turn the pin high to allow the instruction address to flow into the address bus of the ram
      digitalWrite(8, HIGH);
      delay(1000);
      // Select the memory output as input into the register-file
      digitalWrite(14, LOW);

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      // Enable the read pin on ram
      digitalWrite(9, HIGH);
      delay(1000);
      // Enable the write pin in the register to read the value
      digitalWrite(16, HIGH);
      delay(1000);
      // Disable the read pin on ram
      digitalWrite(16, LOW);
    
      digitalWrite(9, LOW);

      digitalWrite(15, HIGH);
    
    }
    else if (op == 1) {
      // Addition instruction
      Serial.println("add");
      // Read the first register address
      j = 0;
      radd = 0;
      for (int i = 37; i >= 31; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      // Enable the read pin in the register to read the value
      digitalWrite(15, HIGH);
      delay(1000);
      // Enable the first operand to flow into the ALU
      digitalWrite(11, LOW);
      digitalWrite(52, HIGH);
      delay(1000);

      // Disable the read pin in the register
      digitalWrite(52, LOW);
      digitalWrite(15, LOW);

      // Read the second register address
      j = 0;
      radd = 0;
      for (int i = 45; i >= 39; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      delay(1000);
      // Enable the read pin in the register to read the value
      digitalWrite(15, HIGH);
      delay(1000);

      // Enable the second operand to flow into the ALU
      digitalWrite(11, HIGH);
      delay(1000);
      digitalWrite(52, HIGH);
      delay(1000);

      digitalWrite(52, LOW);
      // Disable the read pin in the register
      digitalWrite(15, LOW);
      delay(1000);

      // Select the addition option in the adder/subtractor
      digitalWrite(20, LOW);
      digitalWrite(21, LOW);

      // Select the alu output as input into the register-file
      digitalWrite(14, HIGH);

      // Read the third register address
      j = 0;
      radd = 0;
      for (int i = 53; i >= 47; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      // Enable the write pin in the register to read the value
      digitalWrite(16, HIGH);
      delay(1000);
      digitalWrite(16, LOW);
    }
    else if (op == 2) {
      // Subtraction instruction
      Serial.println("subtract");
      // Read the first register address
      j = 0;
      radd = 0;
      for (int i = 37; i >= 31; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }
      // Enable the read pin in the register to read the value
      digitalWrite(15, HIGH);
      delay(1000);
      // Enable the first operand to flow into the ALU
      digitalWrite(11, LOW);
      digitalWrite(52, HIGH);
      delay(1000);

      // Disable the read pin in the register
      digitalWrite(52, LOW);
      digitalWrite(15, LOW);

      // Read the second register address
      j = 0;
      radd = 0;
      for (int i = 45; i >= 39; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      delay(1000);
      // Enable the read pin in the register to read the value
      digitalWrite(15, HIGH);
      delay(1000);

      // Enable the second operand to flow into the ALU
      digitalWrite(11, HIGH);
      delay(1000);
      digitalWrite(52, HIGH);
      delay(1000);

      digitalWrite(52, LOW);
      // Disable the read pin in the register
      digitalWrite(15, LOW);
      delay(1000);

      // Select the asubtraction option in the adder/subtractor
      digitalWrite(20, HIGH);
      digitalWrite(21, LOW);

      // Select the alu output as input into the register-file
      digitalWrite(14, HIGH);

      // Read the third register address
      j = 0;
      radd = 0;
      for (int i = 53; i >= 47; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      // Enable the write pin in the register to read the value
      digitalWrite(16, HIGH);
      delay(1000);
      digitalWrite(16, LOW);
    }
    else if (op == 3) {
      // Store
      Serial.println("store");
      digitalWrite(8, HIGH);
      delay(1000);
      // Read the register address
      int j = 0;
      radd = 0;
      for (int i = 37; i >= 31; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }
      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      // Write the memory address into the output address pins
      j = 0;
      for (int i = 53; i >= 39; i -= 2) {
        digitalWrite(j, digitalRead(i));
        j++;
      }

      // Enable the read pin in the register to read the value
      digitalWrite(15, HIGH);
      delay(1000);
      // Enable the write pin in the memory to write the value
      digitalWrite(10, HIGH);
      delay(1000);
      digitalWrite(10, LOW);

      // Disable the read pin for the register
      digitalWrite(15, LOW);
    }
    else if (op == 4) {
      // Halt
      Serial.println("halt");
      halt = true;
      // Reset the PC
      digitalWrite(12, HIGH);
      delay(1000);
      digitalWrite(12, LOW);  
  }
  else if (op == 5) {
    // Bit-wise xor instruction
      Serial.println("Bit-wise XOR");
      // Read the first register address
      j = 0;
      radd = 0;
      for (int i = 37; i >= 31; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }
      // Enable the read pin in the register to read the value
      digitalWrite(15, HIGH);
      delay(1000);
      // Enable the first operand to flow into the ALU
      digitalWrite(11, LOW);
      digitalWrite(52, HIGH);
      delay(1000);

      // Disable the read pin in the register
      digitalWrite(52, LOW);
      digitalWrite(15, LOW);

      // Read the second register address
      j = 0;
      radd = 0;
      for (int i = 45; i >= 39; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      delay(1000);
      // Enable the read pin in the register to read the value
      digitalWrite(15, HIGH);
      delay(1000);

      // Enable the second operand to flow into the ALU
      digitalWrite(11, HIGH);
      delay(1000);
      digitalWrite(52, HIGH);
      delay(1000);

      digitalWrite(52, LOW);
      // Disable the read pin in the register
      digitalWrite(15, LOW);
      delay(1000);

      // Select the bit wise xor option in the alu
      digitalWrite(21, HIGH);

      // Select the alu output as input into the register-file
      digitalWrite(14, HIGH);

      // Read the third register address
      j = 0;
      radd = 0;
      for (int i = 53; i >= 47; i -= 2) {
        radd |= (digitalRead(i) << j);
        j++;
      }

      // Write the address into the address bus of the register file
      j = 0;
      for (int i = 28; i >= 22; i -= 2) {
        digitalWrite(i, (radd >> j) & 1);
        j++;
      }

      // Enable the write pin in the register to read the value
      digitalWrite(16, HIGH);
      delay(1000);
      digitalWrite(16, LOW);
  }
    
    
    
        // Pulse the output pin HIGH
      digitalWrite(13, HIGH);
      delay(1000);  // Delay for 250 milliseconds (1/4 second)

      // Turn off the output pin
      digitalWrite(13, LOW);
      delay(1000);  // Delay for another 250 milliseconds
  }

  // This sequence repeats, resulting in 4 pulses per second
}