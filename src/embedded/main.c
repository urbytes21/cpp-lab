#include <stdint.h>

#define SYST_CSR (*(volatile uint32_t*)0xE000E010)
#define SYST_RVR (*(volatile uint32_t*)0xE000E014)
#define SYST_CVR (*(volatile uint32_t*)0xE000E018)

#define RCC_APB2ENR (*(volatile uint32_t*)0x40021018)

#define USART1_SR (*(volatile uint32_t*)0x40013800)
#define USART1_DR (*(volatile uint32_t*)0x40013804)
#define USART1_BRR (*(volatile uint32_t*)0x40013808)
#define USART1_CR1 (*(volatile uint32_t*)0x4001380C)

/// @brief Generate a blocking delay using the Cortex-M SysTick timer.
/// @param ms Delay duration in milliseconds.
static void delay_ms(uint32_t ms) {
  while (ms--) {
    SYST_RVR = 8000 - 1;  // 8 MHz -> 1 ms
    SYST_CVR = 0;
    SYST_CSR = 5;  // ENABLE + CPU clock

    while (!(SYST_CSR & (1 << 16))) {}

    SYST_CSR = 0;
  }
}

/// @brief Send a null-terminated string to the host using semihosting.
/// @param s String to transmit.
static void semihost_write0(const char* s) {
  register int op asm("r0") = 0x04;
  register const char* msg asm("r1") = s;

  asm volatile("bkpt 0xAB" : : "r"(op), "r"(msg) : "memory");
}

static void uart_init(void) {
  // Enable USART1 clock
  RCC_APB2ENR |= (1 << 14);

  // 8 MHz PCLK -> 115200 baud
  USART1_BRR = 0x45;

  // UE + TE
  USART1_CR1 = (1 << 13) | (1 << 3);
}

/// @brief
static void uart_putc(char c) {
  while (!(USART1_SR & (1 << 7))) {}

  USART1_DR = c;
}

/// @brief Transmit a null-terminated string over USART1.
/// @param s String to transmit.
static void uart_puts(const char* s) {
  while (*s) {
    if (*s == '\n')
      uart_putc('\r');

    uart_putc(*s++);
  }
}

int main(void) {
  uart_init();

  while (1) {
    uart_puts("Hello STM32-QEMU UART1\n");
    delay_ms(1000);
    semihost_write0("Hello STM32-QEMU semihosting\n");
    delay_ms(1000);
  }
}