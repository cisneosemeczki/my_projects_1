from __future__ import print_function
import os

if os.name == 'nt':
    import msvcrt
    def getch():
        return msvcrt.getch().decode()
else:
    import termios, fcntl, sys, os
    from select import select
    fd = sys.stdin.fileno()
    old_term = termios.tcgetattr(fd)
    new_term = termios.tcgetattr(fd)

    def getch():
        new_term[3] = (new_term[3] & ~termios.ICANON & ~termios.ECHO)
        termios.tcsetattr(fd, termios.TCSANOW, new_term)
        try:
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_term)
        return ch

    def kbhit():
        new_term[3] = (new_term[3] & ~(termios.ICANON | termios.ECHO))
        termios.tcsetattr(fd, termios.TCSANOW, new_term)
        try:
            dr,dw,de = select([sys.stdin], [], [], 0)
            if dr != []:
                return 1
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_term)
            sys.stdout.flush()

        return 0

from dynamixel_sdk import *                    # Uses Dynamixel SDK library

#############################################
# ilosc podlaczonych silnikow
while True:
    a = input("Podaj wspaniala liczbe silnikow (zakres od 1 do 5): ")
    try:
      b = int(a)
      if (b > 0 and b < 6):
        break
      else: print("Podales liczbe nie z zakresu! ")
    except ValueError:
      print("To nie liczba moj drogi! ")

DXL_ID_list = []
for i in range(b):
   id = 11+i
   DXL_ID_list.append(id)
print("   ")
#############################################


# Control table address
ADDR_DRIVE_MODE             = 10
ADDR_OPERATING_MODE         = 11               # Control table address is different in Dynamixel model
ADDR_TORQUE_ENABLE          = 64
ADDR_GOAL_POSITION          = 116
ADDR_PROFILE_VELOCITY       = 112
ADDR_PRESENT_POSITION       = 132


# Protocol version
PROTOCOL_VERSION            = 2.0               # See which protocol version is used in the Dynamixel

# Default setting
DXL_ID                      = DXL_ID_list       # Dynamixel ID : 1
BAUDRATE                    = 1000000           # Dynamixel default baudrate : 57600
DEVICENAME                  = "COM4"            # Check which port is being used on your controller
                                                # ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"

DRIVE_MODE_TYPE             = 0                 # Value for normal mode
TORQUE_ENABLE               = 1                 # Value for enabling the torque
TORQUE_DISABLE              = 0                 # Value for disabling the torque
GOAL_POSITION               = []                # range 0-4096
PROFILE_VELOCITY            = 10                # Value for maximum velocity
DXL_MOVING_STATUS_THRESHOLD = 20                # Dynamixel will rotate between this value
POSITION_CONTROL_MODE       = 3                 # Value for position control mode (operating mode) domyslnie bylo 4 (pozycja wieloobrotowa)

ESC_ASCII_VALUE             = 0x1b
SPACE_ASCII_VALUE           = 0x20

# Initialize PortHandler instance
# Set the port path
# Get methods and members of PortHandlerLinux or PortHandlerWindows
portHandler = PortHandler(DEVICENAME)

# Initialize PacketHandler instance
# Set the protocol version
# Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
packetHandler = PacketHandler(PROTOCOL_VERSION)

# Open port
if portHandler.openPort():
    print("Succeeded to open the port")
else:
    print("Failed to open the port")
    print("Press any key to terminate...")
    getch()
    quit()


# Set port baudrate
if portHandler.setBaudRate(BAUDRATE):
    print("Succeeded to change the baudrate")
else:
    print("Failed to change the baudrate")
    print("Press any key to terminate...")
    getch()
    quit()


for j in range(len(DXL_ID_list)):

    # Set drive mode to normal mode
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, DXL_ID[j], ADDR_DRIVE_MODE, DRIVE_MODE_TYPE)
    if dxl_comm_result != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
    elif dxl_error != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error))
    else:
        print("Drive mode on engine ",j+1," changed to normal mode.")

    # Set operating mode to position control mode
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, DXL_ID[j], ADDR_OPERATING_MODE, POSITION_CONTROL_MODE)
    if dxl_comm_result != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
    elif dxl_error != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error))
    else:
        print("Operating mode on engine ",j+1," changed to position control mode.")

    # Set (write) profile velocity
    dxl_comm_result, dxl_error = packetHandler.write4ByteTxRx(portHandler, DXL_ID[j], ADDR_PROFILE_VELOCITY, PROFILE_VELOCITY)
    if dxl_comm_result != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
    elif dxl_error != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error))
    else:
        print("Profile velocity on engine ",j+1," has been successfully changed.")
        print("   ")



for k in range(len(DXL_ID_list)):

    # Read present position
    dxl_present_position, dxl_comm_result, dxl_error = packetHandler.read4ByteTxRx(portHandler, DXL_ID[k], ADDR_PRESENT_POSITION)
    if dxl_comm_result != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
    elif dxl_error != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error))

    print("Połozenie napedu ", k+1," wynosi: %03d" % dxl_present_position)


for k in range(len(DXL_ID_list)):

    # Enable Dynamixel Torque
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, DXL_ID[k], ADDR_TORQUE_ENABLE, TORQUE_ENABLE)
    if dxl_comm_result != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
    elif dxl_error != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error))
    else:
        print("Dynamixel ", k+1, " has been successfully connected.")

    while True:
        polozenie = input("Podaj nowe polozenie silnika (zakres od 0 do 4096): ")
        try:
          s = int(polozenie)
          if (s > -1 and s < 4096):
            break
          else: print("Podales liczbe nie z zakresu! ")
        except ValueError:
          print("To nie liczba moj drogi! ")
    GOAL_POSITION.append(s)

    print("   ")


for k in range(len(DXL_ID_list)):

    # Write goal position
    dxl_comm_result, dxl_error = packetHandler.write4ByteTxRx(portHandler, DXL_ID[k], ADDR_GOAL_POSITION, GOAL_POSITION[k])
    if dxl_comm_result != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
    elif dxl_error != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error))


present_position = []

for k in range(len(DXL_ID_list)):

    while 1:
        # Read present position
        dxl_present_position, dxl_comm_result, dxl_error = packetHandler.read4ByteTxRx(portHandler, DXL_ID[k], ADDR_PRESENT_POSITION)
        if dxl_comm_result != COMM_SUCCESS:
            print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
        elif dxl_error != 0:
            print("%s" % packetHandler.getRxPacketError(dxl_error))

        if not abs(GOAL_POSITION[k] - dxl_present_position) > DXL_MOVING_STATUS_THRESHOLD:
            present_position.append(dxl_present_position)
            break


print("Wyswietlanie pozycji docelowych oraz osiagnietych przez kazdy naped: ")
for k in range(len(DXL_ID_list)):
    print("   [ID:%03d] GoalPos:%03d  PresPos:%03d" %(DXL_ID[k], GOAL_POSITION[k], present_position[k]), end = "\r")


for k in range(len(DXL_ID_list)):
    # Disable Dynamixel Torque
    dxl_comm_result, dxl_error = packetHandler.write1ByteTxRx(portHandler, DXL_ID[k], ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    if dxl_comm_result != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
    elif dxl_error != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error))
    print("Dynamixel ", k+1, " has been successfully disconnected.")


# Close port
portHandler.closePort()
