# 422-Project-2

# Description of System

Matrix Solver is a learning tool that translates linear algebra operations into a string of steps.

# Authors: 

Gus Cochran, Jerin Spencer, Elijah Thomas, Kaylee Thomas, Drew Tweedale

Initial Commit 5-25-2024
Current Version v1 6-5-2024

Created for Project 2 in Computer Science Software Methodologies (CS422) Spring 24 taught by Professor Anthony Hornof.


# Source Code Setup

Download Node.js

Node.js is the runtime environment that Matrix Solver requires to run. First, go to https://nodejs.org/en/download/prebuilt-installer/current and install the prebuild installer.
This will also install NPM on your computer as , which is the pacakage manager that we use to control the application. Inside the Node.js install wizard, select next, agree to the EULA,
choose whaterever directory you would like to install it in, then next. Some NPM packages require python, so if you don't have python installed, click the checkbox, next, then install.

# How to Compile and Run

Navigate to the root directory of the source code in a terminal. In the terminal, type "node -v" and hit enter to verify that Node.js has been installed. Then, type "npm -v" and hit enter to verify that npm has been installed. If one or both of the packages was not installed, review the source code estup entry. If both Node.js and NPM are installed, type "npm start" to run the application.

# Software Dependencies

Eigen Library: The Eigen library is located within the source code's root directory. 

# Description of Each Subdirectory

eigen: Contains the eigen library required for the operations performed by the solver modules.

node_modules: An artifact of the creation of the Node.js runtime environment. Contains all commonly used
node modules. The modules relevant to the application are electron, child_process, and text-decoder

renderer: Contains the files to be prepended to index.html upon loading.

solvers: Contains the solver implementations written to return the data format required for the application.


