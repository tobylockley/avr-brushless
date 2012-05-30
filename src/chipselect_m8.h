/* 
 * breadboard-esc, an open-source Brushless DC motor controller
 * Copyright (C) 2011 Toby Lockley <tobylockley@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __PINDEFS_M8_H__
#define __PINDEFS_M8_H__ 1

//===================================//
//        ESC PIN DEFINITIONS        //
//===================================//
//Consult microcontroller data sheet before adjusting values
//NOTE: Macro definitions conform to AVR naming conventions.
//	DDR  - Data Direction Register
//	PORT - I/O port name
//	PIN  - Port IN; current state of the I/O port

//---------OUTPUTS----------//
//Note: PINx is used on low side to determine pwm current state
//Channel A
#define HIGH_A_DDR		DDRD
#define HIGH_A_PORT		PORTD
#define HIGH_A			3

#define LOW_A_DDR		DDRD
#define LOW_A_PORT		PORTD
#define LOW_A			4

//Channel B
#define HIGH_B_DDR		DDRD
#define HIGH_B_PORT		PORTD
#define HIGH_B			5

#define LOW_B_DDR		DDRB
#define LOW_B_PORT		PORTB
#define LOW_B			2

//Channel C
#define HIGH_C_DDR		DDRD
#define HIGH_C_PORT		PORTD
#define HIGH_C			7

#define LOW_C_DDR		DDRB
#define LOW_C_PORT		PORTB
#define LOW_C			0

#endif //#ifndef __PINDEFS_M8_H__
