import serial.tools.list_ports as L
for p in L.comports():
    vid = p.vid if p.vid is not None else 0
    pid = p.pid if p.pid is not None else 0
    print(f"{p.device}  vid={hex(vid)} pid={hex(pid)}  {p.description}")
