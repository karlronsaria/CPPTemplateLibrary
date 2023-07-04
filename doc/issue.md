# issue

- [x] 2023_07_03_220628
  - system
    - Visual Studio
  - c++
    ```cpp
    file.open("./res/int_matrix_001.txt");
    ```
  - actual
    - Binding ``file`` returns false; nothing read from file.
  - howto
    1. goto
      1. Project Properties
      2. General
    2. save or change **Output Directory**
    3. c++
      - header
        ```cpp
        // ...
        #include <windows.h>
        #include <string>
        #include <iostream>

        std::wstring ExePath() {
            TCHAR buffer[MAX_PATH] = { 0 };
            GetModuleFileName(NULL, buffer, MAX_PATH);
            std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
            return std::wstring(buffer).substr(0, pos);
        }
        ```
      - source
        ```cpp
        // ...
        std::fstream file;
        file.open(ExePath() + std::wstring(L"../../../../test/res/int_matrix_001.txt");
        ```

- [x] 2023_06_22_233725
  - system
    - Visual Studio
  - when
    - build Google Test project without ``pch.h`` (a precompiled header)
  - actual
    ```
    unexpected end of file while looking for precompiled header. Did you forget to add '#include "pch.h"' to your source?
    ```
  - howto
    1. goto
      1. Project Properties
      2. C/C++
      3. Precompiled Headers
      4. Precompiled Header File
    2. set **Not Using Precompiled Headers**
  - link
    - url: https://stackoverflow.com/questions/8862840/unexpected-end-of-file-error
    - retrieved: 2023_06_22

- [x] 2023_06_22_003300
  - system
    - using Visual Studio
  - when
    ```cpp
    #include <gtest/gtest.h>
    ```
  - actual
    ```
    warning C4996: 'std::tr1': warning STL4002: The non-Standard std::tr1 namespace and TR1-only machinery are deprecated and will be REMOVED. You can define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING to acknowledge that you have received this warning.
    ```
  - howto
    1. goto
      1. Project Properties
      2. C/C++
      3. Preprocessor
      4. Preprocessor Definitions
    2. add ``_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING``
  - link
    - url: https://stackoverflow.com/questions/48091421/vs-2017-command-line-error-d8004
    - retrieved: 2023_06_22
