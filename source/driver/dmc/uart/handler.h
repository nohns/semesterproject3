#ifndef DMC_UART_HANDLER_H
#define DMC_UART_HANDLER_H

#include <linux/types.h>

#include "packet.h"

#include "../util.h"

/**
 * @brief Registers the necessary resources for the uart to function
 */
int dmc_uart_handler_register(int (*on_byte_recv)(u8 data));

/**
 * @brief Unregisters uart resources
 */
int dmc_uart_handler_unregister();

/**
 * @brief Sends a packet over the uart
 */
int dmc_uart_handler_send_packet(struct dmc_packet *packet);

#endif // DMC_UART_HANDLER_H