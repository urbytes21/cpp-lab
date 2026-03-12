## 1. Overview
**TL;DR**
```bash
./scripts/run.sh
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
        $ ./bin/cpp_lab_project
        $ ./bin/cpp_lab_project_test
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
    * (Optional) Run coverage - lcov
        ```bash
        $ ./scripts/gen_coverage_lcov.sh
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

### 3.2 Config C/C++ Debugging (VS Code)

#### 3.2.1. Launch Configuration

To debug C/C++ projects in VS Code, you must create a *launch configuration* that specifies:

- The application entry point (executable)
- How to attach to a running process
- Environment variables needed
- Saved debugging setup details

All launch configs are stored in `.vscode/launch.json` within your workspace.
##### a. Create `launch.json`
- Go to `Run` → `Add Configuration...` or
- Use VS Code chat command:
    ```
    /startDebugging
    ```
    to auto-generate a debug configuration.

##### b. Start Debugging

You can start a debug session in several ways:
- **F5**
- **Ctrl + Shift + D**: Open Debug panel, select a config, press Start
- **Ctrl + Shift + P** → select `Debug: Select and Start Debugging`

#### 3.2.2. Debug Configuration Example

The most important field is the executable that will run:

```json
// .vscode/launch.json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/debug/bin/cpp_lab_project",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "preLaunchTask": "CMake Debug Build",
            "setupCommands": [
                {
                    "description": "Enable pretty printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set disassembly flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

#### 3.2.3. Build Tasks (CMake)

An example `tasks.json` for CMake builds:

```json
// .vscode/tasks.json
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
#### 3.2.4. Run Steps

1. **Open** your project in VS Code
2. **Install Extension:**  
   - *C/C++ Extension Pack*
3. **Install GDB:**
   ```bash
   sudo apt update
   sudo apt install gdb
   ```
4. **Start Debugging:**  
   Press `F5`
5. **Run Without Debugging:**  
   Press `Ctrl + F5`
6. **Build Project (Optional):**  
   Press `Ctrl + Shift + B`

Notes:
| Shortcut        | Action                 |
|-----------------|-----------------------|
| F5              | Start debugging        |
| Ctrl + F5       | Run without debugging  |
| Ctrl + Shift + D| Open Debug panel       |
| Ctrl + Shift + B| Build project          |

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