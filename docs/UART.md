# Raspberry Pi <-> PSoC UART protocol

## v0.0.1

First Byte:

```
MSB 8 7 6 5 4 3 2 1 LSB -- Description
    <------------->        PACKET_TYPE
```

Second Byte:

```
MSB 8 7 6 5 4 3 2 1 LSB -- Description
    <------------->        NUM_BYTES
```

Nth Byte (NUM_BYTES = max 255):
