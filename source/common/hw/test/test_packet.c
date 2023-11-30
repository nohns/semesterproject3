#include <stdio.h>

#include "../include/packet.h"

#define PACKET_TYPE_WITHOUT_DATA DMC_PACKET_MACHINE_OK
#define PACKET_TYPE_WITH_DATA DMC_PACKET_CONTAINER_WEIGHT_MEASURED

int main(void)
{
  int err;

  // Test case 1: null base packet, and marshal afterwards
  struct dmc_packet_fluid_pour_requested packet = {
      .container = 2,
      .amount    = 1,
  };

  struct dmc_packet *base_packet = NULL;
  err = dmc_packet_marshal_fluid_pour_requested(&base_packet, &packet);
  if (err != 0)
  {
    printf("packet marshal failed with err = %d. expected success.\n", err);
    if (base_packet != NULL) dmc_packet_free(base_packet);
    return 1;
  }
  if (base_packet == NULL)
  {
    printf(
        "base_packet not allocated in marshal. expected non-null pointer.\n");
    dmc_packet_free(base_packet);
    return 1;
  }
  struct dmc_packet_fluid_pour_requested unmarshalled_packet;
  err = dmc_packet_unmarshal_fluid_pour_requested(&unmarshalled_packet,
                                                  base_packet);
  if (err != 0)
  {
    printf("packet unmarshal failed with err = %d. expected success.\n", err);
  }
  dmc_packet_free(base_packet);

  if (unmarshalled_packet.container != packet.container)
  {
    printf("unmarshalled packet container = %d, expected %d\n",
           unmarshalled_packet.container, packet.container);
    return 1;
  }
  if (unmarshalled_packet.amount != packet.amount)
  {
    printf("unmarshalled packet amount = %d, expected %d\n",
           unmarshalled_packet.amount, packet.amount);
    return 1;
  }

  printf("tests passed\n");
  return 0;
}