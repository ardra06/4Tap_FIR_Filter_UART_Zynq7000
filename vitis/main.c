#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"

#ifndef FIR_IP_BASE_ADDR
#if defined(XPAR_FIR_AXI2_0_BASEADDR)
#define FIR_IP_BASE_ADDR XPAR_FIR_AXI2_0_BASEADDR
#elif defined(XPAR_FIR_AXI2_0_S00_AXI_BASEADDR)
#define FIR_IP_BASE_ADDR XPAR_FIR_AXI2_0_S00_AXI_BASEADDR
#elif defined(XPAR_DESIGN_1_FIR_AXI2_0_0_BASEADDR)
#define FIR_IP_BASE_ADDR XPAR_DESIGN_1_FIR_AXI2_0_0_BASEADDR
#else
#error "FIR IP Base Address not found in xparameters.h! Check your block design instance name."
#endif
#endif

#define REG0_INPUT_SAMPLE  0   // slv_reg0 (input)
#define REG2_OUTPUT_SAMPLE 8   // slv_reg2 (output)

int main()
{
    init_platform();

    print("\r\n==================================================\r\n");
    print("      Zybo Z7-10 FIR Filter UART Controller       \r\n");
    print("==================================================\r\n");
    print("Enter 16-bit signed integer samples (-32768 to 32767).\r\n\n");

    while(1) {
        int input_val;
        print("Enter Sample: ");
        
        if (scanf("%d", &input_val) != 1) {
            print("\r\nInvalid entry. Please enter a valid integer.\r\n");
            fflush(stdin);
            continue;
        }

        if (input_val < -32768 || input_val > 32767) {
            xil_printf("\r\nWarning: Input %d out of bounds. Clipping value.\r\n", input_val);
            if (input_val < -32768) input_val = -32768;
            if (input_val > 32767)  input_val = 32767;
        }

        Xil_Out32(FIR_IP_BASE_ADDR + REG0_INPUT_SAMPLE, (u32)input_val);

        int32_t output_val = (int32_t)Xil_In32(FIR_IP_BASE_ADDR + REG2_OUTPUT_SAMPLE);

        xil_printf("Input: %6d  ==>  FIR Output: %d\r\n\n", (int16_t)input_val, output_val);
    }

    cleanup_platform();
    return 0;
}
