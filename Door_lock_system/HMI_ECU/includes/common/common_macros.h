/*
 *  File name:  comon_macros.h
 *  Created on: Apr 24, 2019
 *  Author:     Saad
 *  Description: file includes most commonly used macros
 */

#ifndef INCLUDES_COMMON_COMMON_MACROS_H_
#define INCLUDES_COMMON_COMMON_MACROS_H_

/* macro to set a certain BIT inside a register to 1 */
#define CLEAR_BIT(REGISTER,BIT) ((REGISTER)&=(~(1<<(BIT))))

/* macro to clear a certain BIT inside a register (put its value to be zero) */
#define SET_BIT(REGISTER,BIT)  ((REGISTER)|=(1<<(BIT)))

/*macro to toggle a bit */
#define TOGGLE_BIT(REGISTER,BIT) ((REGISTER)^=(1<<(BIT)))

/* macro to check if bit is set (equal to 1) */
#define BIT_IS_SET(REGISTER,BIT) ((REGISTER)&(1<<(BIT)))

/* macro to check if a certain bit inside a register is cleared */
#define BIT_IS_CLEAR(REGISTER,BIT) (!((REGISTER)&(1<<(BIT))))

/* this macro is to rotate right  */
#define ROR(REGISTER,num) ((REGISTER)=(((REGISTER)>>(num))|((REGISTER)<<(8-(num)))))

/* rotate bit of the register in the left direction */
#define ROL(REGISTER,num) ((REGISTER)=(((REGISTER)<<(num))|((REGISTER)>>(8-(num)))))

#endif /* INCLUDES_COMMON_COMMON_MACROS_H_ */
