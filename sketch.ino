// Definisikan pin untuk LED
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int buttonPin = 7;

// Variabel untuk menyimpan status tombol
int buttonState = 0;
int lastButtonState = 0;
bool isRunning = false; // Variabel untuk melacak apakah running mode aktif
int currentLED = 0; // Variabel untuk melacak LED yang menyala

void setup() {
  // Atur pin LED sebagai output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  // Atur pin tombol sebagai input dengan pull-up resistor internal
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Awal semua LED mati
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  // Membaca status tombol
  buttonState = digitalRead(buttonPin);

  // Cek apakah tombol ditekan (LOW karena menggunakan pull-up)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Tombol ditekan, toggle running mode
    isRunning = !isRunning;
    
    // Matikan semua LED saat running mode dimatikan
    if (!isRunning) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
    
    // Debouncing delay untuk tombol
    delay(200);
  }
  
  // Jika running mode aktif
  if (isRunning) {
    // Matikan semua LED terlebih dahulu
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    // Nyalakan LED sesuai dengan urutan
    if (currentLED == 0) {
      digitalWrite(led1, HIGH);  // Nyalakan LED pertama
    } else if (currentLED == 1) {
      digitalWrite(led2, HIGH);  // Nyalakan LED kedua
    } else if (currentLED == 2) {
      digitalWrite(led3, HIGH);  // Nyalakan LED ketiga
    }

    // Pindahkan ke LED berikutnya
    currentLED++;

    // Jika LED ketiga sudah menyala, kembali ke LED pertama
    if (currentLED > 2) {
      currentLED = 0;
    }

    // Berikan delay agar LED terlihat bergantian
    delay(500); // Sesuaikan waktu pergantian LED (500 ms)
  }

  // Simpan status tombol terakhir untuk pengecekan di loop berikutnya
  lastButtonState = buttonState;
}