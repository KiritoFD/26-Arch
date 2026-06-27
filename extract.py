import re
t = open('/tmp/xv6_pipe.log').read()
ch = re.findall(r"UART_TX: 0x[0-9a-f]+ '(.)'", t)
print(''.join(ch)[:1000])
