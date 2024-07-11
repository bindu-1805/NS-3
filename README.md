NS-3 is an open-source, discrete-event network simulator specifically designed for Internet systems. It is a popular choice for researchers and educators due to its ease of use, speed and accuracy compared to other simulators. While the core simulation scripts are written in C++, NS-3 also provides Python scripting support. An NS-3 user will obtain the ns-3 source code, compile it into shared or static libraries, and link the libraries to the main() programs that he or she authors. The main() program is where the specific simulation scenario configuration is performed.

## NS-3 Installation on Ubuntu 22.04

1. Type the following command in the terminal, <br />
```
   $ sudo apt update 
   $ sudo apt install g++ python3 cmake ninja-build git gir1.2-goocanvas-2.0 python3-gi python3-gi-cairo python3-pygraphviz gir1.2-gtk-3.0 ipython3 tcpdump wireshark sqlite sqlite3 libsqlite3-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools openmpi-bin openmpi-common openmpi-doc libopenmpi-dev doxygen graphviz imagemagick python3-sphinx dia imagemagick texlive dvipng latexmk texlive-extra-utils texlive-latex-extra texlive-font-utils libeigen3-dev gsl-bin libgsl-dev libgslcblas0 libxml2 libxml2-dev libgtk-3-dev lxc-utils lxc-templates vtun uml-utilities ebtables bridge-utils libxml2 libxml2-dev libboost-all-dev ccache
```
3. Download version ns-3.41 from the website, [NS-3](https://www.nsnam.org/releases/ns-3-41/).
4. Move the downloaded file to the home folder and extract it there.
5. A separate folder called ns-allinone-3.41 is created in the home folder with all the necessary software.
6. Open the terminal and type in the following commands,
7. ```
   $  cd ns-allinone-3.41 
   $ ./build.py --enable-examples --enable-tests 
   
   ```
   The above line will install all the packages for ns3 along with NetAnim, flow monitor,  applications etc.
   Depending on your system, it can take between 20 minutes to 2 hours.
8. Once the installation is completed. check whether the software is working by typing, <br />
```
   $ cd ns-3.41/ 
   $ ./ns3 run hello-simulator
```

## Testing NS-3

The build installed can be checked by running unit tests using the following command, <br />
```
$ ./test.py 
```
This command should run several hundred unit tests. If they pass, you have made a successful initial build of NS-3.

![unit tests](https://github.com/bindu-1805/NS-3/assets/137310333/c263f0c6-c48e-4c71-837d-8f651f1636ab)

## Running the programs on NS-3

Scratch folders have extra permissions, modules and linkages to run .cc files and .py files. So all .cc/.py files have to be copied to the scratch folder. You can navigate to the scratch folder using, <br />
```
$ cd ns-allinone-3.41/ns-3.41/scratch 
```
To run the program, <br />
```
$ cd ns-allinone-3.41/ns-3.41 
$ cd ./ns3 run scratch/<program_name>
```

## Using NetAnim

NetAnim animates a previously executed simulation using an XML trace file generated during a simulation. <br />
1. To open NetAnim use the following command,
```
$ cd ns-allinone-3.41/netanim-3.109
$ ./NetAnim
```
2. Use the file button to open the xml file.

## Using Tracemetrics

TraceMetrics is a trace file analyzer for NS-3. <br />
1. Download the software from the link (TraceMetrics)[https://sourceforge.net/projects/tracemetrics/]
2. Extract the zip file in the Home folder.
3. ```
   $ cd tracemetrics-1.4.0
   $ java -jar tracemetrics.jar
   ```
4. Once the software opens, choose the tr file to be analyzed.

## Running .plt files

Gnuplot is a portable command-line driven graphing utility for Linux, OS/2, MS Windows, OSX, VMS, and many other platforms. <br />
Use the following command to run the .plt file,
```
$ cd gnuplot gnu.plt
```

## Running PCAP files

To open a .pcap file, <br />
```
wireshark <filename>
```
OR <br />
```
tcpdump -n -t -r <filename>
```


