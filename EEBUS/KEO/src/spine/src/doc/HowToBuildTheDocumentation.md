# HowTo: Building the Doxygen documentation of keo_spine

## PlantUML
The documentation uses [PlantUML](http://de.plantuml.com) to create UML diagrams.
Therefore the plantuml.jar file has to copied to a directory of the build host which is contained in PATH.

## PlantUML and the CMake project
PlantUml is enabled in CMake by setting the CMake option "CREATE_PLANTUML" to ON.
This option finds the 'plantuml.jar' and enables the embedded PlantUML feature in Doxygen.
For stand alone PlantUML files CMake creates a custom target called: "GeneratePlantUml".
Just add the filenames (absolute) of your PlantUML sources to the CMake variable: "PLANTUML_SOURCES" 
and the target will create png's at <build directory>/doc/images/plantuml.
 
## Doxygen
To allow embedding PlantUML in Doxygen, the Doxygen version has to be >= 1.8.4 (i use 1.8.11).

## Building the documentation
Build the documentation from within the build directory.

1. Set the CMake options GENERATE_DOC and CREATE_PLANTUML to 'ON' by calling ccmake
~~~~~~~~~~~~~~~~~~{.sh}
ccmake .
make rebuild_cache
~~~~~~~~~~~~~~~~~~

2. Generate the documentation
~~~~~~~~~~~~~~~~~~{.sh}
make doxygen
~~~~~~~~~~~~~~~~~~

3. Generate separate PlantUML images from the PLANTUML_SOURCES list. (optional)
~~~~~~~~~~~~~~~~~~{.sh}
make GeneratePlantUml
~~~~~~~~~~~~~~~~~~

## Hints
It is helpfull to use the Eclipse PlantUML plugin, when writing documentation with Eclipse.
The content is rendered while editing the embedded diagrams.
