#include "../common/hw/include/packet.h"
#include "dmc/uart.h"

int main()
{
  struct dmc_packet *packet =
      (struct dmc_packet *)kmalloc(sizeof(struct dmc_packet), GFP_KERNEL);
}