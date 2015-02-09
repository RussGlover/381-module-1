/*
 * Screen.h
 *
 *  Created on: 2015-01-26
 *      Author: Allen
 */

#ifndef SCREEN_H_
#define SCREEN_H_

void Screen_Init (void);
void Screen_Clear (void);
void Draw_Menu (void) ;
void Draw_Arrow (int y);
void Draw_Bars (int x,int height,int colour,int pre_height[]);
void Draw_Axis (int colour);
void Draw_Background(int colour);
void Display_Data (short int data[]);
void Char_Clearonly(void);
void Draw_Read(void);
void Draw_Write(void);
void Clear_Arrows(void);
#endif /* SCREEN_H_ */
