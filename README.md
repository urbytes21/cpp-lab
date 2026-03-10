## 1. Overview
**TL;DR**
```bash
./run.sh
```

**Project Hierarchy**
```
includes/   → Header files (.h, .hpp)  
src/        → Source files (.cpp)  
tests/      → GoogleTest test cases  
```

## 2. Dependencies
Make sure the following tools are installed before building the project:
- **g++ / gcc**
- **CMake**
- **Git**
- **lcov** (for code coverage)
- **cppcheck** (for static analysis)
- **Optional:** Install `clang-format` to format C++ code.

**Linux**
```bash
sudo apt install clang-format
find . -regex '.*\.\(cpp\|h\|hpp\)' -exec clang-format -i {} \;
```
**Windows**
```bash
# Install clang-format via Chocolatey
choco install clang-format

# Apply clang-format recursively to .cpp, .h, .hpp files
Get-ChildItem -Recurse -Include *.cpp, *.h, *.hpp | ForEach-Object { clang-format -i $_.FullName }
```
## 3. Setup
### 3.1. Setup the Local Test Environment
- **Ubuntu system**
    * Install `gcc`, `cmake`, `git`, and `pthread` (Skip this step if you already install)
        ```bash
        $ sudo apt-get update
        $ sudo apt-get install g++
        $ sudo apt-get install lcov
        $ sudo apt-get install cmake
        $ sudo apt-get install git
        $ sudo apt install valgrind
        $ sudo apt-get install cppcheck
        $ sudo apt-get install -y clang-tidy
        $ sudo apt install python3-gcovr
        ```
    * Build the application and the tests
        ```bash
        $ cd build
        $ cmake ..
        $ cmake --build .
        ```
    * Run the application and the test
        ```bash
        $ ./cpp_lab_project
        $ ./cpp_lab_project_test
        ```
    * Detect Memory Leak Using [valgrind](https://valgrind.org/)
        ```bash
        $ valgrind --leak-check=full -v ./cpp-lab 
        ```
    * (Optional) Run static analysis - cppcheck
        ```bash
        $ cppcheck "folder" / "file"
        ```
    * (Optional) Run static analysis - clang-tidy
        ```bash
        $ clang-tidy -p build -header-filter='^src/.*' $(find src -name "*.cpp")
        ```
    * (Optional) Run coverage - clang-tidy
        ```bash
        $ clang-tidy -p build -header-filter='^src/.*' $(find src -name "*.cpp")
        ```
- **Docker**
    * Update `Dockerfile`
    * Build the Docker image
        ```
        $ cd build
        $ docker build --tag cpp-lab .
        ```
    * Run an interactive container
        ```
        $ docker run -it cpp-lab:latest /bin/bash
        ```
    * Inspect the environment
        ```
        $ printenv
        ```
    * *Notes:*
        * Use the `-t` or `--tag` flag to set the name of the image to be created. (the full name is actually `cpp-lab:latest`, since latest is the default tag)
        * Opening an interactive shell inside your Docker container to explore, test, or debug the environment built from your image.
        * docker run to start a new container.
        * `-it`: run it interactively:
        * `-i`: keep STDIN open (so you can type commands)
        * `-t`: allocate a terminal (TTY)
        * `cpp-lab:latest`: the image you built earlier.
        * `/bin/bash`: the command to execute inside the container (opens a Bash shell).

### 3.2 Configure C/C++ debugging
```json
// launch.json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/debug/cpp_lab_project", // path to the executable
            "args": [],
            "stopAtEntry": true,
            "cwd": "${workspaceFolder}",    // working directory
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "preLaunchTask": "CMake Debug Build",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
        },
    ]
}

// tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "CMake Debug Configure",
            "type": "shell",
            "command": "cmake",
            "args": [
                "-S",
                ".",
                "-B",
                "build/debug",
                "-DCMAKE_BUILD_TYPE=Debug"
            ]
        },
        {
            "label": "CMake Debug Build",
            "type": "shell",
            "command": "cmake",
            "args": [
                "--build",
                "build/debug"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "reveal": "always"
            },
            "dependsOn": "CMake Debug Configure"
        }
    ]
}
```
- 1. Open project using VSCode
- 2. Install `The C/C++ Extension Pack`
- 3. Install gdb
```bash
$ sudo apt update
$ sudo apt install gdb
```
- 4. `F5`: Start Debug
- 5. `Ctrl + F5`: Run without debug
- 6. `Ctrl + Shift + B`: Build project (optional)


### 3.3 Documentation with `doxygen`
TBD - Refer to this [Documentation with doxygen](https://www.labri.fr/perso/fleury/posts/programming/using-cmake-googletests-and-gcovr-in-a-c-project.html#:~:text=of%20the%C2%A0project.-,Documentation%20with%20doxygen,-Code%20embedded%20documentation)

## 5. Update Docker Image
```bash
# Navigate to the project that contain your Dockerfile
cd cpp-lab

# Build the project by running the following command, swapping out DOCKER_USERNAME with your username.
docker build -t DOCKER_USERNAME/cpp-lab .

# Verify the image exists locally
docker image ls

# To push the image
docker push DOCKER_USERNAME/cpp-lab
```

## 6. TroubleShooting
1. `push access denied, repository does not exist or may require authorization: server message: insufficient_scope: authorization failed`
=> docker login / Docker Desktop login

## 7. Evaluate Executable
- List all sections:
```bash
$ size ./build/cpp-lab
```
- The expected output should be the following:
```bash
   text    data     bss     dec     hex filename
  14791     792     280   15863    ./build/cpp-lab
```

- `.text`: Text Segment - the executable code size, including: complied function, inline, template, constants, string literals
- `.data`: Initialized Data Segment - the memory for the global, static variables, has init value.
- `.bss`: Uninitialized Data Segment - global and static variables that are not initialized