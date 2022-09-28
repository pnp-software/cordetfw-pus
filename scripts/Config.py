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

