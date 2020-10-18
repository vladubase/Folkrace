/****
	*	@name		LINE FOLLOWER ROBOT
	*	@file 		LineFollowerRobot.c
	*
	*	@author 	Uladzislau 'vladubase' Dubatouka
	*				<vladubase@gmail.com>.
	*	@version	V1.0
	*	@date 		Created on 2020.07.14.
	*
	*	@brief 		This program is controlling the Line following robot using PID regulator.
	*				It has a flexible settings system via #defines at the beginning of the .C main file.
	*				IO ports are configured through registers.
	*	
	*	@attention 	Before program Microcontroller check follow:
	*			@a		1. F_CPU - system clock of external quartz resonator (if needed clock division, see datasheet);
	*			@a		2. QTY_OF_SENSORS and used bits (see "Defines" section and "InitSys" function);
	*			@a		3. MOTORS_NOT_PERFECT parameter, if motors are not identical by speed, torque, gear ratio, etc.
	*			@a		4. PID coefficients
	*
	*  	@attention 	The usual procedure for setting up the PID regulator:
	*			@b		1. At a low speed, we adjust the P-controller (we select a value of kP such 
	*							that in the coolest turns the robot passes keeping the line close to its
	*							extreme sensors). kD and kI are equal to zero, i.e. use a pure P-regulator;
	*			@b		2. Increase the speed, select the value of kD. If the robot went without
	*							inertia when setting the P-controller, then the kP value can be left unchanged.
	*							If the robot has already gone with inertia, as is usually the case
	*							with fast robots, then the kP value will need to be lowered -
	*							we will see this by the fact that the robot will cease to deviate
	*							strongly from the line thanks to the help of the D-controller;
	*			@b		3. When the PD controller is configured, then I can be selected,
	*							reducing the deviation of the robot from the line. The values ??of
	*							the coefficients kD and kP are usually also somewhat lower.
	*							An i-controller is useful for racing where a line can make loops.
	*							Deviation of the robot from a straight line is fraught with
	*							the choice of the wrong direction of movement. When racing on tracks
	*							without loops, the PD controller is often used, since in the general
	*							case it allows you to develop a higher speed.
	*
	*   @note		4.25 ms for main cycle (not counting MAIN_CYCLE_DELAY) with 4 sensors in low-state.
	*				6 ms for main cycle (not counting MAIN_CYCLE_DELAY) with 15 sensors in low-state.
	*
*****/


/************************************** Includes **************************************/

#include <mega328p.h>
#include <mega328p_bits.h>
#include <delay.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


/*************************************** Defines **************************************/

// CLOCK
#define		F_CPU				((uint32_t)	20000000)	// Quartz resonator clock frequency

// GENERAL PARAMETERS
#define		QTY_OF_SENSORS		8U						// Quantity of sensors
#define		AVG_SPEED			((uint8_t)	155)		// Average speed of robot

#define		MOTORS_NOT_PERFECT	true 					// Do the motors have different real parameters (e.g. Speed, Torque, etc.)?
#if MOTORS_NOT_PERFECT
	// There is nothing perfect ;)
	#define	L_MOTOR_MISMATCH	((float)	1.0)		// Coefficients of motor power difference
	#define	R_MOTOR_MISMATCH	((float)	1.07)
#endif /* MOTORS_NOT_PERFECT */

// PID
// Setup: P -> PD -> PID
#define		kP					((uint8_t)	1)			// Proportional	feedback coefficient	
#define		kI					((uint8_t)	0)			// Integral 	feedback coefficient
#define		kD					((uint8_t)	0)			// Differential	feedback coefficient
#define		QTY_OF_ERR			((uint8_t)	10)			// Quantity of errors in memory during last (QTY_OF_ERR * MAIN_CYCLE_DELAY) ms
#define		MAIN_CYCLE_DELAY	((uint8_t)	2)			// The main cycle delay (in ms) for correct work of D-regulation

// Sensor order in the right --> direction
#if (QTY_OF_SENSORS >= 1)
    #define	READ_SENSOR_1		PIND & (1 << DDD2)
#endif /* QTY_OF_SENSORS >= 1 */
#if QTY_OF_SENSORS >= 2
    #define	READ_SENSOR_2		PIND & (1 << DDD4)
#endif /* QTY_OF_SENSORS >= 2 */
#if QTY_OF_SENSORS >= 3
    #define	READ_SENSOR_3		PINC & (1 << DDC5)
#endif /* QTY_OF_SENSORS >= 3 */
#if QTY_OF_SENSORS >= 4
    #define	READ_SENSOR_4		PINC & (1 << DDC4)
#endif /* QTY_OF_SENSORS >= 4 */
#if QTY_OF_SENSORS >= 5
    #define	READ_SENSOR_5		PINC & (1 << DDC3)
#endif /* QTY_OF_SENSORS >= 5 */
#if QTY_OF_SENSORS >= 6
    #define	READ_SENSOR_6		PINC & (1 << DDC2)
#endif /* QTY_OF_SENSORS >= 6 */
#if QTY_OF_SENSORS >= 7
    #define	READ_SENSOR_7		PINC & (1 << DDC1)
#endif /* QTY_OF_SENSORS >= 7 */
#if QTY_OF_SENSORS >= 8
    #define	READ_SENSOR_8		PINC & (1 << DDC0)
#endif /* QTY_OF_SENSORS >= 8 */
#if QTY_OF_SENSORS >= 9
    #define	READ_SENSOR_9		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 9 */
#if QTY_OF_SENSORS >= 10
    #define	READ_SENSOR_10		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 10 */
#if QTY_OF_SENSORS >= 11
    #define	READ_SENSOR_11		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 11 */
#if QTY_OF_SENSORS >= 12
    #define	READ_SENSOR_12		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 12 */                   
#if QTY_OF_SENSORS >= 13
    #define	READ_SENSOR_13		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 13 */
#if QTY_OF_SENSORS >= 14
    #define	READ_SENSOR_14		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 14 */
#if QTY_OF_SENSORS >= 15
    #define	READ_SENSOR_15		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 15 */
#if QTY_OF_SENSORS >= 16
    #define	READ_SENSOR_16		PINx & (1 << DDxx)
#endif /* QTY_OF_SENSORS >= 16 */

//#define	READ_IR_SENSOR		PINx & (1 << DDxx)


/*********************************** Global Variables *********************************/

bool line_data[QTY_OF_SENSORS] = {0};					// Store current values from sensor line


/********************************* Function  prototypes *******************************/

void InitSys (void);
void ReadSensorLineData (void);
float CurrentRobotError (void);


/**************************************** Main ****************************************/

void main (void) {
	// DEFINITION OF VARIABLES
	register float error_history[QTY_OF_ERR] = {0};		// Storing the values of recent errors
	register float error_sum = 0.0;						// Sum of errors in history
	register uint8_t i = 0;
	register float P = 0.0;
	register float I = 0.0;
	register float D = 0.0;
	register float PID_total_correction = 0.0;      	// Sum of P, I, D
	register int16_t left_motor_speed = 0;
	register int16_t right_motor_speed = 0;

	// MICROCONTROLLER INITIALIZATION
	InitSys ();

	// Waiting for a signal on IR sensor
	#ifdef READ_IR_SENSOR
		while (READ_IR_SENSOR) {
			LED_1_ON;
			delay_ms (25);
			LED_1_OFF;
			delay_ms (25);
		}
	#endif /* READ_IR_SENSOR */

	//delay_ms (5000);									// This delay is required by the competition rules
	
	// MAIN CYCLE
	while (true) {
		error_sum = 0.0;

	    // Shift error values
		for (i = 0; i < QTY_OF_ERR - 1; i++) {
			error_history[i] = error_history[i + 1];
		}
		error_history[QTY_OF_ERR - 1] = CurrentRobotError ();

		// Calculation of value P
		P = error_history[QTY_OF_ERR - 1] * kP;			// Current error * kP
		// Calculation of value I
		for (i = 0; i < QTY_OF_ERR; i++) {
			error_sum += error_history[i];
		}
		I = error_sum * kI;								// sum of errors * kI
		// Calculation of value D
		D = (error_history[QTY_OF_ERR - 1] -        	// (current error - error in past) * kD
        	error_history[0]) * kD;

		PID_total_correction = (P + I) + D;

		// 
		left_motor_speed  = AVG_SPEED - (uint16_t)PID_total_correction;
		right_motor_speed = AVG_SPEED + (uint16_t)PID_total_correction;

		// Validating a range of variables
		if (left_motor_speed > 255)
			left_motor_speed = 255;
		else if (left_motor_speed < 0)
			left_motor_speed = 0;
		if (right_motor_speed > 255)
			right_motor_speed = 255;
		else if (right_motor_speed < 0)
			right_motor_speed = 0;

		// Motors power difference compensation
		#if MOTORS_NOT_PERFECT
			OCR2A = 0;
			OCR2B = left_motor_speed * L_MOTOR_MISMATCH;
			OCR0A = 0;
			OCR0B = right_motor_speed * R_MOTOR_MISMATCH;
		#else
			OCR2A = 0;
			OCR2B = left_motor_speed;
			OCR0A = 0;
			OCR0B = right_motor_speed;
		#endif /* MOTORS_NOT_PERFECT */

		delay_ms (MAIN_CYCLE_DELAY);
	}
}


/************************************* Functions **************************************/

void InitSys (void) {
	// Motors
	    // Output mode
		DDRB |= (1 << DDB3);			            	// OC2A
		DDRD |= (1 << DDD6) |			            	// OC0A
				(1 << DDD5) |			            	// OC0B
				(1 << DDD3);			            	// OC2B

	// SensorLine
	    // Input mode
		DDRB &= ~((1 << DDB2) | (1 << DDB1) | (1 << DDB0));
		DDRD &= ~(1 << DDD7);

	// Infrared Sensor
	    // Input mode
		#ifdef READ_SENSOR_IR
			DDRx &= ~(1 << DDxx);
		#endif /* READ_SENSOR_IR */

	// Timer/Counter(s) initialization
		// Timer/Counter 0
		// Fast PWM Mode
		// Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
		// TOP = 0xFF
		// Prescaler: 1:64
		TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
		TCCR0A &= ~((1 << COM0A0) | (1 << COM0B0) | (1 << 3) | (1 << 2));
		TCCR0B |= (1 << CS01) | (1 << CS00);
		TCCR0B &= ~((1 << FOC0A) | (1 << FOC0B) | (1 << 5) | (1 << 4) | (1 << WGM02) | (1 << CS02));
		TCNT0  = 0x00;
		TIMSK0 = 0x00;
		OCR0A  = 0x00;	OCR0B  = 0x00;
        
		// Timer/Counter 1
		// Fast PWM 10-bit Mode
		// Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM (non-inverting mode)
		// TOP = 0x03FF
		// Prescaler: 1:64
		TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11) | (1 << WGM10);
		TCCR1A &= ~((1 << COM1A0) | (1 << COM1B0) | (1 << 3) | (1 << 2));
		TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
		TCCR1B &= ~((1 << ICNC1) | (1 << ICES1) | (1 << 5) | (1 << WGM13) | (1 << CS12));
		TCCR1C = 0x00;
		TCNT1H = 0x00;	TCNT1L = 0x00;
		TIMSK1 = 0x00;
		ICR1H  = 0x00;	ICR1L  = 0x00;
		OCR1AH = 0x00;	OCR1AL = 0x00;
		OCR1BH = 0x00;	OCR1BL = 0x00;

		// Timer/Counter 2
		// Fast PWM Mode
		// Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
		// TOP = 0xFF
		// Prescaler: 1:64
		TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
		TCCR2A &= ~((1 << COM2A0) | (1 << COM2B0) | (1 << 3) | (1 << 2));
		TCCR2B |= (1 << CS22);
		TCCR2B &= ~((1 << FOC2A) | (1 << FOC2B) | (1 << 5) | (1 << 4) | (1 << WGM22) | (1 << CS21) | (1 << CS20));
		TCNT2  = 0x00;
		TIMSK2 = 0x00;
		OCR2A  = 0x00;	OCR2B  = 0x00;

	// Crystal Oscillator division factor: 1
		#pragma optsize-
			CLKPR |= (1 << CLKPCE);
			CLKPR = 0x00;
		#ifdef _OPTIMIZE_SIZE_
			#pragma optsize+
		#endif /* _OPTIMIZE_SIZE_ */
}

void ReadSensorLineData (void) {
	#ifdef READ_SENSOR_1
		line_data[0] = READ_SENSOR_1;
	#endif /* READ_SENSOR_1 */
	#ifdef READ_SENSOR_2
		line_data[1] = READ_SENSOR_2;
	#endif /* READ_SENSOR_2 */
	#ifdef READ_SENSOR_3
		line_data[2] = READ_SENSOR_3;
	#endif /* READ_SENSOR_3 */
	#ifdef READ_SENSOR_4
		line_data[3] = READ_SENSOR_4;
	#endif /* READ_SENSOR_4 */
	#ifdef READ_SENSOR_5
		line_data[4] = READ_SENSOR_5;
	#endif /* READ_SENSOR_5 */
	#ifdef READ_SENSOR_6
		line_data[5] = READ_SENSOR_6;
	#endif /* READ_SENSOR_6 */
	#ifdef READ_SENSOR_7
		line_data[6] = READ_SENSOR_7;
	#endif /* READ_SENSOR_7 */
	#ifdef READ_SENSOR_8
		line_data[7] = READ_SENSOR_8;
	#endif /* READ_SENSOR_8 */
	#ifdef READ_SENSOR_9
		line_data[8] = READ_SENSOR_9;
	#endif /* READ_SENSOR_9 */
	#ifdef READ_SENSOR_10
		line_data[9] = READ_SENSOR_10;
	#endif /* READ_SENSOR_10 */
	#ifdef READ_SENSOR_11
		line_data[10] = READ_SENSOR_11;
	#endif /* READ_SENSOR_11 */
	#ifdef READ_SENSOR_12
		line_data[11] = READ_SENSOR_12;
	#endif /* READ_SENSOR_12 */
	#ifdef READ_SENSOR_13
		line_data[12] = READ_SENSOR_13;
	#endif /* READ_SENSOR_13 */
	#ifdef READ_SENSOR_14
		line_data[13] = READ_SENSOR_14;
	#endif /* READ_SENSOR_14 */
	#ifdef READ_SENSOR_15
		line_data[14] = READ_SENSOR_15;
	#endif /* READ_SENSOR_15 */
	#ifdef READ_SENSOR_16
		line_data[15] = READ_SENSOR_16;
	#endif /* READ_SENSOR_16 */
}

float CurrentRobotError (void) {
	register uint8_t i = 0;
	register float current_error = 0.0;
    
	ReadSensorLineData ();

	for (i = 0; i < QTY_OF_SENSORS; i++) {
	    if (line_data[i] != 0) {
            // If the data on the i-th sensor is zero,
            // then the sensor is located above the black line.
            // Odd degree to preserve the sign '-'
            current_error += pow (QTY_OF_SENSORS / 2 - 0.5 - i, 3);
        }
	}

	return current_error;
}
