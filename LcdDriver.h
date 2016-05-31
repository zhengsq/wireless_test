#ifndef _LCD_DRIVE_H
#define _LCD_DRIVE_H



extern     uchar  const CharCode[];
extern     uchar  const DIGITAL[];


void CheckBusy( void );
void WriteCommand( uchar CommandByte );
void WriteData( uchar DataByte );
void LcdClear( void );
void LcdInit( void );
void LcdCharWrite(uchar col,uchar page,uchar datanum ,uchar  const *datappt);
void LcdOneByteWrite(signed char col,uchar page,uchar  order,uchar keystu);
void LcdTwoByteWrite(uchar col,uchar page,uchar datanum ,uchar const *datappt);
void ClearLcdLine(uchar page);
void  LcdPictureWrite(uchar col,uchar page,uchar len ,uchar  const *datappt);
void LcdDigitalWrite(uchar col,uchar page,uchar order);
void LcdBoardWrite(uchar col7,uchar page7);











#endif