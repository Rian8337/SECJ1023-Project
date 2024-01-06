# About

Small inventory management system with C++11

# Running

This program requires C++11 to run. It comes with build tasks for Windows, macOS, and Unix-based operating systems in [Visual Studio Code](https://code.visualstudio.com/).

To compile the program, simply use the suitable build task or run the following command in the root directory:

-   Windows

    ```ps
    g++ -fdiagnostics-color=always -std=c++11 -g $((Get-ChildItem -Filter "*.cpp" -Path "./src" -Recurse).FullName)
    ```

-   macOS or Unix-based operating systems

    ```sh
    g++ -fdiagnostics-color=always -std=c++11 -g $(find ./src -type f -iregex ".*\\.cpp")
    ```
