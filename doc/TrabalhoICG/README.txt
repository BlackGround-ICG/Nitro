
ARQUIVOS
--------------------------------------------------
main.cpp

README.txt


INSTRU��ES
--------------------------------------------------
AS BIBLIOTECAS NECESS�RIAS S�O (A lib lGLEW deve ser add para utilizar o opengl3.x):
-lSDL2 -lGL -lGLU -lGLEW

COMPILANDO O PROJETO (LINUX)
----------------------------------------------------
D� permiss�o de execu��o para o script compilar.sh (chmod u+x 666 compilar.sh) e execute-o (./compilar.sh)

Ser� gerado um execut�vel do projeto com o nome "prog"



EXECUTANDO O PROJETO (LINUX)
-----------------------------------------------------
./prog 

INSTALACAO

 2017  sudo apt-get install libsdl2-2.0
 2018  sudo apt-get install libsdl2-dev
  2021  sudo apt-get install glew-utils 

Debian-based systems (including Ubuntu) can simply do 
"sudo apt-get install libsdl2-2.0" to get the library 
installed system-wide, and all sorts of other useful
dependencies, too. "sudo apt-get install libsdl2-dev"
will install everything necessary to build programs 
that use SDL. Please see docs/README-linux.md for a 
more complete discussion of packages involved.

sudo apt-get install libglew-dev
sudo apt-get install libsdl2-image-dev