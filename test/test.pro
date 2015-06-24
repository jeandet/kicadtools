

TEMPLATE = subdirs
CONFIG   += ordered release

SUBDIRS += dumpLispLikeFiles \
    PCBView \
    QtGuiTests




OTHER_FILES += \
    testFiles/netlist1.net \
    testFiles/netlist2.net \
    testFiles/pcb1.kicad_pcb \
    testFiles/pcb2.kicad_pcb \
    testFiles/pcb3.kicad_pcb




