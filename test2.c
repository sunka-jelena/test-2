#include <LiquidCrystal.h>
#include <util/delay.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte herc[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte karo[8]=
{
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
byte tref[8]=
{
  B00100,
  B01110,
  B01110,
  B11111,
  B01110,
  B00100,
  B00100,
  B00000
  
};
byte pik[8]=
{
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01010,
  B00100
  
};

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}



int main()
{
  	lcd.begin(16, 2);
  	lcd.createChar(0,pik);
  	lcd.createChar(1,karo);
    lcd.createChar(2,herc);
    lcd.createChar(3,tref);
    lcd.setCursor(0, 0);
  	lcd.print("Pritisni '*'");
  	int j=0;
  	int m=0;
  
   
  	
	unsigned char prethodni = 0, sadasnji = 0;
    char taster = 0;
    char novi_taster = 0;
  
	while(1) //stalno proveravam stanje tastera
	{
		taster = ocitaj_taster();
      	prethodni = sadasnji;
		sadasnji = taster;
      
 		if (taster == '*' && !prethodni && sadasnji)
		{
		
			
          lcd.clear();
          for(int i=0; i<4; i++)
          {
          	int broj=random(3);
            lcd.setCursor(i, 0);
            lcd.write(byte(broj));   
            
          }
          
          _delay_ms(2000);
           lcd.clear();
           lcd.print("----");
          	
		}
      else
			{
				if(taster != '5' && !prethodni && sadasnji)
				{
					switch(taster)
					{
						case '2': 
							if(j != 3)
							{
								j++;	
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							
							}
							else
							{
								j=0;
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							}
							break;
                      case '8': 
							if(j != 0)
							{
								j--;	
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							
							}
							else
							{
								j=3;
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							}
							break;
                      case '4': 
							if(m != 0)
							{
								m--;	
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							
							}
							else
							{
								m=3;
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							}
							break;
                      case '6': 
							if(m != 3)
							{
								m++;	
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							
							}
							else
							{
								m=0;
								lcd.blink();
								lcd.setCursor(m, 0);
								lcd.write(byte(j));
							}
							break;
                    }
                }
                      
                      
                      
           }

	}
  
 
  
  	return 0;
}