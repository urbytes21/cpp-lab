/* Reference:
* https://kleinembedded.com/stm32-without-cubeide-part-1-the-bare-necessities
FLASH (0x08000000)
+------------------+
| .isr_vector      |
+------------------+
| .text            |
| .rodata          |
+------------------+
| Initial .data    |  <-- _sidata (LMA)
+------------------+

RAM (0x20000000)
+------------------+
| .data            |  <-- _sdata
+------------------+
| .bss             |  <-- _sbss
+------------------+
| Heap (optional)  |  <-- end
|                  |
+------------------+
|      Stack       |
+------------------+
|     _estack      |
+------------------+
*/

ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    _sidata = LOADADDR(.data);

    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM AT > FLASH

    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    . = ALIGN(8);
    end = .;
}