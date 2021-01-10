# 过滤规则

ftp
http || tcp || arp
ip.src=120.79.158.25
ip.dst=120.79.158.25
ip.addr=120.79.158.25
tcp.port=80
TCP packets containing the 00 00 01 byte sequence can be filtered using the following way:
tcp contains 00:00:01
