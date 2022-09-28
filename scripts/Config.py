#-----------------------------------------------------------------------       
# This module holds global variables for the CsPsCodeGenerator
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

