#include <DS3231.h>
#include<Wire.h>
#include<LiquidCrystal.h>
#define rs 3
#define e 5
#define d4 6
#define d5 7
#define d6 8
#define d7 9
LiquidCrystal lcd(3, 5, 6, 7, 8, 9);
DS3231 clock;
RTCDateTime dig_clk;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  if (!clock.begin()) {
    Serial.println("Could not find RTC");
  }
  clock.setDateTime(__DATE__, __TIME__);
}

void loop() {
  dig_clk = clock.getDateTime();
  clock.forceConversion();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(5, 0);
  if (dig_clk.hour < 10) {
    lcd.print("0");
    lcd.setCursor(6, 0);
    lcd.print(dig_clk.hour);
  }
  else {
    lcd.print(dig_clk.hour);
  }
  lcd.setCursor(7, 0);
  lcd.print(":");
  lcd.setCursor(8, 0);
  if (dig_clk.minute < 10) {
    lcd.print("0");
    lcd.setCursor(9, 0);
    lcd.print(dig_clk.minute);
  }
  else {
    lcd.print(dig_clk.minute);
  }
  lcd.setCursor(10, 0);
  lcd.print(":");
  lcd.setCursor(11, 0);
  if (dig_clk.second < 10) {
    lcd.print("0");
    lcd.setCursor(12, 0);
    lcd.print(dig_clk.second);
  }
  else {
    lcd.print(dig_clk.second);
  }
  if (dig_clk.hour >= 12) {
    lcd.setCursor(14, 0);
    lcd.print("PM");
  }
  else {
    lcd.setCursor(14, 0);
    lcd.print("AM");
  }
  lcd.setCursor(0, 1);
  lcd.print("Date:");
  lcd.setCursor(5, 1);
  if (dig_clk.day < 10) {
    lcd.print("0");
    lcd.setCursor(6, 1);
    lcd.print(dig_clk.day);
  }
  else {
    lcd.print(dig_clk.day);
  }
  lcd.setCursor(7, 1);
  lcd.print("/");
  lcd.setCursor(8, 1);
  if (dig_clk.month < 10) {
    lcd.print("0");
    lcd.setCursor(9, 1);
    lcd.print(dig_clk.month);
  }
  else {
    lcd.print(dig_clk.month);
  }
  lcd.setCursor(10, 1);
  lcd.print("/");
  lcd.setCursor(11, 1);
  lcd.print(dig_clk.year);
  if (dig_clk.second >= 45 && dig_clk.second <= 56) {
    dayTemp();
  }
}
void dayTemp() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Day:");
  lcd.setCursor(4, 0);
  switch (dig_clk.dayOfWeek) {
    case 1:
      lcd.print("Monday");
      break;
    case 2:
      lcd.print("Tuesday");
      break;
    case 3:
      lcd.print("Wednesday");
      break;
    case 4:
      lcd.print("Thursday");
      break;
    case 5:
      lcd.print("Friday");
      break;
    case 6:
      lcd.print("Saturday");
      break;
    case 7:
      lcd.print("Sunday");
      break;
  }
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(5, 1);
  lcd.print(clock.readTemperature());
  lcd.write(223);
  lcd.print("C");
}
