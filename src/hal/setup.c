#include "setup.h"


static void rcc_clock_setup_hsi_3v3(const struct rcc_clock_scale *clock)
{
	/* Enable internal high-speed oscillator (HSI). */
	rcc_osc_on(RCC_HSI);
	rcc_wait_for_osc_ready(RCC_HSI);

	/* Select HSI as SYSCLK source. */
	rcc_set_sysclk_source(RCC_CFGR_SW_HSI);

	/* Set the VOS scale mode */
	rcc_peripheral_enable_clock(&RCC_APB1ENR, RCC_PWR);
	pwr_set_vos_scale(clock->voltage_scale);

	/*
	 * Set prescalers for AHB, ADC, ABP1, ABP2.
	 * Do this before touching the PLL (TODO: why?).
	 */
	rcc_set_hpre(clock->hpre);
	rcc_set_ppre1(clock->ppre1);
	rcc_set_ppre2(clock->ppre2);

	/* Disable PLL oscillator before changing its configuration. */
	rcc_osc_off(RCC_PLL);

	/* Configure the PLL oscillator. */
	rcc_set_main_pll_hsi(clock->pllm, clock->plln, clock->pllp, clock->pllq,
			     clock->pllr);

	/* Enable PLL oscillator and wait for it to stabilize. */
	rcc_osc_on(RCC_PLL);
	rcc_wait_for_osc_ready(RCC_PLL);

	/* Configure flash settings. */
	if (clock->flash_config & FLASH_ACR_DCEN)
		flash_dcache_enable();
	else
		flash_dcache_disable();
	if (clock->flash_config & FLASH_ACR_ICEN)
		flash_icache_enable();
	else
		flash_icache_disable();
	flash_set_ws(clock->flash_config);

	/* Select PLL as SYSCLK source. */
	rcc_set_sysclk_source(RCC_CFGR_SW_PLL);

	/* Wait for PLL clock to be selected. */
	rcc_wait_for_sysclk_status(RCC_PLL);

	/* Set the peripheral clock frequencies used. */
	rcc_ahb_frequency = clock->ahb_frequency;
	rcc_apb1_frequency = clock->apb1_frequency;
	rcc_apb2_frequency = clock->apb2_frequency;

	/* Disable internal high-speed oscillator. */
	rcc_osc_off(RCC_HSI);
}


/**
 * @brief Initial clock setup.
 *
 * Use the Internal High Speed clock (HSI), at 16 MHz, and set the SYSCLK
 * at 168 MHz.
 *
 * The peripheral clocks are set to:
 *
 * - AHB to 168 MHz (max. is 180 MHz)
 * - APB1 to 42 MHz
 * - APB2 to 84 MHz
 *
 * Enable required clocks for the GPIOs and timers as well.
 *
 * A pull-up resistor is used in RX to avoid a floating input when no
 * bluetooth is connected, which could trigger incorrect interruptions.
 *
 * @see Reference manual (RM0090), in particular "Reset and clock control for
 * STM32F405xx" section.
 */
static void setup_clock(void)
{
	rcc_clock_setup_hsi_3v3(&rcc_hse_16mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	/* GPIOs */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);

	/* Bluetooth */
	rcc_periph_clock_enable(RCC_USART1);

	/* Gyroscope */
	rcc_periph_clock_enable(RCC_SPI3);

	/* Timers */
	rcc_periph_clock_enable(RCC_TIM3);
	rcc_periph_clock_enable(RCC_TIM4);
	rcc_periph_clock_enable(RCC_TIM8);
	rcc_periph_clock_enable(RCC_TIM11);

	/* ADC */
	rcc_periph_clock_enable(RCC_ADC2);

	/* DMA */
	rcc_periph_clock_enable(RCC_DMA2);

	/* Enable clock cycle counter */
	dwt_enable_cycle_counter();
}

/**
 * @brief Exceptions configuration.
 *
 * This function configures Nested Vectored Interrupt Controller for IRQ and
 * System Control Block for system interruptions.
 *
 * Interruptions enabled:
 *
 * - DMA 2 stream 7 interrupt.
 * - USART1 interrupt.
 *
 * @see Programming Manual (PM0214).
 */
static void setup_exceptions(void)
{
	nvic_enable_irq(NVIC_DMA2_STREAM7_IRQ);
	nvic_enable_irq(NVIC_USART1_IRQ);
}


/**
 * @brief Set SysTick interruptions frequency and enable SysTick counter.
 *
 * SYSCLK is at 168 MHz as well as the Advanced High-permormance Bus (AHB)
 * because, by default, the AHB divider is set to 1, so the AHB clock has the
 * same frequency as the SYSCLK.
 *
 * SysTick interruption frequency is set to `SYSTICK_FREQUENCY_HZ`.
 *
 * @see RM0090 reference manual and in particular the "Clock tree" figure.
 */
static void setup_systick(void)
{
	systick_set_frequency(SYSTICK_FREQUENCY_HZ, SYSCLK_FREQUENCY_HZ);
	systick_counter_enable();
}


/**
 * @brief Setup for ADC2: configured for regular conversion.
 *
 * This ADC is used to read the battery status.
 *
 * - Power off the ADC to be sure that does not run during configuration
 * - Disable scan mode
 * - Set single conversion mode triggered by software
 * - Configure the alignment (right)
 * - Configure the sample time (15 cycles of ADC clock)
 * - Set regular sequence with `channel_sequence` structure
 * - Power on the ADC
 *
 * @see Reference manual (RM0090) "Analog-to-digital converter".
 */
static void setup_adc2(void)
{
	uint8_t channel_sequence[16];

	channel_sequence[0] = ADC_CHANNEL14;
	adc_power_off(ADC2);
	adc_disable_scan_mode(ADC2);
	adc_set_single_conversion_mode(ADC2);
	adc_set_right_aligned(ADC2);
	adc_set_sample_time_on_all_channels(ADC2, ADC_SMPR_SMP_15CYC);
	adc_set_regular_sequence(ADC2, 1, channel_sequence);
	adc_power_on(ADC2);
}


/**
 * @brief Initial GPIO configuration.
 *
 * Set GPIO modes and initial states.
 *
 * @see STM32F405RG datasheet and in particular the "Alternate function
 * mapping" section.
 */
static void setup_gpio(void)
{
	/* Battery */
	gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO4);

	/* Infrared emitters */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
			GPIO4 | GPIO5 | GPIO6 | GPIO7);
	gpio_clear(GPIOA, GPIO4 | GPIO5 | GPIO6 | GPIO7);

	/* LEDs */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
			GPIO0 | GPIO1 | GPIO2 | GPIO3);
	gpio_clear(GPIOA, GPIO0 | GPIO1 | GPIO2 | GPIO3);

	/* Speaker */
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
	gpio_set_af(GPIOB, GPIO_AF3, GPIO9);

	/* Motor driver */
	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE,
			GPIO6 | GPIO7 | GPIO8 | GPIO9);
	gpio_set_af(GPIOC, GPIO_AF3, GPIO6 | GPIO7 | GPIO8 | GPIO9);

	/* Encoders */
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE,
			GPIO4 | GPIO5 | GPIO6 | GPIO7);
	gpio_set_af(GPIOB, GPIO_AF2, GPIO4 | GPIO5 | GPIO6 | GPIO7);

	/* Bluetooth */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);
	gpio_set(GPIOA, GPIO10);

	/* Buttons */
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO13);

	/* MPU */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO15);
	gpio_set(GPIOA, GPIO15);

	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN,
			GPIO10 | GPIO11 | GPIO12);
	gpio_set_af(GPIOC, GPIO_AF6, GPIO10 | GPIO11 | GPIO12);
}


/**
 * @brief Setup USART for bluetooth communication.
 */
static void setup_usart(void)
{
	usart_set_baudrate(USART1, 921600);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART1, USART_MODE_TX_RX);

	usart_enable(USART1);
}


/**
 * @brief Setup PWM for the motor drivers.
 *
 * TIM8 is used to generate both PWM signals (left and right motor):
 *
 * - Edge-aligned, up-counting timer.
 * - Prescale to increment timer counter at 24 MHz.
 * - Set PWM frequency to 24 kHz.
 * - Configure channels 1, 2, 3 and 4 as output GPIOs.
 * - Set output compare mode to PWM1 (output is active when the counter is
 *   less than the compare register contents and inactive otherwise.
 * - Reset output compare value (set it to 0).
 * - Enable channels 1, 2, 3 and 4 outputs.
 * - Enable outputs in the break subsystem (required on an advanced timer).
 * - Enable timer counter.
 *
 * @see Reference manual (RM0090) "Advanced-control timers (TIM1 and TIM8)"
 * and in particular the "PWM mode" section.
 */
static void setup_motor_driver(void)
{
	timer_set_mode(TIM8, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE,
		       TIM_CR1_DIR_UP);

	timer_set_prescaler(TIM8, (rcc_apb2_frequency / 24000000 - 1));
	timer_set_repetition_counter(TIM8, 0);
	timer_enable_preload(TIM8);
	timer_continuous_mode(TIM8);
	timer_set_period(TIM8, DRIVER_PWM_PERIOD);

	timer_set_oc_mode(TIM8, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_mode(TIM8, TIM_OC2, TIM_OCM_PWM1);
	timer_set_oc_mode(TIM8, TIM_OC3, TIM_OCM_PWM1);
	timer_set_oc_mode(TIM8, TIM_OC4, TIM_OCM_PWM1);
	timer_set_oc_value(TIM8, TIM_OC1, 0);
	timer_set_oc_value(TIM8, TIM_OC2, 0);
	timer_set_oc_value(TIM8, TIM_OC3, 0);
	timer_set_oc_value(TIM8, TIM_OC4, 0);
	timer_enable_oc_output(TIM8, TIM_OC1);
	timer_enable_oc_output(TIM8, TIM_OC2);
	timer_enable_oc_output(TIM8, TIM_OC3);
	timer_enable_oc_output(TIM8, TIM_OC4);

	timer_enable_break_main_output(TIM8);

	timer_enable_counter(TIM8);
}

/**
 * @brief Configure timer to read a quadrature encoder.
 *
 * - Set the Auto-Reload Register (TIMx_ARR).
 * - Set the encoder interface mode counting on both TI1 and TI2 edges.
 * - Configure inputs (see note).
 * - Enable counter.
 *
 * @param[in] timer_peripheral Timer register address base to configure.
 *
 * @note It currently always uses channels 1 and 2.
 *
 * @see Reference manual (RM0090) "TIM2 to TIM5 functional description" and in
 * particular "Encoder interface mode" section.
 */
static void configure_timer_as_quadrature_encoder(uint32_t timer_peripheral)
{
	timer_set_period(timer_peripheral, 0xFFFF);
	timer_slave_set_mode(timer_peripheral, 0x3);
	timer_ic_set_input(timer_peripheral, TIM_IC1, TIM_IC_IN_TI1);
	timer_ic_set_input(timer_peripheral, TIM_IC2, TIM_IC_IN_TI2);
	timer_enable_counter(timer_peripheral);
}


/**
 * @brief Setup timers for the motor encoders.
 *
 * TIM3 for the left motor and TIM4 for the right motor are configured.
 */
static void setup_encoders(void)
{
	configure_timer_as_quadrature_encoder(TIM3);
	configure_timer_as_quadrature_encoder(TIM4);
}


/**
 * @brief Setup SPI.
 *
 * SPI is configured as follows:
 *
 * - Master mode.
 * - Clock baud rate: PCLK1 / speed_div; PCLK1 = 36MHz.
 * - Clock polarity: 0 (idle low; leading edge is a rising edge).
 * - Clock phase: 0 (out changes on the trailing edge and input data
 *   captured on rising edge).
 * - Data frame format: 8-bits.
 * - Frame format: MSB first.
 *
 * NSS is configured to be managed by software.
 */
static void setup_spi(uint8_t speed_div)
{
	spi_reset(SPI3);

	spi_init_master(SPI3, speed_div, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
			SPI_CR1_CPHA_CLK_TRANSITION_1, SPI_CR1_DFF_8BIT,
			SPI_CR1_MSBFIRST);

	spi_enable_software_slave_management(SPI3);
	spi_set_nss_high(SPI3);

	spi_enable(SPI3);
}


/**
 * @brief Setup SPI for gyroscope read, less than 20 MHz.
 *
 * The clock baudrate is 84 MHz / 8 = 10.5 MHz.
 */
void setup_spi_high_speed(void)
{
  setup_spi(SPI_CR1_BAUDRATE_FPCLK_DIV_8);
}


/**
 * @brief Setup SPI for gyroscope Write, less than 1 MHz.
 *
 * The clock baudrate is 84 MHz / 128 = 0.65625 MHz.
 */
void setup_spi_low_speed(void)
{
  setup_spi(SPI_CR1_BAUDRATE_FPCLK_DIV_128);
}


/**
 * @brief Setup PWM for the speaker.
 *
 * TIM11 is used to generate the PWM signals for the speaker:
 *
 * - Edge-aligned, up-counting timer.
 * - Prescale to increment timer counter at SPEAKER_BASE_FREQUENCY_HZ.
 * - Set output compare mode to PWM1 (output is active when the counter is
 *   less than the compare register contents and inactive otherwise.
 * - Disable output compare output (speaker is off by default).
 *
 * @see Reference manual (RM0090) "General-purpose timers (TIM9 to TIM14)"
 * and in particular the "PWM mode" section.
 */
static void setup_speaker(void)
{
	timer_set_mode(TIM11, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE,
		       TIM_CR1_DIR_UP);

	timer_set_prescaler(
	    TIM11, (rcc_apb2_frequency / SPEAKER_BASE_FREQUENCY_HZ - 1));
	timer_set_repetition_counter(TIM11, 0);
	timer_enable_preload(TIM11);
	timer_continuous_mode(TIM11);

	timer_disable_oc_output(TIM11, TIM_OC1);
	timer_set_oc_mode(TIM11, TIM_OC1, TIM_OCM_PWM1);
}


/**
 * @brief Execute all setup functions.
 */
void setup(void)
{
	setup_clock();
	setup_exceptions();
	setup_gpio();
	setup_speaker();
	setup_motor_driver();
	setup_encoders();
	setup_usart();
	setup_adc2();
	setup_mpu();
	setup_systick();
}

