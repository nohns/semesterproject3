#ifndef DMC_PACKET_H
#define DMC_PACKET_H

#ifdef MODULE // Include kernel space memory allocation with kmalloc
#include <linux/slab.h>
#endif

#include <stdlib.h>

/**
 * @brief Type of packet. MSB is required to be 1 as this signals a header byte
 */
enum dmc_packet_type
{
  DMC_PACKET_OUT_OF_ORDER = 0b10000000,
  DMC_PACKET_CONTAINER_WEIGHT_UPDATE = 0b10010010,
};

struct dmc_packet
{
  /**
   * @brief Type of packet. This is the first byte received.
   */
  enum dmc_packet_type type;

  /**
   * @brief Data payload of packet
   */
  char *data;

  /**
   * @brief Length of payload in bytes.
   */
  size_t data_len;
};

/**
 * @brief Allocates and initializes a packet with a type. Primarily
 * used when starting to read data from a given source.
 */
struct dmc_packet *dmc_packet_init(enum dmc_packet_type type)
{
  unsigned char data_bytes = type & 0b00001111;

  // Allocate and initialize packet with default values
  struct dmc_packet *packet;
#ifdef MODULE // Differeniate between kernel and use space allocations
  packet = (struct dmc_packet *)kmalloc(sizeof(struct dmc_packet), GFP_KERNEL);
#else
  packet = (struct dmc_packet *)malloc(sizeof(struct dmc_packet));
#endif
  packet->type = type;
  packet->data_len = 0;
  packet->data = NULL;

  // Allocate packet data if needed
  if (data_bytes > 0)
  {
#ifdef MODULE // Differeniate between kernel and use space allocations
    packet->data = (char *)kmalloc(sizeof(char) * data_bytes, GFP_KERNEL);
#else
    packet->data = (char *)malloc(sizeof(char) * data_bytes);
#endif
  }

  return packet;
}

/**
 * @brief De-allocate packet and its data
 */
void dmc_packet_free(struct dmc_packet *packet)
{
#ifdef MODULE // Differeniate between kernel and use space de-allocations
  kfree((void *)packet->data);
  kfree((void *)packet);
#else
  free((void *)packet->data);
  free((void *)packet);
#endif
}

/**
 * @brief Checks if a packet is fully complete, in the sense that all intended
 * data is received
 * @returns True, if packet is complete.
 */
unsigned char dmc_packet_complete(struct dmc_packet *packet)
{
  unsigned char data_bytes = packet->type & 0b00001111;
  return data_bytes == packet->data_len;
}

/**
 * @brief Appends data byte to packet payload.
 * @returns 0 if successful, 1 if payload is already at capacity.
 */
unsigned char dmc_packet_append_byte(struct dmc_packet *packet,
                                     unsigned char data)
{
  unsigned char data_bytes = packet->type & 0b00001111;
  if (data_bytes == packet->data_len)
  {
    return 1;
  }

  packet->data[packet->data_len++] = data;
  return 0;
}

#endif // DMC_PACKET_H