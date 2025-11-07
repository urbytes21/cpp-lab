## OVERVIEW
 - Structure:
       includes/   → header files (.h, .hpp)
       src/        → source files (.cpp)
       tests/      → GoogleTest test cases

## DEPENDENCIES

## SETUP
* Setup the Local Test Environment
    * Using your own Ubuntu system
        * Install `gcc`, `cmake`, `git`, and `pthread` (Skip this step if you already install)
            ```
            $ sudo apt-get update
            $ sudo apt-get install g++=4:5.3.1-1ubuntu1
            $ sudo apt-get install lcov=1.12-2
            $ sudo apt-get install cmake=3.5.1-1ubuntu3
            $ sudo apt-get install git=1:2.7.4-0ubuntu1.6
            $ sudo apt-get install libpthread-stubs0-dev=0.3-4

            ```
        * Build the application and the tests
            ```
            $ cd build
            $ cmake ..
            $ cmake --build .

            ```
        * Run the application and the test
            ```
            $ ./cpp_lab_project
            $ ./cpp_lab_project_test
            ```
        * (Optional) Run the cpp check
            ```
            $ sudo apt-get install cppcheck
            $ cppcheck "folder" / "file"
            ```
    * Using **Docker**
        * Use the -t or --tag flag to set the name of the image to be created. (the full name is actually sample-ci-cpp:latest, since latest is the default tag)
        * Opening an interactive shell inside your Docker container to explore, test, or debug the environment built from your image.
            * docker run → start a new container.
            * -it → run it interactively:
            * -i = keep STDIN open (so you can type commands)
            * -t = allocate a terminal (TTY)
            * sample-ci-cpp:latest → the image you built earlier.
            * /bin/bash → the command to execute inside the container (opens a Bash shell).
            ```
            docker build --tag sample-ci-cpp .
            docker run -it sample-ci-cpp:latest /bin/bash
            printenv
            ```
