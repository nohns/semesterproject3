#include <stdio.h>

#include "../include/packet.h"

#define PACKET_TYPE_WITHOUT_DATA DMC_PACKET_MACHINE_OK
#define PACKET_TYPE_WITH_DATA DMC_PACKET_CONTAINER_VOLUME_MEASURED

int main(void)
{
  // Test case 1: initialize packets correctly
  struct dmc_packet *p1 = dmc_packet_init(PACKET_TYPE_WITHOUT_DATA);
  struct dmc_packet *p2 = dmc_packet_init(PACKET_TYPE_WITH_DATA);
  if (p1->data != NULL)
  {
    printf("packet type with 0 data bytes had payload allocated.\n");
    return 1;
  }
  if (p1->data_len > 0)
  {
    printf("packet initially had payload of length greater than 0\n");
    return 1;
  }

  unsigned p2_data_bytes = PACKET_TYPE_WITH_DATA & 0b00001111;
  if (p2->data == NULL)
  {
    printf("packet type with %d data bytes did NOT have payload allocated.\n",
           p2_data_bytes);
    return 1;
  }

  // test case 2: append complete data
  for (int i = 0; i < p2_data_bytes; i++)
  {
    if (dmc_packet_append_byte(p2, 0b11111111) != 0)
    {
      printf("packet type with %d data bytes could not append byte with "
             "payload length %ld\n",
             p2_data_bytes, p2->data_len);
      return 1;
    }
  }

  if (p2->data_len != p2_data_bytes)
  {
    printf("packet type with %d data bytes had payload length %ld\n",
           p2_data_bytes, p2->data_len);
    return 1;
  }

  // test case 3: is packet complete
  if (!dmc_packet_complete(p2))
  {
    printf("packet where amount of data bytes from type were equal to payload "
           "data len, was NOT considered complete\n");
    return 1;
  }

  printf("tests passed\n");
  return 0;
}