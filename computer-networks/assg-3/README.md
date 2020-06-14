# Assignment 3

## Questions

1. Display the different header fields (Ethernet headers, IP headers and TCP headers) of the packets intercepted of the NIC of your system using raw socket. Analyze and explain the data.

2. Write a program to schedule booting of ten machines in your laboratory everyday (except Saturday and Sunday) at 10 a.m. in the morning. `(Cron and Wake On LAN)`

## Example Console Output

### Question 1

```
-- socket created successfully

Ethernet Header
===============
|- Source Address       : 50-3E-AA-2E-AA-8C
|- Destination Address  : 54-B8-0A-8D-E4-C0
|- Protocol             : 8

IP Header
=========
|- Version                      : 4
|- Internet Header Length       : 5 DWORDS or 20 Bytes
|- Type Of Service              : 0
|- Total Length                 : 61 Bytes
|- Identification               : 15433
|- Time To Live                 : 64
|- Protocol                     : 17
|- Header Checksum              : 10878
|- Source IP                    : 192.168.0.6
|- Destination IP               : 74.125.200.189

TCP Header
==========
|- Source Port                  : 38741
|- Destination Port             : 443
|- Sequence Number              : 41
|- Acknowledge Sequence         : 21892
|- TCP Header Length            : 8 DWORDS or 32 Bytes
   |- Urgent Flag               : 1
   |- Acknowledgement Flag      : 1
   |- Push Flag                 : 1
   |- Reset Flag                : 0
   |- Synchronize Flag          : 0
   |- Finish Flag               : 0
|- Window Size                  : 10130
|- Checksum                     : 54165
|- Urgent Pointer               : 9682

-- socket closed
```

### Question 2

For console input: ```./wol d0:53:49:96:c4:e8 192.168.0.5```

Output:
```
Packet destination: d0:53:49:96:c4:e8

Broadcast address: 192.168.0.5

-- Wake Up packet sent
```
