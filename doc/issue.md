# issue

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
