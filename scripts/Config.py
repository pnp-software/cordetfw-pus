#-----------------------------------------------------------------------       
# This module holds global variables and constants.
#-----------------------------------------------------------------------       
       
# Dictionary representation of the spec_item table.
# The dictionary key is the database ID. A dictionary entry is a 
# dictionary holding the definition of a spec_item
specItems = {}

# Dictionary linking enumerated types to their enumerated values.
# The key is a spec_item of enumerated type and the value
# is a list of specItems holding the associated enumerated values.
enumTypesToEnumValues = {}

# Dictionary linking enumerated values to the derived packets for which 
# they serve as discriminant.
# The key is a spec_item of enumerated value type and the value
# is a list of specItems holding the derived packets which have that
# enumerated value as discriminant. Normally, the list should only
# contain one item (since the same discriminant value should not be used
# in multiple derived packets)
enumValToDerPckts = {}

# Dictionary linking a packet to its parameters.
# The key is a spec_item of Packet type value type and the value
# is a list of specItems holding the parameters in that packet.
pcktToPcktPars = {}

# Dictionary linking a derived packet to its parameters.
# The key is a spec_item of DerPacket type value type and the value
# is a list of specItems holding the parameters in that packet.
derPcktToPcktPars = {}

# Dictionary linking a packet to its derived packets.
# The key is a spec_item of Packet type value type and the value
# is a list of specItems holding the packets derived from that packet.
pcktToDerPckts = {}

# Length in bytes of the header in a telemetry packet
tmPcktHeaderLen = 20

# Length in bytes of the header in a telecommand packet
tcPcktHeaderLen = 16

# Length in bytes of the header in a telecommand packet
pcktCrcLen = 2


