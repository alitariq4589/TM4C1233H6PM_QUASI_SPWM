/*

 >>> This code is used For production of Sine PWM using PWM interrupts and Systick Timer using following pins

 * Number of pins required:    5
 * PWM input Interrupt pins:   PB_1, PF_4
 * Frequency Production pins:  PF_2, PF_3 (Provide PF_2 to PF_4 and PF_3 to PB_1 with external wire for interrupt)
 * GND:                        Common Ground
 */




// Timer 2 base address
#define TM_1_BASE 0x40031000
#define TM_2_BASE 0x40032000

#define Grid_Frequency 50
#define clk_frequency 16000000

//Clock Registers
#define RCGC_TIMER_R        *(volatile unsigned long *)0x400FE604
#define RCGC_GPIO_R         *(volatile unsigned long *)0x400FE108

//Clock toggling bits
#define CLOCK_GPIOB   0b10          //Port F clock control
#define CLOCK_GPIOF   0x00000020    //Port F clock control

// General purpose timer register definitions for Timer 2
#define GPTM_2_CONFIG_R          *(volatile long *)(TM_2_BASE + 0x000)
#define GPTM_2_TA_MODE_R         *(volatile long *)(TM_2_BASE + 0x004)
#define GPTM_2_TB_MODE_R         *(volatile long *)(TM_2_BASE + 0x008)
#define GPTM_2_CONTROL_R         *(volatile long *)(TM_2_BASE + 0x00C)
#define GPTM_2_INT_MASK_R        *(volatile long *)(TM_2_BASE + 0x018)
#define GPTM_2_INT_CLEAR_R       *(volatile long *)(TM_2_BASE + 0x024)
#define GPTM_2_TA_IL_R           *(volatile long *)(TM_2_BASE + 0x028)
#define GPTM_2_TB_IL_R           *(volatile long *)(TM_2_BASE + 0x02C)
#define GPTM_2_TA_MATCH_R        *(volatile long *)(TM_2_BASE + 0x030)
#define GPTM_2_TB_MATCH_R        *(volatile long *)(TM_2_BASE + 0x034)
#define GPTM_2_TA_PRESCALE_R     *(volatile long *)(TM_2_BASE + 0x038)
#define GPTM_2_TB_PRESCALE_R     *(volatile long *)(TM_2_BASE + 0x03C)
#define GPTM_2_TA_COUNT_R        *(volatile long *)(TM_2_BASE + 0x048)
#define GPTM_2_TB_COUNT_R        *(volatile long *)(TM_2_BASE + 0x04C)

// General purpose timer register definitions for Timer 1
# define GPTM_1_CONFIG_R              *( volatile long *)( TM_1_BASE + 0x000 )
# define GPTM_1_TA_MODE_R             *( volatile long *)( TM_1_BASE + 0x004 )
# define GPTM_1_TB_MODE_R             *( volatile long *)( TM_1_BASE + 0x008 )
# define GPTM_1_CONTROL_R             *( volatile long *)( TM_1_BASE + 0x00C )
# define GPTM_1_INT_MASK_R            *( volatile long *)( TM_1_BASE + 0x018 )
# define GPTM_1_INT_CLEAR_R           *( volatile long *)( TM_1_BASE + 0x024 )
# define GPTM_1_TA_IL_R               *( volatile long *)( TM_1_BASE + 0x028 )
# define GPTM_1_TA_MATCH_R            *( volatile long *)( TM_1_BASE + 0x030 )
# define GPTM_1_TA_PSR_R              *( volatile long *)( TM_1_BASE + 0x038 )
# define GPTM_1_TA_MATCH_PSR_R        *( volatile long *)( TM_1_BASE + 0x040 )
# define GPTM_1_TB_IL_R               *( volatile long *)( TM_1_BASE + 0x02C )
# define GPTM_1_TB_MATCH_R            *( volatile long *)( TM_1_BASE + 0x034 )
# define GPTM_1_TB_PSR_R              *( volatile long *)( TM_1_BASE + 0x03C )
# define GPTM_1_TB_MATCH_PSR_R        *( volatile long *)( TM_1_BASE + 0x044 )


// Timer 2 base address
#define TM_BASE              0x40032000

//Clock Registers
#define RCGC_TIMER_R         *(volatile unsigned long *)0x400FE604
#define RCGC_GPIO_R          *(volatile unsigned long *)0x400FE108

//Clock bits
#define CLOCK_GPIOB          0b10    //Port F clock control


// General purpose timer register definitions for Timer 2
#define GPTM_2B_CONFIG_R          *(volatile long *)(TM_BASE + 0x000)
#define GPTM_2B_TB_MODE_R         *(volatile long *)(TM_BASE + 0x008)
#define GPTM_2B_CONTROL_R         *(volatile long *)(TM_BASE + 0x00C)
#define GPTM_2B_INT_MASK_R        *(volatile long *)(TM_BASE + 0x018)
#define GPTM_2B_INT_CLEAR_R       *(volatile long *)(TM_BASE + 0x024)
#define GPTM_2B_TB_IL_R           *(volatile long *)(TM_BASE + 0x02C)
#define GPTM_2B_TB_MATCH_R        *(volatile long *)(TM_BASE + 0x034)
#define GPTM_2B_TB_PRESCALE_R     *(volatile long *)(TM_BASE + 0x03C)
#define GPTM_2B_TB_COUNT_R        *(volatile long *)(TM_BASE + 0x04C)



// IRQ 0 to 31 enable and disable registers
#define NVIC_EN0_R         *((volatile unsigned long *)0xE000E100)
#define NVIC_DIS0_R        *((volatile unsigned long *)0xE000E180)

#define GPIO_PORTB_AFSEL_R *((volatile unsigned long *)0x40005420)
#define GPIO_PORTB_PCTL_R  *((volatile unsigned long *)0x4000552C)
#define GPIO_PORTB_DEN_R   *((volatile unsigned long *)0x4000551C)

// Timer2 A interrupt is assigned to NVIC IRQ23
#define NVIC_EN0_INT24         0x1000000

// Timer 2A bit field definitions for mode configuration
#define TIM_16_BIT_CONFIG      0x00000004 // 16-bit timer
#define TIM_EDGE_TIME_MODE     0x00000004 // Time capture on edge
#define TIM_2B_CAPTURE_MODE       0x00000003 // Timer capture mode

// Timer event type bit filed definitions
#define TIM_2B_EVENT_NEG_EDGE   0b10000000000 // Event is -ve edge
#define TIM_2B_ENABLE           0b100000000 // Enable timer A

// Timer A capture mode interrupt mask/clear bit field definition
#define TIM_2B_CAP_EVENT_IM     0b10000000000
#define TIM_2B_CAP_EVENT_IC     0b10000000000

// Reload values for Timer A with prescale
#define TIM_2B_INTERVAL         800
#define TIM_2B_PRESCALE         0x000000



//IRQ 0 to 31 enable and disable registers
#define NVIC_EN0_R         *((volatile unsigned long *)0xE000E100)
#define NVIC_DIS0_R        *((volatile unsigned long *)0xE000E180)


//GPIO port PF alternate function configuration
#define GPIO_PORTF_AFSEL_R *((volatile unsigned long *)0x40025420)
#define GPIO_PORTF_PCTL_R  *((volatile unsigned long *)0x4002552C)
#define GPIO_PORTF_DEN_R   *((volatile unsigned long *)0x4002551C)

//GPIO port PB alternate function configuration
#define GPIO_PORTB_AFSEL_R *((volatile unsigned long *)0x40005420)
#define GPIO_PORTB_PCTL_R  *((volatile unsigned long *)0x4000552C)
#define GPIO_PORTB_DEN_R   *((volatile unsigned long *)0x4000551C)

// Timer2A interrupt is assigned to NVIC IRQ23
#define NVIC_EN0_INT23         0x00800000

// Timer2B interrupt is assigned to NVIC IRQ24
#define NVIC_EN0_INT24         0x1000000

// Timer 1 config and mode bit field definitions
# define TIM_16_BIT_CONFIG  0x00000004   // 16- bit timer
# define TIM_PERIODIC_MODE  0x00000002   // Periodic timer mode
# define TIM_B_ENABLE       0x00000100   // Timer A enable control
# define TIM_A_ENABLE       0x00000001
# define TIM_PWM_MODE       0x0000000A   // Timer in PWM mode
# define TIM_PWM_Interrupt  0b1000000000 //Enable PWM Interrupt
# define TIM_EVENT_MODE     0b00
# define TIM_CAPTURE_MODE   0x00000004   // Timer capture mode

// Timer 2A bit field definitions for mode configuration
#define TIM_16_BIT_CONFIG         0x00000004 // 16-bit timer
#define TIM_EDGE_TIME_MODE        0x00000004 // Time capture on edge
#define TIM_2A_CAPTURE_MODE       0x00000003 // Timer capture mode

// Timer event type bit filed definitions
#define TIM_2A_EVENT_POS_EDGE   0x00000000 // Event is +ve edge
#define TIM_2A_EVENT_NEG_EDGE   0x00000004 // Event is -ve edge
#define TIM_2A_EVENT_BOTH_EDGES 0x0000000C // Event on both edges
#define TIM_2A_ENABLE           0x00000001 // Enable timer A

//Timer 2B event type bit field definitions
#define TIM_2B_EVENT_NEG_EDGE   0b10000000000 // Event is -ve edge
#define TIM_2B_ENABLE           0b100000000 // Enable timer A

// Timer A capture mode interrupt mask/clear bit field definition
#define TIM_2A_CAP_EVENT_IM     0x00000004
#define TIM_2A_CAP_EVENT_IC     0x00000004


# define TIM_1A_INTERVAL 640 // Using 25kHz frequency production.
# define TIM_1B_INTERVAL 640 // Using 25kHz frequency production.

# define                            TIM_1A_MATCH 320 // 50% Duty Cycle
# define                            TIM_1B_MATCH 620 // 50% Duty Cycle

// Reload values for Timer 2A with prescale and reload value.
#define TIM_2A_INTERVAL         800
#define TIM_2A_PRESCALE         0

// Timer 2B capture mode interrupt mask/clear bit field definition
#define TIM_2B_CAP_EVENT_IM     0b10000000000
#define TIM_2B_CAP_EVENT_IC     0b10000000000

// Reload values for Timer 2B with prescale
#define TIM_2B_INTERVAL         800
#define TIM_2B_PRESCALE         0x000000

// Systick Register definitions:
#define Systick_Control         *(volatile unsigned long*)(0xE000E010)
#define Systick_Reload          *(volatile unsigned long*)(0xE000E014)
#define Systick_Current         *(volatile unsigned long*)(0xE000E018)

//Systick Flag Definitions:
#define Systick_Control_Count      0x10000
#define Systick_Control_Enable     0x00001
#define Systick_Control_Inturrupt  0x00002
#define Systick_Clock_Control      0x00004
#define Systick_Reload_Value       160000 //Reload value for 9ms interrupt



void Timer1A_Init ( void )
{

    // Enable the clock for port F and Timer1
    RCGC_GPIO_R  |= CLOCK_GPIOF ;
    RCGC_TIMER_R  |= 0x02 ;

    // Configure PortF pin 2 as Timer1 A output
    GPIO_PORTF_AFSEL_R |= 0x00000004 ;
    GPIO_PORTF_PCTL_R  |= 0x00000700 ; // Configure as timer CCP pin
    GPIO_PORTF_DEN_R   |= 0x00000004 ;

    // Enable the clock for Timer 1
    GPTM_1_CONTROL_R &= ~( TIM_A_ENABLE ); // disable timer 1 A

    // Timer1 A configured as 16- bit timer
    GPTM_1_CONFIG_R |= TIM_16_BIT_CONFIG ;


//    GPTM_TA_PSR_R = 4;
//    GPTM_TA_MATCH_PSR_R = 2;
    // Timer1 A in periodic timer , edge count and PWM mode

    GPTM_1_CONTROL_R |= 0b100;
    GPTM_1_INT_MASK_R  |= 0x001;
    GPTM_1_TA_MODE_R |= TIM_PWM_MODE | TIM_PWM_Interrupt ;
    GPTM_1_TA_MODE_R &= ~( TIM_CAPTURE_MODE );

    // Make PWM frequency 1 kHz using reload value of 16000
    GPTM_1_TA_IL_R = TIM_1A_INTERVAL ;

    // Configure PWM duty cycle value ( should be less than 16000)
    GPTM_1_TA_MATCH_R = TIM_1A_MATCH ;

    // Enable timer1 A
//    GPTM_CONTROL_R |= TIM_A_ENABLE | TIM_B_ENABLE ;
}
void Timer1B_Init ( void )
{

    // Enable the clock for port F and Timer1
    RCGC_GPIO_R   |= CLOCK_GPIOF ;
    RCGC_TIMER_R  |= 0x02 ;

    // Configure PortF pin 2 as Timer1 A output
    GPIO_PORTF_AFSEL_R |= 0b1000 ;
    GPIO_PORTF_PCTL_R  |= 0x00007000 ;     // Configure as timer CCP pin
    GPIO_PORTF_DEN_R   |= 0b1000 ;

    // Enable the clock for Timer 1
    GPTM_1_CONTROL_R &= ~( TIM_B_ENABLE ); // disable timer 1 A

    // Timer1 A configured as 16- bit timer
    GPTM_1_CONFIG_R |= TIM_16_BIT_CONFIG ;


//    GPTM_TB_PSR_R = 4;
//    GPTM_TB_MATCH_PSR_R = 2;

    // Timer1 A in periodic timer , edge count and PWM mode
    GPTM_1_INT_MASK_R  |= 0x001;
    GPTM_1_CONTROL_R |= 0b10000000000;
    GPTM_1_TB_MODE_R |= TIM_PWM_MODE | TIM_PWM_Interrupt ;
    GPTM_1_TB_MODE_R &= ~( TIM_CAPTURE_MODE );

    // Make PWM frequency 1 kHz using reload value of 16000
    GPTM_1_TB_IL_R = TIM_1B_INTERVAL ;

    // Configure PWM duty cycle value ( should be less than 16000)
    GPTM_1_TB_MATCH_R = TIM_1B_MATCH ;

    // Enable timer1 A
//    GPTM_CONTROL_R |= TIM_B_ENABLE ;
}


//Initializing Timer 2 for interrupt at negative edge provided by input wave.
void Timer2A_Init(void){

    RCGC_TIMER_R |= 0x04;        // Enable clock for timer 2
    RCGC_GPIO_R |= CLOCK_GPIOF;

    // GPIO port F pin 4 configuration
    GPIO_PORTF_DEN_R   |= 0x00000010;
    GPIO_PORTF_AFSEL_R |= 0x00000010;  // Alternate function selected
    GPIO_PORTF_PCTL_R  |= 0x00070000;  // PF4 as timer capture
                                       // compare input

    GPTM_2_CONFIG_R = TIM_16_BIT_CONFIG; // Configure 16-bit timer

    //  Timer mode is input time capture with count down
    GPTM_2_TA_MODE_R |= TIM_EDGE_TIME_MODE + TIM_2A_CAPTURE_MODE;
    GPTM_2_CONTROL_R |= TIM_2A_EVENT_NEG_EDGE; //Calling Interrupt at negative edge.

    // Configure the timer reload value
    GPTM_2_TA_IL_R       = TIM_2A_INTERVAL; //This reload value sets the lower bound for input wave frequency.
    GPTM_2_TA_PRESCALE_R = TIM_2A_PRESCALE; //This sets the resolution at which the wave frequency is measured

    // Timer0 A interrupt configuration
    GPTM_2_INT_MASK_R |= TIM_2A_CAP_EVENT_IM;
    NVIC_EN0_R          = NVIC_EN0_INT23;         // Enable INT 23 in NVIC

    // Enable the timer
    GPTM_2_CONTROL_R |= TIM_2A_ENABLE;
}

int  Interrupt_number;
void Systick_Frequency_Setup(float ZCD_frequency){
    Systick_Reload        = (float) ((clk_frequency)/(2*ZCD_frequency));
}

int Pulse_number(float ZCD_frequency){
   int pulse_number=11250/ZCD_frequency;
   return pulse_number;
}

void Systick_Init(){
    Systick_Control &= ~(Systick_Control_Enable);
//    Systick_Frequency_Setup();
    Systick_Current  =   0;
    Systick_Control  =   Systick_Control_Enable | Systick_Clock_Control | Systick_Control_Inturrupt;
    GPTM_1_CONTROL_R |= TIM_A_ENABLE;                         //PWMA start
    Interrupt_number = 1;
}

void Systick_handler(){
    Systick_Control &= (~Systick_Control_Count);            //Clear count flag


        if (Interrupt_number == 1){
            GPTM_1_CONTROL_R  |= TIM_B_ENABLE;
            Interrupt_number   = 2;
        }
        else if (Interrupt_number == 2){
            GPTM_1_CONTROL_R  |= TIM_A_ENABLE;
            Interrupt_number   = 1;
        }
}

void Timer2B_Init(void){

    RCGC_TIMER_R |= 0x04;        // Enable clock for timer 2
    RCGC_GPIO_R |= CLOCK_GPIOB;

    // GPIO port B pin 1 configuration
    GPIO_PORTB_DEN_R   |= 0b00000010;
    GPIO_PORTB_AFSEL_R |= 0b00000010;  // Alternate function selected
    GPIO_PORTB_PCTL_R  |= 0x00000070;  // PB1 as timer capture
                                       // compare input

    GPTM_2B_CONFIG_R = TIM_16_BIT_CONFIG; // Configure 16-bit timer

    //  Timer mode is input time capture with count down
    GPTM_2B_TB_MODE_R |= TIM_EDGE_TIME_MODE + TIM_2B_CAPTURE_MODE;
    GPTM_2B_CONTROL_R |= TIM_2B_EVENT_NEG_EDGE;

    // Configure the timer reload value
    GPTM_2B_TB_IL_R       = TIM_2B_INTERVAL;
    GPTM_2B_TB_PRESCALE_R = TIM_2B_PRESCALE;

    // Timer0 A interrupt configuration
    GPTM_2B_INT_MASK_R |= TIM_2B_CAP_EVENT_IM;
    NVIC_EN0_R         = NVIC_EN0_INT24;         // Enable INT 23 in NVIC

    // Enable the timer
    GPTM_2B_CONTROL_R |= TIM_2B_ENABLE;
}
int pulse_count;
int PWM1A_Edge_number=0;
void Timer2A_Handler(void){


    GPTM_2_INT_CLEAR_R |= TIM_2A_CAP_EVENT_IC;  // Clear interrupt flag
    PWM1A_Edge_number++;
    if (PWM1A_Edge_number ==  pulse_count){
        GPTM_1_CONTROL_R  &= ~TIM_A_ENABLE;
        PWM1A_Edge_number=0;
        GPTM_1_TA_MATCH_R=620;
    }
    if (GPTM_1_TA_MATCH_R < 20)
    {
        GPTM_1_TA_MATCH_R = 20;
    }
    else if (GPTM_1_TA_MATCH_R > 620)
    {
        GPTM_1_TA_MATCH_R = 620;
    }
    else if (PWM1A_Edge_number <  pulse_count/2){
        GPTM_1_TA_MATCH_R = GPTM_1_TA_MATCH_R-(pulse_count*0.03);
    }
    else
    GPTM_1_TA_MATCH_R = GPTM_1_TA_MATCH_R+(pulse_count*0.03);
}

int Reload_PWM1B=640;
int PWM_1B_Edge_number=0;
int preserve_PWM_value;
void Timer2B_Handler(void){
    GPTM_2B_INT_CLEAR_R |= TIM_2B_CAP_EVENT_IC;  // Clear interrupt flag
        PWM_1B_Edge_number++;
        if (PWM_1B_Edge_number ==  pulse_count){
            GPTM_1_CONTROL_R  &= ~TIM_B_ENABLE;
            PWM_1B_Edge_number=0;
            GPTM_1_TB_MATCH_R=620;
        }
        if (GPTM_1_TB_MATCH_R < 20)
        {
            GPTM_1_TB_MATCH_R = 20;
        }
        else if (GPTM_1_TB_MATCH_R > 620)
        {
            GPTM_1_TB_MATCH_R = 620;
        }
        else if (PWM_1B_Edge_number <  pulse_count/2){
            GPTM_1_TB_MATCH_R = GPTM_1_TB_MATCH_R-(pulse_count*0.03);
        }

            else
            GPTM_1_TB_MATCH_R = GPTM_1_TB_MATCH_R+(pulse_count*0.03);
}

int main(void)
{
    float ZCD_frequency=100; //This is the total frequency of the SPWM
    Systick_Frequency_Setup(ZCD_frequency);
    pulse_count = Pulse_number(ZCD_frequency);
    Timer1A_Init (); // Initialize the Timer 1A for 25kHz PWM.
    Timer1B_Init (); // Initialize the Timer 1B for 25kHz PWM.
    Timer2A_Init();  // Initialize Timer 2A for Input negative Edge Interrupt
    Timer2B_Init();  // Initialize Timer 2A for Input negative Edge Interrupt
    Systick_Init();  // Initialize Systick Timer Interrupt for

    while(1){

    }
}
