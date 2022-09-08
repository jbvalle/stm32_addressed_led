#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

typedef struct RCC_t{
	uint32_t RCC_CR; 		//0x00
	uint32_t RCC_PLLCFGR;	//0x04
	uint32_t RCC_CFGR;		//0x08
	uint32_t RCC_CIR;		//0x0C
	uint32_t RCC_AHB1RSTR;	//0x10
	uint32_t RCC_AHB2RSTR;	//0x14
	uint32_t res1;			//0x18
	uint32_t res2;			//0x1C
	uint32_t RCC_APB1RSTR;	//0x20
	uint32_t RCC_APB2RSTR;	//0x24
	uint32_t res3;			//0x28
	uint32_t res4;			//0x2C
	uint32_t RCC_AHB1ENR; 	//0x30 RCC_AHB1ENR //GPIOA=1
}RCC_t;

typedef struct GPIOA_t{
	uint32_t GPIOA_MODER; 		//0x00
	uint32_t GPIOA_OTYPER;		//0x04
	uint32_t GPIOA_OSPEEDER;	//0x08
	uint32_t GPIOA_PUPDR;		//0x0C
	uint32_t GPIOA_IDR;			//0x10
	uint32_t GPIOA_ODR;			//0x14
	uint32_t GPIOA_BSRR;		//0x18
}GPIOA_t;

void delayMS(int n){

	for(; n > 0; n--){
		for(int i = 0; i < 3195; i++);
	}
}

int main(void)
{
	RCC_t	* const CRCC   = (RCC_t   *) 0x40023800;
	GPIOA_t * const CGPIOA = (GPIOA_t *) 0x40020000;

	/* Enable GPIOA CLOCK */
	CRCC->RCC_AHB1ENR |= 1;

	/* Reset Pin 5 */
	CGPIOA->GPIOA_MODER &= ~0x00000C00;
	/* Set Pin 5 OUT */
	CGPIOA->GPIOA_MODER |=  0x00000400;

	for(;;){

		CGPIOA->GPIOA_ODR ^= 0x00000020;
		delayMS(500);
	}
}

