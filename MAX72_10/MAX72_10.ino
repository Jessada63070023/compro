/* UNO */
// Use the MD_MAX72XX library to Display a Daft Punk LED Helmet
//
// If RUN_DEMO is set to zero the display cycles changes triggered by a switch on
// the MODE_SWITCH pin. This can be substituted for any trigger as implemented 
// by the helmet wearer. 
// If RUN_DEMO is set to 1 the sketch will cycle each element of the display every 
// DEMO_DELAY seconds, without the need for a switch.
//
// Uses the MD_Keyswitch library found at http://arduinocode.codeplex.com/releases

#include <D:\@CLOUD\GDrive\Arduino\D1\MAX72_10\MD_MAX72xx.h>

// --------------------
// MD_MAX72xx hardware definitions and object
// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may 
// need to be adapted
//
#define	MAX_DEVICES	8
#define	CLK_PIN		13  // 13 or SCK
#define	CS_PIN		12  // 2(tx1/09/GPI02จ IS OK TOO, or SS
#define DATA_PIN  11 // 11 or MOSI

MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);                      // SPI hardware interface

int TD_max_row = 16;
int TD_max_col = (MAX_DEVICES/8)*32;
int TD_max_char_row1 = 10;
int TD_max_char_row2 = 12;
int TD_max_char_col = 16;
int TD_normal_row = 3;
int TD_start_not_thai_char = 33;
int TD_start_thai_char = 161;
int TD_gap_pixel = 1;

// thai over 
const int char_char_x1 = 12;
int char_x1[char_char_x1] = { 209,212,213,214,215,232,233,234,235,236,237,238 };

// thai under
const int char_char_x2 = 2;
int char_x2[char_char_x2] = { 216,217 };

unsigned int char_data1[93][10] = {
  {0,0,0,0,0,0,0,0,0,0},         // 33 !
  {0,0,0,0,0,0,0,0,0,0},         // 34 "
  {0,0,0,0,0,0,0,0,0,0},         // 35 #
  {0,0,0,0,0,0,0,0,0,0},         // 36 $
  {0,0,0,0,0,0,0,0,0,0},         // 37 %
  {0,0,0,0,0,0,0,0,0,0},         // 38 &
  {0,0,0,0,0,0,0,0,0,0},         // 39 '
  {0,0,0,0,0,0,0,0,0,0},         // 40 (
  {0,0,0,0,0,0,0,0,0,0},         // 41 )
  {0,0,0,0,0,0,0,0,0,0},         // 42 *
  {0,0,0,0,0,0,0,0,0,0},         // 43 +
  {0,0,0,0,0,0,0,0,0,0},         // 44 ,
  {0,0,0,0,0,0,0,0,0,0},         // 45 -
  {0,0,0,0,0,0,0,0,0,0},         // 46 .
  {0,0,0,0,0,0,0,0,0,0},         // 47 /
  {0,0,0,0,0,0,0,0,0,0},         // 48 0
  {0,0,0,0,0,0,0,0,0,0},         // 49 1
  {0,0,0,0,0,0,0,0,0,0},         // 50 2
  {0,0,0,0,0,0,0,0,0,0},         // 51 3
  {0,0,0,0,0,0,0,0,0,0},         // 52 4
  {0,0,0,0,0,0,0,0,0,0},         // 53 5
  {0,0,0,0,0,0,0,0,0,0},         // 54 6
  {0,0,0,0,0,0,0,0,0,0},         // 55 7
  {0,0,0,0,0,0,0,0,0,0},         // 56 8
  {0,0,0,0,0,0,0,0,0,0},         // 57 9
  {0,0,0,0,0,0,0,0,0,0},         // 58 :
  {0,0,0,0,0,0,0,0,0,0},         // 59 ;
  {0,0,0,0,0,0,0,0,0,0},         // 60 <
  {0,0,0,0,0,0,0,0,0,0},         // 61 =
  {0,0,0,0,0,0,0,0,0,0},         // 62 >
  {0,0,0,0,0,0,0,0,0,0},         // 63 ?
  {0,0,0,0,0,0,0,0,0,0},         // 64 @
  {6144,6144,15360,15360,9216,26112,26112,32256,49920,49920},         // 65 A
  {65024,49920,49920,49920,65024,49920,49920,49920,49920,65024},         // 66 B
  {15360,26112,49664,49152,49152,49152,49152,49664,26112,15360},         // 67 C
  {64512,50688,49920,49920,49920,49920,49920,49920,50688,64512},         // 68 D
  {65024,49152,49152,49152,65024,49152,49152,49152,49152,65024},         // 69 E
  {65024,49152,49152,49152,65024,49152,49152,49152,49152,49152},         // 70 F
  {15872,25344,49408,49152,49152,52992,49920,49920,25344,15616},         // 71 G
  {49920,49920,49920,49920,65280,49920,49920,49920,49920,49920},         // 72 H
  {49152,49152,49152,49152,49152,49152,49152,49152,49152,49152},         // 73 I
  {3072,3072,3072,3072,3072,3072,3072,52224,52224,30720},         // 74 J
  {50688,52224,55296,61440,61440,61440,55296,52224,50688,49920},         // 75 K
  {49152,49152,49152,49152,49152,49152,49152,49152,49152,65024},         // 76 L
  {49344,49344,57792,57792,62400,62400,57024,57024,52416,52416},         // 77 M
  {49920,58112,62208,62208,56064,56064,52992,52992,50944,49920},         // 78 N
  {15360,26112,49920,49920,49920,49920,49920,49920,26112,15360},         // 79 O
  {65024,49920,49920,49920,49920,65024,49152,49152,49152,49152},         // 80 P
  {15360,26112,49920,49920,49920,49920,49920,52992,26112,16128},         // 81 Q
  {65024,49920,49920,49920,49920,65024,49920,49920,49920,49536},         // 82 R
  {31744,50688,50688,49152,28672,7168,1536,50688,50688,31744},         // 83 S
  {65280,6144,6144,6144,6144,6144,6144,6144,6144,6144},         // 84 T
  {49920,49920,49920,49920,49920,49920,49920,49920,26112,15360},         // 85 U
  {49920,49920,26112,26112,26112,9216,15360,15360,6144,6144},         // 86 V
  {49932,49932,49932,26520,26520,14256,15600,6240,6240,6240},         // 87 W
  {49536,49536,25344,13824,7168,7168,13824,25344,49536,49536},         // 88 X
  {49344,49344,24960,13056,7680,3072,3072,3072,3072,3072},         // 89 Y
  {65408,384,768,1536,3072,6144,12288,24576,49152,65408},         // 90 Z
  {0,0,0,0,0,0,0,0,0,0},         // 91 [
  {0,0,0,0,0,0,0,0,0,0},         // 92 \
  {0,0,0,0,0,0,0,0,0,0},         // 93 ]
  {0,0,0,0,0,0,0,0,0,0},         // 94 ^
  {0,0,0,0,0,0,0,0,0,0},         // 95 _
  {0,0,0,0,0,0,0,0,0,0},         // 96 `
  {0,0,0,0,0,0,0,0,0,0},         // 97 a
  {0,0,0,0,0,0,0,0,0,0},         // 98 b
  {0,0,0,0,0,0,0,0,0,0},         // 99 c
  {0,0,0,0,0,0,0,0,0,0},         // 100 d
  {0,0,0,0,0,0,0,0,0,0},         // 101 e
  {0,0,0,0,0,0,0,0,0,0},         // 102 f
  {0,0,0,0,0,0,0,0,0,0},         // 103 g
  {0,0,0,0,0,0,0,0,0,0},         // 104 h
  {0,0,0,0,0,0,0,0,0,0},         // 105 i
  {0,0,0,0,0,0,0,0,0,0},         // 106 j
  {0,0,0,0,0,0,0,0,0,0},         // 107 k
  {0,0,0,0,0,0,0,0,0,0},         // 108 l
  {0,0,0,0,0,0,0,0,0,0},         // 109 m
  {0,0,0,0,0,0,0,0,0,0},         // 110 n
  {0,0,0,0,0,0,0,0,0,0},         // 111 o
  {0,0,0,0,0,0,0,0,0,0},         // 112 p
  {0,0,0,0,0,0,0,0,0,0},         // 113 q
  {0,0,0,0,0,0,0,0,0,0},         // 114 r
  {0,0,0,0,0,0,0,0,0,0},         // 115 s
  {0,0,0,0,0,0,0,0,0,0},         // 116 t
  {0,0,0,0,0,0,0,0,0,0},         // 117 u
  {0,0,0,0,0,0,0,0,0,0},         // 118 v
  {0,0,0,0,0,0,0,0,0,0},         // 119 w
  {0,0,0,0,0,0,0,0,0,0},         // 120 x
  {0,0,0,0,0,0,0,0,0,0},         // 121 y
  {0,0,0,0,0,0,0,0,0,0},         // 122 z
  {0,0,0,0,0,0,0,0,0,0},         // 123 {
  {0,0,0,0,0,0,0,0,0,0},         // 124 |
  {0,0,0,0,0,0,0,0,0,0},         // 125 }
};

unsigned int char_data2[78][12] = {
  {0,0,0,64512,52224,19456,52224,52224,52224,52224,0,0},         // 161 ก
  {0,0,0,60416,60416,27648,27648,27648,27648,30720,0,0},         // 162 ข
  {0,0,0,44032,60416,27648,27648,27648,27648,30720,0,0},         // 163 ฃ
  {0,0,0,30720,52224,52224,60416,52224,52224,52224,0,0},         // 164 ค
  {0,0,0,52224,64512,52224,60416,52224,52224,52224,0,0},         // 165 ฅ
  {0,0,0,42496,58880,26112,26112,26112,30208,27648,0,0},         // 166 ฆ
  {0,0,0,7168,3072,52224,19456,27648,11264,15360,0,0},         // 167 ง
  {0,0,0,31744,50688,1536,7680,1536,1536,1536,0,0},         // 168 จ
  {0,0,0,30720,52224,3072,52224,52224,56320,27648,0,0},         // 169 ฉ
  {0,0,0,58880,27648,26112,26112,26112,26112,31744,0,0},         // 170 ช
  {0,0,0,42496,60416,26112,26112,26112,26112,31744,0,0},         // 171 ซ
  {0,0,0,63680,52416,19648,52416,52416,52928,60800,0,0},         // 172 ฌ
  {0,0,0,63680,52416,19648,52416,53184,53184,57344,3136,3968},         // 173 ญ
  {0,0,0,31744,26112,9728,26112,26112,26112,58880,1536,32256},         // 174 ฎ
  {0,0,0,31744,26112,9728,26112,26112,26112,58880,7680,28160},         // 175 ฏ
  {0,0,1536,32256,50688,1536,7680,1536,1536,1536,0,32256},         // 176 ฐ
  {0,0,0,48128,62976,26112,26112,26112,26112,26112,0,0},         // 177 ฑ
  {0,0,0,52416,64704,52416,52416,52416,61120,28032,0,0},         // 178 ฒ
  {0,0,0,63680,52416,19648,52416,52416,60864,59072,0,0},         // 179 ณ
  {0,0,0,31744,50688,50688,62976,54784,62976,26112,0,0},         // 180 ด
  {0,0,0,27648,65024,50688,62976,54784,62976,26112,0,0},         // 181 ต
  {0,0,0,63488,52224,19456,52224,52224,60416,60416,0,0},         // 182 ถ
  {0,0,0,60416,30208,26112,26112,26112,26112,26112,0,0},         // 183 ท
  {0,0,0,31744,49152,64512,3072,52224,52224,63488,0,0},         // 184 ธ
  {0,0,0,58880,26112,26112,26112,26112,28160,13824,0,0},         // 185 น
  {0,0,0,58880,26112,26112,26112,26112,26112,31744,0,0},         // 186 บ
  {0,1536,1536,58880,26112,26112,26112,26112,26112,31744,0,0},         // 187 ป
  {0,0,0,25344,49920,56064,56064,56064,56064,65024,0,0},         // 188 ผ
  {0,768,768,25344,49920,56064,56064,56064,56064,65024,0,0},         // 189 ฝ
  {0,0,0,60800,28032,28032,28032,28032,28032,32512,0,0},         // 190 พ
  {0,384,384,60800,28032,28032,28032,28032,28032,32512,0,0},         // 191 ฟ
  {0,0,0,31744,26112,9728,26112,26112,26112,58880,0,0},         // 192 ภ
  {0,0,0,58880,26112,26112,26112,26112,30208,27648,0,0},         // 193 ม
  {0,0,0,27648,52224,60416,27648,52224,52224,63488,0,0},         // 194 ย
  {0,0,0,30720,52224,49152,63488,3072,3072,6144,0,0},         // 195 ร
  {0,0,0,63488,52224,19456,52224,52224,60416,60416,3072,3072},         // 196 ฤ
  {0,0,0,30720,52224,3072,31744,52224,60416,60416,0,0},         // 197 ล
  {0,0,0,31744,26112,9728,26112,26112,26112,58880,1536,1536},         // 198 ฦ
  {0,0,0,28672,55296,55296,6144,6144,55296,28672,0,0},         // 199 ว
  {0,0,3072,31744,52224,52224,60416,52224,52224,52224,0,0},         // 200 ศ
  {0,0,0,58880,26112,26112,28416,26112,26112,31744,0,0},         // 201 ษ
  {0,0,3072,31744,52224,3072,31744,52224,60416,60416,0,0},         // 202 ส
  {0,0,0,60928,28160,30208,26112,26112,26112,26112,0,0},         // 203 ห
  {0,0,192,60800,28032,28032,28032,28032,28032,32512,0,0},         // 204 ฬ
  {0,0,0,30720,52224,3072,60416,52224,52224,64512,0,0},         // 205 อ
  {0,0,3072,31744,52224,3072,60416,52224,52224,64512,0,0},         // 206 ฮ
  {0,0,0,56320,64512,3072,3072,3072,3072,3072,0,0},         // 207 ฯ
  {0,0,0,0,49152,61440,0,49152,61440,0,0,0},         // 208 ะ
  {0,0,49152,63488,0,0,0,0,0,0,0,0},         // 209 ั
  {0,0,0,57344,12288,12288,12288,12288,12288,12288,0,0},         // 210 า
  {49152,49152,0,3584,768,768,768,768,768,768,0,0},         // 211 ำ
  {0,0,0,64512,0,0,0,0,0,0,0,0},         // 212 ิ
  {0,0,3072,64512,0,0,0,0,0,0,0,0},         // 213 ี
  {0,7168,5120,63488,0,0,0,0,0,0,0,0},         // 214 ึ
  {0,5120,5120,64512,0,0,0,0,0,0,0,0},         // 215 ื
  {0,57344,24576,24576,0,0,0,0,0,0,0,0},         // 216 ุ
  {0,60416,27648,31744,0,0,0,0,0,0,0,0},         // 217 ู
  {0,32768,0,0,0,0,0,0,0,0,0,0},         // 218 ฺ
  {}, 
  {}, 
  {}, 
  {}, 
  {}, 
  {0,0,0,49152,49152,49152,49152,49152,49152,49152,0,0},         // 224 เ
  {0,0,0,27648,27648,27648,27648,27648,27648,27648,0,0},         // 225 แ
  {28672,57344,24576,24576,24576,24576,24576,24576,24576,24576,0,0},         // 226 โ
  {24576,61440,45056,12288,12288,12288,12288,12288,12288,12288,0,0},         // 227 ใ
  {40960,61440,28672,12288,12288,12288,12288,12288,12288,12288,0,0},         // 228 ไ
  {0,0,0,57344,12288,12288,12288,12288,12288,12288,12288,12288},         // 229 ๅ
  {0,0,0,55296,64512,35840,52224,3072,3072,3072,3072,3072},         // 230 ๆ
  {1024,30720,50176,64512,0,0,0,0,0,0,0,0},         // 231 ็
  {12288,12288,0,0,0,0,0,0,0,0,0,0},         // 232 ่
  {13312,6144,0,0,0,0,0,0,0,0,0,0},         // 233 ้
  {29696,22528,0,0,0,0,0,0,0,0,0,0},         // 234 ๊
  {6144,15360,6144,0,0,0,0,0,0,0,0,0},         // 235 ๋
  {3072,6144,7168,0,0,0,0,0,0,0,0,0},         // 236 ์
  {3072,3072,0,0,0,0,0,0,0,0,0,0},         // 237 ํ
  {3072,3072,0,0,0,0,0,0,0,0,0,0},         // 238 ๎
};


void TD_setPoint(uint16_t r, uint16_t c, bool state)
{
  uint16_t nr = 0;
  uint16_t nc = 0;

  if (r<=0 || r>TD_max_row) return;
  if (c<=0 || c>TD_max_col) return;
  
  if (r>8) {
    r=r-8;
    nc=TD_max_col;
  }
  nr = r-1;
  nc = nc+TD_max_col-c;
  
  mx.MysetPoint(nr, nc, state);
}

char * TD_IntToBin(unsigned int p_ui)
{
  static char ret[17];        // need to change if expand font width

  for (int i=0; i<TD_max_char_col; i++) ret[TD_max_char_col-1-i]='0'+((p_ui&(1<<i))>0);
  ret[TD_max_char_col] ='\0';

  return ret;
}

void TD_SerialShowBinChar2(int p_idx)
{
  String c;

  Serial.println(p_idx);
  for (int i=0; i<TD_max_char_row2; i++) {
    c = TD_IntToBin(char_data2[p_idx][i]);
    c.replace("1","X");
    c.replace("0"," ");
    Serial.println(c);
  }    
  Serial.println("");
}    

int TD_IsX1(int idx)
{
  int ret=0;

  for (int i=0; i<char_char_x1; i++) {
    if (char_x1[i]==idx) {
      ret=1;
      break;
    }
  }

  return ret;
}

int TD_IsX2(int idx)
{
  int ret=0;

  for (int i=0; i<char_char_x2; i++) {
    if (char_x2[i]==idx) {
      ret=1;
      break;
    }
  }

  return ret;
}

void TD_WriteChar(int p_r, int p_c, int p_idx)
{
  char * c;

  // not thai
  if (p_idx<TD_start_thai_char) {
    p_idx=p_idx-TD_start_not_thai_char;
    //TD_SerialShowBinChar2(p_idx);
    
    for (int i=0; i<TD_max_char_row1; i++) {
      c =  TD_IntToBin(char_data1[p_idx][i]);
      for (int j=0; j<TD_max_char_col; j++)
        if (c[j]=='1') {
          TD_setPoint(p_r+i, p_c+j, true);
        }
    }
  // thai
  } else {
    p_idx=p_idx-TD_start_thai_char;
    //TD_SerialShowBinChar2(p_idx);
    
    for (int i=0; i<TD_max_char_row2; i++) {
      c =  TD_IntToBin(char_data2[p_idx][i]);
      for (int j=0; j<TD_max_char_col; j++)
        if (c[j]=='1') {
          TD_setPoint(p_r+i, p_c+j, true);
        }
    }
  }
  
}

int TD_CharWidth(int p_idx)
{
  char * c;
  int w=0;

  if (p_idx<TD_start_thai_char) {
    p_idx=p_idx-TD_start_not_thai_char;

    for (int i=0; i<TD_max_char_row1; i++) {
      c =  TD_IntToBin(char_data1[p_idx][i]);
      for (int j=0; j<TD_max_char_col; j++)
        if (c[j]=='1') {
          if (j>=w) w=j;
        }
    }

  // thai
  } else {
    p_idx=p_idx-TD_start_thai_char;

    for (int i=0; i<TD_max_char_row2; i++) {
      c =  TD_IntToBin(char_data2[p_idx][i]);
      for (int j=0; j<TD_max_char_col; j++)
        if (c[j]=='1') {
          if (j>=w) w=j;
        }
    }
  }

  return w+1;
}

int TD_Char2Width(int p_idx)
{
  char * c;
  int w=0;

  for (int i=0; i<TD_max_char_row2; i++) {
    c =  TD_IntToBin(char_data2[p_idx][i]);
    for (int j=0; j<TD_max_char_col; j++)
      if (c[j]=='1') {
        if (j>=w) w=j;
      }
  }

  return w+1;
}

void TD_WriteText(int p_r, int p_c, String p_text)
{
  char c1;
  char c2;
  int w=0;
  int idx=0;
  int normal;

  mx.clear();  
  for (int i=0; i<p_text.length(); i++) {
    c1 = p_text[i];
    // E0 224 Thai
    if ((int)c1==224) {
      c1=p_text[i+1];
      c2=p_text[i+2];
      // B8,81(129)  ก - ฮ 
      if ((int)c1==184 && ((int)c2+32)>=161 && ((int)c2+32)<=207) {
        // ก 81 = 129 --> +32 --> 161
         idx=(int)c2+32;
      }
      // B8,B0(176)  สระ
      if ((int)c1==184 && ((int)c2+32)>=208 && ((int)c2+32)<=218) {
        // ะ B0 = 176 --> +32 --> 208
         idx=(int)c2+32;
      }
      // B9,80(128)  สระ
      if ((int)c1==185 && ((int)c2+96)>=224 && ((int)c2+96)<=231) {
        // เ 80 = 176 --> +96 --> 224
         idx=(int)c2+96;
      }
      // B9,B0(136)  วรรณยุก
      if ((int)c1==185 && ((int)c2+96)>=232 && ((int)c2+96)<=238) {
        // ่ 88 = 136 --> +96 --> 208
         idx=(int)c2+96;
      }
      i=i+2;
    } else {
      idx=(int)c1;
    }

    normal=1;
    // thai over
    if (TD_IsX1(idx)==1) {
      w=TD_CharWidth(idx);
      TD_WriteChar(p_r-2,p_c-(w+TD_gap_pixel),idx);
      normal=0;
    } 
    // thai under
    if (TD_IsX2(idx)==1) {
      w=TD_CharWidth(idx);
      TD_WriteChar(p_r+10,p_c-(w+TD_gap_pixel),idx);
      normal=0;
    } 
    if (normal==1) {
      switch (idx) {
        case 32:  // space
          p_c=p_c+8;
          break;
        case 211: // ำ
          w=TD_CharWidth(idx);
          TD_WriteChar(p_r,p_c-(3+TD_gap_pixel),idx);
          p_c=p_c-3+w+TD_gap_pixel;
          break;
        default:
          TD_WriteChar(p_r,p_c,idx);
          w=TD_CharWidth(idx);
          p_c=p_c+w+TD_gap_pixel;
          break;
      }
    }
  }
  mx.MyflushBufferAll();
}

void TD_Text(String p_text)
{
  TD_WriteText(TD_normal_row,1,p_text);
}  

void TD_ScrollText(String p_text, int p_n)
{
  int c;
  int n;

  for (int i=TD_max_col; i>=p_n*-8; i--) {
    TD_WriteText(TD_normal_row,i,p_text);
    
    delay(30);
  }
}  

void setup()
{
  mx.begin();
  Serial.begin(9600);

//  String t;
//  t = "เแโใไ";
//  TD_Text(t);
  
}

void loop() 
{

  String t;
  
//  t = "การทดสอบ";
//  TD_ScrollText(t,10);
//  t = "กขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรฤลฦวศษสหฬอฮ";
//  TD_ScrollText(t,46);
//  t = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//  TD_ScrollText(t,28);
//
//  t = "ภาษาไทย PASA UNGKID OK";
//  TD_ScrollText(t,25);
//  t = "เสียงล่ำลือ เสียงล่ำลือ ถึงข่าวดี";
//  TD_ScrollText(t,25);
//  t = "D ไหม  D ไหม  D ไหม  หา    ดี   ฮ่า";
//  TD_ScrollText(t,35);

  t = "สวัสดีครับ คลิปนี้พูดเรื่องการใช้ DOT MATRIX แสดงภาษาไทย";
  TD_ScrollText(t,45);

//  t = "THIS IS DEMO การทดสอบ";
//  TD_ScrollText(t,25);
  
}

