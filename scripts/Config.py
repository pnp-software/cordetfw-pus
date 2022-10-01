#-----------------------------------------------------------------------       
# This module holds global variables and constants.
#-----------------------------------------------------------------------       
       
# Dictionary representation of the spec_item table.
# The dictionary key is the database ID. A dictionary entry is a 
# dictionary holding the definition of a spec_item
specItems = {}

# Dictionary linking enumerated types to their enumerated values.
# The key is the name of a spec_item of enumerated type and the value
# is a list of specItems holding the associated enumerated values.
enumTypesToEnumValues = {}

# Dictionary linking enumerated values to the derived packets for which 
# they serve as discriminant.
# The key is the name of a spec_item of enumerated value type and the value
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

# Dictionary linking a spec_item name of the form 'Dom:Name" to the
# the spec_item itself.
domNameToSpecItem = {}

# List of spec_items of type OutComponent
outComponents = []

# List of spec_items of type InCommand
inCommands = []

# List of Data Item Types of type InCommand
dataItemTypes = []

# List of Enumerated Types of type InCommand
enumTypes = []

# Directory where generated tables for PUS Spec are stored
generatedTablesDir = 'doc/pus/GeneratedTables'

# Directory where configuration files are stored
configDir = 'tests/PusConfig'

# Length in bytes of the header in a telemetry packet
tmPcktHeaderLen = 20

# Length in bytes of the header in a telecommand packet
tcPcktHeaderLen = 16

# Length in bytes of the header in a telecommand packet
pcktCrcLen = 2

# Maximum number of OutComponents which may be allocated at any one time 
CR_FW_OUTFACTORY_MAX_NOF_OUTCMP = 60

# Maximum length of a line in doxygen comment
MAX_LINE_LENGTH = 80

# Maximum number of InCommands which may be allocated at any one time
CR_FW_INFACTORY_MAX_NOF_INCMD = 63

