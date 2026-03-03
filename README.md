## 1. Overview
**Project Structure**
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
        ```
        $ sudo apt-get update
        $ sudo apt-get install g++
        $ sudo apt-get install lcov
        $ sudo apt-get install cmake
        $ sudo apt-get install git
        $ sudo apt-get install cppcheck
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
    * Detect Memory Leak Using [valgrind](https://valgrind.org/)
        ```
        $ sudo apt install valgrind
        $ valgrind --leak-check=full -v ./cpp-lab 
        ```
    * (Optional) Run static analysis - cppcheck
        ```
        $ sudo apt-get install cppcheck
        $ cppcheck "folder" / "file"
        ```
    * (Optional) Run static analysis - clang-tidy
        ```
        $ sudo apt-get install -y clang-tidy
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

## 6. TROUBLESHOOTING
1. `push access denied, repository does not exist or may require authorization: server message: insufficient_scope: authorization failed`
=> docker login / Docker Desktop login
