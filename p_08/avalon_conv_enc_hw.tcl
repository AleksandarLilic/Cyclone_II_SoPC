# TCL File Generated by Component Editor 13.0sp1
# Mon Feb 22 08:27:13 CET 2021
# DO NOT MODIFY


# 
# avalon_conv_enc "avalon_conv_enc" v1.0
# Aleksandar Lilic 2021.02.22.08:27:13
# Convolutional Encoder
# 

# 
# request TCL package from ACDS 13.1
# 
package require -exact qsys 13.1


# 
# module avalon_conv_enc
# 
set_module_property DESCRIPTION "Convolutional Encoder"
set_module_property NAME avalon_conv_enc
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP custom_accelerators
set_module_property AUTHOR "Aleksandar Lilic"
set_module_property DISPLAY_NAME avalon_conv_enc
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL avalon_conv_enc
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file avalon_conv_enc.vhd VHDL PATH avalon_conv_enc.vhd TOP_LEVEL_FILE
add_fileset_file conv_enc.vhd VHDL PATH conv_enc.vhd


# 
# parameters
# 


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1


# 
# connection point reset_n
# 
add_interface reset_n reset end
set_interface_property reset_n associatedClock clock
set_interface_property reset_n synchronousEdges DEASSERT
set_interface_property reset_n ENABLED true
set_interface_property reset_n EXPORT_OF ""
set_interface_property reset_n PORT_NAME_MAP ""
set_interface_property reset_n SVD_ADDRESS_GROUP ""

add_interface_port reset_n rstn reset_n Input 1


# 
# connection point conv_enc_cpu
# 
add_interface conv_enc_cpu avalon end
set_interface_property conv_enc_cpu addressUnits WORDS
set_interface_property conv_enc_cpu associatedClock clock
set_interface_property conv_enc_cpu associatedReset reset_n
set_interface_property conv_enc_cpu bitsPerSymbol 8
set_interface_property conv_enc_cpu burstOnBurstBoundariesOnly false
set_interface_property conv_enc_cpu burstcountUnits WORDS
set_interface_property conv_enc_cpu explicitAddressSpan 0
set_interface_property conv_enc_cpu holdTime 0
set_interface_property conv_enc_cpu linewrapBursts false
set_interface_property conv_enc_cpu maximumPendingReadTransactions 0
set_interface_property conv_enc_cpu readLatency 0
set_interface_property conv_enc_cpu readWaitStates 0
set_interface_property conv_enc_cpu readWaitTime 0
set_interface_property conv_enc_cpu setupTime 0
set_interface_property conv_enc_cpu timingUnits Cycles
set_interface_property conv_enc_cpu writeWaitTime 0
set_interface_property conv_enc_cpu ENABLED true
set_interface_property conv_enc_cpu EXPORT_OF ""
set_interface_property conv_enc_cpu PORT_NAME_MAP ""
set_interface_property conv_enc_cpu SVD_ADDRESS_GROUP ""

add_interface_port conv_enc_cpu conv_enc_chipselect chipselect Input 1
add_interface_port conv_enc_cpu conv_enc_write write Input 1
add_interface_port conv_enc_cpu conv_enc_writedata writedata Input 32
add_interface_port conv_enc_cpu conv_enc_readdata readdata Output 32
add_interface_port conv_enc_cpu conv_enc_address address Input 2
set_interface_assignment conv_enc_cpu embeddedsw.configuration.isFlash 0
set_interface_assignment conv_enc_cpu embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment conv_enc_cpu embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment conv_enc_cpu embeddedsw.configuration.isPrintableDevice 0

