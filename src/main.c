/**
 * A project to ease the storage of items
 *
 * @authors StockAuto
 */

#include "main.h"

static StockAuto_State current_state;

// User inputs
static StockAuto_Action action_selected;
static uint8_t locker_selected_index = 0;

// Locker memory + initializes it to all empty
static PAGES_LockersStatus lockers_status = {
    .map = {
        LOCKER_EMPTY,
        LOCKER_EMPTY,
        LOCKER_EMPTY,
        LOCKER_EMPTY
    }
};

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_ADC2_Init();
    MX_TIM1_Init();

    INIT_servo();

    OLED_Init();
    OLED_Clear();

    while (1)
    {
        /**
         * State machine
         */
        switch (current_state) {
            case START:
                /* Display a start screen */
                PAGE_Start();
                HAL_Delay(5000);
                current_state = ACTION;
                break;
            case ACTION: {
                /* Display a page to choose the action and get the key pressed (+process it) */
                PAGE_Action();

                // Wait for the user to press a key and returns the key
                char key = keypad_getkey();

                if (key == 'A') {
                    action_selected = GRAB;
                    current_state = LOCKER;
                } else if (key == 'B') {
                    action_selected = PUT;
                    current_state = LOCKER;
                } else {
                    // Possible upgrade with an error message
                }

                break;
            }
            case LOCKER: {
                /* Displays a page to choose locker and gets the key (+ process it) */
                PAGE_Lockers(lockers_status, action_selected);

                // Wait for user input and get the key
                char key = keypad_getkey();

                switch (key) {
                    case '1':
                        if (action_selected == PUT && lockers_status.map[0] == LOCKER_EMPTY) {
                            locker_selected_index = 0;
                            lockers_status.map[0] = LOCKER_OCCUPIED;
                            current_state = EXECUTING;
                        } else if (action_selected == GRAB && lockers_status.map[0] == LOCKER_OCCUPIED) {
                            locker_selected_index = 0;
                            lockers_status.map[0] = LOCKER_EMPTY;
                            current_state = EXECUTING;
                        } else {
                            // Possible upgrade with an error message 
                        }
                        break;
                    case '2':
                        if (action_selected == PUT && lockers_status.map[1] == LOCKER_EMPTY) {
                            locker_selected_index = 1;
                            lockers_status.map[1] = LOCKER_OCCUPIED;
                            current_state = EXECUTING;
                        } else if (action_selected == GRAB && lockers_status.map[1] == LOCKER_OCCUPIED) {
                            locker_selected_index = 1;
                            lockers_status.map[1] = LOCKER_EMPTY;
                            current_state = EXECUTING;
                        } else {
                            // Possible upgrade with an error message 
                        }
                        break;
                    case '3':
                        if (action_selected == PUT && lockers_status.map[2] == LOCKER_EMPTY) {
                            locker_selected_index = 2;
                            lockers_status.map[2] = LOCKER_OCCUPIED;
                            current_state = EXECUTING;
                        } else if (action_selected == GRAB && lockers_status.map[2] == LOCKER_OCCUPIED) {
                            locker_selected_index = 2;
                            lockers_status.map[2] = LOCKER_EMPTY;
                            current_state = EXECUTING;
                        } else {
                            // Possible upgrade with an error message 
                        }
                        break;
                    case '4':
                        if (action_selected == PUT && lockers_status.map[3] == LOCKER_EMPTY) {
                            locker_selected_index = 3;
                            lockers_status.map[3] = LOCKER_OCCUPIED;
                            current_state = EXECUTING;
                        } else if (action_selected == GRAB && lockers_status.map[3] == LOCKER_OCCUPIED) {
                            locker_selected_index = 3;
                            lockers_status.map[3] = LOCKER_EMPTY;
                            current_state = EXECUTING;
                        } else {
                            // Possible upgrade with an error message 
                        }
                        break;
                    case '*':
                        current_state = ACTION; // Maybe display a go back message on the screen
                        break;
                    default:
                        // Possible upgrade with an error message
                        break;
                }

                break;
            }
            case EXECUTING:
                /* Executes the query */
                PAGE_Execution();

                if (action_selected == GRAB) {
                    StockAuto_Grab();
                } else {
                    StockAuto_Put();
                }

                current_state = ACTION;

                break;
            default:
                Error_Handler();
                break;
        }
    }
}

/**
 * Functions
 */

/**
 * @brief Move to the selected locker and grab the item then brings it to the user
 */
void StockAuto_Grab(void) {
    GPIO_step(1300 * (1+locker_selected_index),1,'A');
    GPIO_step(1000,1,'B');
    close_();
    GPIO_step(1000,0,'B');
    GPIO_step(1300 * (1+locker_selected_index),0,'A');
    GPIO_step(1000,1,'B');
    open_();
    GPIO_step(1000,0,'B');
}

/**
 * @brief Grabs the user item then move to the selected locker and put there and then come back
 */
void StockAuto_Put(void) {
    GPIO_step(1000,1,'B');
    close_();
    GPIO_step(1000,0,'B');
    GPIO_step(1300 * (1+locker_selected_index),1,'A');
    GPIO_step(1000,1,'B');
    open_();
    GPIO_step(1000,0,'B');
    GPIO_step(1300 * (1+locker_selected_index),0,'A');
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
