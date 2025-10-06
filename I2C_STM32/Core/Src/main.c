/* STM32 I2C Code for SWD Debug - No UART needed */

#include "main.h"
#include <string.h>

/* Private variables */
I2C_HandleTypeDef hi2c1;

/* Debug variables - Quan sát trong debugger */
typedef struct {
    HAL_StatusTypeDef i2c_scanner_result;
    uint8_t devices_found;
    uint8_t device_addresses[10];

    HAL_StatusTypeDef write_result;
    HAL_StatusTypeDef read_result;

    uint8_t write_data[50];
    uint8_t read_data[50];
    uint8_t data_length;

    uint8_t verification_passed;
    uint32_t test_count;
    uint32_t success_count;
    uint32_t error_count;
} debug_info_t;

debug_info_t debug_info = {0}; // Global debug structure

/* EEPROM Configuration */
#define EEPROM_ADDR 0x50 << 1  // ESP32 slave address
#define EEPROM_SIZE 256

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

HAL_StatusTypeDef EEPROM_Write(uint16_t mem_addr, uint8_t *data, uint16_t len);
HAL_StatusTypeDef EEPROM_Read(uint16_t mem_addr, uint8_t *data, uint16_t len);
void I2C_Scanner(void);
void Run_I2C_Test(void);

/**
 * @brief  The application entry point.
 */
int main(void)
{
    /* MCU Configuration */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    /* Initialize debug info */
    strcpy((char*)debug_info.write_data, "Hello STM32 I2C!");
    debug_info.data_length = strlen((char*)debug_info.write_data);

    /* SET BREAKPOINT HERE - Start debugging */
    debug_info.test_count = 0;
    debug_info.success_count = 0;
    debug_info.error_count = 0;

    /* Infinite loop */
    while (1)
    {
        debug_info.test_count++;

        /* SET BREAKPOINT HERE - Before each test cycle */
        Run_I2C_Test();

        /* SET BREAKPOINT HERE - After each test cycle */
        if(debug_info.verification_passed) {
            debug_info.success_count++;
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET); // LED ON
        } else {
            debug_info.error_count++;
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // LED OFF
        }

        HAL_Delay(2000); // 2 second delay between tests
    }
}

/**
 * @brief Run complete I2C test sequence
 */
void Run_I2C_Test(void)
{
    /* Step 1: Scan I2C bus */
    /* SET BREAKPOINT HERE - Before I2C scan */
    I2C_Scanner();

    /* Step 2: Write data to EEPROM */
    /* SET BREAKPOINT HERE - Before write operation */
    debug_info.write_result = EEPROM_Write(0x00, debug_info.write_data, debug_info.data_length);

    /* Check write result in debugger:
     * debug_info.write_result should be HAL_OK (0x00)
     */

    HAL_Delay(50); // Short delay for ESP32 processing

    /* Step 3: Read data from EEPROM */
    /* SET BREAKPOINT HERE - Before read operation */
    memset(debug_info.read_data, 0, sizeof(debug_info.read_data));
    debug_info.read_result = EEPROM_Read(0x00, debug_info.read_data, debug_info.data_length);

    /* Check read result in debugger:
     * debug_info.read_result should be HAL_OK (0x00)
     * debug_info.read_data should contain "Hello STM32 I2C!"
     */

    /* Step 4: Verify data */
    /* SET BREAKPOINT HERE - Before verification */
    debug_info.verification_passed = (strcmp((char*)debug_info.write_data,
                                            (char*)debug_info.read_data) == 0) ? 1 : 0;

    /* Check verification in debugger:
     * debug_info.verification_passed should be 1 for success
     */
}

/**
 * @brief Scan I2C bus for devices
 */
void I2C_Scanner(void)
{
    debug_info.devices_found = 0;

    /* SET BREAKPOINT HERE - Start of I2C scan */
    for(uint8_t i = 1; i < 128; i++)
    {
        debug_info.i2c_scanner_result = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, 10);

        if(debug_info.i2c_scanner_result == HAL_OK)
        {
            debug_info.device_addresses[debug_info.devices_found] = i;
            debug_info.devices_found++;

            /* SET BREAKPOINT HERE - Device found */
            /* Check debug_info.device_addresses[debug_info.devices_found-1]
             * Should be 0x50 for ESP32 slave */
        }

        if(debug_info.devices_found >= 10) break; // Prevent overflow
    }

    /* SET BREAKPOINT HERE - End of I2C scan */
    /* Check debug_info.devices_found - should be >= 1 */
}

/**
 * @brief Write data to EEPROM (ESP32 slave)
 */
HAL_StatusTypeDef EEPROM_Write(uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    /* SET BREAKPOINT HERE - Before HAL_I2C_Mem_Write */
    HAL_StatusTypeDef result = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, mem_addr,
                                                 I2C_MEMADD_SIZE_8BIT, data, len, 1000);

    /* SET BREAKPOINT HERE - After HAL_I2C_Mem_Write */
    /* Check result - should be HAL_OK (0x00) */
    return result;
}

/**
 * @brief Read data from EEPROM (ESP32 slave)
 */
HAL_StatusTypeDef EEPROM_Read(uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    /* SET BREAKPOINT HERE - Before HAL_I2C_Mem_Read */
    HAL_StatusTypeDef result = HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, mem_addr,
                                                I2C_MEMADD_SIZE_8BIT, data, len, 1000);

    /* SET BREAKPOINT HERE - After HAL_I2C_Mem_Read */
    /* Check result and data content */
    return result;
}

/**
 * @brief System Clock Configuration
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief I2C1 Initialization Function
 */
static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief GPIO Initialization Function
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
 * @brief  This function is executed in case of error occurrence.
 */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

/*
DEBUG STRATEGY với SWD:

1. SET BREAKPOINTS tại các vị trí có comment "SET BREAKPOINT HERE"

2. WATCH VARIABLES:
   - debug_info (toàn bộ struct)
   - debug_info.write_result
   - debug_info.read_result
   - debug_info.verification_passed
   - debug_info.devices_found

3. MEMORY VIEW:
   - Xem debug_info.write_data
   - Xem debug_info.read_data
   - So sánh hai buffer này

4. STEP DEBUGGING:
   - F10: Step over (chạy từng dòng)
   - F11: Step into (vào bên trong hàm)
   - F5: Continue (chạy tiếp đến breakpoint tiếp theo)

5. KIỂM TRA KẾT QUẢ:
   - HAL_OK = 0x00 (thành công)
   - HAL_ERROR = 0x01 (lỗi)
   - HAL_BUSY = 0x02 (bận)
   - HAL_TIMEOUT = 0x03 (timeout)
*/
