"""Read FT2232H EEPROM using FT_EE_Program/FT_EE_Read structured API.

This uses the FT_PROGRAM_DATA structure which is the proper way to read/write
FTDI EEPROMs (handles string layout and checksum automatically).
"""
import ctypes

ftd2xx = ctypes.windll.FTD2XX

# FT_PROGRAM_DATA structure for FT2232H
#typedef struct ft_program_data {
#    DWORD Signature1;          // 0
#    DWORD Signature2;          // 1
#    WORD Version;              // 2
#    WORD VendorId;             // 3
#    WORD ProductId;            // 4
#    char *Manufacturer;        // 5  pointer
#    char *ManufacturerId;       // 6  pointer
#    char *Description;         // 7  pointer
#    char *SerialNumber;        // 8  pointer
#    WORD MaxPower;             // 9
#    WORD PnP;                  // 10
#    WORD SelfPowered;          // 11
#    WORD RemoteWakeup;         // 12
#    //
#    // Rev4 (FT232B, FT245B) extensions
#    //
#    BYTE Rev4;                 // 13
#    BYTE IsoIn;               // 14
#    BYTE IsoOut;              // 15
#    BYTE PullDownEnable;      // 16
#    BYTE SerNumEnable;        // 17
#    BYTE USBVersionEnable;    // 18
#    //
#    // Rev5 (FT2232C) extensions
#    //
#    BYTE Rev5;                // 19
#    BYTE IsoInA;             // 20
#    BYTE IsoInB;             // 21
#    BYTE IsoOutA;            // 22
#    BYTE IsoOutB;            // 23
#    BYTE PullDownEnable5;    // 24
#    BYTE SerNumEnable5;     // 25
#    BYTE USBVersionEnable5;  // 26
#    BYTE AIsHighCurrent;    // 27
#    BYTE BIsHighCurrent;    // 28
#    BYTE IFAIsFifo;         // 29
#    BYTE IFAIsFifoTar;      // 30
#    BYTE IFAIsFastSer;      // 31
#    BYTE AIsVCP;            // 32
#    BYTE IFBIsFifo;         // 33
#    BYTE IFBIsFifoTar;      // 34
#    BYTE IFBIsFastSer;      // 35
#    BYTE BIsVCP;            // 36
#    //
#    // Rev 6 (FT232R) extensions
#    //
#    BYTE UseExtOsc;          // 37
#    BYTE HighDriveIOs;       // 38
#    BYTE EndpointSize;       // 39
#    BYTE PullDownEnableR;    // 40
#    BYTE SerNumEnableR;      // 41
#    BYTE InvertTXD;          // 42
#    ... (FT232R-specific stuff we don't need for FT2232H)
#    //
#    // Rev 7 (FT2232H) extensions
#    //
#    BYTE Rev7;               // channel C/D stuff we skip
#    ...
#} FT_PROGRAM_DATA;

# Define the structure - careful with packing
class FT_PROGRAM_DATA(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("Signature1", ctypes.c_uint32),
        ("Signature2", ctypes.c_uint32),
        ("Version", ctypes.c_uint16),
        ("VendorId", ctypes.c_uint16),
        ("ProductId", ctypes.c_uint16),
        ("Manufacturer", ctypes.c_void_p),
        ("ManufacturerId", ctypes.c_void_p),
        ("Description", ctypes.c_void_p),
        ("SerialNumber", ctypes.c_void_p),
        ("MaxPower", ctypes.c_uint16),
        ("PnP", ctypes.c_uint16),
        ("SelfPowered", ctypes.c_uint16),
        ("RemoteWakeup", ctypes.c_uint16),
        # Rev4
        ("Rev4", ctypes.c_ubyte),
        ("IsoIn", ctypes.c_ubyte),
        ("IsoOut", ctypes.c_ubyte),
        ("PullDownEnable", ctypes.c_ubyte),
        ("SerNumEnable", ctypes.c_ubyte),
        ("USBVersionEnable", ctypes.c_ubyte),
        # Rev5
        ("Rev5", ctypes.c_ubyte),
        ("IsoInA", ctypes.c_ubyte),
        ("IsoInB", ctypes.c_ubyte),
        ("IsoOutA", ctypes.c_ubyte),
        ("IsoOutB", ctypes.c_ubyte),
        ("PullDownEnable5", ctypes.c_ubyte),
        ("SerNumEnable5", ctypes.c_ubyte),
        ("USBVersionEnable5", ctypes.c_ubyte),
        ("AIsHighCurrent", ctypes.c_ubyte),
        ("BIsHighCurrent", ctypes.c_ubyte),
        ("IFAIsFifo", ctypes.c_ubyte),
        ("IFAIsFifoTar", ctypes.c_ubyte),
        ("IFAIsFastSer", ctypes.c_ubyte),
        ("AIsVCP", ctypes.c_ubyte),
        ("IFBIsFifo", ctypes.c_ubyte),
        ("IFBIsFifoTar", ctypes.c_ubyte),
        ("IFBIsFastSer", ctypes.c_ubyte),
        ("BIsVCP", ctypes.c_ubyte),
        # Rev6 (FT232R) - we use dummy bytes for FT2232H
        ("UseExtOsc", ctypes.c_ubyte),
        ("HighDriveIOs", ctypes.c_ubyte),
        ("EndpointSize", ctypes.c_ubyte),
        ("PullDownEnableR", ctypes.c_ubyte),
        ("SerNumEnableR", ctypes.c_ubyte),
        ("InvertTXD", ctypes.c_ubyte),
        ("InvertRXD", ctypes.c_ubyte),
        ("InvertRTS", ctypes.c_ubyte),
        ("InvertCTS", ctypes.c_ubyte),
        ("InvertDTR", ctypes.c_ubyte),
        ("InvertDCD", ctypes.c_ubyte),
        ("InvertRI", ctypes.c_ubyte),
        ("BCDChargeEnable", ctypes.c_ubyte),
        ("BCDForceCDAC", ctypes.c_ubyte),
        ("BCDChargeCurrent", ctypes.c_ubyte*4),
        # Rev7 (FT2232H)
        ("CBus0", ctypes.c_ubyte),
        ("CBus1", ctypes.c_ubyte),
        ("CBus2", ctypes.c_ubyte),
        ("CBus3", ctypes.c_ubyte),
        ("CBus4", ctypes.c_ubyte),
        ("CBus5", ctypes.c_ubyte),
        ("CBus6", ctypes.c_ubyte),
        ("CBus7", ctypes.c_ubyte),
        ("CBus8", ctypes.c_ubyte),
        ("CBus9", ctypes.c_ubyte),
        ("IsFifo5", ctypes.c_ubyte),
        ("IsFifoTar5", ctypes.c_ubyte),
        ("IsFastSer5", ctypes.c_ubyte),
        ("IsFTDIFifoData", ctypes.c_ubyte),
        ("IsFifoDataR", ctypes.c_ubyte),
        ("IsFifoDataTar", ctypes.c_ubyte),
        ("IsFastSerData", ctypes.c_ubyte),
        ("FIFOSignal", ctypes.c_ubyte),
        ("DriverType", ctypes.c_ubyte),
    ]


# Set up function prototypes
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_EE_Read.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
ftd2xx.FT_EE_Read.restype = ctypes.c_uint32
ftd2xx.FT_EE_Program.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
ftd2xx.FT_EE_Program.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32

# Open device
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
print(f"FT_Open(0) status={status}")
if status != 0:
    exit(1)

# Allocate buffers for strings (must be writable)
manuf = ctypes.create_string_buffer(256)
manuf_id = ctypes.create_string_buffer(256)
desc = ctypes.create_string_buffer(256)
serial = ctypes.create_string_buffer(256)

pd = FT_PROGRAM_DATA()
pd.Signature1 = 0
pd.Signature2 = 0xFFFFFFFF
pd.Version = 5  # request FT2232H version

# Set pointers - use raw buffer addresses
pd.Manufacturer = ctypes.addressof(manuf)
pd.ManufacturerId = ctypes.addressof(manuf_id)
pd.Description = ctypes.addressof(desc)
pd.SerialNumber = ctypes.addressof(serial)

# FT_EE_Read signature: FT_STATUS FT_EE_Read(FT_HANDLE ftHandle, PFT_PROGRAM_DATA pData)
status = ftd2xx.FT_EE_Read(handle, ctypes.byref(pd))
print(f"\nFT_EE_Read status={status}")

if status == 0:
    print(f"Signature1 = 0x{pd.Signature1:08x}")
    print(f"Signature2 = 0x{pd.Signature2:08x}")
    print(f"Version    = {pd.Version}")
    print(f"VendorId   = 0x{pd.VendorId:04x}")
    print(f"ProductId  = 0x{pd.ProductId:04x}")
    print(f"Manufacturer = {ctypes.string_at(pd.Manufacturer) if pd.Manufacturer else None}")
    print(f"ManufacturerId = {ctypes.string_at(pd.ManufacturerId) if pd.ManufacturerId else None}")
    print(f"Description = {ctypes.string_at(pd.Description) if pd.Description else None}")
    print(f"SerialNumber = {ctypes.string_at(pd.SerialNumber) if pd.SerialNumber else None}")
    print(f"MaxPower    = {pd.MaxPower} (units of 2mA)")
    print(f"PnP         = {pd.PnP}")
    print(f"SelfPowered = {pd.SelfPowered}")
    print(f"RemoteWakeup = {pd.RemoteWakeup}")
    print()
    print("=== Rev5 (FT2232) settings ===")
    print(f"Rev5                = {pd.Rev5}")
    print(f"IsoInA              = {pd.IsoInA}")
    print(f"IsoInB              = {pd.IsoInB}")
    print(f"IsoOutA             = {pd.IsoOutA}")
    print(f"IsoOutB             = {pd.IsoOutB}")
    print(f"PullDownEnable5     = {pd.PullDownEnable5}")
    print(f"SerNumEnable5       = {pd.SerNumEnable5}")
    print(f"USBVersionEnable5   = {pd.USBVersionEnable5}")
    print(f"AIsHighCurrent      = {pd.AIsHighCurrent}")
    print(f"BIsHighCurrent      = {pd.BIsHighCurrent}")
    print(f"IFAIsFifo           = {pd.IFAIsFifo}")
    print(f"IFAIsFifoTar        = {pd.IFAIsFifoTar}")
    print(f"IFAIsFastSer        = {pd.IFAIsFastSer}")
    print(f"AIsVCP              = {pd.AIsVCP}   <-- Channel A VCP enable (1=VCP, 0=D2XX)")
    print(f"IFBIsFifo           = {pd.IFBIsFifo}")
    print(f"IFBIsFifoTar        = {pd.IFBIsFifoTar}")
    print(f"IFBIsFastSer        = {pd.IFBIsFastSer}")
    print(f"BIsVCP              = {pd.BIsVCP}   <-- Channel B VCP enable")
else:
    print("Failed to read structured EEPROM data")

ftd2xx.FT_Close(handle)
